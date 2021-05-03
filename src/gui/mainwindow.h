  /*! 
   *  \file	 Mainwindow.h
   *  \brief     Soubor obsahuje definice všech použitých příkazů
   *  \author    Michal Majer - xmajer21
   *  \author    Petr Pouč - xpoucp01
   *  \date      Datum vytvoření: 03.05.2021
   */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <QTreeView>
#include <QFileSystemModel>

#include <unordered_map>

#include "topicmodel.h"
#include "new_connection.h"
#include "client.h"
#include "flow_layout.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


/*! 
 *  \brief     Třída všech objektů nacházejících se v hlavním okně aplikace
 *  \details   Mainwindow - hlavní okno obsahující Explorer a dashboard
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 03.05.2021
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(); //destruktor
    QSortFilterProxyModel * proxy_tree;

signals:

  /*!
   *  \brief     Signál zajištující připojení na zadanou adresu
   *  \pre       Signál proběhne pouze pokud byl zadaný parametr client_name a parametr server_adress
   *  \param[in] client_name 	Jméno klienta typu Qstring
   *  \param[in] server_adress	Platná adresa serveru na který se chceme připojit, adresa je typu Qstring
   */
    void connect_client_mainwindow(QString client_name, QString server_address);

  /*! 
   *  \brief     Signál upravující stromovou strukturu
   *  \details   Do stromové struktury je přidáno téma, které si uživatel sám zvolí
   *  \pre	 Pro vytvoření nového topicu je nutné zadat jeho název - parametr topic_string
   *  \param[in] topic_string Název tématu typu Qstring
   *  \post      Ve stromové struktuře je nově přidáno téma
   */
    void add_topic_clicked(QString topic_string);


  /*! 
   *  \brief     Signál upravující stromovou strukturu
   *  \details   Ze stromové struktury je odstraněno téma, které si uživatel sám zvolí
   *  \pre	 Pro odstranění nového tématu je nutné zadat jeho název - parametr topic_string
   *  \param[in] topic_string	Název tématu typu Qstring
   *  \post      Ve stromové struktuře se již dále nenachází zadané téma
   */
    void delete_topic_clicked(QString topic_string);

  /*! 
   *  \brief     Signál zajišťující posílání zpráv
   *  \details   Na vybrané téma je zaslána uživatelem napsaná zpráva
   *  \pre	 Je nezbytné zadat cílové téma
   *  \param[in] topic_string	Název tématu typu Qstring
   *  \param[in] content_string Obsah zprávy typu Qstring
   *  \post      Vybrané téma v sobě obsahuje hodnotu parametru content_string
   */
    void publish_clicked(QString topic_string, QString content_string);


    //TODO - možná smazat?
    void tree_data_changed();

private slots:

  /*! 
   *  \brief     Zavření aplikace
   */
    void on_actionQuit_triggered();

  /*! 
   *  \brief     Zkopírování označeného textu
   */
    void on_actionCopy_triggered();

  /*! 
   *  \brief     Vložení textu jenž byl dříve zkopírován
   */
    void on_actionPaste_triggered();

  /*! 
   *  \brief     Odstranění označeného textu
   */
    void on_actionCut_triggered();

  /*! 
   *  \brief     Vrací zpět provedenou akci
   */
    void on_actionUndo_triggered();

  /*! 
   *  \brief     Vrací změny provedené slotem on_actionUndo_triggered()
   */
    void on_actionRedo_triggered();

  /*! 
   *  \brief     Označí všechen text v rámci jednoho textového objektu
   */
    void on_actionSelect_All_triggered();

  /*! 
   *  \brief     Otevře okno s informacemi o aplikaci, ve které byl projekt vyvíjen
   */
    void on_actionAbout_Aplication_triggered();

    //TODO ODSTRANIT - celá část VIEW v horní liště půjde do prdele
    void on_actionDefault_size_triggered();

  /*! 
   *  \brief     Otevření nového okna
   *  \details   Uživatel klikl na tlačítko connect - otevře se nové okno s nastavením připojení
   */
    void on_buttonConnect_clicked();

   /*! 
    *  \brief     Slot vyšle signál o stlačení tlačítka 
    *  \details   Byl vyslán signál se zadanou cestou tématu, po provedení je přidáno nové téma
    */
    void on_add_topic_clicked();

   /*! 
    *  \brief     Slot vyšle signál o stlačení tlačítka 
    *  \details   Byl vyslán signál, že uživatel chce poslat zprávu, po provedení zadaný topic obsahuje uživatelem napsanou zprávu
    */
    void on_publish_button_clicked();

   /*! 
    *  \brief     Slot náš přepne na stranu číslo 1
    *  \details   Na tránky byl použít QStackedWidget - index0 = explorer, index1 = dashboard
    */
    void on_Explorer_button_clicked();

   /*! 
    *  \brief     Slot náš přepne na stranu číslo 2
    *  \details   Na tránky byl použít QStackedWidget - index0 = explorer, index1 = dashboard
    */
    void on_Dash_button_clicked();

   /*! 
    *  \brief     Zobrazení obrázku
    *  \pre   	  Zpráva musí obsahovat obrázek
    */
    void on_img_msg_clicked();


    void on_treeView_customContextMenuRequested(const QPoint &pos);

    void context_copy_topic();

  /*! 
   *  \brief     Slot upravující stromovou strukturu
   *  \details   Ze stromové struktury jsou odstraněny všechny podtémata zadaného tématu
   *  \pre	 Samotná stromová struktura musí již existovat
   *  \post      Všechny podtémata zadaného tématu již nejsou součásti stromové struktury
   */
    void delete_subtopics();

  /*! 
   *  \brief     Dále již nesledujeme přijaté informace
   *  \details   Všechny témata jsou vymazány ze stromové struktury
   *  \pre	 Samotná stromová struktura musí již existovat
   *  \post      Nesledujeme žádná témata
   */
    void unsubscribe_context();

    
  /*! 
   *  \brief     Přidání widgetu na dashboard
   *  \details   Na dashboard (page index==1) je přidán widget s textovou hodnotou uživatelem zadaného tématu
   */
    void add_to_dashboard_plain_text();

  /*! 
   *  \brief     Přidání widgetu na dashboard
   *  \details   Na dashboard (page index==1) je přidán widget sledující teplotu v jednotlivých místnostech
   */
    void add_to_dashboard_thermostat();

  /*! 
   *  \brief     Přidání widgetu na dashboard
   *  \details   Na dashboard (page index==1) je přidán widget s textovou hodnotou uživatelem zadaného tématu
   */
    void add_to_dashboard_thermometer();

  /*! 
   *  \brief     Přidání widgetu na dashboard
   *  \details   Na dashboard (page index==1) je přidán widget údávající venkovní teplotu
   */
    void add_to_dashboard_camera();

  /*! 
   *  \brief     Přidání widgetu na dashboard
   *  \details   Na dashboard (page index==1) je přidán widget umožňující zobrazit obrázek obsažený v zadaném tématu
   *  \pre	 Zadané téma v sobě musí obsahovat obrázek
   */
    void show_pic_from_topic(QString);

  /*! 
   *  \brief     Přidání widgetu na dashboard
   *  \details   Na dashboard (page index==1) je přidán widget umožňující ovládat osvětlení
   */
    void add_to_dashboard_light();

  /*! 
   *  \brief     Přidání widgetu na dashboard
   *  \details   Na dashboard (page index==1) je přidán widget udávající vlhkost
   */
    void add_to_dashboard_humidity();

  /*! 
   *  \brief     Rozkliknutí stromové struktury
   *  \details   Zobrazí se část stromové struktury na základě indexu 
   *  \pre	 Validní index
   *  \param[in] index udává polohu stromové struktury, index je typu QModelIndex
   */
    void tree_clicked(const QModelIndex &index);


public slots:

    void mqtt_data_changed_slot(QString, QString);

  /*! 
   *  \brief     Zobrazí historii zpráv
   *  \details   Je zaznamenána historie odeslaných zpráv 
   *  \pre	 Validní index
   *  \param[in] index udává polohu stromové struktury, index je typu QModelIndex
   */
    void display_history(const QModelIndex &index);

    void connection_succesful_slot();

  /*! 
   *  \brief     Provede snímek okna aplikace
   *  \details   Po stisknutí tlačítka dojde k otevření nového okna, zde uživatel specifukuje adresář kam chce daný snímek uložit
   */
    void on_screenshot_button_clicked();

  /*! 
   *  \brief     Provede obtisk stromové struktury 
   *  \details   Stromová struktura témat je uložena do složek a souborů specifikovaných uživatelem
   */
    void on_snap_button_clicked();



    void save_tree_structure_slot(QDir);

private:

    void init_tree_context_menu();

  /*! 
   *  \brief     V novém okně je zobrazen obrázek
   *  \pre	 Validní formát obrázku
   *  \param[in] binární hodnota obrázku
   */
    void popup_picture(std::string);

  /*! 
   *  \brief     Zobrazí hodnotu tématu
   *  \pre	 Musí být vybráno téma jehož hodnotu chceme zobrazit
   *  \pre	 Téma nesmí být prázdné
   *  \post      Zobrazí zprávu jako text, nebo jako obrázek pokud se o něj jedná
   */
    void display_message();

    client cli;
    TopicModel mod;

    Ui::MainWindow *ui;

    QMenu *tree_context_menu;
    QModelIndex context_menu_target;

    TopicNode *active_node;

    new_connection *connection_window;

    FlowLayout *tiles_layout;
};
#endif // MAINWINDOW_H