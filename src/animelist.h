/**
 * File:        animelist.h
 * Author:      gre90r
 * Created on:  May 05th, 2015
 * Last Edited: March 2nd, 2018
 */

#ifndef ANIMELIST_H
#define ANIMELIST_H

#include "anime.h"
#include <string>
#include <list>


/**
 * container for anime objects. has CRUD functionality
 */
class Animelist
{
public:
    /**
     * creates an empty list by itself
     */
    Animelist();

    /**
     * create Animelist object with existing list
     * @param animeList list of Anime-objects
     */
    explicit Animelist( const std::list<Anime*>& animeList );
    
    /**
     * copy constructor is forbidden
     */
    Animelist( const Animelist& ) = delete;

    /**
     * destructor deletes list which contains objects created with new.
     * Do not delete list from the outside
     */
    ~Animelist();

    /**
     * assignment operator
     * @param other object to assign to current object
     * @return AnimeList& for cascading
     */
    Animelist& operator=( const Animelist& other );

    /**
     * assignment operator
     * @param other object to assign to current object
     * @return AnimeList& for cascading
     */
    Animelist& operator=( const std::list<Anime*>& other );

    /**
     * @return this animelist as std::list
     */
    std::list<Anime*> getAnimeList() const;

    /**
     * check by name if anime is already in list
     * @note DO NOT CHANGE TO ANIME POINTER!
     * @return true: if anime exists \n
     *         false: if anime does not exist
     */
    bool isInList( const Anime& ) const;

    /**
     * adds anime to list.\n
     * e.g. addAnime( newAnime( "Clannad" ) ); // destructor deletes this
     * @param anime anime object to add
     */
    void addAnime( Anime* anime );

    /**
     * sorts Anime objects by name ascending
     */
    void sort();

    /**
     * compare anime names alphabetically
     * !!! NOT OPTIMIZED !!!
     * @param lvalue anime object (const original pointer)
     * @param rvalue anime object (const original pointer)
     * @return true - if left anime name is less than right
     */
    static bool CompareAnimeObjectsBehindPointersAscending( Anime* const & lvalue, Anime* const & rvalue );

    /**
     * e.g. get string "Clannad" from Anime::toString output "Clannad (Episode 1 of 26)"
     * @param listItemString e.g. "Clannad (Episode 1 / 26)". needs opening bracket
     * @return anime name
     * @throw std::invalid_argument if listitem string format cannot be detected. searches for '(' to be valid
     */
    static std::string getAnimeNameFromToStringPhrase( const std::string& listItemString );

    /**
     * get anime object
     * @param animeName anime name in animelist
     * @return Anime pointer if successful. otherwise nullptr
     */
    Anime* getAnimeByName( const std::string& animeName ) const;

    /**
     * deletes anime from list
     * @param animeName anime to delete
     * @return true: successfully deleted
     *         false: anime name not found in list
     */
    bool deleteAnimeByName( const std::string& animeName );

    /**
     * check if animelist is empty
     * @return true: if no animes are in list\n
     *         false: there is at least one anime in the list
     */
    bool isEmpty() const;

    /**
     * removes pointer from list but does not delete memory
     * @note !!! ONLY USE METHOD IF YOU WANT TO MOVE A POINTER AND WANT TO USE IT SOMEWHERE ELSE !!!
     * @param animeName search string
     */
    void popOutByNameWithoutDeletingMemory( const std::string& animeName );


    /**
     * @return number of animes in list
     */
    size_t size() const;

    /**
     * automatically traverses through list. makes access to list like an array
     * @param index position of element in list
     * @throws std::out_of_range if parameter index is pointer to element out if list
     * @return anime object parameter index points to
     */
    Anime* operator[]( unsigned int index ) const;

    /**
     * clear list. only pops out all elements. does not delete memory
     */
    void clear();

private:
    /**
     * contains all anime objects
     */
    std::list<Anime*> m_animeList;

    /**
     * erases previous content of 'toInsert' and replaces
     * it with the content of 'toCopy'
     * @param toInsert will contain the content of 'toCopy'
     * @param toCopy content to copy in 'toInsert'
     */
    static void copyExternalAnimeList( std::list<Anime*>& toInsert, const std::list<Anime*>& toCopy );

};

#endif // ANIMELIST_H
