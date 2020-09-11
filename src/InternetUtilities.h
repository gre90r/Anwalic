/**
 * @author gre90r
 */

#ifndef UTILITIES_H
#define UTILITIES_H

/**
 * basic operations for internet & browser
 */
class InternetUtilities
{
public:
    InternetUtilities() = delete; // no instance allowed

    /**
    * open URL in browser
    * @param url link to a website
    */
    static void openUrl( const char* url );

private:

};

#endif