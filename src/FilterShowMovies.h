#ifndef FILTER_SHOWMOVIES
#define FILTER_SHOWMOVIES

#include "FilterAnimelist.h"

/**
 * Filter Current List to Show only animes with
 * Total Episodes = 1
 */
class FilterShowMovies : public FilterAnimelist
{
public:
    FilterShowMovies() = delete;
    FilterShowMovies( MainWindow* mw, AnimelistManager* alm, AnwalicService* svc );
    ~FilterShowMovies();

protected:
    QStringList filterOperation() override;
};

#endif