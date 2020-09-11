#ifndef FILTER_SHOWOPENENDEDANIMES
#define FILTER_SHOWOPENENDEDANIMES

#include "FilterAnimelist.h"

/**
 * only display animes which have not set
 * Total Episodes. So only displays these kinds ->
 * "One Piece (Episode 1 / ??)"
 */
class FilterShowOpenEndedAnimes : public FilterAnimelist
{
public:
    FilterShowOpenEndedAnimes() = delete;
    FilterShowOpenEndedAnimes( MainWindow* mw, AnimelistManager* alm, AnwalicService* svc );
    ~FilterShowOpenEndedAnimes();

protected:
    QStringList filterOperation() override;
};

#endif