#include "AnimeListViewHelper.h"
#include "memory.h"


AnimeListViewHelper::AnimeListViewHelper()
    : m_animelistStringListModel( nullptr )
{
}


AnimeListViewHelper::AnimeListViewHelper(const Animelist& _animelist)
    : m_animelistStringListModel( new QStringListModel )
{
    setStringListModelFromAnimelist( _animelist );
}


AnimeListViewHelper::~AnimeListViewHelper()
{
    Memory::safeDelete( m_animelistStringListModel );
}


void AnimeListViewHelper::setStringListModelFromAnimelist( const Animelist& _animeList )
{
    if ( m_animelistStringListModel == nullptr )
    {
        m_animelistStringListModel = new QStringListModel;
    }
    QStringList stringList;
    std::list<Anime*> list( _animeList.getAnimeList() );

    std::list<Anime*>::const_iterator constIt;
    for ( constIt = list.cbegin();
        constIt != list.end();
        ++constIt )
    {
        stringList.append( QString( ( **constIt ).toString().c_str() ) );
    }

    m_animelistStringListModel->setStringList( stringList );
}


QStringListModel* AnimeListViewHelper::getAnimelistStringListModel() const
{
    return m_animelistStringListModel;
}
