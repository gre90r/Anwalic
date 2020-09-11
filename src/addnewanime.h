#ifndef ADDNEWANIME_H
#define ADDNEWANIME_H

#include <QDialog>
#include <anime.h>
#include <string>

namespace Ui {
class AddNewAnime;
}


/**
 * window to add new anime
 */
class AddNewAnime : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewAnime(QWidget *parent = 0);
    ~AddNewAnime();

private slots:

    /**
     * checkbox "I know the total number of episodes" has been clicked.
     * enables/disables the input field for "Total Number of Episodes"
     */
    void on_cbTotalEpisodesAvailable_clicked();

    /**
     * button "Add" clicked.
     * Adds new anime to My Anime List
     */
    void on_btnOK_clicked();

    /**
     * button "Cancel" clicked.
     * Close Add New Anime window. Just close. No further processing
     */
    void on_btnCancel_clicked();

    /**
     * if user enters something in input field "Name".
     * used to enable/disable add-button incase input is invalid
     * @animeName edited text from input filed "Name".
     * @notice Parameter animeName is not used since it will be drawn out if gui later
     */
    void on_etName_textEdited(const QString &animeName);

    //TODO: remove unused code
    /**
     * if user enters something in input field "Total Episodes".
     * used to enable/disable add-button incase input is invalid
     * @totalEpisodes edited text from input filed "Total Episodes"
     * @notice Parameter totalEpisodes is not used since it will be drawn out if gui later
     */
    void on_etTotalEpisodes_textEdited(const QString &totalEpisodes);

    /**
     * if user enters something in input field "URL".
     * used to enable/disable add-button incase input is invalid
     */
    void on_etURL_textChanged();

    /**
     * triggered when input field "Total Episodes" loses focus.
     * after focus loss all form data will be validated. In order
     * to enable/disable the add-button
     */
    void on_etTotalEpisodes_editingFinished();

signals:
    /**
     * send new anime object back to MainWindow for further processing
     * @anime the newly created anime object
     */
    void sendData( Anime* anime );

    
protected:

    /**
     * event called when: ESC key pressed, close() is called
     */
    void reject() override;

private:
    /**************/
    /* Attributes */
    /**************/
    Ui::AddNewAnime *ui;
    std::string m_animeName;
    std::string m_url;
    unsigned int m_totalEpisodes;

    /***********/
    /* Methods */
    /***********/
    /**
     * check if user input in whole form is ok to be added in My Anime List.
     * @param showErrorMessagesEnabled true: show error messages. false: do not show
     * @return true: everything ok. anime is allowed to be added
     *         false: invalid data. cannot add anime
     */
    bool validateFormData( bool showErrorMessagesEnabled = true );

    /**
     * check if total episode has correct type
     * and is in range
     * @param showErrorMessagesEnabled true: show error messages. false: do not show
     * @return true: total episode has correct type and range
     *         false: invalid
     */
    bool validateTotalEpisode( bool showErrorMessagesEnabled = true );

    /**
     * check for correct anime name
     * @return true: correct name
     *         false: invalid. e.g. contains only whitespace(s)
     */
    bool validateAnimeName();

    /**
     * check for correct url format
     * @param showErrorMessagesEnabled true: show error messages. false: do not show
     * @return true: correct url format
     *         false: incorrect url format
     */
    bool validateUrl( bool showErrorMessagesEnabled = true );

    /**
     * check if user input is valid in whole form.
     * if user input is valid -> enables add-button.
     * if user input is invalid -> disables add-button
     * @param showErrorMessagesEnabled true: show error messages. false: do not show
     */
    void validateFormDataAndSetButtons( bool showErrorMessagesEnabled = true );
};

#endif // ADDNEWANIME_H
