#include "FilterShowStartedAnimes.h"
#include "mainwindow.h"
#include "errorview.h"


FilterShowStartedAnimes::FilterShowStartedAnimes( MainWindow* mw, AnimelistManager* alm, AnwalicService* svc )
    : FilterAnimelist( mw, alm, svc )
{
}

FilterShowStartedAnimes::~FilterShowStartedAnimes()
{
    // DO NOT DELETE POINTERS
}

QStringList FilterShowStartedAnimes::filterOperation()
{
    // check worst case: completed animes is selected. button should be disabled when function is called
    if ( m_svc->listSelected() == COMPLETED_ANIMELIST ) { // not allowed when completed animes is selected
        m_mw->m_isFatalError = true;
        ErrorView::internalErrorHandler( "internal error @MainWindow::on_btnShowStartedAnimesOnly_clicked. it should be impossible to click \"Show Started Animes Only\" button while in Completed Animes state" );
        return QStringList();
    }

    // detect animes which will be removed from filtered list -> filtered_list = current_list
    QStringList animesToPop = QStringList(); // all animes in there will be popped out in m_filteredAnimeList
    for ( unsigned int i = 0; i < this->m_alm->getFilteredAnimelist()->size(); i++ )
    {
        // remove animes which do not match the filter
        if ( ( *this->m_alm->getFilteredAnimelist() )[i]->getCurrentEpisode() <= 1 )
        {
            animesToPop.push_back( ( *this->m_alm->getFilteredAnimelist() )[i]->getName().c_str() );
        }
    }

    return animesToPop;
}
