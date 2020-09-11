#ifndef FILTER_SHOWSTARTEDANIMES
#define FILTER_SHOWSTARTEDANIMES

#include "FilterAnimelist.h"

/**
 * Show Animes which have Current Episode greater 1
 */
class FilterShowStartedAnimes : public FilterAnimelist
{
public:
    FilterShowStartedAnimes() = delete;
    FilterShowStartedAnimes( MainWindow* mw, AnimelistManager* alm, AnwalicService* svc );
    ~FilterShowStartedAnimes();

protected:
    QStringList filterOperation() override;
};

#endif