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

#include <unordered_map>

#include "topicmodel.h"
#include "new_connection.h"
#include "client.h"
#include "flow_layout.h"

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

signals:

    void connect_client_mainwindow(QString client_name, QString server_address);

    void add_topic_clicked(QString topic_string);

    void delete_topic_clicked(QString topic_string);

    void publish_clicked(QString topic_string, QString content_string);

    void tree_data_changed();

private slots:

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

    void on_add_topic_clicked();

    void on_publish_button_clicked();

    void on_Explorer_button_clicked();

    void on_Dash_button_clicked();

    void on_img_msg_clicked();

    void on_treeView_customContextMenuRequested(const QPoint &pos);

    void context_copy_topic();

    void delete_subtopics();

    void unsubscribe_context();

    // add to dashboard

    void add_to_dashboard_plain_text();

    void add_to_dashboard_thermostat();

    void add_to_dashboard_thermometer();

    void add_to_dashboard_camera();

    void show_pic_from_topic(QString);

    void add_to_dashboard_light();

    void add_to_dashboard_humidity();

    void tree_clicked(const QModelIndex &index);


public slots:

    void mqtt_data_changed_slot(QString, QString);

    void display_history(const QModelIndex &index);

    void connection_succesful_slot();

    void on_screenshot_button_clicked();

    void on_snap_button_clicked();

    void save_tree_structure_slot(QDir);

private:

    void init_tree_context_menu();

    void popup_picture(std::string);

    void display_message();

    client cli;
    TopicModel mod;

    Ui::MainWindow *ui;

    QMenu *tree_context_menu;
    QModelIndex context_menu_target;

    TopicNode *active_node;

    new_connection *connection_window;

    FlowLayout *tiles_layout;
};
#endif // MAINWINDOW_H
