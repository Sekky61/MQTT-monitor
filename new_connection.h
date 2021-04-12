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

namespace Ui {
class new_connection;
}

class new_connection : public QDialog
{
    Q_OBJECT

public:
    explicit new_connection(QWidget *parent = nullptr);
    ~new_connection();

private slots:
    void on_connect_f_clicked();

    void on_save_f_clicked();

private:
    Ui::new_connection *ui;
};

#endif // NEW_CONNECTION_H
