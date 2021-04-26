#include "snapshot.h"
#include "ui_snapshot.h"
#include "mainwindow.h"
#include "dialog.h"
#include "ui_mainwindow.h"

#include "snapshot_manager.h"
#include <QDir>

Snapshot::Snapshot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Snapshot)
{
    ui->setupUi(this);
    this->setWindowTitle("Snapshot");
}

Snapshot::~Snapshot()
{
    delete ui;
}

void Snapshot::on_print_save_clicked()
{
    QString path = ui->snap_location->toPlainText();
    QDir root = QDir(path);

    emit save_tree_structure(root);
}

void Snapshot::on_directory_button_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->snap_location->setText(dir);
}
