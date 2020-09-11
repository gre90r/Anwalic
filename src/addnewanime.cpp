#include "addnewanime.h"
#include "ui_addnewanime.h"
#include <QMessageBox>
#include <globals.h>
#include <cstring>
#include <QString>
#include "stringsEN.h"
#include "errorview.h"


AddNewAnime::AddNewAnime(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewAnime),
    m_animeName(""),
    m_url(""),
    m_totalEpisodes(0)
{
    ui->setupUi(this);
    this->setFixedSize( this->width(), this->height() );

    // show red cross on window border
    setWindowFlags( Qt::Dialog | Qt::WindowCloseButtonHint );
}

AddNewAnime::~AddNewAnime()
{
    delete ui;
}

void AddNewAnime::on_cbTotalEpisodesAvailable_clicked()
{
    if ( ui->cbTotalEpisodesAvailable->isChecked() )
    {
        ui->etTotalEpisodes->setEnabled( true );
    }
    else
    {
        ui->etTotalEpisodes->setText( "" );
        ui->etTotalEpisodes->setEnabled( false );
    }

    this->validateFormDataAndSetButtons( false ); // do not show error messages
}

void AddNewAnime::on_btnOK_clicked()
{
    // validate user input
    if ( !this->validateFormData() ) {
        return;
    }

    // send new data back to MainWindow
    this->accept();
    Anime* ptrAnime = new Anime( m_animeName, 1, m_totalEpisodes, m_url );
    emit sendData( ptrAnime ); // send to MainWindow
}

void AddNewAnime::on_btnCancel_clicked()
{
    this->close(); // calls reject() which emits
}

void AddNewAnime::on_etName_textEdited(const QString &/*animeName*/) // unused parameter
{
    if ( !this->validateAnimeName() )
        ui->btnOK->setEnabled(false);
    else
        ui->btnOK->setEnabled(true);
}

void AddNewAnime::reject()
{
    emit sendData( nullptr );
}

bool AddNewAnime::validateFormData( bool showErrorMessagesEnabled )
{
    // anime name
    if ( !this->validateAnimeName() ) {
        return false;
    }

    // url
    if ( !this->validateUrl( showErrorMessagesEnabled ) ) {
        return false;
    }

    // total episodes
    if ( !this->validateTotalEpisode( showErrorMessagesEnabled ) ) {
        return false;
    }

    return true;
}

bool AddNewAnime::validateTotalEpisode( bool showErrorMessagesEnabled )
{
    if ( ui->cbTotalEpisodesAvailable->isChecked() )
    {
        m_totalEpisodes = ui->etTotalEpisodes->text().toUInt(); // returns 0 if input is not uint
        // if is 0, wrong type or not in range
        if ( m_totalEpisodes == 0 || m_totalEpisodes >= MAX_NUMBER_EPISODES )
        {
            if ( showErrorMessagesEnabled ) {
                ErrorView::showPopup( STR_INVALID_TOTAL_EPISODES );
            }
            return false;
        }
    }
    else // checkbox not checked
    {
        m_totalEpisodes = MAX_NUMBER_EPISODES;
    }

    return true;
}

bool AddNewAnime::validateAnimeName()
{
    m_animeName = ui->etName->text().toStdString();
    Anime::validateAnimeName( m_animeName ); // if char '(' or ')' exists, it has to be converted to '[' or ']' (weak concept)
    if ( m_animeName.empty() ) {
        return false;
    }

    return true;
}

bool AddNewAnime::validateUrl( bool showErrorMessagesEnabled )
{
    // it is allowed to leave URL field blank.
    // but if a string is set here it must be validated
    m_url = ui->etURL->toPlainText().toStdString();
    if ( !m_url.empty() )
    {
        if ( !Anime::validateURL( m_url ) )
        {
            if ( showErrorMessagesEnabled ) {
                ErrorView::showPopup( STR_INVALID_URL );
            }
            return false;
        }
    }

    return true;
}

void AddNewAnime::validateFormDataAndSetButtons( bool showErrorMessagesEnabled )
{
    if ( !this->validateFormData( showErrorMessagesEnabled ) )
        ui->btnOK->setEnabled( false );
    else
        ui->btnOK->setEnabled( true );
}

void AddNewAnime::on_etTotalEpisodes_textEdited(const QString &/*totalEpisodes*/)
{
    this->validateFormDataAndSetButtons( false ); // do not show error messages
}

void AddNewAnime::on_etURL_textChanged()
{
    this->validateFormDataAndSetButtons( false ); // do not show error messages
}

void AddNewAnime::on_etTotalEpisodes_editingFinished()
{
    this->validateFormDataAndSetButtons( false ); // do not show error messages
}
