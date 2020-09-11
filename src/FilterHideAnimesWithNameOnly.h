#ifndef FILTER_HIDEANIMESWITHNAMEONLY
#define FILTER_HIDEANIMESWITHNAMEONLY

#include "FilterAnimelist.h"

/**
 * Hide Animes which only specified the anime name. so all other
 * information are missing: URL, Total Episodes. Current Episode = 1
 */
class FilterHideAnimesWithNameOnly : public FilterAnimelist
{
public:
    FilterHideAnimesWithNameOnly() = delete;
    FilterHideAnimesWithNameOnly( MainWindow* mw, AnimelistManager* alm, AnwalicService* svc );
    ~FilterHideAnimesWithNameOnly();

protected:
    QStringList filterOperation() override;
};

#endif