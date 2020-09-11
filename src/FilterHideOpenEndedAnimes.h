#ifndef FILTER_HIDEOPENENDEDANIMES
#define FILTER_HIDEOPENENDEDANIMES

#include "FilterAnimelist.h"

/**
 * Hide Animes which have not set Total Episodes.
 * Animes like "Naruto (Episode 1 / ??)" are hidden
 */
class FilterHideOpenEndedAnimes : public FilterAnimelist
{
public:
    FilterHideOpenEndedAnimes() = delete;
    FilterHideOpenEndedAnimes( MainWindow* mw, AnimelistManager* alm, AnwalicService* svc );
    ~FilterHideOpenEndedAnimes();

protected:
    QStringList filterOperation() override;
};

#endif