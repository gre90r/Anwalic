#include "FilterShowMovies.h"


FilterShowMovies::FilterShowMovies( MainWindow* mw, AnimelistManager* alm, AnwalicService* svc )
    : FilterAnimelist( mw, alm, svc )
{
}


FilterShowMovies::~FilterShowMovies()
{
    // DO NOT DELETE POINTERS
}

QStringList FilterShowMovies::filterOperation()
{
    // detect animes which will be removed from filtered list -> filtered_list = current_list
    QStringList animesToPop = QStringList(); // all animes in there will be popped out in m_filteredAnimeList
    for ( unsigned int i = 0; i < this->m_alm->getFilteredAnimelist()->size(); i++ )
    {
        // remove animes which do not match the filter
        if ( ( *this->m_alm->getFilteredAnimelist() )[i]->getTotalEpisodes() > 1 )
        {
            animesToPop.push_back( ( *this->m_alm->getFilteredAnimelist() )[i]->getName().c_str() );
        }
    }

    return animesToPop;
}
