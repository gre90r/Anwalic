#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <list>
#include "anime.h"
#include "animelist.h"
#include "addnewanime.h"
#include "editanimewindow.h"
#include "aboutwindow.h"
#include "preferenceswindow.h"
#include "preferences.h"
#include "AnimeListViewHelper.h"
#include "ListType.h"
#include "AnwalicService.h"

namespace Ui {
class MainWindow;
}

/**
 * the window which is displayed when the program starts.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * initializes program. loads settings.
     * @param parent pointer to parent window, but this is the first window being created
     */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * destructor. standard cleanup
     */
    ~MainWindow();

    /**
     * for main(). check if initialization failed.
     * the returned flag is set in the constructor of MainWindow
     * @return true: if initialization of MainWindow failed, e.g. if file load failed\n
     *         false: if everything went well.
     */
    bool failed() const;

private slots:
    /**
     * quits program. saves lists and preferences
     */
    void on_btnQuit_clicked() const;

    /**
     * add new Anime to My Anime List when button "Add New Anime" is clicked
     */
    void on_btnAddNewAnime_clicked();

    /**
     * receive data from form uiAddNewAnime & add that new anime to list.
     * adds new Anime to list which the user entered in the UI.
     * @param ptrAnime new Anime received from uiAddNewAnime
     */
    void receiveData( Anime* ptrAnime );

    /**
     * is called when form uiEditAnime ends. changes are already applied
     * because a pointer has been sent to directly change data in uiEditAnime
     */
    void receiveDataChanged();

    /**
     * is called when uiAbout ends. only deletes ui
     */
    void receiveGuiAboutFinished();

    /**
     * sets new preferences.
     * receives preferences changed by user from uiPreferences.
     * @param preferences contains new preferences which will be set
     */
    void receivePreferences( Preferences* preferences );

    /**
     * edit anime information when double clicking the list item.
     * calls on_btnEdit_clicked()
     * @param index the current list item which has been double clicked
     */
    void on_lvAnimes_doubleClicked(const QModelIndex &index);

    /**
     * button behaves differently in different program states.
     * the program state is what the user is currently seeing:
     * My Anime List, Completed Anime List or Filtered Anime List\n
     * \n
     * Different behaviors:\n
     * --------------------\n
     * program state: My Anime List\n
     *      -> increments Episode by one when Button says "Episode +1"\n
     *      -> moves anime to completed anime list when Button says "Move to Completed Animes"\n
     * \n
     * program state: Completed List\n
     *      -> Button always says "Move to Now Watching Animes". Moves Anime back to My Anime List\n
     * \n
     * program state: Filtered Anime List\n
     *      -> behaves like in program state: My Anime List\n
     */
    void on_btnIncEpisode_clicked();

    /**
     * episode -1 on selected anime
     */
    void on_btnDecEpisode_clicked();

    /**
     * delete selected Anime in My Anime List
     */
    void on_btnDelete_clicked();

    /**
     * edit Anime object. is also called on list item double clicked
     */
    void on_btnEdit_clicked();

    /**
     * open URL in browser of current selected anime
     */
    void on_btnGoToStream_clicked();

    /**
     * switch between My Anime List and Completed Animes
     */
    void on_btnToggleAnimeLists_clicked();

    /**
     * enable Ui elements which have been disabled by disableUiElementsForGeneralFilteredState().
     * such as Toggle-button, delete-button, export list...
     */
    void enableUiElementsForGeneralFilteredState() const;

    /**
     * enables filter functionalites such as Show Movies Only... in Ui
     */
    void enableUiFilterElements() const;

    /**
     * view copyright, and email to send error reports
     */
    void on_actionAbout_triggered();

    /**
     * select Completed Anime List
     */
    void on_actionCompleted_Animes_triggered();

    /**
     * select My Anime List
     */
    void on_actionMy_Anime_List_triggered();

    /**
     * selects list item when is clicked with a single mouse click
     * @param index - index of current selected list item which is passed by Qt
     */
    void on_lvAnimes_clicked(const QModelIndex &index);

    /**
     * Menu Item clicked: Edit -> Preferences
     */
    void on_actionPreferences_triggered();

    /**
     * opens file dialog to set name and location of the list to export
     */
    void on_actionExport_My_List_triggered();

    /**
     * selects My List in case an imported list was loaded
     */
    void on_actionSelect_My_List_triggered();

    /**
     * selects/imports a list exported by another user
     */
    void on_actionImport_Another_List_triggered();

    /**
     * enable/disable Ui elements for My Anime List
     * or Completed Anime List. call this method when
     * you come back from filtered list. that method restores
     * the Ui state
     */
    void jumpBackToPreviousNotFilteredUiState();

    /**
     * filters My Animelist to show Animes only which have current episode greater 1
     */
    void on_btnShowStartedAnimesOnly_clicked();

    /**
     * copy mylist.anl and mylist_completed.anl. save it to new folder "backup" in program directory.
     * @note both files have to be in the program directory
     */
    void on_actionMake_Backup_triggered() const;

    /**
     * Opens website crunchyroll.com.
     * Menu Item clicked: Website -> chrunchyroll.com
     */
    static void on_actionCrunchyroll_com_triggered();


// methods and attributes which are needed by FilterAnimelist
public:
    /**
     * disables UI elements which are fobidden
     * when list is filtered
     */
    void prepareFilteredState();

    /**
     * refreshing anime list is needed every time the list changes and
     * changes need to be displayed.
     * display anime list to list view. sorts animes ascending by name
     */
    void refreshAnimeList();

    /**
     * opens a new window where the user types in a keyword (called tag)
     * or a whole phrase
     * @return the keyword/phrase the user entered
     */
    std::string userDialogFilterByTag();

    // set to true if it's not secure to save list. is set on fatal and internal errors
    bool m_isFatalError;

private slots:
    /**
     * disables UI elements which are not allowed to click
     * when list is filtered.
     */
    void disableUiElementsForGeneralFilteredState() const;

    /**
     * disable all filter functionalites in UI
     */
    void disableUiFilterElements() const;

    /**
     * display only animes with totalEpisodes = 1
     */
    void on_actionShow_Movies_Only_triggered();

    /**
     * filter animes from list which have totalEpisodes="1"
     */
    void on_actionHide_Movies_triggered();

    /**
     * show animes with totalEpisodes="??"
     */
    void on_actionShow_Open_Ended_Animes_triggered();

    /**
     * hide animes with totalEpisodes="??"
     */
    void on_actionHide_Open_Ended_Animes_triggered();

    /**
     * filter animes from list which match a tag the user enters
     */
    void on_actionFilter_By_Tag_triggered();

    /**
     * filter animes from list which match the following requirements:
     * name="notEmpty" currentEpisode="1" totalEpisodes="??" URL=""
     */
    void on_actionHide_Animes_with_Name_Only_triggered();

    void on_actionWakanim_tv_triggered();

signals:
    /**
     * send data to uiEditAnime
     * @note this is implemented by Qt Framework
     */
    void sendData( Anime*, AnwalicService* );

    /**
     * send preferences to uiPreferences
     * @note this is implemented by Qt Framework
     */
    void sendPreferences( Preferences* );

private:
    /*************************/
    /* private UI attributes */
    /*************************/
    Ui::MainWindow *ui;
    AddNewAnime* uiAddNewAnime;
    EditAnimeWindow* uiEditAnime;
    AboutWindow* uiAbout;
    PreferencesWindow* uiPreferences;

    /**********************/
    /* private attributes */
    /**********************/
    AnwalicService service; // the class which handles the business logic
    QModelIndex m_lastUsedListItemIndex; // holds the last clicked list item
    bool m_initFailed; // saves state if program started correctly
    AnimeListViewHelper* m_animeListViewHelper; // helps to prepare stringListModel

    /*******************/
    /* private methods */
    /*******************/
    /**
     * return anime name from list item that has just been selected.
     * is called everytime the user selects an anime in list
     * @return anime name if successful. if failed: ""
     */
    std::string getAnimeNameFromSelectedListItemAndValidate();

    /**
     * select list item when clicking on it
     * @param listItemIndex the model index returned by the mouse click.
     */
    void selectListViewItem( QModelIndex listItemIndex ) const;

    /**
     * sorts list & sets model on listview
     * @param listType indicates to select list NOW_WATCHING_ANIMES (My Anime List) or COMPLETED_ANIMELIST or FILTERED_ANIMELIST
     */
    void setAnimeListOnListview( ListType listType );

    /**
     * get the current selected list which is currently displayed
     * @return pointer of current list displayed in listview
     */
    Animelist* currentSelectedList() const;

    /**
     * moves a watched anime to completed animes list.
     * @param anime the anime to move to completed animes list
     * @note parameter must be not const in order to move to other list
     */
    void moveAnimeToCompletedList( Anime* anime );

    /**
     * moves an anime from completed anime list to My Anime List.
     * Notice that "Now Watching Anime List" is the former expression for "My Anime List"
     * and is yet not altered.
     * @param anime the anime to move from Completed Anime List to My Anime List
     */
    void moveAnimeToNowWatchingAnimeList( Anime* anime );

    /**
     * sets "Episode +1" or "Move to Completed Animes" on Button.
     * checks state of current anime. when current episode is last episode then
     * "Episode + 1" button is set to "Move to Completed Animes". If it's not the
     * last episode the button's text remains as "Episode +1"
     */
    void updateTextBtnIncEpisode();

    /**
     * set image on GUI background
     * @param imageFilePath path to image
     */
    void uiSetBackground( const char* imageFilePath );

    /**
     * make list item index invalid to select nothing
     */
    void setInvalidListItemIndex();

    /**
     * set MainWindow settings
     */
    void applyPreferences();
    
    /**
     * save current MainWindow size to m_preferences
     */
    void setCurrentWindowSizeToPreferences() const;

    /**
     * count animes in list and display count in caption.
     * Automatically detects which list is selected and calculates
     * number of animes of this list.\n
     * e.g. "My Anime List (13 Animes)".
     */
    void displayNumberOfAnimesInList();

    /**
     * is called when red cross in top right corner of window is pressed
     * @param closeEvent the close event passed by Qt framework
     */
    void closeEvent( QCloseEvent* closeEvent ) override;

    /**
     * set current index as lastUsedListItemIndex
     */
    void setLastUsedListItemIndex();

    /**
     * add more detailed version number in window title for debug session
     */
    void addRevisionNumberToWindowTitle();
};

#endif // MAINWINDOW_H
