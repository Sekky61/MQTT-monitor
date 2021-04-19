/********************************************************************************
** Form generated from reading UI file 'new_connection.ui'
**
** Created by: Qt User Interface Compiler version 6.0.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEW_CONNECTION_H
#define UI_NEW_CONNECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_new_connection
{
public:
    QFrame *frame;
    QLabel *label;
    QLabel *label_6;
    QGroupBox *connection_data;
    QPushButton *connect_f;
    QPushButton *save_f;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_5;
    QLabel *protokol_line;
    QLineEdit *protocol_line;
    QWidget *layout;
    QVBoxLayout *verticalLayout_6;
    QLabel *Port_line;
    QLineEdit *port_line;
    QCheckBox *check_validate;
    QCheckBox *check_encryption;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLineEdit *connectionName_line;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QLineEdit *host_line;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QLineEdit *username_line;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_5;
    QLineEdit *password_line;
    QFrame *frame_2;
    QPushButton *delete_button;
    QListWidget *listWidget;
    QPushButton *loadButton;
    QFrame *separate_line;

    void setupUi(QDialog *new_connection)
    {
        if (new_connection->objectName().isEmpty())
            new_connection->setObjectName(QString::fromUtf8("new_connection"));
        new_connection->resize(758, 433);
        frame = new QFrame(new_connection);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 761, 51));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(230, 0, 181, 41));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 0, 201, 41));
        QFont font1;
        font1.setPointSize(10);
        label_6->setFont(font1);
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        connection_data = new QGroupBox(new_connection);
        connection_data->setObjectName(QString::fromUtf8("connection_data"));
        connection_data->setGeometry(QRect(230, 50, 531, 391));
        connection_data->setStyleSheet(QString::fromUtf8("background-color: rgb(236, 236, 236);"));
        connection_data->setFlat(false);
        connect_f = new QPushButton(connection_data);
        connect_f->setObjectName(QString::fromUtf8("connect_f"));
        connect_f->setGeometry(QRect(344, 292, 121, 41));
        connect_f->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(77, 121, 140);"));
        save_f = new QPushButton(connection_data);
        save_f->setObjectName(QString::fromUtf8("save_f"));
        save_f->setGeometry(QRect(224, 292, 111, 41));
        save_f->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(218, 206, 112);"));
        layoutWidget5 = new QWidget(connection_data);
        layoutWidget5->setObjectName(QString::fromUtf8("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(20, 120, 81, 41));
        verticalLayout_5 = new QVBoxLayout(layoutWidget5);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        protokol_line = new QLabel(layoutWidget5);
        protokol_line->setObjectName(QString::fromUtf8("protokol_line"));

        verticalLayout_5->addWidget(protokol_line);

        protocol_line = new QLineEdit(layoutWidget5);
        protocol_line->setObjectName(QString::fromUtf8("protocol_line"));
        protocol_line->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        verticalLayout_5->addWidget(protocol_line);

        layout = new QWidget(connection_data);
        layout->setObjectName(QString::fromUtf8("layout"));
        layout->setGeometry(QRect(320, 120, 71, 41));
        verticalLayout_6 = new QVBoxLayout(layout);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        Port_line = new QLabel(layout);
        Port_line->setObjectName(QString::fromUtf8("Port_line"));

        verticalLayout_6->addWidget(Port_line);

        port_line = new QLineEdit(layout);
        port_line->setObjectName(QString::fromUtf8("port_line"));
        port_line->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        verticalLayout_6->addWidget(port_line);

        check_validate = new QCheckBox(connection_data);
        check_validate->setObjectName(QString::fromUtf8("check_validate"));
        check_validate->setGeometry(QRect(240, 30, 121, 41));
        check_encryption = new QCheckBox(connection_data);
        check_encryption->setObjectName(QString::fromUtf8("check_encryption"));
        check_encryption->setGeometry(QRect(380, 30, 91, 41));
        layoutWidget4 = new QWidget(connection_data);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(20, 30, 135, 41));
        verticalLayout = new QVBoxLayout(layoutWidget4);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget4);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        connectionName_line = new QLineEdit(layoutWidget4);
        connectionName_line->setObjectName(QString::fromUtf8("connectionName_line"));
        connectionName_line->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(connectionName_line);

        layoutWidget3 = new QWidget(connection_data);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(114, 120, 191, 41));
        verticalLayout_2 = new QVBoxLayout(layoutWidget3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        host_line = new QLineEdit(layoutWidget3);
        host_line->setObjectName(QString::fromUtf8("host_line"));
        host_line->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        verticalLayout_2->addWidget(host_line);

        layoutWidget2 = new QWidget(connection_data);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(20, 200, 135, 41));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_3->addWidget(label_4);

        username_line = new QLineEdit(layoutWidget2);
        username_line->setObjectName(QString::fromUtf8("username_line"));
        username_line->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        verticalLayout_3->addWidget(username_line);

        layoutWidget1 = new QWidget(connection_data);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(170, 200, 135, 41));
        verticalLayout_4 = new QVBoxLayout(layoutWidget1);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_4->addWidget(label_5);

        password_line = new QLineEdit(layoutWidget1);
        password_line->setObjectName(QString::fromUtf8("password_line"));
        password_line->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        password_line->setEchoMode(QLineEdit::Password);

        verticalLayout_4->addWidget(password_line);

        frame_2 = new QFrame(new_connection);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(10, 60, 211, 361));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        delete_button = new QPushButton(frame_2);
        delete_button->setObjectName(QString::fromUtf8("delete_button"));
        delete_button->setGeometry(QRect(124, 322, 81, 31));
        listWidget = new QListWidget(frame_2);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(-5, 1, 221, 361));
        loadButton = new QPushButton(frame_2);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        loadButton->setGeometry(QRect(130, 10, 75, 23));
        listWidget->raise();
        delete_button->raise();
        loadButton->raise();
        separate_line = new QFrame(new_connection);
        separate_line->setObjectName(QString::fromUtf8("separate_line"));
        separate_line->setGeometry(QRect(220, -20, 20, 461));
        separate_line->setStyleSheet(QString::fromUtf8(""));
        separate_line->setFrameShape(QFrame::VLine);
        separate_line->setFrameShadow(QFrame::Sunken);
        QWidget::setTabOrder(connectionName_line, protocol_line);
        QWidget::setTabOrder(protocol_line, host_line);
        QWidget::setTabOrder(host_line, port_line);
        QWidget::setTabOrder(port_line, username_line);
        QWidget::setTabOrder(username_line, password_line);
        QWidget::setTabOrder(password_line, save_f);
        QWidget::setTabOrder(save_f, connect_f);
        QWidget::setTabOrder(connect_f, check_validate);
        QWidget::setTabOrder(check_validate, check_encryption);
        QWidget::setTabOrder(check_encryption, delete_button);

        retranslateUi(new_connection);

        QMetaObject::connectSlotsByName(new_connection);
    } // setupUi

    void retranslateUi(QDialog *new_connection)
    {
        new_connection->setWindowTitle(QString());
        label->setText(QCoreApplication::translate("new_connection", "MQTT Conection", nullptr));
        label_6->setText(QCoreApplication::translate("new_connection", "Saved Connections", nullptr));
        connection_data->setTitle(QString());
        connect_f->setText(QCoreApplication::translate("new_connection", "CONNECT", nullptr));
        save_f->setText(QCoreApplication::translate("new_connection", "SAVE", nullptr));
        protokol_line->setText(QCoreApplication::translate("new_connection", "Protokol", nullptr));
        Port_line->setText(QCoreApplication::translate("new_connection", "Port", nullptr));
        check_validate->setText(QCoreApplication::translate("new_connection", "Validate certificate", nullptr));
        check_encryption->setText(QCoreApplication::translate("new_connection", "Encryption", nullptr));
        label_2->setText(QCoreApplication::translate("new_connection", "Connection name", nullptr));
        label_3->setText(QCoreApplication::translate("new_connection", "Host", nullptr));
        label_4->setText(QCoreApplication::translate("new_connection", "Username", nullptr));
        label_5->setText(QCoreApplication::translate("new_connection", "Password", nullptr));
        delete_button->setText(QCoreApplication::translate("new_connection", "DELETE", nullptr));
        loadButton->setText(QCoreApplication::translate("new_connection", "LOAD", nullptr));
    } // retranslateUi

};

namespace Ui {
    class new_connection: public Ui_new_connection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEW_CONNECTION_H
