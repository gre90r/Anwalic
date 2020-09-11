#include "FilterAnimelist.h"
#include "mainwindow.h"


FilterAnimelist::FilterAnimelist(MainWindow* mw, AnimelistManager* alm, AnwalicService* svc)
    : m_alm(alm),
    m_error(false),
    m_mw(mw),
    m_svc(svc)
{
}

FilterAnimelist::~FilterAnimelist()
{
    // DO NOT DELETE POINTERS SINCE THEY ARE
    // BORROWED FROM MAINWINDOW
}

void FilterAnimelist::applyFilter()
{
    // in case the user clicked Cancel in a dialog
    // go out before anything happens.
    if ( m_error ) {
        return;
    }

    this->disableUiElements();
    this->copyCurrentListToFilteredList();
    if ( m_error ) { // if there was an error while preparing to apply filter
        return;
    }

    // filter operation from derived class
    QStringList animesToPop = this->filterOperation(); 
    // remove animes which do not match the filter
    m_svc->popDetectedAnimesInFilteredListAndSetFilteredState( animesToPop );
    
    // display filtered list 
    m_mw->refreshAnimeList();
}

void FilterAnimelist::copyCurrentListToFilteredList()
{
    // copy pointers from My Anime List -> m_filteredAnimeList.
    // make filteredAnimelist = myAnimelist
    if ( !m_svc->copyCurrentListToFilteredList() ) {
        m_error = true;
    }
}

void FilterAnimelist::disableUiElements()
{
    m_mw->prepareFilteredState(); // disables buttons and sets lastUsedListItemIndex
}
