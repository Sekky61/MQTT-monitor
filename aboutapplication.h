#ifndef ABOUTAPPLICATION_H
#define ABOUTAPPLICATION_H

#include <QDialog>

namespace Ui {
class AboutApplication;
}

class AboutApplication : public QDialog
{
    Q_OBJECT

public:
    explicit AboutApplication(QWidget *parent = nullptr);
    ~AboutApplication();

private:
    Ui::AboutApplication *ui;
};

#endif // ABOUTAPPLICATION_H
