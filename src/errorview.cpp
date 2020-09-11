#include "errorview.h"
#include <QMessageBox>
#include <globals.h>
#include "saveload.h"
#include <iostream>
#include "stringsEN.h"
#include <QIcon>

ErrorView::ErrorView()
{
}

void ErrorView::showPopup( const char* msg )
{
    QMessageBox msgbox;
    msgbox.setWindowIcon( QIcon( "./icon/Anwalic_icon_1.ico" ) );
    msgbox.setIcon( QMessageBox::Icon::Information );
    msgbox.setText( msg );
    msgbox.exec();
}

void ErrorView::showErrorPopup( QWidget* parent, const std::string& errorMsg )
{
    QMessageBox::critical( parent, PROGRAM_NAME, errorMsg.c_str(),
                           QMessageBox::StandardButton::Ok );
}

void ErrorView::showStandardInternalErrorPopup( QWidget* parent )
{
    ErrorView::showErrorPopup( parent, STR_INTERNAL_ERROR_STANDARD_MESSAGE );
}

void ErrorView::internalErrorHandler( const std::string& errorMsg )
{
    std::cerr << errorMsg << std::endl;
    showStandardInternalErrorPopup( nullptr );
    SaveLoad::writeErrorFile( errorMsg );
}

void ErrorView::runtimeErrorHandler( const std::string& errorMsg )
{
    std::cerr << errorMsg << std::endl;
    showErrorPopup( nullptr, errorMsg );
    SaveLoad::writeErrorFile( errorMsg );
}
