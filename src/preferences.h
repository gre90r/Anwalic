#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <string>
#include <QSize>

class Preferences
{
public:

    /**
     * set default preferences
     */
    Preferences();


    Preferences& operator=( const Preferences& ); // define because compiler deletes this on default


    /**
     * writes all preference attributes to config file
     * @note !! NEVER MAKE STATIC !!
     */
    void writeConfigFile() const;

    
    /**
     * reads config file and sets attributes
     * @note !! NEVER MAKE STATIC !!
     */
    void readConfigFile();


    // Getter & Setter
    void setFontSize(const unsigned int s);
    unsigned int getFontSize() const;
    void setBackgroundImagePath(const std::string& p);
    std::string getBackgroundImagePath() const;
    void setWindowSize(const QSize& s);
    QSize getWindowSize() const;
    void setListCaptionColor(std::string c);
    std::string getListCaptionColor() const;


private:
    unsigned int m_fontSize;
    std::string m_listCaptionColor;
    std::string m_backgroundImagePath;
    const std::string m_nameConfigFile;
    QSize m_windowSize;
};

#endif // PREFERENCES_H
