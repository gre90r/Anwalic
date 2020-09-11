#ifndef FILTER_HIDEMOVIES
#define FILTER_HIDEMOVIES

#include "FilterAnimelist.h"

/**
 * Hides Animes which have Total Episodes = 1
 */
class FilterHideMovies : public FilterAnimelist
{
public:
    FilterHideMovies() = delete;
    FilterHideMovies( MainWindow* mw, AnimelistManager* alm, AnwalicService* svc );
    ~FilterHideMovies();

protected:
    QStringList filterOperation() override;
};

#endif