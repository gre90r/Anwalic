/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionGerman;
    QAction *actionEnglish;
    QAction *actionHow_to_use_Anwalic;
    QAction *actionAbout;
    QAction *actionUsername;
    QAction *actionWindow_Size;
    QAction *actionEntry_Width;
    QAction *actionEntry_Font_Size;
    QAction *actionBackground;
    QAction *actionPreferences;
    QAction *actionCompleted_Animes;
    QAction *actionMy_Anime_List;
    QAction *actionAnime_loads_org;
    QAction *actionAchievements;
    QAction *actionImport_Another_List;
    QAction *actionSelect_My_List;
    QAction *actionExport_My_List;
    QAction *actionFind_Anime;
    QAction *actionChangelog;
    QAction *actionShowStartedAnimesOnly;
    QAction *actionMake_Backup;
    QAction *actionCrunchyroll_com;
    QAction *actionKissanime_ru;
    QAction *actionShow_Movies_Only;
    QAction *actionHide_Movies;
    QAction *actionShow_Open_Ended_Animes;
    QAction *actionHide_Open_Ended_Animes;
    QAction *actionFilter_By_Tag;
    QAction *actionAnimefreak_tv;
    QAction *actionHide_Animes_with_Name_Only;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QFrame *line;
    QPushButton *btnDecEpisode;
    QPushButton *btnQuit;
    QPushButton *btnAddNewAnime;
    QPushButton *btnIncEpisode;
    QSpacerItem *verticalSpacer_2;
    QPushButton *btnEdit;
    QSpacerItem *verticalSpacer_3;
    QLabel *labListName;
    QPushButton *btnShowStartedAnimesOnly;
    QPushButton *btnToggleAnimeLists;
    QListView *lvAnimes;
    QSpacerItem *verticalSpacer;
    QPushButton *btnDelete;
    QPushButton *btnGoToStream;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuEdit;
    QMenu *menuList;
    QMenu *menuHelp;
    QMenu *menuWebsites;
    QMenu *menuFilter;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 700);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(800, 700));
        MainWindow->setMaximumSize(QSize(4096, 4096));
        QFont font;
        font.setPointSize(9);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("icon/Anwalic_icon_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionGerman = new QAction(MainWindow);
        actionGerman->setObjectName(QStringLiteral("actionGerman"));
        actionGerman->setEnabled(false);
        actionEnglish = new QAction(MainWindow);
        actionEnglish->setObjectName(QStringLiteral("actionEnglish"));
        actionEnglish->setEnabled(false);
        actionHow_to_use_Anwalic = new QAction(MainWindow);
        actionHow_to_use_Anwalic->setObjectName(QStringLiteral("actionHow_to_use_Anwalic"));
        actionHow_to_use_Anwalic->setEnabled(false);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionAbout->setCheckable(false);
        actionAbout->setEnabled(true);
        actionUsername = new QAction(MainWindow);
        actionUsername->setObjectName(QStringLiteral("actionUsername"));
        actionUsername->setEnabled(false);
        actionWindow_Size = new QAction(MainWindow);
        actionWindow_Size->setObjectName(QStringLiteral("actionWindow_Size"));
        actionWindow_Size->setEnabled(false);
        actionEntry_Width = new QAction(MainWindow);
        actionEntry_Width->setObjectName(QStringLiteral("actionEntry_Width"));
        actionEntry_Width->setEnabled(false);
        actionEntry_Font_Size = new QAction(MainWindow);
        actionEntry_Font_Size->setObjectName(QStringLiteral("actionEntry_Font_Size"));
        actionEntry_Font_Size->setEnabled(false);
        actionBackground = new QAction(MainWindow);
        actionBackground->setObjectName(QStringLiteral("actionBackground"));
        actionBackground->setEnabled(false);
        actionPreferences = new QAction(MainWindow);
        actionPreferences->setObjectName(QStringLiteral("actionPreferences"));
        actionPreferences->setEnabled(true);
        actionCompleted_Animes = new QAction(MainWindow);
        actionCompleted_Animes->setObjectName(QStringLiteral("actionCompleted_Animes"));
        actionCompleted_Animes->setEnabled(true);
        actionMy_Anime_List = new QAction(MainWindow);
        actionMy_Anime_List->setObjectName(QStringLiteral("actionMy_Anime_List"));
        actionMy_Anime_List->setEnabled(true);
        actionAnime_loads_org = new QAction(MainWindow);
        actionAnime_loads_org->setObjectName(QStringLiteral("actionAnime_loads_org"));
        actionAchievements = new QAction(MainWindow);
        actionAchievements->setObjectName(QStringLiteral("actionAchievements"));
        actionAchievements->setEnabled(false);
        actionImport_Another_List = new QAction(MainWindow);
        actionImport_Another_List->setObjectName(QStringLiteral("actionImport_Another_List"));
        actionImport_Another_List->setEnabled(true);
        actionSelect_My_List = new QAction(MainWindow);
        actionSelect_My_List->setObjectName(QStringLiteral("actionSelect_My_List"));
        actionSelect_My_List->setEnabled(true);
        actionExport_My_List = new QAction(MainWindow);
        actionExport_My_List->setObjectName(QStringLiteral("actionExport_My_List"));
        actionExport_My_List->setEnabled(true);
        actionFind_Anime = new QAction(MainWindow);
        actionFind_Anime->setObjectName(QStringLiteral("actionFind_Anime"));
        actionFind_Anime->setEnabled(true);
        actionChangelog = new QAction(MainWindow);
        actionChangelog->setObjectName(QStringLiteral("actionChangelog"));
        actionChangelog->setEnabled(false);
        actionShowStartedAnimesOnly = new QAction(MainWindow);
        actionShowStartedAnimesOnly->setObjectName(QStringLiteral("actionShowStartedAnimesOnly"));
        actionMake_Backup = new QAction(MainWindow);
        actionMake_Backup->setObjectName(QStringLiteral("actionMake_Backup"));
        actionCrunchyroll_com = new QAction(MainWindow);
        actionCrunchyroll_com->setObjectName(QStringLiteral("actionCrunchyroll_com"));
        actionKissanime_ru = new QAction(MainWindow);
        actionKissanime_ru->setObjectName(QStringLiteral("actionKissanime_ru"));
        actionShow_Movies_Only = new QAction(MainWindow);
        actionShow_Movies_Only->setObjectName(QStringLiteral("actionShow_Movies_Only"));
        actionShow_Movies_Only->setCheckable(false);
        actionShow_Movies_Only->setEnabled(true);
        actionHide_Movies = new QAction(MainWindow);
        actionHide_Movies->setObjectName(QStringLiteral("actionHide_Movies"));
        actionHide_Movies->setCheckable(false);
        actionHide_Movies->setEnabled(true);
        actionShow_Open_Ended_Animes = new QAction(MainWindow);
        actionShow_Open_Ended_Animes->setObjectName(QStringLiteral("actionShow_Open_Ended_Animes"));
        actionShow_Open_Ended_Animes->setCheckable(false);
        actionShow_Open_Ended_Animes->setEnabled(true);
        actionHide_Open_Ended_Animes = new QAction(MainWindow);
        actionHide_Open_Ended_Animes->setObjectName(QStringLiteral("actionHide_Open_Ended_Animes"));
        actionHide_Open_Ended_Animes->setCheckable(false);
        actionHide_Open_Ended_Animes->setEnabled(true);
        actionFilter_By_Tag = new QAction(MainWindow);
        actionFilter_By_Tag->setObjectName(QStringLiteral("actionFilter_By_Tag"));
        actionFilter_By_Tag->setEnabled(true);
        actionAnimefreak_tv = new QAction(MainWindow);
        actionAnimefreak_tv->setObjectName(QStringLiteral("actionAnimefreak_tv"));
        actionAnimefreak_tv->setEnabled(true);
        actionHide_Animes_with_Name_Only = new QAction(MainWindow);
        actionHide_Animes_with_Name_Only->setObjectName(QStringLiteral("actionHide_Animes_with_Name_Only"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
        gridLayout->setContentsMargins(20, 9, 20, -1);
        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 41, 4, 1, 1);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 39, 0, 1, 6);

        btnDecEpisode = new QPushButton(centralWidget);
        btnDecEpisode->setObjectName(QStringLiteral("btnDecEpisode"));
        btnDecEpisode->setMinimumSize(QSize(300, 50));
        QFont font1;
        font1.setPointSize(12);
        btnDecEpisode->setFont(font1);

        gridLayout->addWidget(btnDecEpisode, 13, 5, 1, 1);

        btnQuit = new QPushButton(centralWidget);
        btnQuit->setObjectName(QStringLiteral("btnQuit"));
        btnQuit->setMinimumSize(QSize(300, 60));
        btnQuit->setMaximumSize(QSize(160, 16777215));
        QFont font2;
        font2.setPointSize(16);
        btnQuit->setFont(font2);
        btnQuit->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(btnQuit, 41, 5, 1, 1);

        btnAddNewAnime = new QPushButton(centralWidget);
        btnAddNewAnime->setObjectName(QStringLiteral("btnAddNewAnime"));
        btnAddNewAnime->setMinimumSize(QSize(0, 60));
        btnAddNewAnime->setFont(font2);

        gridLayout->addWidget(btnAddNewAnime, 41, 0, 1, 1);

        btnIncEpisode = new QPushButton(centralWidget);
        btnIncEpisode->setObjectName(QStringLiteral("btnIncEpisode"));
        btnIncEpisode->setMinimumSize(QSize(300, 50));
        btnIncEpisode->setFont(font1);

        gridLayout->addWidget(btnIncEpisode, 11, 5, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 12, 5, 1, 1);

        btnEdit = new QPushButton(centralWidget);
        btnEdit->setObjectName(QStringLiteral("btnEdit"));
        btnEdit->setMinimumSize(QSize(300, 50));
        btnEdit->setFont(font1);

        gridLayout->addWidget(btnEdit, 20, 5, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_3, 21, 5, 1, 1);

        labListName = new QLabel(centralWidget);
        labListName->setObjectName(QStringLiteral("labListName"));
        labListName->setMinimumSize(QSize(0, 50));
        labListName->setFont(font2);
        labListName->setAutoFillBackground(false);
        labListName->setFrameShape(QFrame::Panel);
        labListName->setFrameShadow(QFrame::Raised);
        labListName->setScaledContents(false);
        labListName->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labListName, 5, 0, 1, 1);

        btnShowStartedAnimesOnly = new QPushButton(centralWidget);
        btnShowStartedAnimesOnly->setObjectName(QStringLiteral("btnShowStartedAnimesOnly"));
        btnShowStartedAnimesOnly->setEnabled(true);
        btnShowStartedAnimesOnly->setMinimumSize(QSize(420, 50));
        btnShowStartedAnimesOnly->setMaximumSize(QSize(16777215, 16777215));
        btnShowStartedAnimesOnly->setFont(font1);

        gridLayout->addWidget(btnShowStartedAnimesOnly, 3, 0, 1, 1);

        btnToggleAnimeLists = new QPushButton(centralWidget);
        btnToggleAnimeLists->setObjectName(QStringLiteral("btnToggleAnimeLists"));
        btnToggleAnimeLists->setMinimumSize(QSize(300, 60));
        btnToggleAnimeLists->setMaximumSize(QSize(300, 16777215));
        btnToggleAnimeLists->setFont(font1);
        btnToggleAnimeLists->setAcceptDrops(false);
        btnToggleAnimeLists->setAutoFillBackground(false);
        btnToggleAnimeLists->setCheckable(false);
        btnToggleAnimeLists->setFlat(false);

        gridLayout->addWidget(btnToggleAnimeLists, 3, 5, 1, 1);

        lvAnimes = new QListView(centralWidget);
        lvAnimes->setObjectName(QStringLiteral("lvAnimes"));
        lvAnimes->setMinimumSize(QSize(300, 400));
        lvAnimes->setFont(font);
        lvAnimes->setEditTriggers(QAbstractItemView::NoEditTriggers);

        gridLayout->addWidget(lvAnimes, 11, 0, 22, 1);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 38, 0, 1, 1);

        btnDelete = new QPushButton(centralWidget);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        btnDelete->setMinimumSize(QSize(300, 50));
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(false);
        font3.setWeight(50);
        btnDelete->setFont(font3);

        gridLayout->addWidget(btnDelete, 22, 5, 1, 1);

        btnGoToStream = new QPushButton(centralWidget);
        btnGoToStream->setObjectName(QStringLiteral("btnGoToStream"));
        btnGoToStream->setMinimumSize(QSize(300, 120));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        QBrush brush2(QColor(127, 127, 127, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush2);
        QBrush brush3(QColor(170, 170, 170, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        QBrush brush4(QColor(166, 0, 255, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        QBrush brush5(QColor(255, 255, 220, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush5);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        btnGoToStream->setPalette(palette);
        QFont font4;
        font4.setPointSize(20);
        font4.setBold(false);
        font4.setWeight(50);
        btnGoToStream->setFont(font4);

        gridLayout->addWidget(btnGoToStream, 30, 5, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuList = new QMenu(menuBar);
        menuList->setObjectName(QStringLiteral("menuList"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuWebsites = new QMenu(menuBar);
        menuWebsites->setObjectName(QStringLiteral("menuWebsites"));
        menuFilter = new QMenu(menuBar);
        menuFilter->setObjectName(QStringLiteral("menuFilter"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuList->menuAction());
        menuBar->addAction(menuFilter->menuAction());
        menuBar->addAction(menuWebsites->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuEdit->addAction(actionPreferences);
        menuList->addAction(actionSelect_My_List);
        menuList->addAction(actionImport_Another_List);
        menuList->addAction(actionExport_My_List);
        menuList->addSeparator();
        menuList->addAction(actionMake_Backup);
        menuList->addSeparator();
        menuHelp->addAction(actionAbout);
        menuWebsites->addAction(actionAnime_loads_org);
        menuWebsites->addAction(actionCrunchyroll_com);
        menuWebsites->addAction(actionKissanime_ru);
        menuWebsites->addAction(actionAnimefreak_tv);
        menuFilter->addAction(actionShow_Movies_Only);
        menuFilter->addAction(actionShow_Open_Ended_Animes);
        menuFilter->addSeparator();
        menuFilter->addAction(actionHide_Movies);
        menuFilter->addAction(actionHide_Open_Ended_Animes);
        menuFilter->addAction(actionHide_Animes_with_Name_Only);
        menuFilter->addSeparator();
        menuFilter->addAction(actionFilter_By_Tag);
        menuFilter->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Anwalic", 0));
        actionGerman->setText(QApplication::translate("MainWindow", "German", 0));
        actionEnglish->setText(QApplication::translate("MainWindow", "English", 0));
        actionHow_to_use_Anwalic->setText(QApplication::translate("MainWindow", "How to use Anwalic", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        actionUsername->setText(QApplication::translate("MainWindow", "Username", 0));
        actionWindow_Size->setText(QApplication::translate("MainWindow", "Window Size", 0));
        actionEntry_Width->setText(QApplication::translate("MainWindow", "Entry Width", 0));
        actionEntry_Font_Size->setText(QApplication::translate("MainWindow", "List Item Font Size", 0));
        actionBackground->setText(QApplication::translate("MainWindow", "Background", 0));
        actionPreferences->setText(QApplication::translate("MainWindow", "Preferences", 0));
        actionCompleted_Animes->setText(QApplication::translate("MainWindow", "Completed Animes", 0));
        actionMy_Anime_List->setText(QApplication::translate("MainWindow", "My Anime List", 0));
        actionAnime_loads_org->setText(QApplication::translate("MainWindow", "anime-loads.org", 0));
        actionAchievements->setText(QApplication::translate("MainWindow", "Achievements", 0));
        actionImport_Another_List->setText(QApplication::translate("MainWindow", "Import Another List", 0));
        actionSelect_My_List->setText(QApplication::translate("MainWindow", "Select My List", 0));
        actionExport_My_List->setText(QApplication::translate("MainWindow", "Export My List", 0));
        actionFind_Anime->setText(QApplication::translate("MainWindow", "find Anime", 0));
        actionChangelog->setText(QApplication::translate("MainWindow", "Changelog", 0));
        actionShowStartedAnimesOnly->setText(QApplication::translate("MainWindow", "ShowStartedAnimesOnly", 0));
        actionMake_Backup->setText(QApplication::translate("MainWindow", "Create Backup", 0));
        actionCrunchyroll_com->setText(QApplication::translate("MainWindow", "crunchyroll.com", 0));
        actionKissanime_ru->setText(QApplication::translate("MainWindow", "kissanime.ru", 0));
        actionShow_Movies_Only->setText(QApplication::translate("MainWindow", "Show Movies", 0));
        actionHide_Movies->setText(QApplication::translate("MainWindow", "Hide Movies", 0));
        actionShow_Open_Ended_Animes->setText(QApplication::translate("MainWindow", "Show Open Ended Animes", 0));
        actionHide_Open_Ended_Animes->setText(QApplication::translate("MainWindow", "Hide Open Ended Animes", 0));
        actionFilter_By_Tag->setText(QApplication::translate("MainWindow", "Filter By Tag", 0));
        actionAnimefreak_tv->setText(QApplication::translate("MainWindow", "animefreak.tv", 0));
        actionHide_Animes_with_Name_Only->setText(QApplication::translate("MainWindow", "Hide Animes with Name Only", 0));
#ifndef QT_NO_TOOLTIP
        btnDecEpisode->setToolTip(QApplication::translate("MainWindow", "decrement Episode by one", 0));
#endif // QT_NO_TOOLTIP
        btnDecEpisode->setText(QApplication::translate("MainWindow", "Episode -1", 0));
#ifndef QT_NO_TOOLTIP
        btnQuit->setToolTip(QApplication::translate("MainWindow", "Quits program. Your list is always automatically saved", 0));
#endif // QT_NO_TOOLTIP
        btnQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
#ifndef QT_NO_TOOLTIP
        btnAddNewAnime->setToolTip(QApplication::translate("MainWindow", "Adds new Anime to the list above", 0));
#endif // QT_NO_TOOLTIP
        btnAddNewAnime->setText(QApplication::translate("MainWindow", "Add New Anime", 0));
#ifndef QT_NO_TOOLTIP
        btnIncEpisode->setToolTip(QApplication::translate("MainWindow", "increment Episode by one", 0));
#endif // QT_NO_TOOLTIP
        btnIncEpisode->setText(QApplication::translate("MainWindow", "Episode +1", 0));
#ifndef QT_NO_TOOLTIP
        btnEdit->setToolTip(QApplication::translate("MainWindow", "edit name, episodes & url", 0));
#endif // QT_NO_TOOLTIP
        btnEdit->setText(QApplication::translate("MainWindow", "Edit", 0));
        labListName->setText(QApplication::translate("MainWindow", "My Anime List", 0));
#ifndef QT_NO_TOOLTIP
        btnShowStartedAnimesOnly->setToolTip(QApplication::translate("MainWindow", "only shows entries in Anime List with Episode > 1", 0));
#endif // QT_NO_TOOLTIP
        btnShowStartedAnimesOnly->setText(QApplication::translate("MainWindow", "Show Started Animes Only", 0));
#ifndef QT_NO_TOOLTIP
        btnToggleAnimeLists->setToolTip(QApplication::translate("MainWindow", "view your Completed Animes. click again to go back", 0));
#endif // QT_NO_TOOLTIP
        btnToggleAnimeLists->setText(QApplication::translate("MainWindow", "Toggle\n"
"Completed Animes <-> My Anime List", 0));
#ifndef QT_NO_TOOLTIP
        btnDelete->setToolTip(QApplication::translate("MainWindow", "remove Anime from list forever", 0));
#endif // QT_NO_TOOLTIP
        btnDelete->setText(QApplication::translate("MainWindow", "Delete", 0));
#ifndef QT_NO_TOOLTIP
        btnGoToStream->setToolTip(QApplication::translate("MainWindow", "starts your browser with specified URL", 0));
#endif // QT_NO_TOOLTIP
        btnGoToStream->setText(QApplication::translate("MainWindow", "Go To Stream", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
        menuList->setTitle(QApplication::translate("MainWindow", "List", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menuWebsites->setTitle(QApplication::translate("MainWindow", "Websites", 0));
        menuFilter->setTitle(QApplication::translate("MainWindow", "Filter", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
