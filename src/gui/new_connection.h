  /*! 
   *  \file	 new_connection.h
   *  \brief     Okno připojení na server
   *  \author    Michal Majer - xmajer21
   *  \author    Petr Pouč - xpoucp01
   *  \date      Datum vytvoření: 03.05.2021
   */


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
#include <QSortFilterProxyModel>

namespace Ui {
class new_connection;
}

/**
 * \brief Struktura pro uložení parametrů připojení
 */
class Profile {
public:
    Profile() {}

    Profile(QString csv_line){
        QStringList attributes = csv_line.split(";");
        name = attributes[0];
        username = attributes[1];
        password = attributes[2];

        protocol = attributes[3];
        host = attributes[4];
        port = attributes[5];
    }


    QString username;
    QString password;
    QString name;

    QString protocol;
    QString host;
    QString port;
};

/*! 
 *  \brief     Model pro zobrazení uložených připojení
 *  \details   Okno new_connection umí ukládat připojení. Levý sloupec (list view) využívá tento model.
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 03.05.2021
 */
class ProfilesListModel : public QAbstractListModel {
public:

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  
    QList<Profile> profile_list;
};


/*! 
 *  \brief     Třída všech objektů nacházejících se v okně new_connection
 *  \details   Okno new_connection slouží pro zadání všech potřebných údajů k připojení
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 03.05.2021
 */
class new_connection : public QDialog
{
    Q_OBJECT


public:
    explicit new_connection(QWidget *parent = nullptr);
    ~new_connection();

signals:
  /*!
   *  \brief     Signál zajištující připojení na uživatelem zadaný server
   *  \pre       Signál proběhne pouze pokud byly zadány všechny pořebné parametry pro připojení
   *  \param     client_id      Identifikační jméno klienta
   *  \param     password       Heslo pro připojení na server
   *  \param     server_name	Název serveru na který se chceme připojit
   */
    void connect_to_server(QString client_id, QString password, QString server_name);

private slots:
  /*!
   *  \brief     Zavolán signál zajišťující připojení k serveru
   *  \details   Jsou zpracovány všechny zadané informace nutné pro připojení, s těmito informacemi proběhne signál connect_to_server
   */
    void on_connect_f_clicked();

  /*!
   *  \brief     Všechny udáje jsou zpracovány a připraveny k uložení do profilu
   *  \details   K samotnému ukládání dochází až ve slotu save_profile(Profile)
   */
    void on_save_f_clicked();

  /*!
   *  \brief     Z profilu je vymazáno jedno uložené připojení
   */
    void on_delete_button_clicked();

  /*!
   *  \brief     Uložení zpracovaných údajů zadaných uživatelem do Profilu
   *  \details   Všechny iformace jsou uloženy jako jedno připojení
   *  \param[in] Profile objekt obsahující všechny potřebné informace
   */
    void save_profile(Profile);


  /*!
   *  \brief     Naplnění formuláře
   *  \details   Po dvojkliknutí na jedno z uložených připojení jsou všechna textová pole okna new_connection naplněná informacemi, uloženými v tomto spojení
   *  \param[in] index	udává jedno konkrétní uložené spojení
   */
    void on_listView_doubleClicked(const QModelIndex &index);

private:
    Ui::new_connection *ui;
    ProfilesListModel *model_con;
};

#endif // NEW_CONNECTION_H
