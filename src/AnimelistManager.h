#ifndef ANIMELIST_MANAGER_H
#define ANIMELIST_MANAGER_H

#include "animelist.h"
#include <QString>
#include "saveload.h"

/**
 * CRUD functionality for all animelists (CRUD = create read update delete).\n
 * get all anime related data from here, including the lists they are organized in.\n
 * everytime you need to retrieve information for animelists you get it from here.\n
 * Does not handle preferences data.
 */
class AnimelistManager
{
public:
    /**
     * forbidden default constructor
     */
    AnimelistManager() = delete;

    /**
     * constructor. initializes attributes. no other functionality
     * @param saveload needed to load My Anime List and Completed Anime List from file
     */
    explicit AnimelistManager( SaveLoad* saveload );

    /**
     * destructor. cleanup
     */
    ~AnimelistManager();

    /*******************/
    /* Setter & Getter */
    /*******************/

    Animelist* getMyAnimelist() const;
    void setMyAnimeList( Animelist );
    Animelist* getCompletedAnimelist() const;
    void setCompletedAnimeList( Animelist );
    Animelist* getFilteredAnimelist() const;

    /**
     * get list which was selected before filtering.
     * @return MY_ANIMELIST or COMPLETED_ANIMELIST
     */
    ListType getListSelectedBeforeFiltering() const;

    /**
     * from imported list get the myanimelist path
     * @return path of myanimelist of imported list
     */
    QString getImportedPathMyAnimelist() const;

    /**
     * from imported list get the completed animelist path
     * @return path of completed animelist of imported list
     */
    QString getImportedPathCompletedAnimelist() const;
    
    /**
     * set new path imported list's My Anime List
     * @param path new path to My Anime List of imported list
     */
    void setImportedPathMyAnimelist( const QString& path );

    /**
     * set new path imported list's Completed Anime List
     * @param path new path to Completed Anime List of imported list
     */
    void setImportedPathCompletedAnimelist( const QString& path );

    /**
     * checks if current loaded list is my own list or a list from someone else which
     * has been imported.
     * @return true: active list is My List. means it is not an imported list of someone else\n
     *         false: active list is an imported list of someone else
     */
    bool isActiveListMyList() const;

    /**
     * moves an anime from completed anime list to My Anime List.
     * Notice that "Now Watching Anime List" is the former expression for "My Anime List"
     * and is yet not altered.
     * @param anime the anime to move from Completed Anime List to My Anime List
     */
    void moveAnimeToMyAnimeList( Anime* anime ) const;

    /**
     * moves a watched anime to completed animes list.
     * @param anime the anime to move to completed animes list
     */
    void moveAnimeToCompletedAnimelist( Anime* anime ) const;

    /**
     * counts anime entries in My Anime List
     * @return number of animes contained in My Anime List
     */
    size_t countAnimesInMyAnimeList() const;

    /**
     * counts anime entries in Completed Anime List
     * @return number of animes contained in Completed Anime List
     */
    size_t countAnimesInCompletedAnimeList() const;

    /**
     * counts anime entries in Filtered Anime List
     * @return number of animes contained in Filtered Anime List
     */
    size_t countAnimesInFilteredAnimeList() const;

    /**
     * copy pointers from My Anime List -> m_filteredAnimeList
     */
    void passOriginalAnimePointersFromMyAnimeListToFilteredAnimeList();

    /**
     * copy pointers from Completed Anime List -> m_filteredAnimeList
     */
    void passOriginalAnimePointersFromCompletedAnimeListToFilteredAnimeList();

    /**
     * copies anime pointers from current list (My Anime List)
     * or (Completed Anime List) to filtered list
     * @return true: copy successful
     *         false: when tried to filter filtered list
     */
    bool copyCurrentListToFilteredList();

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
     * selects My list, meaning that we no longer want an imported list to be displayed.\n
     * it switches the MyAnimeList and CompletedAnimeList files
     * @param saveload needed to reload MyList
     */
    void selectMyList( SaveLoad* saveload );

    /**
     * load imported list.\n
     * @note saveload must be reloaded with new filepaths before this function call
     * @param saveload contains the new filepaths.
     * @param importedMyAnimeListPath path to the imported My Anime List
     * @param importedCompletedListPath path to the imported Completed Anime List
     */
    void selectAnotherList(SaveLoad* saveload, const QString& importedMyAnimeListPath, const QString& importedCompletedListPath);

    /**
     * See which list is currently selected.\n
     * This method does not refer to the state if it's an imported list or not.
     * It refers to the state of the current loaded list, if My Anime List, Completed Anime List or
     * Filtered Anime List is currently displayed.
     * @throws std::exception if no list is currently selected
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

    

private:
    Animelist* m_myAnimelist; // My Anime List. The animes which are currently watched are saved here
    Animelist* m_completedAnimelist; // Completed Anime List
    Animelist* m_filteredAnimeList; // Filtered Anime List.
    QString m_importedMyAnimeListPath; // e.g. C:/Users/gre90r/gre90r.anl
    QString m_importedCompletedListPath; // e.g. C:/Users/gre90r/gre90r_completed.anl
    bool m_activeListIsMyList; // saves if current list has been imported or it's My List
    ListType m_listSelected; // e.g. MY_ANIMELIST or COMPLETED_ANIMELIST or FILTERED_ANIMELIST
    bool m_isFiltered;
    ListType m_listSelectedBeforeFiltering;
};

#endif