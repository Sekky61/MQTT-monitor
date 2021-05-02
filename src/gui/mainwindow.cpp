#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutapplication.h"
#include "new_connection.h"
#include "topicmodel.h"
#include "dialog.h"
#include "snapshot.h"
#include "snapshot_manager.h"

#include <iostream>
#include <QByteArray>
#include <QDataStream>
#include <QBuffer>
#include <QImageReader>
#include <QClipboard>

#include "dash_tile.h"
#include "thermostat_tile.h"
#include "fulltext_tile.h"
#include "camera_tile.h"
#include "light_tile.h"
#include "temperature_tile.h"
#include "humidity_tile.h"


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    cli(),
    mod(cli),
    ui(new Ui::MainWindow),
    tree_context_menu(new QMenu()),
    context_menu_target(),
    active_node(nullptr),
    connection_window(nullptr)
{
    // qt
    ui->setupUi(this);

    // setup tree
    ui->treeView->setModel(&mod);
    QObject::connect(ui->treeView, &QAbstractItemView::clicked, this, &MainWindow::tree_clicked);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    // aktualizace zobrazeni pri prichodu mqtt zpravy
    QObject::connect(&cli, &client::mqtt_data_changed, &mod, &TopicModel::incoming_data_change);
    QObject::connect(&cli, &client::mqtt_data_changed, this, &MainWindow::mqtt_data_changed_slot);

    // Spojeni se serverem
    QObject::connect(&cli, &client::connection_succesful, this, &MainWindow::connection_succesful_slot);
    QObject::connect(ui->button_disconnect, &QAbstractButton::clicked, &cli, &client::user_clicked_disconnect);

    // MQTT interakce
    QObject::connect(this, &MainWindow::add_topic_clicked, &cli, &client::add_topic_slot);
    QObject::connect(this, &MainWindow::delete_topic_clicked, &cli, &client::delete_topic_slot);
    QObject::connect(this, &MainWindow::publish_clicked, &cli, &client::publish_slot);

    // Dashboard layout
    tiles_layout = new FlowLayout(ui->dashboard_widget);
    tiles_layout->setContentsMargins(20, 20, 20, 20);
    ui->dashboard_widget->setLayout(tiles_layout);
    tiles_layout->activate();

    // ReadOnly zobrazovanych zprav
    ui->value_text->setReadOnly(true);

    init_tree_context_menu();
}

void MainWindow::init_tree_context_menu(){

    // tree context menu
    // pravy klik na topic zobrazi
    //
    // Add to dashboard   >  Plain text
    //                       Thermostat
    // Copy full path        Thermometer
    // Delete all subtopics  Camera feed
    // Unsubscribe           Light
    //                       Humidity

    // dashboard submenu
    QMenu *dash_submenu = tree_context_menu->addMenu("Add to dashboard");

    QAction *tile_add_plaintext = new QAction("Plain text", this);
    QObject::connect(tile_add_plaintext, &QAction::triggered, this, &MainWindow::add_to_dashboard_plain_text);

    QAction *tile_add_thermostat = new QAction("Thermostat", this);
    QObject::connect(tile_add_thermostat, &QAction::triggered, this, &MainWindow::add_to_dashboard_thermostat);

    QAction *tile_add_thermometer = new QAction("Thermometer", this);
    QObject::connect(tile_add_thermometer, &QAction::triggered, this, &MainWindow::add_to_dashboard_thermometer);

    QAction *tile_add_camera = new QAction("Camera feed", this);
    QObject::connect(tile_add_camera, &QAction::triggered, this, &MainWindow::add_to_dashboard_camera);

    QAction *tile_add_light = new QAction("Light", this);
    QObject::connect(tile_add_light, &QAction::triggered, this, &MainWindow::add_to_dashboard_light);

    QAction *tile_add_humidity = new QAction("Humidity", this);
    QObject::connect(tile_add_humidity, &QAction::triggered, this, &MainWindow::add_to_dashboard_humidity);

    dash_submenu->addActions({tile_add_plaintext, tile_add_thermostat, tile_add_thermometer, tile_add_camera, tile_add_light, tile_add_humidity});

    // Other context menu options

    QAction *copy_full_path_action = new QAction("Copy full path", this);
    QObject::connect(copy_full_path_action, &QAction::triggered, this, &MainWindow::context_copy_topic);

    QAction *delete_subtopics_action = new QAction("Delete all subtopics", this);
    QObject::connect(delete_subtopics_action, &QAction::triggered, this, &MainWindow::delete_subtopics);

    QAction *unsubscribe_action = new QAction("Unsubscribe", this);
    QObject::connect(unsubscribe_action, &QAction::triggered, this, &MainWindow::unsubscribe_context);

    tree_context_menu->addActions({copy_full_path_action, delete_subtopics_action, unsubscribe_action});
}

MainWindow::~MainWindow()
{
    delete ui;
    // todo cli?
}

void MainWindow::display_message()
{
    // Pokud neni vybran topic, nic nezobrazovat
    if(active_node == nullptr){
        ui->value_text->setPlainText(QString());
        ui->img_msg->setVisible(false);
        return;
    }

    // Pokud topic neobsahuje zpravy, nic nezobrazovat
    auto msg_ptr = active_node->get_latest_msg();
    if(msg_ptr == nullptr){
        ui->value_text->setPlainText(QString());
        ui->img_msg->setVisible(false);
        return;
    }

    std::string payload = (*msg_ptr)->get_payload();

    // Zjistit, zda jde o obrazek
    // Zkusit precist jako obrazek a zjistit, jestli bylo precteni uspesne
    QImage img;
    img.loadFromData(reinterpret_cast<const uchar*>(payload.data()), payload.size());

    if(img.format() == QImage::Format_Invalid){
        // Neni obrazek, zobrazit zpravu jako text
        QString qmsg = QString::fromStdString(payload);
        ui->value_text->setPlainText(qmsg);
        ui->img_msg->setVisible(false);
    } else {
        // Je obrazek, zobrazit tlacitko "Zobrazit obrazek"
        ui->value_text->setPlainText(QString());
        ui->img_msg->setVisible(true);
    }
}

void MainWindow::display_history(const QModelIndex &index)
{
    auto node_ptr = static_cast<TopicNode*>(index.internalPointer());
    if(node_ptr == nullptr){
        std::cerr << "zadne zpravy\n";
        //ui->value_text->setPlainText(QString());
        return;
    }

    auto &messages = node_ptr->Msgs;

    QString res;

    for(auto msg: messages){
        res += QString::fromStdString(msg->get_payload()) + "\n";
    }

    //ui-> HISTORY FIELD

    //todo pics
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionSelect_All_triggered()
{
    ui->textEdit->selectAll();
}

void MainWindow::on_actionAbout_Aplication_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionDefault_size_triggered()
{
    //ještě nevím co tady
    ui->textEdit->selectAll();
}

void MainWindow::on_buttonConnect_clicked()
{
    connection_window = new new_connection(this);

    QObject::connect(connection_window, &new_connection::connect_to_server, &cli, &client::user_clicked_connect);
    connection_window->setModal(true);
    connection_window->exec();
}

void MainWindow::connection_succesful_slot()
{
    if(connection_window){
        connection_window->close();
        delete connection_window;
        connection_window = nullptr;
    }
}

void MainWindow::on_add_topic_clicked()
{
    //tree path - zde chceme přidat topic
    QString topic_path = ui->topic_search->text();
    ui->topic_search->setText("");
    emit add_topic_clicked(topic_path);
}

// Publish message
void MainWindow::on_publish_button_clicked()
{
    QString topic = ui->path_message->text(); //pošle zprávu na zadanou adresu
    QString text = ui->textEdit->toPlainText(); //zpráva

    emit publish_clicked(topic, text);
}

void MainWindow::on_Explorer_button_clicked()
{
    ui->Pages->setCurrentIndex(0);
}

void MainWindow::on_Dash_button_clicked()
{
    ui->Pages->setCurrentIndex(1);
    tiles_layout->trigger_redraw();
}

//bude zobrazovat obrázek
void MainWindow::on_img_msg_clicked()
{
    if(active_node == nullptr){
        return;
    }

    auto msg_ptr = active_node->get_latest_msg();
    if(msg_ptr == nullptr){
        return;
    }

    std::string payload = (*msg_ptr)->get_payload();

    popup_picture(payload);
}

void MainWindow::show_pic_from_topic(QString topic)
{
    //popup s nejnovejsim obrazkem z topicu

    auto node = cli.sys->get_node_by_topic(topic.toStdString());

    if(node == nullptr){
        return;
    }

    auto msg = node->get_latest_msg();

    if(msg == nullptr || *msg == nullptr){
        return;
    }

    std::string payload = (*msg)->get_payload();

    popup_picture(payload);
}

void MainWindow::popup_picture(std::string payload)
{
    QImage img;
    img.loadFromData(reinterpret_cast<const uchar*>(payload.data()), payload.size());

    if(img.format() == QImage::Format_Invalid){
        std::cerr << "CANNOT DISPLAY PICTURE\n";
        return;
    }

    std::cerr << "OK - SHOWING PICTURE\n";

    QDialog dia = QDialog();
    QLabel pic_lbl = QLabel(&dia);

    QPixmap map;
    map.convertFromImage(img);
    pic_lbl.setPixmap(map);

    dia.resize(img.width(), img.height());
    dia.exec();
}

// CONTEXT MENU

void MainWindow::on_treeView_customContextMenuRequested(const QPoint &pos)
{
    std::cerr << "context menu request\n";
    context_menu_target = ui->treeView->indexAt(pos);
    if (context_menu_target.isValid()) {
        tree_context_menu->exec(ui->treeView->viewport()->mapToGlobal(pos));
    }
}

void MainWindow::add_to_dashboard_plain_text()
{
    if (context_menu_target.isValid()) {
        auto node = static_cast<TopicNode *>(context_menu_target.internalPointer());
        if(node){
            fulltext_tile *tile = new fulltext_tile(this, QString::fromStdString(node->fullTopic));
            QObject::connect(&cli, &client::mqtt_data_changed, tile, &fulltext_tile::incoming_data);
            tiles_layout->addWidget(tile);
            tiles_layout->activate();
        }
    }
}

void MainWindow::add_to_dashboard_thermostat()
{
    if (context_menu_target.isValid()) {
        auto node = static_cast<TopicNode *>(context_menu_target.internalPointer());
        if(node){
            thermostat_tile *tile = new thermostat_tile(this, QString::fromStdString(node->fullTopic));
            QObject::connect(&cli, &client::mqtt_data_changed, tile, &thermostat_tile::incoming_data);
            QObject::connect(tile, &thermostat_tile::send_data, &cli, &client::publish_slot);
            tiles_layout->addWidget(tile);
            tiles_layout->activate();
        }
    }
}

void MainWindow::add_to_dashboard_thermometer()
{
    if (context_menu_target.isValid()) {
        auto node = static_cast<TopicNode *>(context_menu_target.internalPointer());
        if(node){
            temperature_tile *tile = new temperature_tile(this, QString::fromStdString(node->fullTopic));
            QObject::connect(&cli, &client::mqtt_data_changed, tile, &temperature_tile::incoming_data);
            tiles_layout->addWidget(tile);
            tiles_layout->activate();
        }
    }
}

void MainWindow::add_to_dashboard_camera()
{
    if (context_menu_target.isValid()) {
        auto node = static_cast<TopicNode *>(context_menu_target.internalPointer());
        if(node){
            camera_tile *tile = new camera_tile(this, QString::fromStdString(node->fullTopic));
            QObject::connect(tile, &camera_tile::show_pic, this, &MainWindow::show_pic_from_topic);
            tiles_layout->addWidget(tile);
            tiles_layout->activate();
        }
    }
}

void MainWindow::add_to_dashboard_light()
{
    if (context_menu_target.isValid()) {
        auto node = static_cast<TopicNode *>(context_menu_target.internalPointer());
        if(node){
            light_tile *tile = new light_tile(this, QString::fromStdString(node->fullTopic));
            QObject::connect(&cli, &client::mqtt_data_changed, tile, &light_tile::incoming_data);
            QObject::connect(tile, &light_tile::send_data, &cli, &client::publish_slot);
            tiles_layout->addWidget(tile);
            tiles_layout->activate();
        }
    }
}

void MainWindow::add_to_dashboard_humidity()
{
    if (context_menu_target.isValid()) {
        auto node = static_cast<TopicNode *>(context_menu_target.internalPointer());
        if(node){
            humidity_tile *tile = new humidity_tile(this, QString::fromStdString(node->fullTopic));
            QObject::connect(&cli, &client::mqtt_data_changed, tile, &humidity_tile::incoming_data);
            tiles_layout->addWidget(tile);
            tiles_layout->activate();
        }
    }
}

void MainWindow::tree_clicked(const QModelIndex &index)
{
    if(!index.isValid()){
        active_node = nullptr;
    } else {
        active_node = static_cast<TopicNode*>(index.internalPointer());
    }

    display_message();
}

void MainWindow::context_copy_topic()
{
    if (context_menu_target.isValid()) {
        QClipboard *clipboard = QGuiApplication::clipboard();
        auto node = static_cast<TopicNode *>(context_menu_target.internalPointer());
        if(node){
            clipboard->setText(QString::fromStdString(node->fullTopic));
        }
    }
}

void MainWindow::delete_subtopics()
{
    if (context_menu_target.isValid()) {
        auto node = static_cast<TopicNode *>(context_menu_target.internalPointer());
        if(node){
            node->delete_children();
            emit tree_data_changed();
        }
    }
}

void MainWindow::unsubscribe_context()
{
    if (context_menu_target.isValid()) {
        auto node = static_cast<TopicNode *>(context_menu_target.internalPointer());
        if(node){

            QString topic = QString::fromStdString(node->fullTopic);
            emit delete_topic_clicked(topic);
            emit tree_data_changed();
        }
    }
}

// END OF CONTEXT MENU

void MainWindow::mqtt_data_changed_slot(QString topic, QString msg)
{
    Q_UNUSED(topic);
    Q_UNUSED(msg);
    display_message();
}

void MainWindow::on_screenshot_button_clicked()
{
    auto active_window = qApp->activeWindow();
    if (active_window)
    {
        QPixmap pixmap(active_window->size());
        active_window->render(&pixmap);

        std::unique_ptr<Dialog> screenshot = std::make_unique<Dialog>(this, pixmap);
        screenshot->setModal(true);
        screenshot->exec();
    }
}

void MainWindow::on_snap_button_clicked()
{
    auto snap = std::make_unique<Snapshot>(this);

    QObject::connect(snap.get(), &Snapshot::save_tree_structure, this, &MainWindow::save_tree_structure_slot);

    snap->setModal(true);
    snap->exec();

    //zde se bude ukládat stromová struktura
}

void MainWindow::save_tree_structure_slot(QDir root)
{
    snapshot_manager mngr;
    mngr.create_snapshot(root, &cli);
}
