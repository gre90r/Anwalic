#include "InternetUtilities.h"
#include "stringsEN.h"
#include "errorview.h"
#include <QDesktopServices>
#include <QUrl>

void InternetUtilities::openUrl(const char* url)
{
    if ( !( QDesktopServices::openUrl( QUrl( url ) ) ) )
    {
        ErrorView::runtimeErrorHandler( std::string( STR_FAILED_TO_OPEN_URL_YOU_TRIED_TO_ACCESS )
            + ":\n\n" + url );
    }
}
