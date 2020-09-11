#ifndef PREFERENCESWINDOW_H
#define PREFERENCESWINDOW_H

#include <QDialog>
#include "preferences.h"
#include <QStringList>


namespace Ui {
class preferencesWindow;
}

class PreferencesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesWindow(QWidget *parent = 0);
    ~PreferencesWindow();

signals:
    void sendPreferences( Preferences* );

private slots:
    void on_btnCancel_clicked();

    void on_btnApply_clicked();

    void on_btnCustomBackground_clicked();

    void on_cbSetCustomBackground_clicked();

    void receivePreferences( Preferences* );

protected:
    /**
     * event called when: ESC key pressed, close() method is called
     */
    void reject() override;

private:
    Ui::preferencesWindow *ui;
    QStringList m_availableFontSizes;
};

#endif // PREFERENCESWINDOW_H
