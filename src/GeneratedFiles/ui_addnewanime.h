/********************************************************************************
** Form generated from reading UI file 'addnewanime.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDNEWANIME_H
#define UI_ADDNEWANIME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_AddNewAnime
{
public:
    QLabel *label;
    QLineEdit *etName;
    QLabel *label_2;
    QTextEdit *etURL;
    QCheckBox *cbTotalEpisodesAvailable;
    QLineEdit *etTotalEpisodes;
    QPushButton *btnOK;
    QPushButton *btnCancel;

    void setupUi(QDialog *AddNewAnime)
    {
        if (AddNewAnime->objectName().isEmpty())
            AddNewAnime->setObjectName(QStringLiteral("AddNewAnime"));
        AddNewAnime->resize(380, 280);
        QIcon icon;
        icon.addFile(QStringLiteral("icon/Anwalic_icon_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        AddNewAnime->setWindowIcon(icon);
        label = new QLabel(AddNewAnime);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(true);
        label->setGeometry(QRect(19, 20, 81, 23));
        QFont font;
        font.setPointSize(9);
        label->setFont(font);
        label->setTextFormat(Qt::AutoText);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        etName = new QLineEdit(AddNewAnime);
        etName->setObjectName(QStringLiteral("etName"));
        etName->setGeometry(QRect(110, 20, 251, 23));
        label_2 = new QLabel(AddNewAnime);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(19, 60, 81, 70));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2->setWordWrap(true);
        etURL = new QTextEdit(AddNewAnime);
        etURL->setObjectName(QStringLiteral("etURL"));
        etURL->setGeometry(QRect(110, 60, 251, 70));
        etURL->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        cbTotalEpisodesAvailable = new QCheckBox(AddNewAnime);
        cbTotalEpisodesAvailable->setObjectName(QStringLiteral("cbTotalEpisodesAvailable"));
        cbTotalEpisodesAvailable->setGeometry(QRect(110, 140, 251, 21));
        etTotalEpisodes = new QLineEdit(AddNewAnime);
        etTotalEpisodes->setObjectName(QStringLiteral("etTotalEpisodes"));
        etTotalEpisodes->setEnabled(false);
        etTotalEpisodes->setGeometry(QRect(130, 170, 41, 23));
        etTotalEpisodes->setAlignment(Qt::AlignCenter);
        btnOK = new QPushButton(AddNewAnime);
        btnOK->setObjectName(QStringLiteral("btnOK"));
        btnOK->setEnabled(false);
        btnOK->setGeometry(QRect(110, 230, 111, 31));
        btnCancel = new QPushButton(AddNewAnime);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(250, 230, 111, 31));

        retranslateUi(AddNewAnime);

        QMetaObject::connectSlotsByName(AddNewAnime);
    } // setupUi

    void retranslateUi(QDialog *AddNewAnime)
    {
        AddNewAnime->setWindowTitle(QApplication::translate("AddNewAnime", "Add New Anime", 0));
        label->setText(QApplication::translate("AddNewAnime", "Name", 0));
#ifndef QT_NO_TOOLTIP
        etName->setToolTip(QApplication::translate("AddNewAnime", "Name of the Anime", 0));
#endif // QT_NO_TOOLTIP
        etName->setText(QString());
        label_2->setText(QApplication::translate("AddNewAnime", "URL to Stream", 0));
#ifndef QT_NO_TOOLTIP
        etURL->setToolTip(QApplication::translate("AddNewAnime", "Internet address where you can watch the anime", 0));
#endif // QT_NO_TOOLTIP
        etURL->setHtml(QApplication::translate("AddNewAnime", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans Serif'; font-size:9pt;\"><br /></p></body></html>", 0));
        cbTotalEpisodesAvailable->setText(QApplication::translate("AddNewAnime", "I know the total number of episodes", 0));
#ifndef QT_NO_TOOLTIP
        etTotalEpisodes->setToolTip(QApplication::translate("AddNewAnime", "Total Number of Episodes", 0));
#endif // QT_NO_TOOLTIP
        etTotalEpisodes->setText(QString());
        btnOK->setText(QApplication::translate("AddNewAnime", "Add", 0));
        btnCancel->setText(QApplication::translate("AddNewAnime", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class AddNewAnime: public Ui_AddNewAnime {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDNEWANIME_H
