#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>
#include <QString>
namespace Ui {
class AboutWindow;
}

class AboutWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = 0);
    ~AboutWindow();

signals:
    void sendGuiFinished();

private slots:
    void on_btnOk_clicked();

protected:
    /**
     * event called when: ESC key pressed, close() is called
     */
    void reject() override;

private:
    Ui::AboutWindow *ui;
    const char* m_iconPath;
};

#endif // ABOUTWINDOW_H
