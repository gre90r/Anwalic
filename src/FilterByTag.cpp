#include "FilterByTag.h"
#include "mainwindow.h"
#include <boost/algorithm/string/find.hpp>


FilterByTag::FilterByTag( MainWindow* mw, AnimelistManager* alm, AnwalicService* svc )
    : FilterAnimelist( mw, alm, svc )
{
    // the user is shown a dialog window where he types in the filter word
    std::string tag = mw->userDialogFilterByTag();
    if ( tag.empty() ) {
        // user clicked Cancel or entered nothing
        m_error = true;
        m_tag = "";
        return;
    }

    // user clicked OK and entered something
    m_error = false; // it already is set to false, but that makes the code better to read
    m_tag = tag;
}

FilterByTag::~FilterByTag()
{
    // DO NOT DELETE POINTERS
}

QStringList FilterByTag::filterOperation()
{
    // detect animes which will be removed from filtered list -> filtered_list = current_list
    QStringList animesToPop = QStringList(); // all animes in there will be popped out in m_filteredAnimeList
    for ( unsigned int i = 0;
        i < this->m_alm->getFilteredAnimelist()->size();
        i++ )
    {
        // remove animes which do not match the filter
        std::string animeName = ( *this->m_alm->getFilteredAnimelist() )[i]->getName();
        if ( !boost::ifind_first( animeName, m_tag ) ) // remove animes which do not contain the tag
        {
            animesToPop.push_back( ( *this->m_alm->getFilteredAnimelist() )[i]->getName().c_str() );
        }
    }

    return animesToPop;
}
