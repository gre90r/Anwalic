/**
 * @author gre90r
 */

#ifndef ANIMELISTVIEWHELPER_H
#define ANIMELISTVIEWHELPER_H

#include <QStringListModel>
#include "animelist.h"


/**
 * prepares StringListModel
 */
class AnimeListViewHelper
{
public:

    /**
     * initialize to null
     */
    AnimeListViewHelper();


    /**
     * builds StringListModel with parameter _animelist
     * @param _animelist StringListModel will be build with this list
     */
    explicit AnimeListViewHelper( const Animelist& _animelist );


    /**
     * clean up
     */
    ~AnimeListViewHelper();
 

    /**
    * @return string list model of animelist
    */
    QStringListModel* getAnimelistStringListModel() const;

    /**
    * sets QStringListModel with Anime series information from m_animeList
    * @param _list information to fill the StringListModel with
    */
    void setStringListModelFromAnimelist( const Animelist& _list );

private:

    /**
    * each entry contains Anime name & episode as string -> Clannad (Episode 12 of 26).
    * necessary to set ListView.
    */
    QStringListModel* m_animelistStringListModel;

};

#endif