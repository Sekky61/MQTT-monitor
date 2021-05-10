  /*! 
   *  \file	 dialog.h
   *  \brief     Dialogové okno uložení snímku obrazovky
   *  \author    Michal Majer - xmajer21
   *  \author    Petr Pouč - xpoucp01
   *  \date      Datum vytvoření: 03.05.2021
   */


#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPixmap>

namespace Ui {
class Dialog;
}

/**
  * \brief Dialogové okno pro screenshot
  */
class Dialog : public QDialog
{
    Q_OBJECT

    QPixmap screen;

public:
    explicit Dialog(QWidget *parent, QPixmap screen_map);
    ~Dialog();

private slots:
  /*! 
   *  \brief     Uložení snímku
   *  \details   Pořízený snímek je ve formátu *.JPG uložen na uživatelem zadanou lokaci
   */
    void on_print_save_clicked();

  /*! 
   *  \brief     Výber adresáře
   *  \details   Uživatel si vybere adresář pro uložení pořízeného snímku
   */
    void on_directory_button_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
