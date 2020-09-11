/*
 * Copyright 2015 gre90r
 */

//#ifndef _DEBUG // do not create main in debug mode. because unit test has main method

#include "mainwindow.h"
#include <QApplication>
#include <QScreen>
#include <QRect>
#include <QDesktopWidget>
#include <QMessageBox>
#include <stdexcept>
#include "errorview.h"
#include <string>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;

    if ( mainWindow.failed() )
    {
        QMessageBox::critical( nullptr, "Anwalic", "initialization failed! error code 1000", QMessageBox::Ok );
        return 1000;
    }

    // center window
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    mainWindow.move( screenGeometry.width() / 2 - mainWindow.width() / 2,
                     screenGeometry.height() / 2 - mainWindow.height() / 2);
    mainWindow.show();

    try
    {
        return a.exec();
    }
    catch( const std::exception& e )
    {
        ErrorView::internalErrorHandler( std::string( "unhandled exception caught in main: " ) +
                                         std::string( e.what() ) +
                                         std::string( ". error code 2000"));
        return 2000;
    }
    catch( ... )
    {
        ErrorView::internalErrorHandler( "FATAL ERROR. Unknown exception caught. Program has to quit! error code 3000" );
        return 3000;
    }

    return -1;
}

//#endif
