#include "StringUtils.h"
#include <sstream>


StringUtils::StringUtils()
{
}


StringUtils::~StringUtils()
{
}


void StringUtils::toLower(std::string& _str)
{
    if ( isUppercase( _str ) )
    {
        _str[0] += 32;
    }
}

void StringUtils::toUpper(std::string& _str)
{
    if ( isLowercase( _str ) )
    {
        _str[0] -= 32;
    }
}


bool StringUtils::isLowercase(const std::string& _str)
{
    if ( _str.empty() ) return false;
    if ( _str.at( 0 ) >= 97 && _str.at( 0 ) <= 122 )
    {
        return true;
    }
    return false;
}


bool StringUtils::isUppercase(const std::string& _str)
{
    if ( _str.empty() ) return false;
    if ( _str.at( 0 ) >= 65 && _str.at( 0 ) <= 90 )
    {
        return true;
    }
    return false;
}

unsigned StringUtils::string2uint(const std::string& s)
{
    std::stringstream ss;
    unsigned int number = 0;

    ss << s; // write string to stringstream
    ss >> number; // implicit cast of stringstream converts string to unsigend int

    return number;
}
