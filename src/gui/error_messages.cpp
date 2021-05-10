/*!
 *  \file      error_messages.cpp
 *  \brief     Vyskakovací okno hlásící chybu
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 03.05.2021
 */

#include <QMessageBox>

void error_message(QString(text)){

    //QTimer::singleShot(2500, mbox, SLOT(hide()));
    QMessageBox msgBox(QMessageBox::Warning, "ERROR!!", text, QMessageBox::Ok);
    msgBox.exec();
}
