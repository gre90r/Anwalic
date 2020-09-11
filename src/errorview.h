#ifndef ERRORVIEW_H
#define ERRORVIEW_H

#include <string>
#include <QWidget>

/**
 * handles displaying errors to user and writing log files.
 * these methods are normally called when an error has been
 * thrown.\n
 * \n
 * when an error occurs you normally want to call internalErrorHandler() or runtimeErrorHandler().\n
 * -> displays error message to user\n
 * -----> calls one of the show... methods. e.g. showErrorPopup()\n
 * -> writes error file\n
 * -> writes error to console\n
 * \n
 *      when to use what\n
 * \n     
 * showPopup: when displaying a message. No error occured. Just display a message.\n
 * showErrorPopup: when it is needed to inform the user. Display technical details (error message)\n
 * showStandardInternalErrorPopup: when it is needed to inform the user. Do not tell technical details\n
 * internalErrorHandler: when error is caused by a programming mistake. informs user about a mistake but does not tell details.\n
 * runtimeErrorHandler: when error is NOT caused by a programming mistake.
 *                      program itself caused an error. e.g. by processing data.
 *                      error message is displayed to user
 */
class ErrorView
{
public:
    ErrorView();

    /**
     * shows a message box without any icons. Only text and Ok button
     * @param msg message to display in the popup
     */
    static void showPopup( const char* msg );

    /**
     * show MessageBox with error message passed by argument
     * @param parent parent window
     * @param errorMsg error message to display
     */
    static void showErrorPopup( QWidget* parent, const std::string& errorMsg );

    /**
     * shows standard excuse message
     * @param parent parent window
     */
    static void showStandardInternalErrorPopup( QWidget* parent );

    /**
     * display popup with standard error message & write error file & write error to cerr
     * @param errorMsg error information
     */
    static void internalErrorHandler( const std::string& errorMsg );

    /**
     * display critical popup with error information & write error file & write error to cerr
     * @param errorMsg error information
     */
    static void runtimeErrorHandler( const std::string& errorMsg );
};

#endif // ERRORVIEW_H
