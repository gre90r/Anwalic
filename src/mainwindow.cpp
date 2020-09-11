/**
 * Developer information:
 *      "service"
 *          is the class which holds the business logic.
 *          it's called everytime when sorting, filtering, basically some data processing has to be done
 *              usage: service.findAnimeByName(anime);
 *                  But you define a method here which calls findAnime. So you do:
 *                  MainWindow::findAnimeByName(Anime* anime) { service.findAnimeByName(anime); }
 *      do not call AnimelistManager directly. use "service" class. it will pass it to AnimelistManager
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "animelist.h"
#include <list>
#include <stdexcept>
#include <QStringListModel>
#include <QMessageBox>
#include <globals.h>
#include <QFont>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include "errorview.h"
#include "memory.h"
#include "stringsEN.h"
#include <QDesktopServices>
#include <QPixmap>
#include <QPalette>
#include <QLineEdit>
#include <QFileDialog>
#include <QCloseEvent>
#include <QTime>
#include <QInputDialog>
#include "FilterShowMovies.h"
#include "FilterShowOpenEndedAnimes.h"
#include "FilterHideMovies.h"
#include "FilterHideOpenEndedAnimes.h"
#include "FilterHideAnimesWithNameOnly.h"
#include "FilterByTag.h"
#include "FilterShowStartedAnimes.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_isFatalError( false ),
    ui(new Ui::MainWindow),
    uiAddNewAnime( nullptr ),
    uiEditAnime( nullptr ),
    uiAbout( nullptr ),
    uiPreferences( nullptr ),
    service(
        DEFAULT_ANIME_LIST_PATH,
        DEFAULT_ANIME_LIST_COMPLETED_PATH,
        Preferences() // standard settings for MainWindow: FontSize 14, window size 800x700, default pic
    ),
    m_lastUsedListItemIndex( QModelIndex() ),
    m_initFailed( false ),
    m_animeListViewHelper( new AnimeListViewHelper() )
{
    // setup GUI
    ui->setupUi(this);
    setWindowTitle( std::string( std::string( PROGRAM_NAME ) + " " + std::string( PROGRAM_VERSION ) ).c_str() );
#ifdef _DEBUG
    addRevisionNumberToWindowTitle(); // add more detailed version number for debug session
#endif
    setWindowFlags( windowFlags() | Qt::CustomizeWindowHint | Qt::WindowMaximizeButtonHint );
    applyPreferences(); // mainwindow size, listview font size, background image

    try
    {
        refreshAnimeList();
    }
    catch ( const std::invalid_argument& e )
    {
        std::cerr << "Mainwindow::MainWindow: " << e.what() << std::endl;
        ErrorView::showErrorPopup( this, STR_YOUR_SAVE_FILE_IS_CORRUPTED );
        m_isFatalError = true;
        m_initFailed = true;
    }
}


MainWindow::~MainWindow()
{
    Memory::safeDelete( uiPreferences );
    Memory::safeDelete( uiAbout );
    Memory::safeDelete( uiAddNewAnime );
    Memory::safeDelete( uiEditAnime );
    Memory::safeDelete( m_animeListViewHelper );
    delete ui;
}


void MainWindow::on_btnQuit_clicked() const
{
    service.save(m_isFatalError);
    this->setCurrentWindowSizeToPreferences();
    service.writeConfigFile();
    QApplication::quit();
}


void MainWindow::closeEvent( QCloseEvent* closeEvent )
{
    closeEvent->accept(); // accept to handle close event. otherwise it could be dragged to parent
    on_btnQuit_clicked(); // call the program's standard quit method
}


void MainWindow::on_btnAddNewAnime_clicked()
{
    uiAddNewAnime = new AddNewAnime( this );
    uiAddNewAnime->setModal( true ); // no access on parent window possible
    uiAddNewAnime->show();
    connect( uiAddNewAnime, SIGNAL( sendData( Anime* ) ), this, SLOT( receiveData( Anime* ) ) );
}


void MainWindow::receiveData( Anime* ptrAnime )
{
    Memory::safeDelete( uiAddNewAnime );
    if ( ptrAnime == nullptr ) return; // Cancel button has been clicked

    if ( service.getMyAnimelist()->isInList( *ptrAnime ) || service.getCompletedAnimelist()->isInList( *ptrAnime )  )
    {
        ErrorView::showPopup( STR_ANIME_ALREADY_IN_LIST );
        return;
    }
    service.getMyAnimelist()->addAnime( ptrAnime );
    refreshAnimeList();
    service.save(m_isFatalError);
}


void MainWindow::refreshAnimeList()
{
    displayNumberOfAnimesInList();
    setAnimeListOnListview( service.listSelected() ); // sorts list & sets model from current selected list
    if ( currentSelectedList()->isEmpty() )
    {
        ui->lvAnimes->setCurrentIndex( QModelIndex() ); // make invalid QModelIndex
        return;
    }
    selectListViewItem( m_lastUsedListItemIndex ); // select last used list item
}


void MainWindow::on_lvAnimes_doubleClicked(const QModelIndex &index)
{
    ui->lvAnimes->setCurrentIndex( index );

    // do not allow editing completed list
    if ( service.listSelected() == COMPLETED_ANIMELIST ) {
        return;
    }

    // do not allow editing filtered completed list
    if (   service.listSelected() == FILTERED_ANIMELIST
        && service.getListSelectedBeforeFiltering() == COMPLETED_ANIMELIST )
    {
        return;
    }

    on_btnEdit_clicked(); // opens edit Anime window
}


void MainWindow::on_btnIncEpisode_clicked()
{
    // fetch anime name in any case
    std::string animeName = this->getAnimeNameFromSelectedListItemAndValidate();
    if ( animeName == "" ) return; // error message already shown
    Anime* selectedAnime = service.findAnimeByName( animeName, m_isFatalError, this->currentSelectedList() );
    if ( selectedAnime == nullptr ) return; // error message already shown

    // when list is filtered
    if ( service.listSelected() == FILTERED_ANIMELIST )
    {
        if ( service.getListSelectedBeforeFiltering() == MY_ANIMELIST )
        {
            /********************************/
            /* state: FILTERED MY ANIMELIST */
            /********************************/

            // FALLTHROUGH TO MY ANIMELIST.
            // Filtered My Animelist shall behave like unfiltered My Animelist
        }
        else if ( service.getListSelectedBeforeFiltering() == COMPLETED_ANIMELIST )
        {
            /***************************************/
            /* state: FILTERED COMPLETED ANIMELIST */
            /***************************************/
            // same behavior as in Completed Animelist
            service.moveAnimeToMyAnimeList( selectedAnime );
            refreshAnimeList();
            service.save( m_isFatalError );
            return;
        }
        else
        {
            ErrorView::internalErrorHandler( "internal error @MainWindow::on_btnIncEpisode_clicked(). invalid program state in filtered animelist." );
            return;
        }
    }

    // Button Episode +1 turned into "Move to My Anime List" and has been clicked in My Anime List select state
    if ( service.listSelected() == COMPLETED_ANIMELIST )
    {
        /******************************/
        /* state: COMPLETED_ANIMELIST */
        /******************************/
        service.moveAnimeToMyAnimeList( selectedAnime );
        refreshAnimeList();
        service.save( m_isFatalError );
        return;
    }

    /*********************************************/
    /* state: MY_ANIMELIST || FILTERED_ANIMELIST */
    /*********************************************/

    // Button Episode +1 turned into  "Move to Completed Animes" and has been clicked in My Anime List select state
    // m_listSelected == NOW_WATCHING_ANIMES (My Anime List)
    if ( selectedAnime->getCurrentEpisode() >= selectedAnime->getTotalEpisodes() ) // when anime is at max episode move to completed animes
    {    
        /*************************************/
        /* Button = Move to Completed Animes */
        /*************************************/

        // do not move when (4096 / ??). limits increasing episode to 4096 or whatever MAX_NUMBER_EPISODES is
        if ( selectedAnime->getCurrentEpisode() == MAX_NUMBER_EPISODES ) {   
            return;
        }

        // user dialog: do you want to move
        int ret = QMessageBox::question( this, PROGRAM_NAME, STR_DO_YOU_WANT_TO_MOVE_THIS_ANIME_TO_COMPLETED_ANIME_LIST,
            QMessageBox::Yes, QMessageBox::No );
        if ( ret == QMessageBox::No ) {
            return;
        }

        service.moveAnimeToCompletedAnimelist( selectedAnime );

        ui->btnIncEpisode->setText( STR_EPISODE_PLUS_1 );
        setInvalidListItemIndex(); // make model index invalid because after moving no item is selected
        refreshAnimeList();
        service.save( m_isFatalError );
        return;
    }

    // anime not completed yet, so increase episode
    selectedAnime->incEpisode();

    // "Episode +1" has been clicked in my anime list
    // just came to max number
    if ( selectedAnime->getCurrentEpisode() >= selectedAnime->getTotalEpisodes() )
    {
        if ( !(selectedAnime->getCurrentEpisode() == MAX_NUMBER_EPISODES) )
        {
            ui->btnIncEpisode->setText( STR_MOVE_TO_COMPLETED_ANIMES );
        }
    }

    refreshAnimeList();
    service.save( m_isFatalError );
}


void MainWindow::on_btnDecEpisode_clicked()
{
    std::string animeName = this->getAnimeNameFromSelectedListItemAndValidate();
    if ( animeName == "" ) return; // do not show error message here. if it's fatal it is already shown
    Anime* anime = service.findAnimeByName( animeName, m_isFatalError, this->currentSelectedList() );
    if ( anime == nullptr ) return; // error message already shown

    if ( anime->getCurrentEpisode() <= anime->getTotalEpisodes() ) {
        ui->btnIncEpisode->setText( STR_EPISODE_PLUS_1 );
    }

    anime->decEpisode();
    refreshAnimeList();
    service.save( m_isFatalError );
    
}


std::string MainWindow::getAnimeNameFromSelectedListItemAndValidate()
{
    // get string from list item e.g. "Clannad (Episode 1 of 26)"
    std::string listEntry = ui->lvAnimes->currentIndex().data().toString().toStdString(); // list item to string

    return service.getAnimeNameFromSelectedListItemAndValidate(listEntry, m_isFatalError); // caution: m_isFatalError may be altered
}


void MainWindow::selectListViewItem( QModelIndex listItemIndex ) const
{
    ui->lvAnimes->setCurrentIndex( listItemIndex );
}


void MainWindow::on_btnDelete_clicked()
{
    std::string animeName = this->getAnimeNameFromSelectedListItemAndValidate();
    if ( animeName == "" ) return; // do not show error here. if it's fatal it has already been shown

    int ret = QMessageBox::question( this, PROGRAM_NAME,
                std::string( std::string( STR_DO_YOU_REALLY_WANT_TO_DELETE ) + " \"" + animeName + "\" "
                             + STR_FROM_THE_LIST_FOREVER ).c_str(),
                             QMessageBox::Yes,
                             QMessageBox::No
              );
    if ( ret == QMessageBox::No ) return;
    if ( !currentSelectedList()->deleteAnimeByName( animeName ) )
    {
        // anime not found
        m_isFatalError = true;
        ErrorView::internalErrorHandler( "MainWindow::on_btnDelete_clicked: failed to delete anime" );  
    }
    refreshAnimeList();
    service.save( m_isFatalError );
}


void MainWindow::receiveDataChanged()
{
    Memory::safeDelete( uiEditAnime );
    refreshAnimeList();
    updateTextBtnIncEpisode();
    service.save( m_isFatalError );
}


void MainWindow::on_btnEdit_clicked()
{
    uiEditAnime = new EditAnimeWindow( this );
    uiEditAnime->setModal( true ); // no access on parent window possible

    // uiMain -> uiEdit
    connect( this, SIGNAL( sendData( Anime*, AnwalicService* ) ), uiEditAnime, SLOT( receiveData( Anime*, AnwalicService* ) ) );
    // uiEdit -> uiMain
    connect( uiEditAnime, SIGNAL( sendDataChanged() ), this, SLOT( receiveDataChanged() ) );

    std::string animeName = this->getAnimeNameFromSelectedListItemAndValidate();
    if ( animeName == "" )
    {
        // no list item selected
        Memory::safeDelete( uiEditAnime );
        return;
    }
    Anime* anime = currentSelectedList()->getAnimeByName( animeName );
    if ( anime == nullptr )
    {
        // anime not found in list
        Memory::safeDelete( uiEditAnime );
        return; // error Msg already shown
    }

    emit sendData( anime, &service );
    uiEditAnime->show();
}


void MainWindow::on_btnGoToStream_clicked()
{
    std::string animeName = this->getAnimeNameFromSelectedListItemAndValidate();
    if ( animeName == "" ) return; // error already shown
    Anime* anime = currentSelectedList()->getAnimeByName( animeName );
    if ( anime == nullptr ) return; // error already shown
    
    std::string url = anime->getUrl();
    if ( url.empty() )
    {
        ErrorView::showPopup( STR_YOU_DID_NOT_SPECIFY_A_URL );
        return;
    }

    AnwalicService::openURL( url.c_str() );
}


bool MainWindow::failed() const
{
    return m_initFailed;
}


void MainWindow::receiveGuiAboutFinished()
{
    Memory::safeDelete( uiAbout );
}


void MainWindow::on_actionAbout_triggered()
{
    uiAbout = new AboutWindow( this );
    uiAbout->setModal( true );
    uiAbout->show();
    connect( uiAbout, SIGNAL( sendGuiFinished() ), this, SLOT( receiveGuiAboutFinished() ) );
}


void MainWindow::on_actionCompleted_Animes_triggered()
{
    service.setListSelected( COMPLETED_ANIMELIST );

    ui->btnAddNewAnime->setEnabled( false );
    ui->btnIncEpisode->setEnabled( true );
    updateTextBtnIncEpisode();
    ui->btnDecEpisode->setEnabled( false );
    ui->btnEdit->setEnabled( false );
    ui->btnDelete->setEnabled( false );
    ui->btnShowStartedAnimesOnly->setEnabled( false );
    if ( service.isActiveListMyList() ) {
        ui->labListName->setText( STR_COMPLETED_ANIMES );
    }
    else {
        ui->labListName->setText( service.getSavefileNameCompletedAnimelist().c_str() );
    }
    ui->actionShow_Open_Ended_Animes->setEnabled( false );
    ui->actionHide_Open_Ended_Animes->setEnabled( false );
    ui->actionHide_Animes_with_Name_Only->setEnabled( false );

    refreshAnimeList();
}


void MainWindow::setAnimeListOnListview( ListType listType )
{
    switch ( listType ) {
        case MY_ANIMELIST:
            service.getMyAnimelist()->sort();
            m_animeListViewHelper->setStringListModelFromAnimelist( *service.getMyAnimelist() );
            break;
        case COMPLETED_ANIMELIST:
            service.getCompletedAnimelist()->sort();
            m_animeListViewHelper->setStringListModelFromAnimelist( *service.getCompletedAnimelist() );
            break;
        case FILTERED_ANIMELIST:
            service.getFilteredAnimelist()->sort();
            m_animeListViewHelper->setStringListModelFromAnimelist( *service.getFilteredAnimelist() );
            break;
        default:
            m_isFatalError = true;
            throw std::invalid_argument( "internal error: @MainWindow::setAnimeListOnListview(). "
                                         "unknown list type!" );
    }
    QStringListModel* stringListModel = m_animeListViewHelper->getAnimelistStringListModel();
    ui->lvAnimes->setModel( stringListModel );
}


Animelist* MainWindow::currentSelectedList() const
{
    if ( service.listSelected() == MY_ANIMELIST ) {
        return service.getMyAnimelist();
    }
    if ( service.listSelected() == COMPLETED_ANIMELIST ) {
        return service.getCompletedAnimelist();
    }
    if ( service.listSelected() == FILTERED_ANIMELIST ) {
        return service.getFilteredAnimelist();
    }

    throw std::runtime_error( "internal error: @MainWindow::currentSelectedList(). invalid list selection value!" );
}


void MainWindow::on_lvAnimes_clicked(const QModelIndex &index)
{
    ui->lvAnimes->setCurrentIndex( index );
    setLastUsedListItemIndex();
    updateTextBtnIncEpisode(); // sets "Episode +1" or "Move to Completed Animes" on Button
}


void MainWindow::moveAnimeToCompletedList( Anime* anime )
{
    // decision button. do you want to move.
    int buttonClicked = QMessageBox::question(
        this, PROGRAM_NAME, STR_DO_YOU_WANT_TO_MOVE_THIS_ANIME_TO_COMPLETED_ANIME_LIST,
        QMessageBox::Yes, QMessageBox::No
    );
    if ( buttonClicked == QMessageBox::No ) {
        return;
    }

    service.moveAnimeToCompletedAnimelist( anime );
    ui->btnIncEpisode->setText( STR_EPISODE_PLUS_1 );
    setInvalidListItemIndex(); // make model index invalid because after moving no item is selected
}


void MainWindow::moveAnimeToNowWatchingAnimeList( Anime* anime )
{
    service.moveAnimeToMyAnimeList( anime );
    setInvalidListItemIndex(); // make model index invalid because after moving no item is selected
}


void MainWindow::updateTextBtnIncEpisode()
{
    /*****************************/
    /* state: FILTERED ANIMELIST */
    /*****************************/
    // when list is filtered
    if ( service.listSelected() == FILTERED_ANIMELIST )
    {
        if ( service.getListSelectedBeforeFiltering() == MY_ANIMELIST )
        {
            /********************************/
            /* state: FILTERED MY ANIMELIST */
            /********************************/

            // FALLTHROUGH TO STATE MY ANIMELIST.
            // filtered my animelist shall behave like unfiltered my animelist
        }
        else if ( service.getListSelectedBeforeFiltering() == COMPLETED_ANIMELIST )
        {
            /***************************************/
            /* state: FILTERED COMPLETED ANIMELIST */
            /***************************************/

            ui->btnIncEpisode->setText( STR_MOVE_TO_MY_ANIMELIST );
            return;
        }
        else
        {
            ErrorView::internalErrorHandler( "internal error @MainWindow::updateTextBtnIncEpisode(): invalid program state in Filtered Animelist." );
            return;
        }
    }

    /******************************/
    /* state: COMPLETED ANIMELIST */
    /******************************/

    // when arriving at Completed Anime List change text to "Move to My Anime List"
    if ( service.listSelected() == COMPLETED_ANIMELIST )
    {
        ui->btnIncEpisode->setText( STR_MOVE_TO_MY_ANIMELIST );
        return;
    }

    /***********************/
    /* state: MY ANIMELIST */
    /***********************/

    // get current selected anime
    std::string animeName = this->getAnimeNameFromSelectedListItemAndValidate();
    if ( animeName == "" ) {
        return;
    }
    Anime* selectedAnime = currentSelectedList()->getAnimeByName( animeName );
    if ( selectedAnime == nullptr ) {
        return;
    }

    // check if "Move to Completed Animes" must be displayed
    if ( selectedAnime->getCurrentEpisode() < selectedAnime->getTotalEpisodes() )
    {
        // current episode is not last episode. display "Episode +1"
        ui->btnIncEpisode->setText( STR_EPISODE_PLUS_1 );
    }
    else
    {
        if ( selectedAnime->getCurrentEpisode() == MAX_NUMBER_EPISODES )
        {
            // still show Episode + 1 in case of (4096 / ??)
            ui->btnIncEpisode->setText( STR_EPISODE_PLUS_1 );
            return;
        }
        // current episode is last episode. display "Move to Completed Animes"
        ui->btnIncEpisode->setText( STR_MOVE_TO_COMPLETED_ANIMES );
    }
}


void MainWindow::uiSetBackground( const char* imageFilePath )
{
    QPixmap pixmap( imageFilePath );
    if ( pixmap.isNull() ) {
        std::cerr << std::string( "runtime error: @MainWindow::uiSetBackground(). "
                                  "Could not load pixmap from " ) +
                                  std::string( "\"" + std::string( imageFilePath )+ "\"\n" );
        ErrorView::showPopup( STR_YOUR_IMAGE_FILE_IS_UNREADABLE ); // no fatal error
        return;
    }
    pixmap.scaled( this->size(), Qt::IgnoreAspectRatio );

    QPalette paletteBackground;
    paletteBackground.setBrush( QPalette::Background, pixmap );
    this->setPalette( paletteBackground ); // set new background image
}


void MainWindow::setInvalidListItemIndex()
{
    ui->lvAnimes->setCurrentIndex( QModelIndex() );
    m_lastUsedListItemIndex = QModelIndex();
}


void MainWindow::on_actionPreferences_triggered()
{
    uiPreferences = new PreferencesWindow( this );
    uiPreferences->setModal( true );
    uiPreferences->show();
    connect( this, SIGNAL( sendPreferences( Preferences* ) ), uiPreferences, SLOT( receivePreferences( Preferences* )));
    connect( uiPreferences, SIGNAL( sendPreferences( Preferences* ) ), this, SLOT( receivePreferences( Preferences* )));
    emit sendPreferences( service.getPreferences() );
}


void MainWindow::receivePreferences( Preferences* preferences )
{
    Memory::safeDelete( uiPreferences );
    if ( preferences == nullptr ) {
        return;
    }
    service.getPreferences()->setBackgroundImagePath( preferences->getBackgroundImagePath() );
    service.getPreferences()->setFontSize( preferences->getFontSize() );
    service.getPreferences()->setListCaptionColor( preferences->getListCaptionColor() );
    service.getPreferences()->setWindowSize( QSize( this->width(), this->height() ) );
    service.getPreferences()->writeConfigFile();
    this->applyPreferences();
}


void MainWindow::applyPreferences()
{
    ui->lvAnimes->setFont( QFont( "Sans Serif", service.getPreferences()->getFontSize(), -1, false ) );
    ui->labListName->setStyleSheet(
        QString( QString ( "QLabel { color : " ) +
        QString( service.getPreferences()->getListCaptionColor().c_str() ) +
        QString( "; }" ) )
    );
    this->uiSetBackground( service.getPreferences()->getBackgroundImagePath().c_str() );
    this->resize( service.getPreferences()->getWindowSize() );
}


void MainWindow::setCurrentWindowSizeToPreferences() const
{
    service.getPreferences()->setWindowSize( QSize( this->width(), this->height() ) );
}


void MainWindow::on_actionExport_My_List_triggered()
{
    QString exportPathAndName = QFileDialog::getSaveFileName(
        this, "Export Anime List. Please choose a location and name.",
        ".", "Anwalic List File ( *.anl )"
    );
    if ( exportPathAndName == "" ) { // Cancel has been clicked
        return; 
    }
    exportPathAndName += ".anl";
    service.exportAnimelist( exportPathAndName );
}


void MainWindow::on_actionSelect_My_List_triggered()
{
    if ( service.isActiveListMyList() ) {
        on_actionMy_Anime_List_triggered();
        return;
    }

    // prepare to display My List. Currently there is an imported list displayed
    // set/reset all relevant MainWindow attributes
    service.selectMyList();

    m_lastUsedListItemIndex = QModelIndex();
    on_actionMy_Anime_List_triggered();
}


void MainWindow::on_btnToggleAnimeLists_clicked()
{
    m_lastUsedListItemIndex = QModelIndex(); // set invalid index to select nothing

    if ( service.listSelected() == MY_ANIMELIST ) {
        on_actionCompleted_Animes_triggered(); // display Completed Anime List
    }
    else {
        on_actionMy_Anime_List_triggered(); // display My Anime List
    }

    this->updateTextBtnIncEpisode(); // changes Button to "Episode +1" or "Move to My Anime List" 
}


void MainWindow::enableUiElementsForGeneralFilteredState() const
{
    ui->btnAddNewAnime->setEnabled( true );
    ui->btnToggleAnimeLists->setEnabled( true );
    ui->btnDelete->setEnabled( true );
    ui->actionImport_Another_List->setEnabled( true );
    ui->actionSelect_My_List->setEnabled( true );
    ui->actionExport_My_List->setEnabled( true );
    //ui->btnShowStartedAnimesOnly->setEnabled( true );
    ui->btnShowStartedAnimesOnly->setText( STR_SHOW_STARTED_ANIMES_ONLY );
}


void MainWindow::enableUiFilterElements() const
{
    ui->actionShow_Movies_Only->setEnabled( true );
    ui->actionHide_Movies->setEnabled( true );
    ui->actionShow_Open_Ended_Animes->setEnabled( true );
    ui->actionHide_Open_Ended_Animes->setEnabled( true );
    ui->actionFilter_By_Tag->setEnabled( true );
    ui->actionHide_Animes_with_Name_Only->setEnabled( true );
}

void MainWindow::on_btnShowStartedAnimesOnly_clicked()
{
    setLastUsedListItemIndex();

    if ( service.listSelected() == FILTERED_ANIMELIST ) // current state: filtered
    {
        /***************************************/
        /* Button is displaying "Clear Filter" */
        /***************************************/
        // every filter is being cleared here

        // enable Ui elements which have been disabled by disableUiElementsForGeneralFilteredState()
        // such as Toggle-button, delete-button, export list...
        enableUiElementsForGeneralFilteredState();

        // enables filter functionalites such as Show Movies Only...
        enableUiFilterElements();

        // prepare to show unfiltered My Anime List again
        service.clearFilteredAnimeList();

        jumpBackToPreviousNotFilteredUiState();

        refreshAnimeList();
    }
    else // current state: not filtered
    {
        /***************************************************/
        /* Button is displaying "Show Started Animes Only" */
        /***************************************************/
        
        //TODO: remove old code
        //// disable Ui elements which are not allowed to click in filtered state
        //disableUiElementsForGeneralFilteredState();

        //// disable all filter functionalities in Ui
        //disableUiFilterElements();

        //// check worst case: completed animes is selected. button should be disabled when function is called
        //if ( service.listSelected() == COMPLETED_ANIMELIST ) { // not allowed when completed animes is selected
        //    m_isFatalError = true;
        //    ErrorView::internalErrorHandler( "internal error @MainWindow::on_btnShowStartedAnimesOnly_clicked. it should be impossible to click \"Show Started Animes Only\" button while in Completed Animes state" );
        //    return;
        //}

        //// display only animes with Episode > 1
        //service.filterByStartedAnimesOnly();

        //// display filtered list 
        //refreshAnimeList();

        FilterShowStartedAnimes filterShowStartedAnimes(this, service.getAnimelistManager(), &service);
        filterShowStartedAnimes.applyFilter();
    }
}


void MainWindow::on_actionMake_Backup_triggered() const
{
    service.createBackup();
}


void MainWindow::setLastUsedListItemIndex()
{
    QModelIndex currentIndex = ui->lvAnimes->currentIndex( ); // get list item
    if ( !currentIndex.isValid() )
    {
        currentIndex = QModelIndex(); // set index that selects nothing
    }
    m_lastUsedListItemIndex = currentIndex;
}


void MainWindow::displayNumberOfAnimesInList()
{
    if ( service.listSelected() == MY_ANIMELIST )
    {
        if ( service.isActiveListMyList() )
        {
            /********************************/
            /* not imported & My Anime List */
            /********************************/
            ui->labListName->setText( QString( STR_MY_ANIME_LIST )
                + " (" + QString( std::to_string( service.countAnimesInMyAnimeList() ).c_str() ) + " Animes)" );
        }
        else
        {
            /*********************************/
            /* imported list & My Anime List */
            /*********************************/
            ui->labListName->setText( service.getImportedPathMyAnimelist()
                + " (" + QString( std::to_string( service.countAnimesInMyAnimeList() ).c_str() ) + " Animes)" );
        }
    }
    else if ( service.listSelected() == COMPLETED_ANIMELIST )
    {
        if ( service.isActiveListMyList() )
        {
            /***************************************/
            /* not imported & Completed Anime List */
            /***************************************/
            ui->labListName->setText( QString( STR_COMPLETED_ANIMES )
                + " (" + QString( std::to_string( service.countAnimesInCompletedAnimeList() ).c_str() ) + " Animes)" );
        }
        else
        {
            /****************************************/
            /* imported list & Completed Anime List */
            /****************************************/
            ui->labListName->setText( service.getImportedPathCompletedAnimelist()
                + " (" + QString( std::to_string( service.countAnimesInCompletedAnimeList() ).c_str() ) + " Animes)" );
        }
    }
    else if ( service.listSelected() == FILTERED_ANIMELIST )
    {
        ui->labListName->setText( QString( std::to_string( service.countAnimesInFilteredAnimeList() ).c_str() )
            + " Filtered Animes" );
    }
    else
    {
        m_isFatalError = true;
        ErrorView::internalErrorHandler( "internal error @MainWindow::displayNumberOfAnimesInList: unknown list selected" );
    }
}


void MainWindow::on_actionCrunchyroll_com_triggered()
{
    AnwalicService::openURL( STR_URL_CRUNCHYROLL_COM );
}

void MainWindow::on_actionWakanim_tv_triggered()
{
    AnwalicService::openURL( STR_URL_WAKANIM_TV );
}

void MainWindow::on_actionMy_Anime_List_triggered()
{
    service.setListSelected( MY_ANIMELIST );

    ui->btnAddNewAnime->setEnabled( true );
    ui->btnIncEpisode->setEnabled( true );
    ui->btnIncEpisode->setText( STR_EPISODE_PLUS_1 );
    ui->btnDecEpisode->setEnabled( true );
    ui->btnEdit->setEnabled( true );
    ui->btnDelete->setEnabled( true );
    ui->btnShowStartedAnimesOnly->setEnabled( true );
    if ( service.isActiveListMyList() ) {
        ui->labListName->setText( STR_MY_ANIME_LIST );
    }
    else {
        ui->labListName->setText( service.getSavefileNameMyAnimelist().c_str() );
    }
    ui->actionShow_Open_Ended_Animes->setEnabled( true );
    ui->actionHide_Open_Ended_Animes->setEnabled( true );
    ui->actionHide_Animes_with_Name_Only->setEnabled( true );

    refreshAnimeList();
}

void MainWindow::on_actionImport_Another_List_triggered()
{
    // user dialog: open file. user selects/imports another animelist
    QString importedListPath = QFileDialog::getOpenFileName(
        this, "Import another Animelist. Please select a .anl file without the \"_completed\" suffix",
        ".", "Anwalic List File ( *.anl )" );
    if ( importedListPath == "" ) {
        return; // Cancel has been clicked
    }

    service.selectAnotherList( importedListPath );

    m_lastUsedListItemIndex = QModelIndex(); // set invalid index to select nothing
    on_actionMy_Anime_List_triggered();
}

void MainWindow::jumpBackToPreviousNotFilteredUiState()
{
    if ( service.getListSelectedBeforeFiltering() == MY_ANIMELIST )
    {
        on_actionMy_Anime_List_triggered();
    }
    else if ( service.getListSelectedBeforeFiltering() == COMPLETED_ANIMELIST )
    {
        on_actionCompleted_Animes_triggered();
    }
    else
    {
        ErrorView::internalErrorHandler( "internal error @MainWindow::jumpBackToPreviousNotFilteredUiState(). Cannot restore Ui state from current Filtered List." );
    }
}

void MainWindow::disableUiElementsForGeneralFilteredState() const
{
    // disable
    ui->btnAddNewAnime->setEnabled( false );
    ui->btnToggleAnimeLists->setEnabled( false );
    ui->btnDelete->setEnabled( false );
    ui->actionImport_Another_List->setEnabled( false );
    ui->actionSelect_My_List->setEnabled( false );
    ui->actionExport_My_List->setEnabled( false );

    // but enable Clear Filter button in any case
    ui->btnShowStartedAnimesOnly->setEnabled( true );
    ui->btnShowStartedAnimesOnly->setText( STR_CLEAR_FILTER );
}

void MainWindow::disableUiFilterElements() const
{
    ui->actionShow_Movies_Only->setEnabled( false );
    ui->actionHide_Movies->setEnabled( false );
    ui->actionShow_Open_Ended_Animes->setEnabled( false );
    ui->actionHide_Open_Ended_Animes->setEnabled( false );
    ui->actionFilter_By_Tag->setEnabled( false );
    ui->actionHide_Animes_with_Name_Only->setEnabled( false );
}

void MainWindow::prepareFilteredState()
{
    setLastUsedListItemIndex();

    // disable Ui elements which are not allowed to click in filtered state
    disableUiElementsForGeneralFilteredState();

    // disable all filter functionalities in Ui
    disableUiFilterElements();
}

void MainWindow::on_actionShow_Movies_Only_triggered()
{
    //TODO: remove old code
    //prepareFilteredState(); // disables UI elements

    //// display only animes with totalEpisodes = 1
    //service.showMoviesOnly();

    //// display filtered list 
    //refreshAnimeList();

    //TODO: bad code. AnimelistManager is passed as NOT CONST. make class AnimelistManager a friend class
    //^- but would probably not operate on the same AnimeListManager as in AnwalicService if making friend class.
    //^- it's correct as it is right now. there is ONLY ONE AnimeListManager and its reference must be passed.
    FilterShowMovies filterShowMovies(this, service.getAnimelistManager(), &service);
    filterShowMovies.applyFilter();
}

void MainWindow::on_actionHide_Movies_triggered()
{
    //TODO: remove old code
    //prepareFilteredState(); // disables UI elements

    //// display only animes with totalEpisodes = 1
    //service.hideMovies();

    //// display filtered list 
    //refreshAnimeList();

    FilterHideMovies filterHideMovies( this, service.getAnimelistManager(), &service );
    filterHideMovies.applyFilter();
}

void MainWindow::on_actionShow_Open_Ended_Animes_triggered()
{
    //TODO: remove old code
    //prepareFilteredState(); // disables UI elements

    //// display only animes with totalEpisodes = 1
    //service.showOpenEndedAnimes();

    //// display filtered list 
    //refreshAnimeList();

    FilterShowOpenEndedAnimes filterShowOpenEndedAnimes( this, service.getAnimelistManager(), &service );
    filterShowOpenEndedAnimes.applyFilter();
}

void MainWindow::on_actionHide_Open_Ended_Animes_triggered()
{
    //TODO: remove old code
    //prepareFilteredState(); // disables UI elements

    //// display only animes with totalEpisodes = 1
    //service.hideOpenEndedAnimes();

    //// display filtered list 
    //refreshAnimeList();

    FilterHideOpenEndedAnimes filterHideOpenEndedAnimes( this, service.getAnimelistManager(), &service );
    filterHideOpenEndedAnimes.applyFilter();
}

std::string MainWindow::userDialogFilterByTag()
{
    bool ok;
    QString userInput = QInputDialog::getText( this, "Filter by Tag",
        "Enter a word or a phrase which is contained in the anime's name", QLineEdit::Normal,
        "", &ok );
    
    if ( ok && !userInput.isEmpty() ) {
        return userInput.toStdString();
    }

    return "";
}

void MainWindow::on_actionFilter_By_Tag_triggered()
{
    //TODO: remove old code
    //// the user is shown a window where he types string
    //std::string tag = userDialogFilterByTag();
    //if ( tag.empty() ) {
    //    return; // user clicked cancel
    //}

    //prepareFilteredState(); // disables UI elements

    //// display only animes with totalEpisodes = 1
    //service.filterByTag( tag );

    //// display filtered list 
    //refreshAnimeList();

    FilterByTag filterByTag( this, service.getAnimelistManager(), &service );
    filterByTag.applyFilter();
}

void MainWindow::addRevisionNumberToWindowTitle()
{
    QTime timeNow( QTime::currentTime() );
    QDate dateNow( QDate::currentDate() );
    setWindowTitle( std::string( std::string( PROGRAM_NAME ) + " " + std::string( PROGRAM_VERSION )
        + " rev "
        + std::string( std::to_string( dateNow.year() ) + "."
        + std::to_string( dateNow.month() ) + "."
        + std::to_string( dateNow.day() ) + "."
        + std::to_string( timeNow.hour() ) + std::to_string( timeNow.minute() ) + std::to_string( timeNow.second() ) ) ).c_str() );
}

void MainWindow::on_actionHide_Animes_with_Name_Only_triggered()
{
    //TODO: remove old code
    //prepareFilteredState(); // disables UI elements

    //// remove animes from list which have: name="notEmpty" currentEpisode="1" totalEpisodes="??" URL=""
    //service.hideAnimesWithNameOnly();

    //// display filtered list 
    //refreshAnimeList();

    FilterHideAnimesWithNameOnly filterHideAnimesWithNameOnly( this, service.getAnimelistManager(), &service );
    filterHideAnimesWithNameOnly.applyFilter();
}
