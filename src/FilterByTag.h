#ifndef FILTER_BYTAG
#define FILTER_BYTAG

#include "FilterAnimelist.h"

/**
 * Filter by a word the user enters
 */
class FilterByTag : public FilterAnimelist
{
public:
    FilterByTag() = delete;
    FilterByTag( MainWindow* mw, AnimelistManager* alm, AnwalicService* svc );
    ~FilterByTag();

protected:
    QStringList filterOperation() override;

private:
    std::string m_tag;
};

#endif