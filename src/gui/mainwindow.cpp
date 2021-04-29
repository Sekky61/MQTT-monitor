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
    displayed_topic(),
    connection_window(nullptr)
{
    ui->setupUi(this);

    // aktualizace zobrazeni pri prichodu mqtt zpravy
    QObject::connect(&cli, &client::mqtt_data_changed, &mod, &TopicModel::incoming_data_change);
    QObject::connect(&cli, &client::mqtt_data_changed, this, &MainWindow::mqtt_data_changed_slot);

    QObject::connect(&cli, &client::connection_succesful, this, &MainWindow::connection_succesful_slot);
    QObject::connect(ui->button_disconnect, &QAbstractButton::clicked, &cli, &client::user_clicked_disconnect);

    // add_topic_clicked
    QObject::connect(this, &MainWindow::add_topic_clicked, &cli, &client::add_topic_slot);
    QObject::connect(this, &MainWindow::delete_topic_clicked, &cli, &client::delete_topic_slot);
    QObject::connect(this, &MainWindow::publish_clicked, &cli, &client::publish_slot);

    ui->treeView->setModel(&mod);

    //ui->tiles_layout->setSpacing(10);

    QWidget *gridLayoutWidget = new QWidget(ui->page_2);
    gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
    gridLayoutWidget->setGeometry(QRect(0, 80, 1070, 700));

    tiles_layout = new FlowLayout(gridLayoutWidget);
    tiles_layout->setObjectName(QString::fromUtf8("tiles_layout"));
    tiles_layout->setContentsMargins(20, 20, 20, 20);
    gridLayoutWidget->setLayout(tiles_layout);
    tiles_layout->activate();

    ui->value_text->setReadOnly(true);
    //ui->value_text_2->setReadOnly(true);

    //ui->progressBar->setTextVisible(false);
    //ui->dial->setWrapping(false);

    //na záčátku bude nastaveno na hodnotu přijatou ze zprávy
    int message_val = 13; //to si přepiš
    //ui->lcdNumber->display(message_val);
    //ui->progressBar->setValue(message_val);
    //ui->lcdNumber->setSmallDecimalPoint(true);


    //dashboard text - vždy
    ui->radio_text->setChecked(true);
    ui->radio_text->setAutoExclusive(true);

    //lihts - readonly
    //ui->device_lights_opt->setReadOnly(true);
    //ui->room_lights_opt->setReadOnly(true);

    //základní nastavení widgetů na dashboardu - widgety jsou defaultně vypnuté
    //ui->thermo_stacked->setCurrentIndex(1);
    //ui->light_stacked->setCurrentIndex(1);
    //ui->cameras_stacked->setCurrentIndex(1);
    //ui->temperature_stacked->setCurrentIndex(1);
    //ui->water_stacked->setCurrentIndex(1);

    // context menu

    // dashboard submenu

    QMenu *dash_submenu = tree_context_menu->addMenu("Add to dashboard");

    QAction *tile_add_plaintext = new QAction("Plain text", this);
    QObject::connect(tile_add_plaintext, &QAction::triggered, this, &MainWindow::add_to_dashboard_plain_text);
    dash_submenu->addAction(tile_add_plaintext);

    QAction *tile_add_thermostat = new QAction("Thermostat", this);
    QObject::connect(tile_add_thermostat, &QAction::triggered, this, &MainWindow::add_to_dashboard_thermostat);
    dash_submenu->addAction(tile_add_thermostat);

    QAction *tile_add_thermometer = new QAction("Thermometer", this);
    QObject::connect(tile_add_thermometer, &QAction::triggered, this, &MainWindow::add_to_dashboard_thermometer);
    dash_submenu->addAction(tile_add_thermometer);

    QAction *tile_add_camera = new QAction("Camera feed", this);
    QObject::connect(tile_add_camera, &QAction::triggered, this, &MainWindow::add_to_dashboard_camera);
    dash_submenu->addAction(tile_add_camera);

    QAction *tile_add_light = new QAction("Light", this);
    QObject::connect(tile_add_light, &QAction::triggered, this, &MainWindow::add_to_dashboard_light);
    dash_submenu->addAction(tile_add_light);

    QAction *tile_add_humidity = new QAction("Humidity", this);
    QObject::connect(tile_add_humidity, &QAction::triggered, this, &MainWindow::add_to_dashboard_humidity);
    dash_submenu->addAction(tile_add_humidity);

    // Other options

    QAction *copy_full_path_action = new QAction("Copy full path", this);
    QObject::connect(copy_full_path_action, &QAction::triggered, this, &MainWindow::context_copy_topic);
    tree_context_menu->addAction(copy_full_path_action);

    QAction *delete_subtopics_action = new QAction("Delete all subtopics", this);
    QObject::connect(delete_subtopics_action, &QAction::triggered, this, &MainWindow::delete_subtopics);
    tree_context_menu->addAction(delete_subtopics_action);

    QAction *unsubscribe_action = new QAction("Unsubscribe", this);
    QObject::connect(unsubscribe_action, &QAction::triggered, this, &MainWindow::unsubscribe_context);
    tree_context_menu->addAction(unsubscribe_action);

    QObject::connect(ui->treeView, &QAbstractItemView::clicked, this, &MainWindow::display_message);

    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
}


MainWindow::~MainWindow()
{
    delete ui;
    //this->setCentralWidget(ui->textEdit);
}

void MainWindow::display_message(const QModelIndex &index)
{
    displayed_topic = index;

    auto node_ptr = static_cast<TopicNode*>(index.internalPointer());
    if(node_ptr == nullptr){
        std::cerr << "zadne zpravy\n";
        ui->value_text->setPlainText(QString());
        ui->img_msg->setVisible(false);
        return;
    }



    auto msg_ptr = node_ptr->get_latest_msg();
    if(msg_ptr == nullptr){
        std::cerr << "zadne zpravy\n";
        ui->value_text->setPlainText(QString());
        ui->img_msg->setVisible(false);
        return;
    }

    std::string payload = (*msg_ptr)->get_payload();

    QImage img;
    img.loadFromData(reinterpret_cast<const uchar*>(payload.data()), payload.size());

    if(img.format() == QImage::Format_Invalid){
        std::cerr << "SIZE 0 - NOT A PICTURE\n";
        QString qmsg = QString::fromStdString(payload);
        ui->value_text->setPlainText(qmsg);
        ui->img_msg->setVisible(false);
    } else {
        std::cerr << "OK - PICTURE\n";
        ui->value_text->setPlainText(QString());
        ui->img_msg->setVisible(true);
    }

    //on_img_msg_clicked
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
        connection_window->close(); // todo disconnect signal
        delete connection_window;
        connection_window = nullptr;
    }
}

void MainWindow::on_searchButton_clicked()
{
    QString val = ui->searchValue->text();
    ui->searchValue->setText("");
    //filtrování stromové struktury
    proxy_tree = new QSortFilterProxyModel(this);
    proxy_tree->setSourceModel(&mod);
    proxy_tree->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy_tree->setRecursiveFilteringEnabled(true);
    proxy_tree->setFilterKeyColumn(0); //If the value is -1, the keys will be read from all columns
    proxy_tree->setFilterFixedString(val);

    ui->treeView->setModel(proxy_tree);
}

void MainWindow::on_add_topic_clicked()
{
    //tree path - zde chceme přidat topic
    QString topic_path = ui->topic_search->text();
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
    //tohle patří do funkce kde budeš zpracovávat zprávu
    if(displayed_topic.isValid()){

        auto node_ptr = static_cast<TopicNode*>(displayed_topic.internalPointer());
        if(node_ptr == nullptr){
            std::cerr << "zadne zpravy\n";
            //ui->value_text->setPlainText(QString());
            return;
        }

        auto msg_ptr = node_ptr->get_latest_msg();
        if(msg_ptr == nullptr){
            std::cerr << "zadne zpravy\n";
            ui->value_text->setPlainText(QString());
            ui->img_msg->setVisible(false);
            return;
        }

        std::string payload = (*msg_ptr)->get_payload();

        QImage img;
        img.loadFromData(reinterpret_cast<const uchar*>(payload.data()), payload.size());

        if(img.format() == QImage::Format_Invalid){
            std::cerr << "CANNOT DISPLAY PICTURE\n";
        } else {
            std::cerr << "OK - SHOWING PICTURE\n";
            QDialog dia = QDialog();
            QLabel pic_lbl = QLabel(&dia);

            QPixmap map;
            map.convertFromImage(img);
            pic_lbl.setPixmap(map);
            std::cerr << pic_lbl.width() << " - " << pic_lbl.height();
            dia.resize(img.width(), img.height());
            dia.exec();
        }

    }
    //ui->img_msg->setEnabled(false);
    //ui->img_msg->setVisible(false);
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

void MainWindow::on_copy_topic_path_clicked()
{
    auto index = ui->treeView->currentIndex();
    if(index == QModelIndex()){
        std::cerr << "Nothing selected\n";
        return;
    }
    auto *node_ptr = static_cast<TopicNode *>(index.internalPointer());
    if(node_ptr == nullptr){
        std::cerr << "Selected index has nullptr\n";
        return;
    }
    QString full_topic_path = QString::fromStdString(node_ptr->fullTopic);
    ui->topic_search->setText(full_topic_path);
}

void MainWindow::on_delete_subtopics_clicked()
{
    auto index = ui->treeView->currentIndex();
    if(index == QModelIndex()){
        std::cerr << "Nothing selected\n";
        return;
    }
    auto *node_ptr = static_cast<TopicNode *>(index.internalPointer());
    if(node_ptr == nullptr){
        std::cerr << "Selected index has nullptr\n";
        return;
    }
}

void MainWindow::add_to_dashboard_plain_text()
{
    if (context_menu_target.isValid()) {
        auto node = static_cast<TopicNode *>(context_menu_target.internalPointer());
        if(node){
            fulltext_tile *tile = new fulltext_tile(QString::fromStdString(node->fullTopic));
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
            thermostat_tile *tile = new thermostat_tile(QString::fromStdString(node->fullTopic));
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
            temperature_tile *tile = new temperature_tile(QString::fromStdString(node->fullTopic));
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
            camera_tile *tile = new camera_tile(QString::fromStdString(node->fullTopic));
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
            light_tile *tile = new light_tile(QString::fromStdString(node->fullTopic));
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
            humidity_tile *tile = new humidity_tile(QString::fromStdString(node->fullTopic));
            QObject::connect(&cli, &client::mqtt_data_changed, tile, &humidity_tile::incoming_data);
            tiles_layout->addWidget(tile);
            tiles_layout->activate();
        }
    }
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
    display_message(displayed_topic);
}

/*void MainWindow::on_dial_valueChanged(int value)
{
    //nastavuje se na hodnotu ciferníku
    ui->lcdNumber->display(value);
    ui->progressBar->setValue(value);

}

void MainWindow::on_temp_button_clicked()
{
    int new_val = ui->lcdNumber->value(); //získáme novou hodnotu zprávy
    //TODO přepis zprávy
}

void MainWindow::on_dial_actionTriggered(int action)
{

}
*/

void MainWindow::on_screenshot_button_clicked()
{
    WId window = QWidget::winId(); //rozměry window
    QScreen *screen = QGuiApplication::primaryScreen();
    auto map = std::make_unique<QPixmap>(screen->grabWindow(window));


    std::unique_ptr<Dialog> screenshot = std::make_unique<Dialog>();
    screenshot->setModal(true);
    screenshot->exec();
}
/*
void MainWindow::on_light_set_button_clicked()
{
    QString room = ui->room_lights_opt->text();
    QString device = ui->device_lights_opt->text();
    if (ui->lights_on->isChecked()){
        //zapnutí světel na zadané lokaci
    }
    if (!(ui->lights_off->isChecked())){
        //vypnutí světel na zadané lokaci
    }
}
*/
/*
void MainWindow::on_snapshot_button_clicked()
{
    //zobrazí obrázek
}*/

void MainWindow::on_snap_button_clicked()
{
    auto snap = std::make_unique<Snapshot>(this);

    QObject::connect(snap.get(), &Snapshot::save_tree_structure, this, &MainWindow::save_tree_structure_slot);

    snap->setModal(true);
    snap->exec();

    //zde se bude ukládat stromová struktura
}
/*
void MainWindow::on_dashboard_add_clicked()
{
    //thermostat
    if(ui->radio_thermo->isChecked()){
        //aktivuje se widget
        ui->thermo_stacked->setCurrentIndex(0);
    }else if(!(ui->radio_thermo->isChecked())){
        //widget se vypne
        ui->thermo_stacked->setCurrentIndex(1);
    }

    //lights
    if(ui->radio_light->isChecked()){
        ui->light_stacked->setCurrentIndex(0);
    }else if(!(ui->radio_light->isChecked())){
        ui->light_stacked->setCurrentIndex(1);
    }

    //cameras
    if(ui->radio_cameras->isChecked()){
        ui->cameras_stacked->setCurrentIndex(0);
    }else if(!(ui->radio_cameras->isChecked())){
        ui->cameras_stacked->setCurrentIndex(1);
    }

    //temperature
    if(ui->radio_temp->isChecked()){
        ui->temperature_stacked->setCurrentIndex(0);
    }else if(!(ui->radio_temp->isChecked())){
        ui->temperature_stacked->setCurrentIndex(1);
    }

    //watteriness
    if(ui->radio_water->isChecked()){
        ui->water_stacked->setCurrentIndex(0);
    }else if(!(ui->radio_water->isChecked())){
        ui->water_stacked->setCurrentIndex(1);
    }
}
*/

void MainWindow::save_tree_structure_slot(QDir root)
{
    snapshot_manager mngr;
    mngr.create_snapshot(root, &cli);
}
