#include "preferenceswindow.h"
#include "ui_preferenceswindow.h"
#include <QDesktopServices>
#include "globals.h"
#include <QFileDialog>
#include <iostream>
#include <string>
#include "errorview.h"
#include "stringsEN.h"

PreferencesWindow::PreferencesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::preferencesWindow)
{
    ui->setupUi(this);
    this->setFixedSize( this->width(), this->height() );

    // enable red cross in top right corner of window
    setWindowFlags( Qt::Dialog | Qt::WindowCloseButtonHint );

    m_availableFontSizes.append( "8" );
    m_availableFontSizes.append( "10" );
    m_availableFontSizes.append( "12" );
    m_availableFontSizes.append( "14" );
    m_availableFontSizes.append( "16" );
    m_availableFontSizes.append( "18" );
    m_availableFontSizes.append( "20" );
    m_availableFontSizes.append( "22" );
    m_availableFontSizes.append( "24" );
    m_availableFontSizes.append( "26" );
    m_availableFontSizes.append( "28" );
    m_availableFontSizes.append( "30" );
    m_availableFontSizes.append( "32" );
    m_availableFontSizes.append( "36" );
    m_availableFontSizes.append( "40" );
    m_availableFontSizes.append( "72" );
    m_availableFontSizes.append( "96" );
    m_availableFontSizes.append( "128" ); // extra big size for 4k monitors
    ui->comboFontSize->addItems( m_availableFontSizes );

    ui->comboListCaptionColor->addItem( "black" );
    ui->comboListCaptionColor->addItem( "white" );

    ui->label->setFocus(); // take focus off the comboBox
}

PreferencesWindow::~PreferencesWindow()
{
    delete ui;
}

void PreferencesWindow::on_btnCancel_clicked()
{
    this->close(); // calls reject() which emits
}

void PreferencesWindow::on_btnApply_clicked()
{
    Preferences preferences;

    // Font Size
    preferences.setFontSize( ui->comboFontSize->currentText().toUInt() );

    // List Caption Color
    preferences.setListCaptionColor( ui->comboListCaptionColor->currentText().toStdString() ); // setter makes tolower

    // Background
    if ( ui->cbSetCustomBackground->isChecked() )
    {
        if ( ui->leCustomBackground->text().isEmpty() )
        {
            ErrorView::showPopup( STR_NO_BACKGROUND_CHOSEN );
            return;
        }
        preferences.setBackgroundImagePath( ui->leCustomBackground->text().toStdString() );
    }
    else
    {
        preferences.setBackgroundImagePath( DEFAULT_BACKGROUND_IMAGE_PATH );
    }

    this->accept();
    emit sendPreferences( &preferences );
}

void PreferencesWindow::on_btnCustomBackground_clicked()
{
    QString filePath = QFileDialog::getOpenFileName( this, "Select a Background Image", ".",
                                                     "Images (*.jpg *.jpeg *.png)" );
    if ( filePath == "" ) return; // Cancel has been clicked

    ui->leCustomBackground->setText( filePath );
}

void PreferencesWindow::on_cbSetCustomBackground_clicked()
{
    if ( ui->cbSetCustomBackground->isChecked() )
    {
        ui->leCustomBackground->setEnabled( true );
        ui->btnCustomBackground->setEnabled( true );
    }
    else
    {
        ui->leCustomBackground->setEnabled( false );
        ui->btnCustomBackground->setEnabled( false );
    }
}

void PreferencesWindow::receivePreferences( Preferences* preferences )
{
    // Font Size
    {
        int currentIndex = ui->comboFontSize->findText( QString::number( preferences->getFontSize() ) );
        if ( currentIndex < 0 )
        {
            std::cerr << "internal error: @PreferencesWindow::receivePreferences(). "
                         "Could not set comboFontSize in PreferencesWindow";
        }
        ui->comboFontSize->setCurrentIndex( currentIndex );
    }

    // List Caption Color
    {
        int currentIndex = ui->comboListCaptionColor->findText( QString( preferences->getListCaptionColor().c_str() ) );
        if ( currentIndex < 0 )
        {
            std::cerr << "internal error: @PreferencesWindow::receivePreferences(). "
                         "Could not set comboListCaptionColor in PreferencesWindow";
        }
        ui->comboListCaptionColor->setCurrentIndex( currentIndex );
    }

    // if current background is not default
    if ( preferences->getBackgroundImagePath() != std::string( DEFAULT_BACKGROUND_IMAGE_PATH ) )
    {
        ui->cbSetCustomBackground->setChecked( true );
        ui->leCustomBackground->setEnabled( true );
        ui->btnCustomBackground->setEnabled( true );
        ui->leCustomBackground->setText( preferences->getBackgroundImagePath().c_str() );
    }
    else
    {
        ui->cbSetCustomBackground->setChecked( false );
        ui->leCustomBackground->setEnabled( false );
        ui->btnCustomBackground->setEnabled( false );
        ui->leCustomBackground->setText( "" );
    }
}

void PreferencesWindow::reject()
{
    emit sendPreferences( nullptr );
}
