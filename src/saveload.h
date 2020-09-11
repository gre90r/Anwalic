/**
 * File:        saveload.h
 * Author:      gre90r
 * Created on:  May 05th, 2015
 *
 * Description:
 *      handles file input/output of animelist save file.
 *      includes writing error files.
 */

#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "anime.h"
#include <string>
#include <list>
#include <fstream>
#include <QString>
#include "ListType.h"

/**
 * saves & loads animelists. is also used to exchange animelists e.g.
 * when you import a list.\n
 * you can simply reload or exchange lists with this:\n
 * Memory::safeDelete( m_saveload );\n
 * m_saveload = new SaveLoad( myAnimelistFilepath, completedAnimelistFilepath );\n
 */
class SaveLoad
{
public:
    /**
     * forbidden default constructor
     */
    SaveLoad() = delete;

    /**
     * sets filepaths for my anime list and completed anime list.
     * @note does not load lists. you have to explicitly call:\n
     * m_animeList = new Animelist( saveload->load() );\n
     * and m_completedAnimeList = new Animelist( saveload->loadCompletedAnimeList() );
     * @param filepathMyAnimeList filepath of my animelist save file
     * @param filepathCompletedAnimeList filepath of completed animelist save file
     */
    SaveLoad( const std::string& filepathMyAnimeList, const std::string& filepathCompletedAnimeList );

    /**
     * destructor
     */
    ~SaveLoad();

    /**
     * forbid copy constructor
     */
    SaveLoad( const SaveLoad& ) = delete;

    /**
     * forbid assignment operator
     */
    SaveLoad& operator=( SaveLoad& ) = delete;

    /**
     * read anime list savefile.\n
     * if called without arguments it loads My Anime List by default.
     * @note NEVER MAKE STATIC !!\n
     *       Should be called without filepath argument because the class holds filepaths and uses them.\n
     *       When called with filePath you can use the total path to the file. Be careful when
     *       calling loadCompletedAnimeList() method. There you must pass the exact argument just as in
     *       this method.
     * @param listType decides if My Anime List (previously called: now watching anime list) or completed anime list has to be loaded.
     * @param filePathMyAnimeList path to My Anime List file
     * @throw std::invalid_argument \n - if file could not be found/opened
     *                                 - if string to int cast fails on episode number
     * @return on success: list of Animes saved in file.\n
     *         if fails: returns empty list on read error
     */
    std::list<Anime*> load( ListType listType = MY_ANIMELIST, std::string filePathMyAnimeList = "" );

    /**
     * loads my animelist from file
     * @return my animelist as list object
     */
    std::list<Anime*> loadMyAnimelist();

    /**
     * Should be called without arguments because the class holds filepaths from where to load.
     * If you pass a filePath argument when calling this method make sure you DO NOT pass
     * the path to the completed list. You HAVE TO pass the filePath of my anime list.
     * The method automatically inserts the _completed suffix
     * @note never make static
     * @param filePathMyAnimeList path to completed animelist. by default takes the
     * @return completed animelist as list object
     */
    std::list<Anime*> loadCompletedAnimeList( std::string filePathMyAnimeList = "" );

    /**
     * write anime list & completed anime list to a save file. writes
     * one save file for my anime list and one file for completed anime list
     * @note never make static
     * @param myAnimeList My Anime List list object
     * @param completedAnimeList Completed Anime List list object
     * @param filepathMyAnimeList path to my animelist file. by default it takes the my anime list filepath
     */
    void save( const std::list<Anime*>& myAnimeList,
               const std::list<Anime*>& completedAnimeList,
               std::string filepathMyAnimeList = "" );

    /**
     * writes error message to a specific error file.
     * @param errorMsg error message with technical details
     */
    static void writeErrorFile( const std::string& errorMsg );

    /**
     * attach completed suffix at end of filepath.\n
     * e.g. make "/home/gregor/gregor_completed.anl" from "/home/gregor/gregor.anl"
     * @param filepath where to insert suffix
     */
    static void insertCompletedSuffix( std::string& filepath );

    /**
     * attach completed suffix at end of filepath.\n
     * e.g. make "/home/gregor/gregor_completed.anl" from "/home/gregor/gregor.anl"
     * @param filepath where to insert suffix
     */
    static void insertCompletedSuffix( QString& filepath );

private:
    const std::string m_filepathMyAnimeList;
    const std::string m_filepathCompletedAnimeList;

    /**
     * write completed anime list to save file.
     * by default takes m_filepathCompletedAnimeList.
     * @note never make static
     * @param animeList the list to save
     * @param filepath location to save the parameter animeList. by default takes m_filepathCompletedAnimeList
     */
    void saveCompletedAnimeList( const std::list<Anime*>& animeList, std::string filepath = "" );

};

#endif // FILEIO_H
