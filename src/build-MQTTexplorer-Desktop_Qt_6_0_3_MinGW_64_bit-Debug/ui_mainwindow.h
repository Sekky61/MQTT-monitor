/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.0.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionAbout_Aplication;
    QAction *actionQuit;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionSelect_All;
    QAction *actionDefault_size;
    QAction *actionIncrease_size;
    QAction *actionReduce_size;
    QAction *actionPaste;
    QAction *actionjde_to;
    QWidget *centralwidget;
    QFrame *frame_menu;
    QPushButton *Explorer_button;
    QPushButton *Dash_button;
    QStackedWidget *Pages;
    QWidget *page;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QWidget *layoutWidget_main;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *copy_topic_2;
    QLineEdit *topic_search;
    QPushButton *delete_topic_2;
    QPushButton *add_topic;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *Stats_label;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *path_message;
    QLabel *Message_label;
    QLabel *value_label;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_3;
    QPushButton *publish_button;
    QTextEdit *textEdit;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_4;
    QGraphicsView *graphicsView;
    QLabel *value_label_3;
    QScrollArea *scrollArea_4;
    QWidget *scrollAreaWidgetContents_8;
    QGraphicsView *graphicsView_3;
    QTreeView *treeView;
    QFrame *frame;
    QLabel *sing_label;
    QLineEdit *lineEdit;
    QPushButton *searchButton;
    QPushButton *buttonConnect;
    QPushButton *button_disconnect;
    QWidget *page_2;
    QFrame *frame_2;
    QLabel *sing_label_3;
    QFrame *frame_3;
    QPushButton *toogle_button;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuView;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1150, 850);
        MainWindow->setMaximumSize(QSize(1150, 850));
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionAbout_Aplication = new QAction(MainWindow);
        actionAbout_Aplication->setObjectName(QString::fromUtf8("actionAbout_Aplication"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionQuit->setCheckable(false);
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        actionUndo->setCheckable(false);
        actionUndo->setChecked(false);
        actionUndo->setEnabled(true);
        actionUndo->setVisible(true);
        actionUndo->setShortcutVisibleInContextMenu(true);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionSelect_All = new QAction(MainWindow);
        actionSelect_All->setObjectName(QString::fromUtf8("actionSelect_All"));
        actionDefault_size = new QAction(MainWindow);
        actionDefault_size->setObjectName(QString::fromUtf8("actionDefault_size"));
        actionIncrease_size = new QAction(MainWindow);
        actionIncrease_size->setObjectName(QString::fromUtf8("actionIncrease_size"));
        actionReduce_size = new QAction(MainWindow);
        actionReduce_size->setObjectName(QString::fromUtf8("actionReduce_size"));
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        actionjde_to = new QAction(MainWindow);
        actionjde_to->setObjectName(QString::fromUtf8("actionjde_to"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMaximumSize(QSize(1200, 800));
        frame_menu = new QFrame(centralwidget);
        frame_menu->setObjectName(QString::fromUtf8("frame_menu"));
        frame_menu->setGeometry(QRect(0, 80, 81, 835));
        frame_menu->setMaximumSize(QSize(16777215, 16777215));
        frame_menu->setLayoutDirection(Qt::LeftToRight);
        frame_menu->setAutoFillBackground(false);
        frame_menu->setStyleSheet(QString::fromUtf8("background-color: rgb(103, 103, 103);"));
        frame_menu->setFrameShape(QFrame::StyledPanel);
        frame_menu->setFrameShadow(QFrame::Raised);
        Explorer_button = new QPushButton(frame_menu);
        Explorer_button->setObjectName(QString::fromUtf8("Explorer_button"));
        Explorer_button->setGeometry(QRect(0, 0, 81, 41));
        QFont font;
        font.setPointSize(7);
        font.setBold(true);
        Explorer_button->setFont(font);
        Explorer_button->setAutoFillBackground(false);
        Explorer_button->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	color: rgb(255, 255, 255);\n"
"	background-color: rgb(103, 103, 103);\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: rgb(77, 121, 140);\n"
"}"));
        Explorer_button->setFlat(true);
        Dash_button = new QPushButton(frame_menu);
        Dash_button->setObjectName(QString::fromUtf8("Dash_button"));
        Dash_button->setGeometry(QRect(0, 50, 81, 31));
        Dash_button->setFont(font);
        Dash_button->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	color: rgb(255, 255, 255);\n"
"	background-color: rgb(103, 103, 103);\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: rgb(77, 121, 140);\n"
"}"));
        Dash_button->setFlat(true);
        Pages = new QStackedWidget(centralwidget);
        Pages->setObjectName(QString::fromUtf8("Pages"));
        Pages->setGeometry(QRect(80, 0, 1071, 791));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        scrollArea = new QScrollArea(page);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(430, 80, 641, 751));
        scrollArea->setStyleSheet(QString::fromUtf8("border-color: rgb(255, 255, 255);"));
        scrollArea->setLineWidth(0);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 639, 749));
        layoutWidget_main = new QWidget(scrollAreaWidgetContents_2);
        layoutWidget_main->setObjectName(QString::fromUtf8("layoutWidget_main"));
        layoutWidget_main->setGeometry(QRect(70, 10, 501, 71));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_main);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        copy_topic_2 = new QPushButton(layoutWidget_main);
        copy_topic_2->setObjectName(QString::fromUtf8("copy_topic_2"));
        copy_topic_2->setAutoFillBackground(false);
        copy_topic_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(77, 121, 140);"));
        copy_topic_2->setFlat(false);

        horizontalLayout_2->addWidget(copy_topic_2);

        topic_search = new QLineEdit(layoutWidget_main);
        topic_search->setObjectName(QString::fromUtf8("topic_search"));
        topic_search->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"border: 2px solid rgb(37,39,48);\n"
"border-left:none;\n"
"border-right:none;\n"
"border-top:none;\n"
"border-radius: 20px;\n"
"}"));
        topic_search->setClearButtonEnabled(true);

        horizontalLayout_2->addWidget(topic_search);

        delete_topic_2 = new QPushButton(layoutWidget_main);
        delete_topic_2->setObjectName(QString::fromUtf8("delete_topic_2"));
        delete_topic_2->setAutoFillBackground(false);
        delete_topic_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(77, 121, 140);"));
        delete_topic_2->setFlat(false);

        horizontalLayout_2->addWidget(delete_topic_2);

        add_topic = new QPushButton(layoutWidget_main);
        add_topic->setObjectName(QString::fromUtf8("add_topic"));
        add_topic->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(77, 121, 140);"));

        horizontalLayout_2->addWidget(add_topic);

        layoutWidget = new QWidget(scrollAreaWidgetContents_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 590, 131, 111));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Stats_label = new QLabel(layoutWidget);
        Stats_label->setObjectName(QString::fromUtf8("Stats_label"));
        QFont font1;
        font1.setPointSize(12);
        Stats_label->setFont(font1);
        Stats_label->setStyleSheet(QString::fromUtf8("color:rgb(191, 191, 191);"));

        verticalLayout->addWidget(Stats_label);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        path_message = new QLineEdit(scrollAreaWidgetContents_2);
        path_message->setObjectName(QString::fromUtf8("path_message"));
        path_message->setGeometry(QRect(70, 120, 221, 20));
        path_message->setAutoFillBackground(false);
        path_message->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"border: 2px solid rgb(37,39,48);\n"
"border-left:none;\n"
"border-right:none;\n"
"border-top:none;\n"
"border-radius: 20px;\n"
"}"));
        path_message->setClearButtonEnabled(true);
        Message_label = new QLabel(scrollAreaWidgetContents_2);
        Message_label->setObjectName(QString::fromUtf8("Message_label"));
        Message_label->setGeometry(QRect(70, 90, 61, 21));
        Message_label->setFont(font1);
        Message_label->setStyleSheet(QString::fromUtf8("color:rgb(191, 191, 191);"));
        value_label = new QLabel(scrollAreaWidgetContents_2);
        value_label->setObjectName(QString::fromUtf8("value_label"));
        value_label->setGeometry(QRect(70, 300, 71, 21));
        value_label->setFont(font1);
        value_label->setStyleSheet(QString::fromUtf8("color:rgb(191, 191, 191);"));
        scrollArea_2 = new QScrollArea(scrollAreaWidgetContents_2);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(70, 150, 531, 141));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 529, 139));
        publish_button = new QPushButton(scrollAreaWidgetContents_3);
        publish_button->setObjectName(QString::fromUtf8("publish_button"));
        publish_button->setGeometry(QRect(420, 100, 101, 31));
        publish_button->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(77, 121, 140);"));
        textEdit = new QTextEdit(scrollAreaWidgetContents_3);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(0, -10, 531, 151));
        scrollArea_2->setWidget(scrollAreaWidgetContents_3);
        textEdit->raise();
        publish_button->raise();
        scrollArea_3 = new QScrollArea(scrollAreaWidgetContents_2);
        scrollArea_3->setObjectName(QString::fromUtf8("scrollArea_3"));
        scrollArea_3->setGeometry(QRect(70, 330, 531, 101));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 529, 99));
        graphicsView = new QGraphicsView(scrollAreaWidgetContents_4);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(-10, -10, 561, 111));
        scrollArea_3->setWidget(scrollAreaWidgetContents_4);
        value_label_3 = new QLabel(scrollAreaWidgetContents_2);
        value_label_3->setObjectName(QString::fromUtf8("value_label_3"));
        value_label_3->setGeometry(QRect(70, 440, 71, 21));
        value_label_3->setFont(font1);
        value_label_3->setStyleSheet(QString::fromUtf8("color:rgb(191, 191, 191);"));
        scrollArea_4 = new QScrollArea(scrollAreaWidgetContents_2);
        scrollArea_4->setObjectName(QString::fromUtf8("scrollArea_4"));
        scrollArea_4->setGeometry(QRect(70, 470, 531, 101));
        scrollArea_4->setWidgetResizable(true);
        scrollAreaWidgetContents_8 = new QWidget();
        scrollAreaWidgetContents_8->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_8"));
        scrollAreaWidgetContents_8->setGeometry(QRect(0, 0, 529, 99));
        graphicsView_3 = new QGraphicsView(scrollAreaWidgetContents_8);
        graphicsView_3->setObjectName(QString::fromUtf8("graphicsView_3"));
        graphicsView_3->setGeometry(QRect(-5, -9, 541, 111));
        scrollArea_4->setWidget(scrollAreaWidgetContents_8);
        scrollArea->setWidget(scrollAreaWidgetContents_2);
        treeView = new QTreeView(page);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setGeometry(QRect(0, 80, 431, 721));
        treeView->header()->setVisible(false);
        frame = new QFrame(page);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(-70, 0, 1151, 80));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(77, 121, 140);"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        sing_label = new QLabel(frame);
        sing_label->setObjectName(QString::fromUtf8("sing_label"));
        sing_label->setGeometry(QRect(130, 20, 211, 41));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Rockwell"));
        font2.setPointSize(18);
        sing_label->setFont(font2);
        sing_label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        sing_label->setAlignment(Qt::AlignCenter);
        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(370, 20, 341, 41));
        lineEdit->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"background-color: rgb(121, 162, 180);\n"
"border: 2px solid rgb(255,255,255);\n"
"border-radius: 20px;\n"
"}"));
        lineEdit->setReadOnly(false);
        lineEdit->setClearButtonEnabled(true);
        searchButton = new QPushButton(frame);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));
        searchButton->setGeometry(QRect(740, 20, 91, 41));
        searchButton->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        buttonConnect = new QPushButton(frame);
        buttonConnect->setObjectName(QString::fromUtf8("buttonConnect"));
        buttonConnect->setGeometry(QRect(850, 20, 111, 41));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Poor Richard"));
        font3.setPointSize(14);
        buttonConnect->setFont(font3);
        buttonConnect->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(77, 121, 140);"));
        buttonConnect->setFlat(true);
        button_disconnect = new QPushButton(frame);
        button_disconnect->setObjectName(QString::fromUtf8("button_disconnect"));
        button_disconnect->setGeometry(QRect(970, 20, 131, 41));
        button_disconnect->setFont(font3);
        button_disconnect->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(77, 121, 140);"));
        button_disconnect->setFlat(true);
        Pages->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        frame_2 = new QFrame(page_2);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(-70, 0, 1151, 80));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(77, 121, 140);"));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        sing_label_3 = new QLabel(frame_2);
        sing_label_3->setObjectName(QString::fromUtf8("sing_label_3"));
        sing_label_3->setGeometry(QRect(490, 20, 211, 41));
        sing_label_3->setMinimumSize(QSize(211, 41));
        sing_label_3->setFont(font2);
        sing_label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        sing_label_3->setAlignment(Qt::AlignCenter);
        Pages->addWidget(page_2);
        frame_3 = new QFrame(centralwidget);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(0, 0, 81, 80));
        frame_3->setAutoFillBackground(false);
        frame_3->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        toogle_button = new QPushButton(frame_3);
        toogle_button->setObjectName(QString::fromUtf8("toogle_button"));
        toogle_button->setGeometry(QRect(0, 0, 81, 81));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(toogle_button->sizePolicy().hasHeightForWidth());
        toogle_button->setSizePolicy(sizePolicy);
        QFont font4;
        font4.setPointSize(10);
        toogle_button->setFont(font4);
        toogle_button->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 0);"));
        MainWindow->setCentralWidget(centralwidget);
        Pages->raise();
        frame_3->raise();
        frame_menu->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1150, 21));
        menubar->setFocusPolicy(Qt::NoFocus);
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuEdit->setAutoFillBackground(false);
        menuEdit->setTearOffEnabled(false);
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        MainWindow->setMenuBar(menubar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuView->menuAction());
        menuFile->addAction(actionAbout_Aplication);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addAction(actionSelect_All);
        menuView->addAction(actionDefault_size);
        menuView->addAction(actionIncrease_size);
        menuView->addAction(actionReduce_size);

        retranslateUi(MainWindow);

        Pages->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MQTT Explorer", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
        actionAbout_Aplication->setText(QCoreApplication::translate("MainWindow", "About Aplication", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        actionUndo->setText(QCoreApplication::translate("MainWindow", "Undo         Ctrl+Z", nullptr));
        actionRedo->setText(QCoreApplication::translate("MainWindow", "Redo          Ctrl+Shift+Z", nullptr));
        actionCut->setText(QCoreApplication::translate("MainWindow", "Cut              Ctrl+X", nullptr));
        actionCopy->setText(QCoreApplication::translate("MainWindow", "Copy          Ctrl+C", nullptr));
        actionSelect_All->setText(QCoreApplication::translate("MainWindow", "Select All    Ctrl+A", nullptr));
        actionDefault_size->setText(QCoreApplication::translate("MainWindow", "Default size", nullptr));
        actionIncrease_size->setText(QCoreApplication::translate("MainWindow", "Increase size", nullptr));
        actionReduce_size->setText(QCoreApplication::translate("MainWindow", "Reduce size", nullptr));
        actionPaste->setText(QCoreApplication::translate("MainWindow", "Paste          Ctrl+V", nullptr));
        actionjde_to->setText(QCoreApplication::translate("MainWindow", "jde to?", nullptr));
        Explorer_button->setText(QCoreApplication::translate("MainWindow", "EXPLORER", nullptr));
        Dash_button->setText(QCoreApplication::translate("MainWindow", "DASHBOARD", nullptr));
        copy_topic_2->setText(QCoreApplication::translate("MainWindow", "Copy path", nullptr));
        topic_search->setPlaceholderText(QCoreApplication::translate("MainWindow", " Insert tree path...", nullptr));
        delete_topic_2->setText(QCoreApplication::translate("MainWindow", "Delete sub-topics", nullptr));
        add_topic->setText(QCoreApplication::translate("MainWindow", "Add topic", nullptr));
        Stats_label->setText(QCoreApplication::translate("MainWindow", "Stats", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Messages:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Subtopics:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Messages Subtopics:", nullptr));
        path_message->setPlaceholderText(QCoreApplication::translate("MainWindow", "Where to send your message?...", nullptr));
        Message_label->setText(QCoreApplication::translate("MainWindow", "Topic", nullptr));
        value_label->setText(QCoreApplication::translate("MainWindow", "Value", nullptr));
        publish_button->setText(QCoreApplication::translate("MainWindow", "PUBLISH", nullptr));
        value_label_3->setText(QCoreApplication::translate("MainWindow", "History", nullptr));
        sing_label->setText(QCoreApplication::translate("MainWindow", "MQTT Explorer", nullptr));
        lineEdit->setInputMask(QString());
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", " Search...", nullptr));
        searchButton->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        buttonConnect->setText(QCoreApplication::translate("MainWindow", "CONNECT", nullptr));
        button_disconnect->setText(QCoreApplication::translate("MainWindow", "DISCONNECT", nullptr));
        sing_label_3->setText(QCoreApplication::translate("MainWindow", "DASHBOARD", nullptr));
        toogle_button->setText(QCoreApplication::translate("MainWindow", "PAGES", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "Application", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
