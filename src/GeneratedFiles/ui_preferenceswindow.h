/********************************************************************************
** Form generated from reading UI file 'preferenceswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCESWINDOW_H
#define UI_PREFERENCESWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_preferencesWindow
{
public:
    QLabel *label;
    QComboBox *comboFontSize;
    QLineEdit *leCustomBackground;
    QCheckBox *cbSetCustomBackground;
    QPushButton *btnCustomBackground;
    QPushButton *btnApply;
    QPushButton *btnCancel;
    QLabel *label_2;
    QComboBox *comboListCaptionColor;

    void setupUi(QDialog *preferencesWindow)
    {
        if (preferencesWindow->objectName().isEmpty())
            preferencesWindow->setObjectName(QStringLiteral("preferencesWindow"));
        preferencesWindow->resize(500, 220);
        QIcon icon;
        icon.addFile(QStringLiteral("icon/Anwalic_icon_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        preferencesWindow->setWindowIcon(icon);
        label = new QLabel(preferencesWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 131, 16));
        comboFontSize = new QComboBox(preferencesWindow);
        comboFontSize->setObjectName(QStringLiteral("comboFontSize"));
        comboFontSize->setGeometry(QRect(170, 20, 72, 23));
        comboFontSize->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        comboFontSize->setFrame(true);
        leCustomBackground = new QLineEdit(preferencesWindow);
        leCustomBackground->setObjectName(QStringLiteral("leCustomBackground"));
        leCustomBackground->setEnabled(false);
        leCustomBackground->setGeometry(QRect(40, 128, 391, 23));
        leCustomBackground->setReadOnly(true);
        cbSetCustomBackground = new QCheckBox(preferencesWindow);
        cbSetCustomBackground->setObjectName(QStringLiteral("cbSetCustomBackground"));
        cbSetCustomBackground->setEnabled(true);
        cbSetCustomBackground->setGeometry(QRect(20, 98, 181, 21));
        btnCustomBackground = new QPushButton(preferencesWindow);
        btnCustomBackground->setObjectName(QStringLiteral("btnCustomBackground"));
        btnCustomBackground->setEnabled(false);
        btnCustomBackground->setGeometry(QRect(440, 128, 41, 23));
        btnApply = new QPushButton(preferencesWindow);
        btnApply->setObjectName(QStringLiteral("btnApply"));
        btnApply->setGeometry(QRect(260, 170, 101, 31));
        btnCancel = new QPushButton(preferencesWindow);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(380, 170, 101, 31));
        label_2 = new QLabel(preferencesWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 60, 131, 16));
        comboListCaptionColor = new QComboBox(preferencesWindow);
        comboListCaptionColor->setObjectName(QStringLiteral("comboListCaptionColor"));
        comboListCaptionColor->setGeometry(QRect(170, 60, 72, 23));

        retranslateUi(preferencesWindow);

        QMetaObject::connectSlotsByName(preferencesWindow);
    } // setupUi

    void retranslateUi(QDialog *preferencesWindow)
    {
        preferencesWindow->setWindowTitle(QApplication::translate("preferencesWindow", "Preferences", 0));
        label->setText(QApplication::translate("preferencesWindow", "List Item Font Size", 0));
        cbSetCustomBackground->setText(QApplication::translate("preferencesWindow", "Set Custom Background", 0));
        btnCustomBackground->setText(QApplication::translate("preferencesWindow", "...", 0));
        btnApply->setText(QApplication::translate("preferencesWindow", "Apply", 0));
        btnCancel->setText(QApplication::translate("preferencesWindow", "Cancel", 0));
        label_2->setText(QApplication::translate("preferencesWindow", "List Caption Color", 0));
    } // retranslateUi

};

namespace Ui {
    class preferencesWindow: public Ui_preferencesWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCESWINDOW_H
