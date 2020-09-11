#ifndef ANWALIC_SERVICE_H
#define ANWALIC_SERVICE_H

#include <string>
#include "AnimelistManager.h"
#include "preferences.h"
#include "AnimeListViewHelper.h"
#include "saveload.h"

/**
 * holds business logic of program.\n
 * handles: sorting, filtering, finding, config file\n
 * also takes requests to process animelist information but is passed
 * to AnimelistManager.
 */
class AnwalicService
{
public:
    /**
     * forbidden default constructor
     */
    AnwalicService() = delete;

    /**
     * constructor
     * @param savefilenameMyAnimelist filename My Anime List.
     * @param savefilenameCompletedAnimelist filename Completed Anime List
     * @param preferences preferences to apply. has to be loaded from file
     */
    explicit AnwalicService(
        const std::string& savefilenameMyAnimelist,
        const std::string& savefilenameCompletedAnimelist,
        const Preferences& preferences
    );

    /**
     * destructor. cleanup
     */
    ~AnwalicService();

    /**********/
    /* Getter */
    /**********/
    std::string getSavefileNameMyAnimelist() const;
    std::string getSavefileNameCompletedAnimelist() const;
    Preferences* getPreferences() const;
    Animelist* getMyAnimelist() const;
    Animelist* getCompletedAnimelist() const;
    Animelist* getFilteredAnimelist() const;
    /**
     * getter is not const because because AnimelistManager needs to
     * be passed to FilterAnimelist classes in order to filter.
     * Therefore the filtered list in AnimelistManager will be altered
     * TODO: fix bad code. do not let NOT CONST attribute out of class
     * ^- sadly this must be done because there is ONLY ONE AnimeListManager and
     * ^- in order to operate on this the reference must be let out of the class
     * ^- to achieve a covenient way of implementing FilterAnimelist. The class
     * ^- a whole in one solution.
     */
    AnimelistManager* getAnimelistManager();

    /**
     * get anime name of current selected list item.
     * will return
     * @param listEntry current selected list item. e.g. "YuruYuri (Episode 9 / 12)"
     * @param isFatalError the program state. it is set to true if list item format is wrong, when '(' cannot be found
     * @return anime name. in the above example it would return "YuruYuri" 
     */
    std::string getAnimeNameFromSelectedListItemAndValidate(const std::string& listEntry, bool& isFatalError) const;

    /**
     * find anime name in current selected list the user is currently seeing
     * @param animeName
     * @param isFatalError the program state. it is set to true if anime name cannot be found in list
     * @param currentSelectedList the list the user is currently seeing
     * @return success: anime object. if fails returns nullptr
     */
    Anime* findAnimeByName(const std::string& animeName, bool& isFatalError, Animelist* currentSelectedList);

    /**
     * move anime from Completed Anime List to My Anime List
     * @param anime the anime to move to My Anime List
     */
    void moveAnimeToMyAnimeList( Anime* anime );

    /**
     * move anime from My Anime List to Completed Anime List
     * @param anime the anime to move to Completed Anime List
     */
    void moveAnimeToCompletedAnimelist( Anime* anime );

    /**
     * saves lists: my anime list & completed anime list
     * @param isFatalError program state. if program occurs a fatal error then do not save
     */
    void save(const bool& isFatalError) const;

    /**
     * checks if current loaded list is my own list or a list from someone else which
     * has been imported.
     * @return true: active list is My List. means it is not an imported list of someone else\n
     *         false: active list is an imported list of someone else
     */
    bool isActiveListMyList() const;

    /**
     * count how much animes are in My Anime List
     * @return number of animes in My Anime List
     */
    size_t countAnimesInMyAnimeList() const;

    /**
     * count how much animes are in Completed Anime List
     * @return number of animes in Completed Anime List
     */
    size_t countAnimesInCompletedAnimeList() const;

    /**
     * count how much animes are in Filtered Anime List
     * @return number of animes in Filtered Anime List
     */
    size_t countAnimesInFilteredAnimeList() const;

    /**
     * delete filtered anime list
     */
    void clearFilteredAnimeList();

    /**
     * remove filtered animelist.\n
     * the entries within are not deleted but popped out, because My Anime List
     * is still using the entries. Filtered Anime List just borrows it from
     * My Anime List
     * @note cannot delete m_filteredAnimeList easily because it shares
     * the same pointers with m_animelist. so if delete is called on m_animelist (and it has been deleted before!)
     * m_filteredAnimeList cannot access already deleted objects. so just pop already
     * deleted pointers and then call delete on m_filteredAnimeList.
     */
    void deleteFilteredAnimeList();

    /**
     * writes all preference attributes to config file
     * @note !! NEVER MAKE STATIC !!
     */
    void writeConfigFile() const;

    /**
     * selects My list, meaning that we no longer want an imported list to be displayed.\n
     * it switches the MyAnimeList and CompletedAnimeList files.
     */
    void selectMyList();

    /**
     * load imported list
     * @param importedListPath filepath of My Anime List. e.g. "/home/gregor/gregor.anl"
     */
    void selectAnotherList( const QString& importedListPath );

    /**
     * See which list is currently selected.\n
     * This method does not refer to the state if it's an imported list or not.
     * It refers to the state of the current loaded list, if My Anime List, Completed Anime List or
     * Filtered Anime List is currently displayed.
     * @throws std::exception if no list is currently selected.
     * @return which list is currently selected/displayed on the window.\n
     *         MY_ANIMELIST: My Anime List is currently displayed.\n
     *         COMPLETED_ANIMELIST: Completed Anime List is currently displayed.\n
     *         FILTERED_ANIMELIST: Filtered Anime List is currently displayed.
     */
    ListType listSelected() const;

    /**
     * set which list is currently displayed:
     * My Anime List, Completed Anime List or Filtered Anime List.\n
     * Is called when list is switched
     * @param listType list type of list which will be displayed
     */
    void setListSelected( const ListType& listType );

    /**
     * set current list state to filtered or not filtered
     * @param state new state. true = isFiltered, false = isNotFiltered
     */
    void setListIsFiltered( const bool& state );

    /**********/
    /* Filter */
    /**********/
    //TODO: remove old code
    /**
     * display only animes which have episode > 1
     */
    //void filterByStartedAnimesOnly();

    //TODO: remove old code
    /**
     * displays only animes with totalEpisodes = 1
     */
    //void showMoviesOnly();

    /**
     * creates backup files in subfolder of program directory -> ./Anwalic/backup.
     * one file for myanimelist.anl and one file for myanimelist_completed.anl.
     * e.g. mylist20180303_124023.anl & mylist20180303_124023_completed.anl, these two files are one backup.\n
     */
    void createBackup() const;

    /**
     * from imported list get the completed animelist path
     * @return path of completed animelist of imported list
     */
    QString getImportedPathCompletedAnimelist() const;

    /**
     * from imported list get the myanimelist path
     * @return path of myanimelist of imported list
     */
    QString getImportedPathMyAnimelist() const;

    /**
     * save My Anime List in specified location
     * @param exportPathAndName the specified location where to save My Anime List
     */
    void exportAnimelist(const QString& exportPathAndName) const;

    //TODO: remove old code
    /**
     * filter animes meet the following requirements:
     * name="a name" currentEpisode="1" totalEpisodes="??" URL=""
     */
    //void hideAnimesWithNameOnly();

    /**
     * filters list by removing the entries animesToPop holds.
     * automatically alteres filtered list
     * @param animesToPop list of animes which will be filtered
     */
    void popDetectedAnimesInFilteredListAndSetFilteredState(const QStringList& animesToPop);

    //TODO: remove old code
    /**
     * hide movies in current selected list
     * movies are animes which match the following requirements:
     * totalEpisodes="1"
     */
    //void hideMovies();

    //TODO: remove old code
    /**
     * hide animes which match the following requirements:
     * totalEpisodes="??"
     */
    //void hideOpenEndedAnimes();

    //TODO: remove old code
    /**
     * show animes which match the following requirements:
     * totalEpisodes="??"
     */
    //void showOpenEndedAnimes();

    //TODO: remove old code
    /**
     * filter by keyword the user enters.
     * e.g. user enters "ger sub", so the list shows only
     * animes containing this string
     * @param tag keyword to search in animelist. do not make const
     */
    //void filterByTag(std::string tag);

    /**
     * opens a URL in browser
     * @param url the url to open in browser
     */
    static void openURL( const char* url );

    /**
     * copies anime pointers from current list (My Anime List)
     * or (Completed Anime List) to filtered list
     * @return true: copy successful
     *         false: when tried to filter filtered list
     */
    bool copyCurrentListToFilteredList();

    /**
     * get list which was selected before filtering.
     * @return MY_ANIMELIST or COMPLETED_ANIMELIST
     */
    ListType getListSelectedBeforeFiltering() const;

    /**
     * search CompletedAnimelist for already existing anime name
     * @param animeName the anime name to check for duplicate
     * @return true: animeName is a duplicate
     *         false: animeName does not exist
     */
    bool searchCompletedAnimelistForDuplicate( const std::string& animeName );

private:
    std::string m_savefilenameMyAnimelist;
    std::string m_savefilenameCompletedAnimelist;
    SaveLoad* m_saveload;
    AnimelistManager m_animelistManager;
    Preferences* m_preferences;
};

#endif