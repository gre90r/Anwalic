/********************************************************************************
** Form generated from reading UI file 'aboutwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTWINDOW_H
#define UI_ABOUTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AboutWindow
{
public:
    QPushButton *btnOk;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *labelIcon;

    void setupUi(QDialog *AboutWindow)
    {
        if (AboutWindow->objectName().isEmpty())
            AboutWindow->setObjectName(QStringLiteral("AboutWindow"));
        AboutWindow->resize(480, 460);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AboutWindow->sizePolicy().hasHeightForWidth());
        AboutWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Liberation Sans"));
        AboutWindow->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("icon/Anwalic_icon_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        AboutWindow->setWindowIcon(icon);
        btnOk = new QPushButton(AboutWindow);
        btnOk->setObjectName(QStringLiteral("btnOk"));
        btnOk->setGeometry(QRect(300, 400, 161, 41));
        QFont font1;
        font1.setFamily(QStringLiteral("Liberation Sans"));
        font1.setPointSize(16);
        btnOk->setFont(font1);
        label = new QLabel(AboutWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 10, 481, 20));
        QFont font2;
        font2.setFamily(QStringLiteral("Liberation Sans"));
        font2.setPointSize(16);
        font2.setBold(true);
        font2.setWeight(75);
        label->setFont(font2);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(AboutWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 34, 481, 20));
        QFont font3;
        font3.setFamily(QStringLiteral("Liberation Sans"));
        font3.setPointSize(12);
        label_2->setFont(font3);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(AboutWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 400, 261, 41));
        QFont font4;
        font4.setFamily(QStringLiteral("Liberation Sans"));
        font4.setPointSize(11);
        font4.setUnderline(false);
        label_3->setFont(font4);
        label_3->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        label_3->setWordWrap(true);
        label_4 = new QLabel(AboutWindow);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 190, 241, 51));
        label_4->setFont(font3);
        label_4->setCursor(QCursor(Qt::IBeamCursor));
        label_4->setFrameShape(QFrame::NoFrame);
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_4->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);
        label_5 = new QLabel(AboutWindow);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 70, 441, 41));
        label_5->setFont(font3);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_5->setWordWrap(true);
        label_7 = new QLabel(AboutWindow);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 120, 441, 61));
        label_7->setFont(font3);
        label_7->setCursor(QCursor(Qt::ArrowCursor));
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_7->setWordWrap(true);
        labelIcon = new QLabel(AboutWindow);
        labelIcon->setObjectName(QStringLiteral("labelIcon"));
        labelIcon->setGeometry(QRect(20, 250, 441, 128));
        labelIcon->setAlignment(Qt::AlignCenter);

        retranslateUi(AboutWindow);

        QMetaObject::connectSlotsByName(AboutWindow);
    } // setupUi

    void retranslateUi(QDialog *AboutWindow)
    {
        AboutWindow->setWindowTitle(QApplication::translate("AboutWindow", "About", 0));
        btnOk->setText(QApplication::translate("AboutWindow", "OK ~(\302\260.\302\260)~", 0));
        label->setText(QApplication::translate("AboutWindow", "Anwalic", 0));
        label_2->setText(QApplication::translate("AboutWindow", "(Anime Watch List Creator)", 0));
        label_3->setText(QApplication::translate("AboutWindow", "Copyright 2015-2018 gre90r.\n"
"All rights reserved.", 0));
        label_4->setText(QApplication::translate("AboutWindow", "Contact information\n"
"Email: gregor_hoben@live.de", 0));
        label_5->setText(QApplication::translate("AboutWindow", "Anwalic is a program to organize your Animelist. Keep track on what you are watching!", 0));
        label_7->setText(QApplication::translate("AboutWindow", "You want to report an error?\n"
"Send me an email with the .ane error file, .cfg config file and all .anl list files. Describe the error as detailed as possible.", 0));
        labelIcon->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AboutWindow: public Ui_AboutWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTWINDOW_H
