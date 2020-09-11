#include "saveload.h"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include "errorview.h"
#include "globals.h"
#include "memory.h"
#include <QDate>
#include <QTime>

SaveLoad::SaveLoad( const std::string& filepathMyAnimeList, const std::string& filepathCompletedAnimeList )
    : m_filepathMyAnimeList( filepathMyAnimeList ),
      m_filepathCompletedAnimeList( filepathCompletedAnimeList )
{
}

SaveLoad::~SaveLoad()
{
}

std::list<Anime*> SaveLoad::load( ListType listType, std::string filePath )
{
    // check if either my animelist or completed animelist has been selected.
    if ( !( ( listType == MY_ANIMELIST ) || ( listType == COMPLETED_ANIMELIST ) ) ) {
        // throw if filtered animelist is selected
        throw std::invalid_argument( "internal error: @SaveLoad::load(). Wrong function invokation! Expected list type MY_ANIMELIST or COMPLETED_ANIMELIST." );
    }

    std::string filePathCompleted = "";
    if ( filePath == "" ) {
        filePath = m_filepathMyAnimeList;
        filePathCompleted = m_filepathCompletedAnimeList;
    }
    else {
        /* keep now watching list file path */
        // only set completed list file path
        filePathCompleted = filePath;
        insertCompletedSuffix( filePathCompleted );
    }

    std::ifstream ifStream( ( listType == MY_ANIMELIST )
                              ? filePath
                              : filePathCompleted,
                              std::ios::in );
    if ( ( !ifStream ) && ( listType == COMPLETED_ANIMELIST ) ) {
        return std::list<Anime*>(); // return empty list if no completed anime list exists
    }

    if ( !ifStream ) {
        std::cout << "First program start detected! Do not load anything.\n";
        return std::list<Anime*>(); // empty list
    }

    std::list<Anime*> animeList;
    std::string buffer = "";
    std::string animeName = "";
    unsigned int currentEpisode = 0;
    unsigned int totaleEpisodes = 0;
    std::string url = "";

    // LOAD CORE. one iteration reads a single Anime object.
    // ends if all animes are read
    while( ifStream.peek() != EOF ) // !m_ioStream.eof()
    {
        // read anime name
        std::getline( ifStream, animeName, '|' );

        // read current episode number
        std::getline( ifStream, buffer, '|' );
        try {
            currentEpisode = std::stoi( buffer );
        }
        catch( const std::exception& e ) {
            ErrorView::runtimeErrorHandler( std::string( e.what() ) + std::string( "\n" ) +
                                            std::string( "runtime error: failed to load current episode of " ) +
                                            std::string( animeName ) );
            break;
        }

        // read total episode number
        std::getline( ifStream, buffer, '|' );
        try {
            totaleEpisodes = std::stoi( buffer );
        }
        catch ( const std::exception& e ) {
            ErrorView::runtimeErrorHandler( std::string( e.what( ) ) + std::string( "\n" ) + 
                                            std::string( "runtime error: failed to load total episode of " ) +
                                            std::string( animeName ) );
            break;
        }

        // read url (till '\n' character)
        std::getline( ifStream, url );

        animeList.push_back( new Anime( animeName, currentEpisode, totaleEpisodes, url ) );
    }

    if ( ifStream.eof() ) { // if end of file reached without errors 
        ifStream.close();
        return animeList; // success
    }

    // else: error occured
    ifStream.close();
    Memory::safeDeleteAnimeList( animeList );
    throw std::invalid_argument( "File read error! Cannot read episode number." ); // stoi conversion failed
}

std::list<Anime*> SaveLoad::loadMyAnimelist()
{
    return load( MY_ANIMELIST ); // will take filepath m_filepathMyAnimeList by default
}


std::list<Anime*> SaveLoad::loadCompletedAnimeList( std::string filePathMyAnimeList )
{
    return load( COMPLETED_ANIMELIST, filePathMyAnimeList );
}


void SaveLoad::save( const std::list<Anime*>& myAnimeList,
                     const std::list<Anime*>& completedAnimeList,
                     std::string filepathMyAnimeList )
{
    if ( filepathMyAnimeList == "" ) filepathMyAnimeList = m_filepathMyAnimeList; // take default filename if not specified

    std::ofstream ofStream( filepathMyAnimeList.c_str(), std::ios::out | std::ios::trunc );
    if ( !ofStream ) throw std::invalid_argument( "File for my animelist could not be opened/created!" );

    std::list<Anime*>::const_iterator cIt;
    std::stringstream wholeList;

    // one iteration writes one Anime to file
    for ( cIt = myAnimeList.cbegin(); cIt != myAnimeList.cend(); ++cIt )
    {
        wholeList << (*cIt)->getName() << "|";
        wholeList << (*cIt)->getCurrentEpisode() << "|";
        wholeList << (*cIt)->getTotalEpisodes() << "|";
        wholeList << (*cIt)->getUrl() << "\n";
    }

    ofStream << wholeList.str();
    ofStream.close();

    saveCompletedAnimeList( completedAnimeList, filepathMyAnimeList );
}


void SaveLoad::saveCompletedAnimeList( const std::list<Anime*>& animeList, std::string filepath )
{
    if ( filepath == "" )
        filepath = m_filepathCompletedAnimeList; // take default filename if not specified
    else
        insertCompletedSuffix( filepath );

    std::ofstream ofStream( filepath.c_str(), std::ios::out | std::ios::trunc );
    if ( !ofStream ) throw std::invalid_argument( "File for completed animes could not be opened/created!" );

    std::list<Anime*>::const_iterator cIt;
    std::stringstream wholeList;

    // one iteration writes one Anime to file
    for ( cIt = animeList.cbegin(); cIt != animeList.cend(); ++cIt )
    {
        wholeList << (*cIt)->getName() << "|";
        wholeList << (*cIt)->getCurrentEpisode() << "|";
        wholeList << (*cIt)->getTotalEpisodes() << "|";
        wholeList << (*cIt)->getUrl() << "\n";
    }

    ofStream << wholeList.str();
    ofStream.close();
}


void SaveLoad::writeErrorFile( const std::string& errorMsg )
{
    std::string fileName = ERROR_FILENAME;
    std::ofstream outStream( fileName.c_str(), std::ios::out | std::ios::app );
    if ( !outStream )
    {
        std::cerr << "error writing error file. wtf";
        ErrorView::showErrorPopup( nullptr, "internal error: failed to write error file. wtf /(°.°)/" );
        return;
    }
    outStream << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << "\n";
    outStream << PROGRAM_NAME << " " << PROGRAM_VERSION << "\n";
    outStream << QDate::currentDate().toString().toStdString() << ", ";
        QTime now( QTime::currentTime() );
    outStream << now.hour() << ":" << now.minute() << ":" << now.second()  << "\n" << "\n";
    outStream << errorMsg;
    outStream << "\n" << "\n";
    outStream << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << "\n";
}


void SaveLoad::insertCompletedSuffix( std::string& filepath )
{
    filepath.insert( filepath.size() - std::string( ".anl" ).size(), "_completed" );
}


void SaveLoad::insertCompletedSuffix( QString& filepath )
{
    filepath.insert( filepath.size() - std::string( ".anl" ).size(), "_completed" );
}
