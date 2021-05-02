#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardPaths>

Dialog::Dialog(QWidget *parent, QPixmap screen_map) :
    QDialog(parent),
    screen(screen_map),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Printscreen");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_print_save_clicked()
{
    QString location = ui->location->toPlainText();
    screen.save(location, "JPG");
    close();
}

void Dialog::on_directory_button_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QDir::currentPath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->location->setText(dir+"/screenshot.jpg");
}
