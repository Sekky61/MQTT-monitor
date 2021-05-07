  /*! 
   *  \file	 mainwindow.h
   *  \brief     Hlavní okno aplikace
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

    /*!
     * \brief Konstruktor inicializuje klienta MQTT, propojí ho signály s mainwindow
     * \param parent rodič v hierarchii QT widgetů
     */
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow(); //destruktor

signals:

  /*! 
   *  \brief     Signál upravující stromovou strukturu
   *  \details   Signál přijímá MQTT client. Ten začne odebírat topic \ref topic_string a přidá ho do stromové struktury
   *  \param     topic_string Název tématu
   *  \post      Ve stromové struktuře je nově přidáno téma
   */
    void add_topic_clicked(QString topic_string);

  /*! 
   *  \brief     Signál upravující stromovou strukturu
   *  \details   Signál přijímá MQTT client. Zvolené téma odstraní ze stromové struktury a přestane na něm přijímat nové zprávy.
   *  \param     topic_string	Název tématu
   *  \post      Ve stromové struktuře se již dále nenachází zadané téma
   */
    void delete_topic_clicked(QString topic_string);

  /*! 
   *  \brief     Signál zajišťující posílání zpráv
   *  \details   Signál přijímá MQTT client. Na vybrané téma je zaslána zpráva
   *  \param     topic_string	Název tématu
   *  \param     content_string Obsah zprávy
   *  \post      Vybrané téma v sobě obsahuje hodnotu parametru content_string
   */
    void publish_clicked(QString topic_string, QString content_string);

    /*!
     * \brief Změní maximální počet zpráv v historii
     * \param limit nový limit
     */
    void change_history_limit(int limit);

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

    //TODO ODSTRANIT - celá část VIEW v horní liště půjde do pwdele
    void on_actionDefault_size_triggered();

  /*! 
   *  \brief     Otevření okna připojení na MQTT server
   *  \details   Uživatel klikl na tlačítko connect - otevře se nové okno s nastavením připojení
   */
    void on_buttonConnect_clicked();

   /*! 
    *  \brief     Slot přijímá signál tlačítka \ref add_topic
    *  \details   Slot přečte textové pole \ref topic_input_line, vyšle signál \ref add_topic_clicked
    */
    void on_add_topic_clicked();

   /*! 
    *  \brief     Slot přijímá signál tlačítka \ref publish_button
    *  \details   Byl vyslán signál, že uživatel chce poslat zprávu, na zadané téma je zaslána zpráva
    */
    void on_publish_button_clicked();

   /*! 
    *  \brief     Slot náš přepne na stranu číslo 1 - Explorer
    *  \details   Na tránky byl použít QStackedWidget - index0 = explorer, index1 = dashboard
    */
    void on_Explorer_button_clicked();

   /*! 
    *  \brief     Slot náš přepne na stranu číslo 2 - Dashboard
    *  \details   Na tránky byl použít QStackedWidget - index0 = explorer, index1 = dashboard
    */
    void on_Dash_button_clicked();

   /*! 
    *  \brief     Zobrazení obrázku
    *  \pre   	  Zpráva musí obsahovat obrázek
    */
    void on_img_msg_clicked();

    /*!
     * \brief   Slot registruje kliknutí pravého tlačítka na stromové struktuře témat
     * \param   pos souřadnice kliknutí
     * \details Převede souřadnice kliknutí na cíl kliknutí (téma), uloží ho do \ref context_menu_target a zobrazí kontextové menu
     */
    void on_treeView_customContextMenuRequested(const QPoint &pos);

    /*!
     * \brief   Akce kontextového menu. Zkopíruje název tématu do schránky (clipboard)
     * \details Akce je provedena na tématu referovaném v \ref context_menu_target
     */
    void context_copy_topic();

  /*! 
   *  \brief     Slot upravující stromovou strukturu
   *  \details   Ze stromové struktury jsou odstraněny všechny podtémata zadaného tématu.
   *             Akce je provedena na tématu referovaném v \ref context_menu_target
   *  \pre       Samotná stromová struktura musí již existovat
   *  \post      Všechna podtémata zadaného tématu již nejsou součásti stromové struktury, nejsou sledována klientem
   */
    void delete_subtopics();

  /*! 
   *  \brief     Odhlášení ze sledování tématu
   *  \details   Akce je provedena na tématu referovaném v \ref context_menu_target
   *  \pre       Samotná stromová struktura musí již existovat
   *  \post      Nesledujeme téma \ref context_menu_target
   */
    void unsubscribe_context();
    
  /*! 
   *  \brief     Přidání widgetu plain_text na dashboard
   *  \details   Na dashboard (page index==1) je přidán widget s textovou hodnotou uživatelem zadaného tématu
   */
    void add_to_dashboard_plain_text();

  /*! 
   *  \brief     Přidání widgetu thermostat na dashboard
   *  \details   Na dashboard (page index==1) je přidán widget ovládající teplotu v místnosti
   */
    void add_to_dashboard_thermostat();

  /*! 
   *  \brief     Přidání widgetu thermometer na dashboard
   *  \details   Na dashboard (page index==1) je přidán widget zobrazující data z uživatelem zadaného tématu jako teplotu
   */
    void add_to_dashboard_thermometer();

  /*! 
   *  \brief     Přidání widgetu camera na dashboard
   *  \details   Na dashboard (page index==1) je přidán widget zobrazující obrazová data z tématu
   */
    void add_to_dashboard_camera();

  /*! 
   *  \brief     Zobrazení obrázku ve vyskakovacím okně
   *  \details   Souvisí s implementací \ref camera_tile
   *  \param     topic  Téma, jehož zpráva se zobrazí
   *  \pre       Poslední zpráva tématu by měla být obrazová
   */
    void show_pic_from_topic(QString topic);

  /*! 
   *  \brief     Přidání widgetu light na dashboard
   *  \details   Na dashboard (page index==1) je přidán widget umožňující ovládat osvětlení
   */
    void add_to_dashboard_light();

  /*! 
   *  \brief     Přidání widgetu humidity na dashboard
   *  \details   Na dashboard (page index==1) je přidán widget udávající vlhkost
   */
    void add_to_dashboard_humidity();

  /*! 
   *  \brief     Slot reaguje na změnu v aktivním tématu
   *  \details   Nastavuje \ref active_node - aktivní téma
   *  \param     index index modelu topicmodel
   */
    void tree_clicked(const QModelIndex &index);

    /*!
     * \brief blokuje přidání tématu, pokud je řádek prázdný
     * \param arg1 obsah řádku
     */
    void on_topic_input_line_textChanged(const QString &arg1);

    /*!
     * \brief nastaví nový limit délky historie zpráv
     */
    void on_set_limit_btn_clicked();

public slots:

    /*!
     * \brief Slot reaguje na změny ve stromu zpráv, překreslí okno
     */
    void mqtt_data_changed_slot(QString, QString);

  /*! 
   *  \brief     Zobrazí historii zpráv
   *  \details   Je zaznamenána historie odeslaných zpráv
   */
    void display_history();

    /*!
     * \brief Slot po připojení na server zavírá okno \ref new_connection
     */
    void connection_succesful_slot();

  /*! 
   *  \brief     Provede snímek okna aplikace
   *  \details   Po stisknutí tlačítka dojde k otevření nového okna, zde uživatel specifukuje adresář kam chce daný snímek uložit
   */
    void on_screenshot_button_clicked();

  /*! 
   *  \brief     Provede obtisk stromové struktury témat
   *  \details   Stromová struktura témat je uložena do složek a souborů na místo specifikované uživatelem
   */
    void on_snap_button_clicked();

    /*!
     * \brief Uloží obtisk stromové struktury témat
     * \details Slot obdrží signál z vyskakovacího okna \ref Snapshot, strom uloží pomocí \ref snapshot_manager
     * \param root vybrané umístění uložení stromu
     */
    void save_tree_structure_slot(QDir root);

private:

    /*!
     * \brief Součást konstruktoru. Inicializuje kontextové menu
     */
    void init_tree_context_menu();

  /*! 
   *  \brief V novém okně je zobrazen obrázek
   *  \pre	 Validní formát obrázku
   *  \param binární data obrázku
   */
    void popup_picture(std::string);

  /*! 
   *  \brief    Zobrazí poslední zprávu tématu
   *  \pre      Musí být vybráno téma jehož hodnotu chceme zobrazit
   *  \post     Pokusí se rozpoznat obrazová data, případně zprávu zobrazí jako text
   */
    void display_message();

    /*!
     * \brief MQTT klient
     */
    client cli;

    /*!
     * \brief Adapter dat z klienta do modelu zobrazitelného v treeView
     */
    TopicModel mod;

    /*!
     * \brief Qt
     */
    Ui::MainWindow *ui;

    /*!
     * \brief Kontextové menu pro treeView
     */
    QMenu *tree_context_menu;

    /*!
     * \brief Cíl kontextového menu
     */
    QModelIndex context_menu_target;

    /*!
     * \brief Rozkliknuté téma
     */
    TopicNode *active_node;

    /*!
     * \brief Odkaz na okno správce připojení
     */
    new_connection *connection_window;

    /*!
     * \brief Layout dlaždic v dashboardu
     */
    FlowLayout *tiles_layout;
};

#endif // MAINWINDOW_H
