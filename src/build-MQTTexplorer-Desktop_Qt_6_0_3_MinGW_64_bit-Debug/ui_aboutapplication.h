/********************************************************************************
** Form generated from reading UI file 'aboutapplication.ui'
**
** Created by: Qt User Interface Compiler version 6.0.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTAPPLICATION_H
#define UI_ABOUTAPPLICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_AboutApplication
{
public:

    void setupUi(QDialog *AboutApplication)
    {
        if (AboutApplication->objectName().isEmpty())
            AboutApplication->setObjectName(QString::fromUtf8("AboutApplication"));
        AboutApplication->resize(240, 320);

        retranslateUi(AboutApplication);

        QMetaObject::connectSlotsByName(AboutApplication);
    } // setupUi

    void retranslateUi(QDialog *AboutApplication)
    {
        AboutApplication->setWindowTitle(QCoreApplication::translate("AboutApplication", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutApplication: public Ui_AboutApplication {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTAPPLICATION_H
