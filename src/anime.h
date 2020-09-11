/*
 * File:        anime.h
 * Author:      gre90r
 * Created on:  May 05th, 2015
 * Last edit:   January 05th, 2017
 *
 * Description:
 *      contains name, current episode number, total episode number
 *      & url to stream of an anime
 */

#ifndef ANIME_H
#define ANIME_H

#include <string>

/**
 * the data it is all about. These objects
 * are being displayed & processed
 */
class Anime
{
public:
    /**
     * create object with the following default values:\n
     * name = "";\n
     * episode = 1;\n
     * totalEpsiodes = MAX_NUMBER_EPISODES;\n
     * url = "";
     */
    Anime();

    /**
     * set only anime name. everything else receives a default value
     * @param name Anime name
     */
    explicit Anime( std::string name ) ;

    /**
     * set anime name & current episode only.
     * @param name Anime name
     * @param episode current episode
     */
    explicit Anime( std::string name , unsigned int episode );

    /**
     * set anime name, current episode & total episodes only.
     * @param name Anime name
     * @param episode current episode
     * @param totalEpisodes max episodes
     */
    explicit Anime( std::string name, unsigned int episode,
                    unsigned int totalEpisodes );

    /**
     * set all attributes
     * @param name Anime name
     * @param episode current episode
     * @param totalEpisodes max epsiodes
     * @param url internet address of stream website
     */
    explicit Anime( std::string name, unsigned int episode,
                    unsigned int totalEpisodes, std::string url );

    // Getter
    std::string getName() const;
    unsigned int getCurrentEpisode() const;
    unsigned int getTotalEpisodes() const;
    std::string getUrl() const;

    /**
     * rules for proper anime name:\n
     * -> remove critical characters like ( and |.\n
     * -> anime name has a maximum length of 200 characters.
     * @param name animeName to validate
     */
    void setName(const std::string& name);

    /**
     * set current episode
     * @param episode current episode to set
     */
    void setEpisode(const unsigned int& episode);

    /**
     * set total episodes
     * @param totalEpisodes number to set as totalEpisodes
     */
    void setTotalEpisodes(const unsigned int& totalEpisodes);

    /**
     * set & validate url. must contain http:// or https:// prefix
     * @param url http internet address of a website
     */
    void setUrl( const std::string& url );

    /**
     * validate url. must contain http:// or https:// prefix
     * @param url to validate
     * @return true: if string is a URL<br>
     *         false: if it's not a http or https URL
     */
    static bool validateURL( const std::string& url );

    /*
     * increases episode count by one
     */
    void incEpisode();

    /*
     * decreases episode count by one
     */
    void decEpisode();

    /**
     * return following information from anime as string: name, current episode, total epsiodes
     * @return e.g. Clannad (Episode 12 / 26)
     */
    std::string toString() const;

    /**
     * perform alphabetical less operation. Clannad < Yuri. clannad < Yuri.
     * @param otherAnime anime object to compare with this object
     * @return true: if object's name is less than other Anime object's name<br>
     *         false: if other's Anime name is alphabetically less than this object's name
     */
    bool operator<( const Anime& otherAnime) const;

    /**
     * remove invalid characters in Anime name such as: ( and |<br>
     * if char '(' or ')' exists, it will be converted to '[' or ']' because anime name in listview is read until '(' appears.<br>
     * remove | because save file seperates attributes with this character
     * @param str will be checked if it contains '(' or ')'
     */
    static void validateAnimeName( std::string& str );

private:
    std::string m_name; // anime name
    unsigned int m_currentEpisode; // current episode
    unsigned int m_totalEpisodes; // total episodes
    std::string m_url; // internet address of stream website
};

#endif // ANIME_H
