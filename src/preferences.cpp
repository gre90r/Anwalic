#include "preferences.h"
#include <fstream>
#include <QString>
#include "errorview.h"
#include "globals.h"

Preferences::Preferences()
    : m_fontSize( 14 ),
      m_listCaptionColor( "black" ),
      m_backgroundImagePath( DEFAULT_BACKGROUND_IMAGE_PATH ),
      m_nameConfigFile( "anwalic.cfg" ),
      m_windowSize( QSize( 800, 700 ) ) // minimum size of MainWindow. DO NOT DECREASE VALUE !
{
}

void Preferences::writeConfigFile() const
{
    std::ofstream ofStream( m_nameConfigFile.c_str(), std::ios::out | std::ios::trunc );
    if ( !ofStream )
    {
        ErrorView::runtimeErrorHandler( std::string( "runtime error: Could not write config file " ) +
                                        std::string( m_nameConfigFile ) );
        return;
    }

    ofStream << m_fontSize << "\n"; // FontSize
    ofStream << m_listCaptionColor << "\n"; // List Caption Color
    ofStream << m_backgroundImagePath << "\n"; // Background Image
    ofStream << m_windowSize.width() << "x" << m_windowSize.height() << "\n"; // WindowSize

    ofStream.close();
}

void Preferences::readConfigFile()
{
    std::ifstream ifStream( m_nameConfigFile.c_str(), std::ios::in );
    if ( !ifStream ) return; // no preferences set yet

    std::string buffer;

    // Font Size
    std::getline( ifStream, buffer );
    m_fontSize = QString( buffer.c_str() ).toUInt();

    // List Caption Color
    std::getline( ifStream, m_listCaptionColor );

    // Background Image
    std::getline( ifStream, m_backgroundImagePath );

    // Window Size
    std::getline( ifStream, buffer, 'x' );
    m_windowSize.setWidth( QString( buffer.c_str() ).toInt() );
    std::getline( ifStream, buffer );
    m_windowSize.setHeight( QString( buffer.c_str() ).toInt() );

    ifStream.close();
}

Preferences& Preferences::operator=( const Preferences& other )
{
    m_backgroundImagePath = other.getBackgroundImagePath();
    m_fontSize = other.getFontSize();
    m_listCaptionColor = other.getListCaptionColor();
    m_windowSize = other.getWindowSize();
    // name of config file not needed to be copied
    return *this;
}

void Preferences::setFontSize(const unsigned s)
{
    m_fontSize = s;
}

unsigned Preferences::getFontSize() const
{
    return m_fontSize;
}

void Preferences::setBackgroundImagePath(const std::string& p)
{
    m_backgroundImagePath = p;
}

std::string Preferences::getBackgroundImagePath() const
{
    return m_backgroundImagePath;
}

void Preferences::setWindowSize(const QSize& s)
{
    m_windowSize = s;
}

QSize Preferences::getWindowSize() const
{
    return m_windowSize;
}

void Preferences::setListCaptionColor(std::string c)
{
    for (size_t i = 0; i < c.size(); ++i)
    {
        c[i] = tolower(c[i]);
    }
    m_listCaptionColor = c;
}

std::string Preferences::getListCaptionColor() const
{
    return m_listCaptionColor;
}
