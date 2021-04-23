#include <QMessageBox>

void error_message(QString(text)){

    //QTimer::singleShot(2500, mbox, SLOT(hide()));
    QMessageBox msgBox(QMessageBox::Warning, "ERROR!!", text, QMessageBox::Ok);
    msgBox.exec();
}
