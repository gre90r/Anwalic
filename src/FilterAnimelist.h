#ifndef FILTER_ANIMELIST
#define FILTER_ANIMELIST

#include "AnwalicService.h"

class AnimelistManager;
class MainWindow;

/**
 * Abstract Base Class for List Filtering.
 * Handles Everything needed: En-/Disabling Ui Elements, ...
 * 
 * Usage:
 *      create new filter:
 *          Inherit and only Override 'filterOperation'.
 *      apply filter:
 *          instanciate the derived class and call "applyFilter()"
 *          method
 *      remove filter:
 *          is not implemented because the button "Clear Filter"
 *          handles this. so you just instantiate the class, call
 *          method "applyFilter" and then you can immediatly remove
 *          this class instantiation
 */
class FilterAnimelist
{
public:
    FilterAnimelist() = delete;

    /**
     * give access to what it needs: MainWindow Ui Elements,
     * Animelists and give functionality from AnwalicService
     * @param mw main window which is displaying the animelist
     * @param alm contains all animelists
     * @param svc program functionalities which e.g. alters animelists
     */
    FilterAnimelist( MainWindow* mw, AnimelistManager* alm, AnwalicService* svc );

    /**
     * memory cleanup
     */
    virtual ~FilterAnimelist();

    /**
     * remove filter and show previous animelist
     */
    // no need to clear filter since the button "Clear Filter"
    // handles this
    //void clearFilter();

    /**
     * apply filter on current animelist.
     */
    void applyFilter();

protected:
    /**************/
    /* ATTRIBUTES */
    /**************/
    /**
    * contains all lists. needed to set filtered list
    * and switch back to unfiltered list
    */
    AnimelistManager* m_alm;

    /**
     * if any error occured which prevents the filtering this flag is set
     */
    bool m_error;

    /**
     * GUI elements to access buttons
     */
    MainWindow* m_mw;

    /**
     * operations on animelist
     */
    AnwalicService* m_svc;

    /***********/
    /* METHODS */
    /***********/
    /**
     * filtering algorithm
     * @note override this
     * @return name of animes to remove
     */
    virtual QStringList filterOperation() = 0;

private:
    /***********/
    /* METHODS */
    /***********/
    /**
     * copy the list which shall be filtered.
     */
    void copyCurrentListToFilteredList();

    /**
     * disable Ui Elements in MainWindow which should not
     * be used while list is filtered. e.g apply another
     * filter is not allowed.
     */
    void disableUiElements();

    /**
     * enable Ui Elements which have previously been disabled by method disableUiElements
     */
    // not needed since "Clear Filter" button handles this
    //void enableUiElements();
};

#endif