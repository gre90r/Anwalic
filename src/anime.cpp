#include "anime.h"
#include <iostream>
#include <sstream>
#include "globals.h"
#include "StringUtils.h"
#include <boost/algorithm/string.hpp>


Anime::Anime()
    : m_name( "" ),
      m_currentEpisode( 1 ),
      m_totalEpisodes( MAX_NUMBER_EPISODES ),
      m_url( "" )
{
}


Anime::Anime( std::string name )
    : m_currentEpisode( 1 ),
      m_totalEpisodes( MAX_NUMBER_EPISODES ),
      m_url( "" )
{
    StringUtils::toUpper( name );
    setName( name );
}


Anime::Anime( std::string name, unsigned int episode )
    : m_totalEpisodes( MAX_NUMBER_EPISODES ),
      m_url( "" )

{
    StringUtils::toUpper( name );
    setName( name );
    setEpisode( episode );
}


Anime::Anime( std::string name, unsigned int episode,
              unsigned int totalEpisodes )
    : m_url( "" )
{
    StringUtils::toUpper( name );
    setName( name );
    setEpisode( episode );
    setTotalEpisodes( totalEpisodes );
}


Anime::Anime(std::string name, unsigned int episode,
             unsigned int totalEpisodes, std::string url)
{
    StringUtils::toUpper( name );
    setName( name );
    setEpisode( episode );
    setTotalEpisodes( totalEpisodes );
    setUrl( url ); // validates URL
}

std::string Anime::getName() const
{
    return m_name;
}

unsigned Anime::getCurrentEpisode() const
{
    return m_currentEpisode;
}

unsigned Anime::getTotalEpisodes() const
{
    return m_totalEpisodes;
}

std::string Anime::getUrl() const
{
    return m_url;
}


void Anime::incEpisode()
{
    if ( m_currentEpisode < m_totalEpisodes ) {
        ++m_currentEpisode;
    }
}


void Anime::decEpisode()
{
    if ( m_currentEpisode > 1 ) {
        --m_currentEpisode;
    }
}


void Anime::setName( const std::string& name)
{
    std::string nameToValidate = name.substr( 0, MAX_ANIME_NAME_LENGTH );
    validateAnimeName( nameToValidate );
    m_name = nameToValidate;
}


void Anime::setEpisode(const unsigned int& episode)
{
    if ( episode == 0 )
    {
        m_currentEpisode = 1;
        return;
    }
    if ( episode > MAX_NUMBER_EPISODES ) // in case of negative numbers
    {
        m_currentEpisode = 1;
        return;
    }
    m_currentEpisode = episode;
}

void Anime::setTotalEpisodes(const unsigned int& totalEpisodes)
{
    if ( totalEpisodes == 0 )
    {
        m_totalEpisodes = MAX_NUMBER_EPISODES;
        return;
    }
    if ( totalEpisodes > MAX_NUMBER_EPISODES ) // in case of negative numbers
    {
        m_totalEpisodes = MAX_NUMBER_EPISODES;
        return;
    }
    m_totalEpisodes = totalEpisodes;
}

void Anime::setUrl( const std::string& url )
{
    std::string trimmedUrl = url;
    boost::trim( trimmedUrl );
    if ( validateURL( trimmedUrl ) )
        m_url = trimmedUrl;
    else
        m_url = "";
}


bool Anime::validateURL( const std::string& url)
{
    if ( url.empty() ) return false;

    // detect http:// or https:// prefix
    if ( url.find( "http://" ) == 0 ) return true; // if the "h" from http:// is the first character
    if ( url.find( "https://" ) == 0 ) return true;

    // http:// and https:// not detected
    std::cerr << "invalid url: no http:// or https:// prefix found" << std::endl;
    return false;
}


std::string Anime::toString() const
{
    std::stringstream ss;

    ss << m_name;
    ss << " (Episode " << m_currentEpisode << " / ";
    if ( m_totalEpisodes == MAX_NUMBER_EPISODES ) // this is true if max episodes is unknown
        ss << "??";
    else
        ss << m_totalEpisodes;
    ss << ")";

    return ss.str();
}


bool Anime::operator<( const Anime& other ) const
{
    if ( StringUtils::isUppercase( m_name )
        && StringUtils::isUppercase( other.getName() ) )
    {
        return m_name < other.getName();
    }

    if ( StringUtils::isLowercase( other.getName() ) )
    {
        // convert this.m_name to lowercase, too
        std::string thisNameLower = m_name;
        StringUtils::toLower( thisNameLower );
        return thisNameLower < other.getName();
    }

    if ( StringUtils::isUppercase( other.getName() ) )
    {
        // convert this.m_name to uppercase, too
        std::string thisNameUpper = m_name;
        StringUtils::toUpper( thisNameUpper );
        return thisNameUpper < other.getName();
    }

    return m_name < other.getName();
}


void Anime::validateAnimeName( std::string& str )
{
    boost::trim( str );
    if ( StringUtils::isLowercase( str ) ) StringUtils::toUpper( str );
    for ( size_t i = 0; i < str.size( ); i++ )
    {
        if ( str.at( i ) == '(' ) str[i] = '['; // conflict, because getAnimeByName() reads until '('
        if ( str.at( i ) == ')' ) str[i] = ']';
        if ( str.at( i ) == '|' ) str[i] = '/'; // conflict, because listfile-reads are until '|' sign
    }
}