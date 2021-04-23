#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QApplication>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QSortFilterProxyModel>
#include <QTreeView>
#include <QFileSystemModel>

#include "topicmodel.h"
#include "new_connection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(); //destruktor
    QSortFilterProxyModel * proxy_tree;

    void set_tree_model(TopicModel *mod);

signals:

    void connect_client_mainwindow(QString client_name, QString server_address);

    void add_topic_clicked(QString topic_string);

    void publish_clicked(QString topic_string, QString content_string);

private slots:

    void display_message(const QModelIndex &index);

    void connect_to_client_from_dialog(QString client_name, QString server_address);

    void on_actionQuit_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionSelect_All_triggered();

    void on_actionAbout_Aplication_triggered();

    void on_actionDefault_size_triggered();

    void on_buttonConnect_clicked();

    void on_searchButton_clicked();

    void on_add_topic_clicked();

    void on_copy_topic_2_clicked();

    void on_delete_topic_2_clicked();

    void on_publish_button_clicked();

    void on_Explorer_button_clicked();

    void on_Dash_button_clicked();

    void on_img_msg_clicked();

    void on_dumpButton_clicked();

public slots:

    void connection_succesful_slot();

private:
    Ui::MainWindow *ui;
    QString current_file = ""; //jméno souboru ve kterém pracujeme
    QStandardItemModel model;
    TopicModel *mod;

    new_connection *connection_window;
};
#endif // MAINWINDOW_H
