#include "aboutapplication.h"
#include "ui_aboutapplication.h"

AboutApplication::AboutApplication(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutApplication)
{
    ui->setupUi(this);
}

AboutApplication::~AboutApplication()
{
    delete ui;
}
