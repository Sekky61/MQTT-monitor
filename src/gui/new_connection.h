#ifndef NEW_CONNECTION_H
#define NEW_CONNECTION_H

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

namespace Ui {
class new_connection;
}

class Profile {
public:
    Profile() {}

    Profile(QString csv_line){
        QStringList attributes = csv_line.split(";");
        name = attributes[0];
        username = attributes[1];
        password = attributes[2];

        protocol = attributes[3];
        host = attributes[4];
        port = attributes[5];
    }


    QString username;
    QString password;
    QString name;

    QString protocol;
    QString host;
    QString port;
};

class ProfilesListModel : public QAbstractListModel {
public:

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QList<Profile> profile_list;
};

class new_connection : public QDialog
{
    Q_OBJECT


public:
    explicit new_connection(QWidget *parent = nullptr);
    ~new_connection();

private slots:
    void on_connect_f_clicked();
    void on_save_f_clicked();
    void on_delete_button_clicked();
    void save_profile(Profile);
    void on_listView_doubleClicked(const QModelIndex &index);

private:
    Ui::new_connection *ui;
    ProfilesListModel *model_con;
    //QMessageBox *mBox = new QMessageBox;
};

#endif // NEW_CONNECTION_H
