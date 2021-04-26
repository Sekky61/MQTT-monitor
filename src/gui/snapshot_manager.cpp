#include <QFile>
#include "snapshot_manager.h"

snapshot_manager::snapshot_manager()
{

}

int snapshot_manager::create_snapshot(QDir root_dir, client *cli)
{
    if(cli == nullptr){
        std::cerr << " cli null\n";
        return 1;
    }

    if(cli->sys == nullptr){
        std::cerr << " sys null\n";
        return 1;
    }

    auto &root = cli->sys->messages_root;
    if(root == nullptr){
        std::cerr << " messages null\n";
        return 1;
    }

    std::cerr << "Creating snapshot\n";
    std::cerr << root_dir.path().toStdString();
    if(!root_dir.mkpath("snapshot")){
        std::cerr << " mkdir failed\n";
        return 1;
    }

    if(!root_dir.cd("snapshot")){
        std::cerr << " cd failed\n";
        return 1;
    }
    std::cerr << "In snapshot dir\n" << root_dir.path().toStdString() << "\n";

    for(auto &child : root->Children){
        QDir root_cpy = QDir(root_dir);
        QString topic = QString::fromStdString(child->Topic);
        root_cpy.mkpath(topic);
        root_cpy.cd(topic);
        int ret = dump_topic(root_cpy, child.get());
        if(ret != 0){
            return ret;
        }
    }


    return 0;
}

int snapshot_manager::dump_topic(QDir dir, TopicNode *node){

    if(node == nullptr){
        return 0;
    }

    QString file_name("payload.txt");

    // Vytvorit payload.txt
    QFile payload_file = QFile(dir.path() + "/" + file_name);

    mqtt::const_message_ptr *last_message = node->get_latest_msg();
    if(last_message != nullptr){
        if(*last_message != nullptr){
            if(payload_file.open(QIODevice::WriteOnly)){
                std::string content = (*last_message)->get_payload();
                payload_file.write(content.data());
            } else {
                return 1;
            }
        }
    }

    // Vytvorit slozky pro potomky
    for(auto &child: node->Children){
        QString topic(child->Topic.data());
        dir.mkdir(topic);
        QDir child_dir(dir);
        child_dir.cd(topic);
        int ret = dump_topic(child_dir, child.get());
        if(ret != 0){
            return ret;
        }
    }

    return 0;
}
