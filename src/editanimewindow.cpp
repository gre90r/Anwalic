#include "editanimewindow.h"
#include "ui_editanimewindow.h"
#include <QMessageBox>
#include "globals.h"
#include "stringsEN.h"


EditAnimeWindow::EditAnimeWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditAnimeWindow)
{
    ui->setupUi(this);
    this->setFixedSize( this->width(), this->height() );

    // enable red cross in top right corner of window
    setWindowFlags( Qt::Dialog | Qt::WindowCloseButtonHint );
}

EditAnimeWindow::~EditAnimeWindow()
{
    delete ui;
}

/**
 * Button clicked: Save
 */
void EditAnimeWindow::on_btnSave_clicked()
{
    if ( !dataChangeIsValid() )
        return; // error messages already shown

    // write to orignal anime object ( no send back necessary )
    m_originalAnime->setName( ui->etName->text().toStdString() );
    m_originalAnime->setEpisode( ui->etCurrentEpisode->text().toUInt() );
    if ( ui->etTotalEpisodes->text().toStdString() == "??" )
        m_originalAnime->setTotalEpisodes( MAX_NUMBER_EPISODES );
    else
        m_originalAnime->setTotalEpisodes( ui->etTotalEpisodes->text().toUInt() );
    m_originalAnime->setUrl( ui->etUrl->toPlainText().toStdString() );


    this->accept();
    emit sendDataChanged();
}

/**
 * Button clicked: Cancel
 * @brief close window without saving
 */
void EditAnimeWindow::on_btnCancel_clicked()
{
    this->close();
}

/**
 * receives data from mainwindow & inserts it to text fields
 * @param anime pointer to anime object
 */
void EditAnimeWindow::receiveData( Anime* anime, AnwalicService* svc )
{
    m_originalAnime = anime; // holds pointer to orignal anime object
    m_svc = svc;

    ui->etName->setText( QString( anime->getName().c_str() ) );
    ui->etCurrentEpisode->setText( QString::number( anime->getCurrentEpisode() ) );
    if ( anime->getTotalEpisodes() == MAX_NUMBER_EPISODES )
    {
        ui->etTotalEpisodes->setText( "??" );
    }
    else
    {
        ui->etTotalEpisodes->setText( QString::number( anime->getTotalEpisodes() ) );
    }
    ui->etUrl->setPlainText( anime->getUrl().c_str() );
}

bool EditAnimeWindow::dataChangeIsValid()
{
    // if <<<ANIME NAME>>>
    std::string animeName = ui->etName->text().toStdString();
    Anime::validateAnimeName( animeName ); // if char '(' or ')' exists, it will be converted to '[' or ']'
    // empty
    if ( animeName.empty() )
    {
        QMessageBox::information( this, PROGRAM_NAME,
                                  STR_INVALID_NAME, QMessageBox::Ok );
        return false;
    }
    ui->etName->setText( animeName.c_str() );
    // check for anime name duplicate
    if ( m_svc->searchCompletedAnimelistForDuplicate( animeName ) ) {
        // duplicate found
        QMessageBox::information( this, PROGRAM_NAME,
                                  STR_ANIME_ALREADY_IN_LIST, QMessageBox::Ok );
        return false;
    }

    // if <<<CURRENT EPISODE>>> is not a number
    if ( ui->etCurrentEpisode->text().toUInt() == 0 )
    {
        QMessageBox::information( this, PROGRAM_NAME,
                                  STR_INVALID_CURRENT_EPISODE, QMessageBox::Ok );
        return false;
    }

    // if <<<TOTAL EPISODES>>> == "??"
    if ( !( ui->etTotalEpisodes->text().toStdString() == "??" ) )
    {
        // if totalEpisodes is not a number
        if ( ui->etTotalEpisodes->text().toUInt() == 0 )
        {
            QMessageBox::information( this, PROGRAM_NAME,
                                      STR_INVALID_TOTAL_EPISODES, QMessageBox::Ok );
            return false;
        }
        // if currentEpisode > totalEpisodes
        if ( ui->etCurrentEpisode->text().toUInt() > ui->etTotalEpisodes->text().toUInt() )
        {
            QMessageBox::information( this, PROGRAM_NAME,
                                      STR_INVALID_TOTAL_EPISODES, QMessageBox::Ok );
            return false;
        }
    }

    // if user typed something in for <<<URL>>>. validate URL
    if ( !( ui->etUrl->toPlainText().toStdString().empty()) )
    {
        // validate URL
        if ( !Anime::validateURL( ui->etUrl->toPlainText().toStdString() ) )
        {
            QMessageBox::information( this, PROGRAM_NAME,
                                      STR_INVALID_URL, QMessageBox::Ok );
            return false;
        }
    }

    return true;
}

void EditAnimeWindow::reject()
{
    emit sendDataChanged(); // only refreshes list and button. No changes will be applied.
                            // necessary to delete this window
}
