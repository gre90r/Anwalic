#ifndef STRINGUTILS
#define STRINGUTILS

#include <string>

/**
 * string utilities which are not in the standard library
 */
class StringUtils
{
public:
    StringUtils();
    ~StringUtils();

    /**
     * sets first character to lowercase
     * @param _str string to convert to lowercase
     */
    static void toLower( std::string& _str );

    /**
     * sets first character to uppercase
     * @param _str string to convert to uppercase
     */
    static void toUpper( std::string& _str );

    /**
     * check if first character is lowercase
     * @param _str string to check
     * @return true: if it's lowercase.<br>
     *         false: on anything else
     */
    static bool isLowercase( const std::string& _str );

    /**
     * check if first charachter is uppercase
     * @param _str string to check
     * @return true: if it's uppercase.<br>
     *         false: if it's anything else
     */
    static bool isUppercase( const std::string& _str );

    /**
     * cast string to unsigned int
     * @param s string that shall be casted
     * @return the extracted number from the parameter s
     */
    static unsigned int string2uint( const std::string& s );
};

#endif
