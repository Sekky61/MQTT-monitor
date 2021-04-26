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

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent) ,
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->value_text->setReadOnly(true);
    ui->value_text_2->setReadOnly(true);

    ui->progressBar->setTextVisible(false);
    ui->dial->setWrapping(false);

    //na záčátku bude nastaveno na hodnotu přijatou ze zprávy
    int message_val = 13; //to si přepiš
    ui->lcdNumber->display(message_val);
    ui->progressBar->setValue(message_val);
    ui->lcdNumber->setSmallDecimalPoint(true);


    //dashboard text - vždy
    ui->radio_text->setChecked(true);
    ui->radio_text->setAutoExclusive(true);

    //lihts - readonly
    ui->device_lights_opt->setReadOnly(true);
    ui->room_lights_opt->setReadOnly(true);

    //základní nastavení widgetů na dashboardu - widgety jsou defaultně vypnuté
    ui->thermo_stacked->setCurrentIndex(1);
    ui->light_stacked->setCurrentIndex(1);
    ui->cameras_stacked->setCurrentIndex(1);
    ui->temperature_stacked->setCurrentIndex(1);
    ui->water_stacked->setCurrentIndex(1);



    tree_context_menu = new QMenu();

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

void MainWindow::set_tree_model(TopicModel *new_model)
{
    mod = new_model;
    ui->treeView->setModel(new_model);
    QObject::connect(this, &MainWindow::tree_data_changed, new_model, &TopicModel::incoming_data_change);
}

void MainWindow::set_client_ptr(client *cl)
{
    cli_ptr = cl;
}

void MainWindow::display_message(const QModelIndex &index)
{
    auto msg_ptr = static_cast<TopicNode*>(index.internalPointer())->get_latest_msg();
    if(msg_ptr == nullptr){
        std::cerr << "zadne zpravy\n";
        return;
    }
    std::string payload = (*msg_ptr)->get_payload();
    QString qmsg = QString::fromStdString(payload);
    ui->value_text->setPlainText(qmsg);

    QByteArray arr = QByteArray(payload.data());

    QDataStream stream = QDataStream(arr);

    QBuffer buf = QBuffer(&arr);

    QByteArray imageFormat = QImageReader::imageFormat(&buf);

    if(imageFormat.size() == 0){
        std::cerr << "SIZE 0\n";
    } else {
        std::cerr << "OK\n";
    }

    //on_img_msg_clicked
}

void MainWindow::connect_to_client_from_dialog(QString client_name, QString server_address)
{
    std::cout << "Slot connect_to_client_from_dialog activated\n";
    emit connect_client_mainwindow(client_name, server_address);
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

    QObject::connect(connection_window, &new_connection::connect_to_server, this, &MainWindow::connect_to_client_from_dialog);
    connection_window->setModal(true);
    connection_window->exec();
}

void MainWindow::on_searchButton_clicked()
{
    QString val = ui->searchValue->text();
    ui->searchValue->setText("");
    //filtrování stromové struktury
    proxy_tree = new QSortFilterProxyModel(this);
    proxy_tree->setSourceModel(mod);
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
}

//bude zobrazovat obrázek
void MainWindow::on_img_msg_clicked()
{
    //tohle patří do funkce kde budeš zpracovávat zprávu
    ui->img_msg->setEnabled(false);
    ui->img_msg->setVisible(false);
}

void MainWindow::connection_succesful_slot()
{
    if(connection_window){
        connection_window->close(); // todo disconnect signal
        delete connection_window;
        connection_window = nullptr;
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

void MainWindow::on_treeView_customContextMenuRequested(const QPoint &pos)
{
    std::cerr << "context menu request\n";
    context_menu_target = ui->treeView->indexAt(pos);
    if (context_menu_target.isValid()) {
        tree_context_menu->exec(ui->treeView->viewport()->mapToGlobal(pos));
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

void MainWindow::on_dial_valueChanged(int value)
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


void MainWindow::on_screenshot_button_clicked()
{
    WId window = QWidget::winId(); //rozměry window
    QScreen *screen = QGuiApplication::primaryScreen();
    auto map = std::make_unique<QPixmap>(screen->grabWindow(window));


    std::unique_ptr<Dialog> screenshot = std::make_unique<Dialog>();
    screenshot->setModal(true);
    screenshot->exec();
}

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

void MainWindow::on_snapshot_button_clicked()
{
    //zobrazí obrázek
}

void MainWindow::on_snap_button_clicked()
{
    auto snap = std::make_unique<Snapshot>(this);

    QObject::connect(snap.get(), &Snapshot::save_tree_structure, this, &MainWindow::save_tree_structure_slot);

    snap->setModal(true);
    snap->exec();

    //zde se bude ukládat stromová struktura
}

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

void MainWindow::save_tree_structure_slot(QDir root)
{
    snapshot_manager mngr;
    mngr.create_snapshot(root, cli_ptr);
}
