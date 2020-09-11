#ifndef EDITANIMEWINDOW_H
#define EDITANIMEWINDOW_H

#include <QDialog>
#include "anime.h"
#include "AnwalicService.h"


namespace Ui {
class EditAnimeWindow;
}

class EditAnimeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditAnimeWindow(QWidget *parent = 0);
    ~EditAnimeWindow();

private slots:
    /**
     * user clicked button "Save"
     */
    void on_btnSave_clicked();

    /**
     * user clicked button "Cancel"
     */
    void on_btnCancel_clicked();

    /**
     * receive data from MainWindow
     * @param anime the clicked anime from ListView
     * @param svc has access to search operations, lists etc
     */
    void receiveData( Anime* anime, AnwalicService* svc );

signals:
    /**
     * notify MainWindow about changed data
     */
    void sendDataChanged();

private:
    Ui::EditAnimeWindow *ui;
    Anime* m_originalAnime; // holds pointer to orignal anime object from animelist
    AnwalicService* m_svc; // access to search animelists

    /**
     * validates all user input.
     * @note this method is respnsible for showing errors
     */
    bool dataChangeIsValid();

protected:
    /**
     * is called when: ESC key is pressed. close() method is called
     */
    void reject() override;

};

#endif // EDITANIMEWINDOW_H
