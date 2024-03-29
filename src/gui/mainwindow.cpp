#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutapplication.h"
#include "new_connection.h"
#include "dialog.h"
#include "snapshot.h"

#include "dash_tile.h"
#include "thermostat_tile.h"
#include "fulltext_tile.h"
#include "camera_tile.h"
#include "light_tile.h"
#include "temperature_tile.h"
#include "humidity_tile.h"

#include "flow_layout.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent) ,
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dash_tile *tile1 = new dash_tile();
    fulltext_tile *tile2 = new fulltext_tile();
    camera_tile *tile3 = new camera_tile();
    thermostat_tile *tile4 = new thermostat_tile();
    light_tile *tile5 = new light_tile();
    temperature_tile *tile6 = new temperature_tile();
    humidity_tile *tile7 = new humidity_tile();

    //ui->tiles_layout->setSpacing(10);

    QWidget *gridLayoutWidget = new QWidget(ui->page_2);
    gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
    gridLayoutWidget->setGeometry(QRect(0, 80, 1070, 700));

    FlowLayout *tiles_layout = new FlowLayout(gridLayoutWidget);
    tiles_layout->setObjectName(QString::fromUtf8("tiles_layout"));
    tiles_layout->setContentsMargins(20, 20, 20, 20);
    gridLayoutWidget->setLayout(tiles_layout);
    tiles_layout->activate();

    tiles_layout->addWidget(tile1);
    tiles_layout->addWidget(tile2);
    tiles_layout->addWidget(tile3);
    tiles_layout->addWidget(tile4);
    tiles_layout->addWidget(tile5);
    tiles_layout->addWidget(tile6);
    tiles_layout->addWidget(tile7);

    //tiles_layout->activate();
    //tiles_layout->activate();
    //tiles_layout->addItem(item2);
/*
    ui->tiles_layout->setContentsMargins(20,20,20,20);

    ui->tiles_layout->setSizeConstraint(QLayout::SetMaximumSize);

    ui->tiles_layout->addWidget(tile1, 0, 0);
    ui->tiles_layout->addWidget(tile2, 0, 1);
    ui->tiles_layout->addWidget(tile3, 1, 0);
    ui->tiles_layout->addWidget(tile4, 1, 1);
    ui->tiles_layout->addWidget(tile5, 2, 1);
    ui->tiles_layout->addWidget(tile6, 2, 2);
    ui->tiles_layout->addWidget(tile7, 0, 2);*/

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



    QList<QStandardItem*> list;
    auto item = new QStandardItem("localhost");
    auto sys = new QStandardItem("$SYS");

    auto broker = new QStandardItem("broker");
    auto clients = new QStandardItem("clients");
    auto load = new QStandardItem("load");
    auto broker_messages = new QStandardItem("messages");
    auto store = new QStandardItem("store");
    auto subscriptions = new QStandardItem("subscriptions");
    auto retained_messages = new QStandardItem("retained_messages");
    auto broker_publish = new QStandardItem("publish");
    auto broker_bytes = new QStandardItem("bytes");

    auto messages = new QStandardItem("messages");
    auto recieved = new QStandardItem("recieved");
    auto sent = new QStandardItem("sent");
    auto publish = new QStandardItem("publish");
    auto sockets = new QStandardItem("sockets");
    auto connections = new QStandardItem("connections");
    auto p_sent = new QStandardItem("sent");
    auto bytes = new QStandardItem("bytes");
    auto b_recieved = new QStandardItem("recieved");
    auto b_sent = new QStandardItem("sent");
    auto store_messages = new QStandardItem("messages");
    auto broker_publish_messages = new QStandardItem("messages");
    auto broker_publish_bytes = new QStandardItem("bytes");
    auto broker_bytes_recieved = new QStandardItem("messages");
    auto broker_bytes_sent = new QStandardItem("bytes");


    broker->appendRow(new QStandardItem("version"));
    broker->appendRow(new QStandardItem("uptime"));

    clients->appendRow(new QStandardItem("total"));
    clients->appendRow(new QStandardItem("maximum"));
    clients->appendRow(new QStandardItem("active"));
    clients->appendRow(new QStandardItem("connected"));


    recieved->appendRow(new QStandardItem("1min"));
    recieved->appendRow(new QStandardItem("5min"));
    recieved->appendRow(new QStandardItem("15min"));
    sent->appendRow(new QStandardItem("1min"));
    sent->appendRow(new QStandardItem("5min"));
    sent->appendRow(new QStandardItem("15min"));

    p_sent->appendRow(new QStandardItem("1min"));
    p_sent->appendRow(new QStandardItem("5min"));
    p_sent->appendRow(new QStandardItem("15min"));

    b_recieved->appendRow(new QStandardItem("1min"));
    b_recieved->appendRow(new QStandardItem("5min"));
    b_recieved->appendRow(new QStandardItem("15min"));
    b_sent->appendRow(new QStandardItem("1min"));
    b_sent->appendRow(new QStandardItem("5min"));
    b_sent->appendRow(new QStandardItem("15min"));

    sockets->appendRow(new QStandardItem("1min"));
    sockets->appendRow(new QStandardItem("5min"));
    sockets->appendRow(new QStandardItem("15min"));

    connections->appendRow(new QStandardItem("1min"));
    connections->appendRow(new QStandardItem("5min"));
    connections->appendRow(new QStandardItem("15min"));

    broker_messages->appendRow(new QStandardItem("stored"));
    broker_messages->appendRow(new QStandardItem("recieved"));
    broker_messages->appendRow(new QStandardItem("sent"));

    store_messages->appendRow(new QStandardItem("count"));
    store_messages->appendRow(new QStandardItem("bytes"));

    subscriptions->appendRow(new QStandardItem("count"));
    retained_messages->appendRow(new QStandardItem("count"));

    broker_publish_messages->appendRow(new QStandardItem("sent"));
    broker_publish_bytes->appendRow(new QStandardItem("sent"));

    item->appendRow(sys);
    sys->appendRow(broker);
    broker->appendRow(clients);
    broker->appendRow(load);
    broker->appendRow(broker_messages);
    broker->appendRow(store);
    broker->appendRow(subscriptions);
    broker->appendRow(retained_messages);
    broker->appendRow(broker_publish);
    broker->appendRow(broker_bytes);
    load->appendRow(messages);
    load->appendRow(publish);
    load->appendRow(bytes);
    load->appendRow(sockets);
    store->appendRow(store_messages);
    load->appendRow(connections);
    messages->appendRow(recieved);
    messages->appendRow(sent);
    publish->appendRow(p_sent);
    bytes->appendRow(b_recieved);
    bytes->appendRow(b_sent);
    broker_publish->appendRow(broker_publish_messages);
    broker_publish->appendRow(broker_publish_bytes);
    broker_bytes->appendRow(broker_bytes_recieved);
    broker_bytes->appendRow(broker_bytes_sent);


    list.push_back(item);
    model.appendRow(list);
    ui->treeView->setModel(&model);

}


MainWindow::~MainWindow()
{
    delete ui;
    //this->setCentralWidget(ui->textEdit);
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
    new_connection connection;
    connection.setModal(true);
    connection.exec();
}

void MainWindow::on_searchButton_clicked()
{
    //filtrování stromové struktury
    proxy_tree = new QSortFilterProxyModel(this);
    proxy_tree->setSourceModel(&model);
    proxy_tree->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy_tree->setFilterKeyColumn(-1); //If the value is -1, the keys will be read from all columns
    proxy_tree->setFilterFixedString("broker");
}

void MainWindow::on_add_topic_clicked()
{
    //tree path - zde chceme přidat topic
    QString topic_path = ui->topic_search->text();
}

void MainWindow::on_copy_topic_2_clicked()
{
    ui->topic_search->setText("naše pozice ve stromové struktuře");
}

void MainWindow::on_delete_topic_2_clicked()
{
    //vymaže subtopics na této pozici
    QString topic_path = ui->topic_search->text();
}

void MainWindow::on_publish_button_clicked()
{
    QString message_path = ui->path_message->text(); //pošle zprávu na zadanou adresu
    QString text = ui->textEdit->toPlainText(); //zpráva


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
    QPixmap *map = new QPixmap(screen->grabWindow(window));


    Dialog *screenshot = new Dialog(this);
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
void MainWindow::on_snapshot_button_clicked()
{
    //zobrazí obrázek
}

void MainWindow::on_snap_button_clicked()
{
    Snapshot *snap = new Snapshot(this);
    snap->setModal(true);
    snap->exec();
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
