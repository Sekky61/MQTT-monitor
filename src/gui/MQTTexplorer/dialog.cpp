#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
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
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap *map = new QPixmap(screen->grabWindow(0));
    map->save(location, "JPG");

}

void Dialog::on_directory_button_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->location->setText(dir+"/payload.jpg");
}
