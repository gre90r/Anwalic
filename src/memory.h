#ifndef MEMORY_H
#define MEMORY_H

#include <list>
#include "anime.h"

/**
 * properly deletes objects created with new
 */
class Memory
{
public:
    Memory();

    /**
     * use everytime you need to call delete on something
     * @param ptr the pointer to delete
     */
    template< typename T >
    static void safeDelete( T*& ptr )
    {
        if ( ptr != nullptr )
        {
            delete ptr;
            ptr = nullptr;
        }
    }

    /**
     * DO NOT USE EXCEPT IN ANIMELIST DESTRUCTOR.\n
     * Deletes all anime pointers in an animelist
     * @param animeList list holding pointers to anime objects
     */
    static void safeDeleteAnimeList( std::list<Anime*>& animeList )
    {
        std::list<Anime*>::iterator it;
        for ( it = animeList.begin(); it != animeList.end(); ++it )
        {
            safeDelete( *it );
        }
    }
};

#endif // MEMORY_H
