/********************************************************************************
** Form generated from reading UI file 'editanimewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITANIMEWINDOW_H
#define UI_EDITANIMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditAnimeWindow
{
public:
    QPushButton *btnCancel;
    QPushButton *btnSave;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *etName;
    QLineEdit *etCurrentEpisode;
    QLineEdit *etTotalEpisodes;
    QPlainTextEdit *etUrl;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QDialog *EditAnimeWindow)
    {
        if (EditAnimeWindow->objectName().isEmpty())
            EditAnimeWindow->setObjectName(QStringLiteral("EditAnimeWindow"));
        EditAnimeWindow->resize(440, 300);
        QIcon icon;
        icon.addFile(QStringLiteral("icon/Anwalic_icon_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        EditAnimeWindow->setWindowIcon(icon);
        btnCancel = new QPushButton(EditAnimeWindow);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(330, 252, 91, 31));
        btnCancel->setAutoDefault(false);
        btnSave = new QPushButton(EditAnimeWindow);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setGeometry(QRect(220, 252, 91, 31));
        btnSave->setAutoDefault(true);
        label = new QLabel(EditAnimeWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 101, 23));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(EditAnimeWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 50, 101, 23));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(EditAnimeWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 80, 101, 23));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        etName = new QLineEdit(EditAnimeWindow);
        etName->setObjectName(QStringLiteral("etName"));
        etName->setGeometry(QRect(140, 20, 281, 23));
        etCurrentEpisode = new QLineEdit(EditAnimeWindow);
        etCurrentEpisode->setObjectName(QStringLiteral("etCurrentEpisode"));
        etCurrentEpisode->setGeometry(QRect(140, 50, 41, 23));
        etCurrentEpisode->setAlignment(Qt::AlignCenter);
        etTotalEpisodes = new QLineEdit(EditAnimeWindow);
        etTotalEpisodes->setObjectName(QStringLiteral("etTotalEpisodes"));
        etTotalEpisodes->setGeometry(QRect(140, 80, 41, 23));
        etTotalEpisodes->setAlignment(Qt::AlignCenter);
        etUrl = new QPlainTextEdit(EditAnimeWindow);
        etUrl->setObjectName(QStringLiteral("etUrl"));
        etUrl->setGeometry(QRect(140, 110, 281, 121));
        label_4 = new QLabel(EditAnimeWindow);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 110, 101, 121));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_5 = new QLabel(EditAnimeWindow);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(190, 80, 221, 23));

        retranslateUi(EditAnimeWindow);

        btnSave->setDefault(false);


        QMetaObject::connectSlotsByName(EditAnimeWindow);
    } // setupUi

    void retranslateUi(QDialog *EditAnimeWindow)
    {
        EditAnimeWindow->setWindowTitle(QApplication::translate("EditAnimeWindow", "Edit Anime", 0));
        btnCancel->setText(QApplication::translate("EditAnimeWindow", "Cancel", 0));
        btnSave->setText(QApplication::translate("EditAnimeWindow", "Save", 0));
        label->setText(QApplication::translate("EditAnimeWindow", "Name", 0));
        label_2->setText(QApplication::translate("EditAnimeWindow", "Current Episode", 0));
        label_3->setText(QApplication::translate("EditAnimeWindow", "Total Episodes", 0));
        etName->setText(QString());
        etUrl->setPlainText(QString());
        label_4->setText(QApplication::translate("EditAnimeWindow", "URL", 0));
        label_5->setText(QApplication::translate("EditAnimeWindow", "<html><head/><body><p><span style=\" color:#515151;\">enter ?? if you don't know</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class EditAnimeWindow: public Ui_EditAnimeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITANIMEWINDOW_H
