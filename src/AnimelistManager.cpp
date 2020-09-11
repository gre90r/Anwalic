#include "AnimelistManager.h"
#include "memory.h"
#include "errorview.h"


AnimelistManager::AnimelistManager(SaveLoad* saveload)
    : m_myAnimelist( new Animelist( saveload->load() ) ),
    m_completedAnimelist( new Animelist( saveload->loadCompletedAnimeList() ) ),
    m_filteredAnimeList( nullptr ),
    m_importedMyAnimeListPath( QString() ),
    m_importedCompletedListPath( QString() ),
    m_activeListIsMyList( true ),
    m_listSelected( MY_ANIMELIST ),
    m_isFiltered( false ),
    m_listSelectedBeforeFiltering( MY_ANIMELIST )
{
}


AnimelistManager::~AnimelistManager()
{
    Memory::safeDelete( m_myAnimelist );
    Memory::safeDelete( m_completedAnimelist );
    m_filteredAnimeList = nullptr; // objects are already deleted by m_animelist. calling delete here will crash program.
                                   // technically this should not be a memory leak.
}

Animelist* AnimelistManager::getMyAnimelist() const
{
    return m_myAnimelist;
}

void AnimelistManager::setMyAnimeList(Animelist al)
{
    Memory::safeDelete( m_myAnimelist );
    m_myAnimelist = new Animelist( al.getAnimeList() );
}

Animelist* AnimelistManager::getCompletedAnimelist() const
{
    return m_completedAnimelist;
}

void AnimelistManager::setCompletedAnimeList(Animelist cl)
{
    Memory::safeDelete( m_completedAnimelist );
    m_completedAnimelist = new Animelist( cl.getAnimeList() );
}

Animelist* AnimelistManager::getFilteredAnimelist() const
{
    return m_filteredAnimeList;
}

ListType AnimelistManager::getListSelectedBeforeFiltering() const
{
    return m_listSelectedBeforeFiltering;
}

QString AnimelistManager::getImportedPathMyAnimelist() const
{
    return m_importedMyAnimeListPath;
}

QString AnimelistManager::getImportedPathCompletedAnimelist() const
{
    return m_importedCompletedListPath;
}

void AnimelistManager::setImportedPathMyAnimelist(const QString& path)
{
    m_importedMyAnimeListPath = path;
}

void AnimelistManager::setImportedPathCompletedAnimelist(const QString& path)
{
    m_importedCompletedListPath = path;
}

bool AnimelistManager::isActiveListMyList() const
{
    return m_activeListIsMyList;
}

void AnimelistManager::moveAnimeToMyAnimeList(Anime* anime) const
{
    m_myAnimelist->addAnime( anime );

    // NOT deleting anime object memory. just pop out from list. NEVER delete here!
    m_completedAnimelist->popOutByNameWithoutDeletingMemory( anime->getName() );

    // if filtered list exists, delete there too
    if ( m_filteredAnimeList ) {
        m_filteredAnimeList->popOutByNameWithoutDeletingMemory( anime->getName() );
    }
}

void AnimelistManager::moveAnimeToCompletedAnimelist(Anime* anime) const
{
    // move to completed anime list
    m_completedAnimelist->addAnime( anime );

    // NOT deleting anime object memory. just pop out from list. NEVER DELETE here
    m_myAnimelist->popOutByNameWithoutDeletingMemory( anime->getName() );

    // if filtered list exists, delete there too
    if ( m_filteredAnimeList ) {
        m_filteredAnimeList->popOutByNameWithoutDeletingMemory( anime->getName() );
    }
}

size_t AnimelistManager::countAnimesInMyAnimeList() const
{
    return m_myAnimelist->size();
}

size_t AnimelistManager::countAnimesInCompletedAnimeList() const
{
    return m_completedAnimelist->size();
}

size_t AnimelistManager::countAnimesInFilteredAnimeList() const
{
    if ( m_filteredAnimeList ) {
        // if there is a filtered list
        return m_filteredAnimeList->size();
    }

    // if there's no filtered list
    return 0;
}

void AnimelistManager::passOriginalAnimePointersFromMyAnimeListToFilteredAnimeList()
{
    //Memory::safeDelete( m_filteredAnimeList );
    deleteFilteredAnimeList();
    m_filteredAnimeList = new Animelist();

    for ( unsigned int i = 0; i < m_myAnimelist->size(); i++ )
    {
        try
        {
            m_filteredAnimeList->addAnime( ( *m_myAnimelist )[i] ); // copies pointers only
        }
        catch ( const std::out_of_range& e )
        {
            ErrorView::internalErrorHandler( std::string( e.what() ) + std::string( "index out of range in: AnimelistManager::passOriginalAnimePointersFromMyAnimeListToFilteredAnimeList. Could not filter Animes properly. On button \"Show Started Animes Only\"" ) );
        }
        catch ( ... )
        {
            ErrorView::internalErrorHandler( "unknown error in: AnimelistManager::passOriginalAnimePointersFromMyAnimeListToFilteredAnimeList. On button \"Show Started Animes Only\"" );
        }
    }
}

void AnimelistManager::passOriginalAnimePointersFromCompletedAnimeListToFilteredAnimeList()
{
    deleteFilteredAnimeList();
    m_filteredAnimeList = new Animelist();

    for ( unsigned int i = 0; i < m_completedAnimelist->size(); i++ )
    {
        try
        {
            m_filteredAnimeList->addAnime( ( *m_completedAnimelist )[i] ); // copies pointers only
        }
        catch ( const std::out_of_range& e )
        {
            ErrorView::internalErrorHandler( std::string( e.what() ) + std::string( "index out of range in: AnimelistManager::passOriginalAnimePointersFromCompletedAnimeListToFilteredAnimeList. Could not filter Animes properly. When tried to filter list." ) );
        }
        catch ( ... )
        {
            ErrorView::internalErrorHandler( "unknown error in: AnimelistManager::passOriginalAnimePointersFromCompletedAnimeListToFilteredAnimeList. When tried to filter list." );
        }
    }
}

bool AnimelistManager::copyCurrentListToFilteredList()
{
    if ( listSelected() == MY_ANIMELIST )
    {
        // My Anime List is being filtered
        passOriginalAnimePointersFromMyAnimeListToFilteredAnimeList();
        m_listSelectedBeforeFiltering = MY_ANIMELIST;
    }
    else if ( listSelected() == COMPLETED_ANIMELIST )
    {
        // Completed Anime List is being filtered
        passOriginalAnimePointersFromCompletedAnimeListToFilteredAnimeList();
        m_listSelectedBeforeFiltering = COMPLETED_ANIMELIST;
    }
    else // that must be a filtered list. but filtering a filtered list is not allowed
    {
        ErrorView::internalErrorHandler( "internal error @AnwalicService::filterByMoviesOnly(). cannot filter filtered list." );
        return false;
    }
    return true;
}

void AnimelistManager::clearFilteredAnimeList()
{
    if ( m_filteredAnimeList ) {
        m_filteredAnimeList->clear();
        Memory::safeDelete( m_filteredAnimeList );
        //m_filteredAnimeList = nullptr; // delete filtered animelist like this. when you call delete on this the original list would be missing entries
    }

    m_isFiltered = false;
}

void AnimelistManager::deleteFilteredAnimeList()
{
    if ( m_filteredAnimeList ) {
        m_filteredAnimeList->clear(); // pop already deleted pointers to delete AnimeList* in next step
        Memory::safeDelete( m_filteredAnimeList );
    }
}

void AnimelistManager::selectMyList(SaveLoad* saveload)
{
    Memory::safeDelete( m_myAnimelist );
    Memory::safeDelete( m_completedAnimelist );
    m_myAnimelist = new Animelist( saveload->load( MY_ANIMELIST ) );
    m_completedAnimelist = new Animelist( saveload->loadCompletedAnimeList() );
    m_activeListIsMyList = true;
}

void AnimelistManager::selectAnotherList(SaveLoad* saveload, const QString& importedMyAnimeListPath, const QString& importedCompletedListPath)
{
    Memory::safeDelete( m_myAnimelist );
    Memory::safeDelete( m_completedAnimelist );
    m_myAnimelist = new Animelist( saveload->load( MY_ANIMELIST ) );
    m_completedAnimelist = new Animelist( saveload->loadCompletedAnimeList() );
    m_importedMyAnimeListPath = importedMyAnimeListPath;
    m_importedCompletedListPath = importedCompletedListPath;
    m_activeListIsMyList = false;
}

ListType AnimelistManager::listSelected() const
{
    switch ( m_listSelected )
    {
        // break out of switch if it's one of these cases
        case MY_ANIMELIST:
        case COMPLETED_ANIMELIST:
        case FILTERED_ANIMELIST:
            break;

        default:
            //throw std::exception( "fatal error: invalid program state. There is no list selected." );
            throw std::exception();
    }

    return m_listSelected;
}

void AnimelistManager::setListSelected(const ListType& listType)
{
    m_listSelected = listType;
}

void AnimelistManager::setListIsFiltered(const bool& state)
{
    m_isFiltered = state;
}
