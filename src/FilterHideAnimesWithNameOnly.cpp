#include "FilterHideAnimesWithNameOnly.h"
#include "globals.h"


FilterHideAnimesWithNameOnly::FilterHideAnimesWithNameOnly( MainWindow* mw, AnimelistManager* alm, AnwalicService* svc )
    : FilterAnimelist( mw, alm, svc )
{
}

FilterHideAnimesWithNameOnly::~FilterHideAnimesWithNameOnly()
{
    // DO NOT DELETE POINTERS
}

QStringList FilterHideAnimesWithNameOnly::filterOperation()
{
    // detect animes which will be removed from filtered list -> filtered_list = current_list
    QStringList animesToPop = QStringList(); // all animes in there will be popped out in m_filteredAnimeList
    for ( unsigned int i = 0; i < this->m_alm->getFilteredAnimelist()->size(); i++ )
    {
        // remove animes which do not match the filter
        if ( !( *this->m_alm->getFilteredAnimelist() )[i]->getName().empty()
            && ( *this->m_alm->getFilteredAnimelist() )[i]->getCurrentEpisode() == 1
            && ( *this->m_alm->getFilteredAnimelist() )[i]->getTotalEpisodes() == MAX_NUMBER_EPISODES
            && ( *this->m_alm->getFilteredAnimelist() )[i]->getUrl().empty()

            )
        {
            animesToPop.push_back( ( *this->m_alm->getFilteredAnimelist() )[i]->getName().c_str() );
        }
    }

    return animesToPop;
}
