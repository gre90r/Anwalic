#include "AnwalicService.h"
#include "errorview.h"
#include "memory.h"
#include "globals.h"
#include <QFileDialog>
#include <QDate>
#include "stringsEN.h"
#include "InternetUtilities.h"
#include <boost/algorithm/string/find.hpp>


AnwalicService::AnwalicService(
    const std::string& savefilenameMyAnimelist, 
    const std::string& savefilenameCompletedAnimelist,
    const Preferences& preferences )
        : m_savefilenameMyAnimelist(savefilenameMyAnimelist),
          m_savefilenameCompletedAnimelist(savefilenameCompletedAnimelist),
          m_saveload( new SaveLoad( savefilenameMyAnimelist, savefilenameCompletedAnimelist ) ),
          m_animelistManager( m_saveload ), // loads animelists from file
          m_preferences( new Preferences( preferences ) ) // be careful here. default copy constructor is called
{
    m_preferences->readConfigFile();
}

AnwalicService::~AnwalicService()
{
    Memory::safeDelete( m_preferences );
    Memory::safeDelete( m_saveload );
}

std::string AnwalicService::getSavefileNameMyAnimelist() const
{
    return m_savefilenameMyAnimelist;
}

std::string AnwalicService::getSavefileNameCompletedAnimelist() const
{
    return m_savefilenameCompletedAnimelist;
}

Preferences* AnwalicService::getPreferences() const
{
    return m_preferences;
}

Animelist* AnwalicService::getMyAnimelist() const
{
    return m_animelistManager.getMyAnimelist();
}

Animelist* AnwalicService::getCompletedAnimelist() const
{
    return m_animelistManager.getCompletedAnimelist();
}

Animelist* AnwalicService::getFilteredAnimelist() const
{
    return m_animelistManager.getFilteredAnimelist();
}

AnimelistManager* AnwalicService::getAnimelistManager()
{
    return &m_animelistManager;
}

std::string AnwalicService::getAnimeNameFromSelectedListItemAndValidate(const std::string& listEntry, bool& isFatalError) const
{
    // get anime name from string of list item
    std::string animeName = "";
    try
    {
        animeName = Animelist::getAnimeNameFromToStringPhrase( listEntry );
    }
    catch ( const std::invalid_argument& error )
    {
        std::string errorMsg = error.what();
        errorMsg += "\nexception caught @MainWindow::getAnimeNameFromSelectedListItemAndValidate(). "
            "cannot translate list item string to Anime name!\n";
        isFatalError = true;
        ErrorView::internalErrorHandler( errorMsg );
        return "";
    }
    return animeName;
}

Anime* AnwalicService::findAnimeByName(const std::string& animeName, bool& isFatalError, Animelist* currentSelectedList)
{
    // search anime by name in current selected list
    Anime* animeSelected = currentSelectedList->getAnimeByName( animeName );
    if ( animeSelected == nullptr )
    {
        std::string errorMsg = "internal error: @MainWindow::findAnimeByName(). "
            "AnimeList::getAnimeByName() failed! Cannot find Anime in current selected list";
        isFatalError = true;
        ErrorView::internalErrorHandler( errorMsg );
        return nullptr; // anime not found. internal error
    }
    return animeSelected;
}

void AnwalicService::moveAnimeToMyAnimeList(Anime* anime)
{
    m_animelistManager.moveAnimeToMyAnimeList( anime );
}

void AnwalicService::moveAnimeToCompletedAnimelist(Anime* anime)
{
    m_animelistManager.moveAnimeToCompletedAnimelist( anime );
}

void AnwalicService::save(const bool& isFatalError) const
{
    if ( !isFatalError ) {
        m_saveload->save(
            m_animelistManager.getMyAnimelist()->getAnimeList(),
            m_animelistManager.getCompletedAnimelist()->getAnimeList()
        );
    }
}

bool AnwalicService::isActiveListMyList() const
{
    return m_animelistManager.isActiveListMyList();
}

size_t AnwalicService::countAnimesInMyAnimeList() const
{
    return m_animelistManager.countAnimesInMyAnimeList();
}

size_t AnwalicService::countAnimesInCompletedAnimeList() const
{
    return m_animelistManager.countAnimesInCompletedAnimeList();
}

size_t AnwalicService::countAnimesInFilteredAnimeList() const
{
    return m_animelistManager.countAnimesInFilteredAnimeList();
}

void AnwalicService::clearFilteredAnimeList()
{
    m_animelistManager.clearFilteredAnimeList();
    m_animelistManager.setListSelected( m_animelistManager.getListSelectedBeforeFiltering() );
}

void AnwalicService::deleteFilteredAnimeList()
{
    m_animelistManager.deleteFilteredAnimeList();
}

void AnwalicService::writeConfigFile() const
{
    m_preferences->writeConfigFile();
}

void AnwalicService::selectMyList()
{
    // reload filepaths MyAnimeList and CompletedAnimeList to point to MyList (not an imported list which was displayed previously)
    Memory::safeDelete( m_saveload );
    m_savefilenameMyAnimelist = DEFAULT_ANIME_LIST_PATH;
    m_savefilenameCompletedAnimelist = DEFAULT_ANIME_LIST_COMPLETED_PATH;
    m_saveload = new SaveLoad( m_savefilenameMyAnimelist, m_savefilenameCompletedAnimelist );

    m_animelistManager.selectMyList( m_saveload );
}

void AnwalicService::selectAnotherList( const QString& importedListPath )
{
    QString importedCompletedListPath = importedListPath;
    SaveLoad::insertCompletedSuffix( importedCompletedListPath ); // e.g. "/.../list.anl" -> "/.../list_completed.anl"

    // validate importedCompletedListPath
    // It has to exist a "<name>_completed.anl" file in the same location. So check for it
    // by opening it
    std::ifstream ifStream( importedCompletedListPath.toStdString().c_str(), std::ios::in );
    if ( !ifStream )
    {
        // could not open <name>_completed.anl
        ifStream.close();
        ErrorView::showPopup( std::string(
            std::string(
            "Failed to select another list. There does not exist a completed list to your "
            "selected list \"" ) + std::string( importedListPath.toStdString() ) +
            std::string( "\". " ) + std::string( "Expected \"" ) +
            importedCompletedListPath.toStdString() + "\" as completed list. " +
            "DO NOT select the completed list!" ).c_str() );
        return;
    }
    ifStream.close(); // validation end. file could be opened so it is a valid filepath

    // reload all relevant MainWindow attributes
    Memory::safeDelete( m_saveload );
    m_savefilenameMyAnimelist = importedListPath.toStdString();
    m_savefilenameCompletedAnimelist = importedCompletedListPath.toStdString();
    m_saveload = new SaveLoad( m_savefilenameMyAnimelist, m_savefilenameCompletedAnimelist );
    m_animelistManager.selectAnotherList( m_saveload, importedListPath, importedCompletedListPath );
}

ListType AnwalicService::listSelected() const
{
    try {
        return m_animelistManager.listSelected();
    }
    catch ( const std::exception& e )
    {
        // catch error state: no list selected.
        ErrorView::internalErrorHandler( e.what() );
        //throw std::exception( e.what() ); // rethrow. leads to program quit
        throw std::exception();
    }
}

void AnwalicService::setListSelected(const ListType& listType)
{
    m_animelistManager.setListSelected( listType );
}

void AnwalicService::setListIsFiltered(const bool& state)
{
    m_animelistManager.setListIsFiltered( state );
}

//TODO: remove old code
//void AnwalicService::filterByStartedAnimesOnly()
//{
//    // copy pointers from My Anime List -> m_filteredAnimeList.
//    // make filteredAnimelist = myAnimelist
//    if ( !copyCurrentListToFilteredList() ) {
//        return;
//    }
//
//    // detect animes which will be removed from filtered list -> filtered_list = current_list
//    QStringList animesToPop = QStringList(); // all animes in there will be popped out in m_filteredAnimeList
//    for ( unsigned int i = 0; i < m_animelistManager.getFilteredAnimelist()->size(); i++ )
//    {
//        // remove animes which do not match the filter
//        if ( ( *m_animelistManager.getFilteredAnimelist() )[i]->getCurrentEpisode() <= 1 )
//        {
//            animesToPop.push_back( ( *m_animelistManager.getFilteredAnimelist() )[i]->getName().c_str() );
//        }
//    }
//
//    popDetectedAnimesInFilteredListAndSetFilteredState( animesToPop );
//}

void AnwalicService::createBackup() const
{
    // check if mylist.anl exists
    if ( !QFile::exists( "./mylist.anl" ) ) {
        ErrorView::internalErrorHandler( "@MainWindow::on_actionMake_Backup_triggered(): mylist.anl does not exist!" );
        return;
    }

    // create subfolder backup
    const char* backupDirName = "./backup";
    QDir backupDir = QDir( backupDirName );
    if ( !backupDir.exists() )
        QDir( "." ).mkdir( "backup" ); // if dir does not exist, create folder "backup" in program directory

    // new filenames for copies. date & time will be inserted to both filenames
    QDate dateNow = QDate::currentDate();
    QTime timeNow = QTime::currentTime();
    QString year = std::to_string( dateNow.year() ).c_str();
    QString month = std::to_string( dateNow.month() ).c_str();
    if ( month.size() == 1 ) month.insert( 0, "0" ); // e.g.: change 8 to 08
    QString day = std::to_string( dateNow.day() ).c_str();
    if ( day.size() == 1 ) day.insert( 0, "0" );
    QString hour = std::to_string( timeNow.hour() ).c_str();
    if ( hour.size() == 1 ) hour.insert( 0, "0" );
    QString minute = std::to_string( timeNow.minute() ).c_str();
    if ( minute.size() == 1 ) minute.insert( 0, "0" );
    QString second = std::to_string( timeNow.second() ).c_str();
    if ( second.size() == 1 ) second.insert( 0, "0" );
    QString newFileNameMylist = QString( backupDirName ) + "/mylist"
        + year + month + day + QString( "_" )
        + hour + minute + second
        + ".anl";
    QString newFileNameMylist_completed = QString( backupDirName ) + "/mylist"
        + year + month + day + QString( "_" )
        + hour + minute + second
        + "_completed"
        + ".anl";

    // copy mylist.anl & mylist_completed.anl to ./Anwalic/backup
    if ( ( QFile::copy( DEFAULT_ANIME_LIST_PATH, newFileNameMylist ) )
        && ( QFile::copy( DEFAULT_ANIME_LIST_COMPLETED_PATH, newFileNameMylist_completed ) ) )
    {
        // sucess if both copies succeeded
        QString successMsg = "Backup created successfully in \"" + QString( backupDir.absolutePath() ) + "\"";
        ErrorView::showPopup( successMsg.toStdString().c_str() );
    }
    else { // failed if one or both did not succeed. also fails if file already exists
        ErrorView::showErrorPopup( nullptr, STR_BACKUP_FAILED_COULD_NOT_COPY );
    }
}

QString AnwalicService::getImportedPathCompletedAnimelist() const
{
    return m_animelistManager.getImportedPathCompletedAnimelist();
}

QString AnwalicService::getImportedPathMyAnimelist() const
{
    return m_animelistManager.getImportedPathMyAnimelist();
}

void AnwalicService::exportAnimelist(const QString& exportPathAndName) const
{
    try {
        m_saveload->save(
            m_animelistManager.getMyAnimelist()->getAnimeList(),
            m_animelistManager.getCompletedAnimelist()->getAnimeList(),
            exportPathAndName.toStdString() );
    }
    catch ( const std::exception& e )
    {
        ErrorView::runtimeErrorHandler( std::string("Cannot export animelist! ") + e.what() );
    }
}

//TODO: remove old code
//void AnwalicService::hideAnimesWithNameOnly()
//{
//    // copy pointers from My Anime List -> m_filteredAnimeList.
//    // make filteredAnimelist = myAnimelist
//    if ( !copyCurrentListToFilteredList() ) {
//        return;
//    }
//
//    // detect animes which will be removed from filtered list -> filtered_list = current_list
//    QStringList animesToPop = QStringList(); // all animes in there will be popped out in m_filteredAnimeList
//    for ( unsigned int i = 0; i < m_animelistManager.getFilteredAnimelist()->size(); i++ )
//    {
//        // remove animes which do not match the filter
//        if (    !( *m_animelistManager.getFilteredAnimelist() )[i]->getName().empty()
//             &&  ( *m_animelistManager.getFilteredAnimelist() )[i]->getCurrentEpisode() == 1
//             &&  ( *m_animelistManager.getFilteredAnimelist() )[i]->getTotalEpisodes() == MAX_NUMBER_EPISODES
//             &&  ( *m_animelistManager.getFilteredAnimelist() )[i]->getUrl().empty()
//             
//           )
//        {
//            animesToPop.push_back( ( *m_animelistManager.getFilteredAnimelist() )[i]->getName().c_str() );
//        }
//    }
//
//    popDetectedAnimesInFilteredListAndSetFilteredState( animesToPop );
//}

void AnwalicService::popDetectedAnimesInFilteredListAndSetFilteredState(const QStringList& animesToPop)
{
    // pop detected animes.
    // make filteredAnimelist -= animes with totalEpisode == 1
    for ( int i = 0; i < animesToPop.size(); i++ )
    {
        m_animelistManager.getFilteredAnimelist()->popOutByNameWithoutDeletingMemory( animesToPop.at( i ).toStdString() );
    }

    m_animelistManager.setListIsFiltered( true );
    m_animelistManager.setListSelected( FILTERED_ANIMELIST );
}

//TODO: remove old code
//void AnwalicService::hideMovies()
//{
//    // copy pointers from My Anime List -> m_filteredAnimeList.
//    // make filteredAnimelist = myAnimelist
//    if ( !copyCurrentListToFilteredList() ) {
//        return;
//    }
//
//    // detect animes which will be removed from filtered list -> filtered_list = current_list
//    QStringList animesToPop = QStringList(); // all animes in there will be popped out in m_filteredAnimeList
//    for ( unsigned int i = 0; i < m_animelistManager.getFilteredAnimelist()->size(); i++ )
//    {
//        // remove animes which do not match the filter
//        if ( ( *m_animelistManager.getFilteredAnimelist() )[i]->getTotalEpisodes() == 1 )
//        {
//            animesToPop.push_back( ( *m_animelistManager.getFilteredAnimelist() )[i]->getName().c_str() );
//        }
//    }
//
//    popDetectedAnimesInFilteredListAndSetFilteredState(animesToPop);
//}

//TODO: remove old code
//void AnwalicService::hideOpenEndedAnimes()
//{
//    // copy pointers from My Anime List -> m_filteredAnimeList.
//    // make filteredAnimelist = myAnimelist
//    if ( !copyCurrentListToFilteredList() ) {
//        return;
//    }
//
//    // detect animes which will be removed from filtered list -> filtered_list = current_list
//    QStringList animesToPop = QStringList(); // all animes in there will be popped out in m_filteredAnimeList
//    for ( unsigned int i = 0; i < m_animelistManager.getFilteredAnimelist()->size(); i++ )
//    {
//        // remove animes which do not match the filter
//        if ( ( *m_animelistManager.getFilteredAnimelist() )[i]->getTotalEpisodes() == MAX_NUMBER_EPISODES )
//        {
//            animesToPop.push_back( ( *m_animelistManager.getFilteredAnimelist() )[i]->getName().c_str() );
//        }
//    }
//
//    popDetectedAnimesInFilteredListAndSetFilteredState( animesToPop );
//}

//TODO: remove old code
//void AnwalicService::showOpenEndedAnimes()
//{
//    // copy pointers from My Anime List -> m_filteredAnimeList.
//    // make filteredAnimelist = myAnimelist
//    if ( !copyCurrentListToFilteredList() ) {
//        return;
//    }
//
//    // detect animes which will be removed from filtered list -> filtered_list = current_list
//    QStringList animesToPop = QStringList(); // all animes in there will be popped out in m_filteredAnimeList
//    for ( unsigned int i = 0; i < m_animelistManager.getFilteredAnimelist()->size(); i++ )
//    {
//        // remove animes which do not match the filter
//        if ( ( *m_animelistManager.getFilteredAnimelist() )[i]->getTotalEpisodes() != MAX_NUMBER_EPISODES )
//        {
//            animesToPop.push_back( ( *m_animelistManager.getFilteredAnimelist() )[i]->getName().c_str() );
//        }
//    }
//
//    popDetectedAnimesInFilteredListAndSetFilteredState( animesToPop );
//}

//TODO: remove old code
//void AnwalicService::filterByTag(std::string tag)
//{
//    // copy pointers from My Anime List -> m_filteredAnimeList.
//    // make filteredAnimelist = myAnimelist
//    if ( !copyCurrentListToFilteredList() ) {
//        return;
//    }
//
//    // detect animes which will be removed from filtered list -> filtered_list = current_list
//    QStringList animesToPop = QStringList(); // all animes in there will be popped out in m_filteredAnimeList
//    for (   unsigned int i = 0;
//            i < m_animelistManager.getFilteredAnimelist()->size();
//            i++ )
//    {
//        // remove animes which do not match the filter
//        std::string animeName = ( *m_animelistManager.getFilteredAnimelist() )[i]->getName();
//        if ( !boost::ifind_first( animeName, tag ) ) // remove animes which do not contain the tag
//        {
//            animesToPop.push_back( ( *m_animelistManager.getFilteredAnimelist() )[i]->getName().c_str() );
//        }
//    }
//
//    popDetectedAnimesInFilteredListAndSetFilteredState( animesToPop );
//}

void AnwalicService::openURL(const char* url)
{
    InternetUtilities::openUrl( url );
}

bool AnwalicService::copyCurrentListToFilteredList()
{
    return m_animelistManager.copyCurrentListToFilteredList();
}

ListType AnwalicService::getListSelectedBeforeFiltering() const
{
    return m_animelistManager.getListSelectedBeforeFiltering();
}

bool AnwalicService::searchCompletedAnimelistForDuplicate(const std::string& animeName)
{
    // search MyAnimelist
    //{
    //    std::list<Anime*> myAnimelist = m_animelistManager.getMyAnimelist()->getAnimeList();
    //    std::list<Anime*>::const_iterator constIt;
    //    for ( constIt = myAnimelist.cbegin(); constIt != myAnimelist.end(); ++constIt )
    //    {
    //        if ( ( *constIt )->getName() == animeName )
    //        {
    //            return true; // duplicate found
    //        }
    //    }
    //}

    // search Completed Animelist
    {
        std::list<Anime*> completedAnimelist = m_animelistManager.getCompletedAnimelist()->getAnimeList();
        std::list<Anime*>::const_iterator constIt;
        for ( constIt = completedAnimelist.cbegin(); constIt != completedAnimelist.end(); ++constIt )
        {
            if ( ( *constIt )->getName() == animeName )
            {
                return true; // duplicate found
            }
        }
    }

    return false; // no duplicate. anime name does not exist
}

//TODO: remove old code
//void AnwalicService::showMoviesOnly()
//{
//    // copy pointers from My Anime List -> m_filteredAnimeList.
//    // make filteredAnimelist = myAnimelist
//    if ( !copyCurrentListToFilteredList() ) {
//        return;
//    }
//
//    // detect animes which will be removed from filtered list -> filtered_list = current_list
//    QStringList animesToPop = QStringList(); // all animes in there will be popped out in m_filteredAnimeList
//    for ( unsigned int i = 0; i < m_animelistManager.getFilteredAnimelist()->size(); i++ )
//    {
//        // remove animes which do not match the filter
//        if ( ( *m_animelistManager.getFilteredAnimelist() )[i]->getTotalEpisodes() > 1 )
//        {
//            animesToPop.push_back( ( *m_animelistManager.getFilteredAnimelist() )[i]->getName().c_str() );
//        }
//    }
//
//    popDetectedAnimesInFilteredListAndSetFilteredState( animesToPop );
//}
