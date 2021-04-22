#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutapplication.h"
#include "new_connection.h"


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent) ,
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->value_text->setReadOnly(true);

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
    //QApplication::aboutQt;
    AboutApplication aboutapplication;
    aboutapplication.setModal(true);
    aboutapplication.exec();
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
