#include <QFile>
#include "snapshot_manager.h"

snapshot_manager::snapshot_manager()
{

}

int snapshot_manager::create_snapshot(QDir root_dir, client &cli)
{
    if(!root_dir.mkdir("snapshot")){
        return 1;
    }

    if(!root_dir.cd("snapshot")){
        return 1;
    }

    auto *root = cli.sys->messages_root;
    if(root == nullptr){
        return 1;
    }

    for(auto *child : root->Children){
        int ret = dump_topic(root_dir, child);
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
    QFile payload_file = QFile(file_name);
    if(payload_file.open(QIODevice::WriteOnly)){
        mqtt::const_message_ptr *last_message = node->get_latest_msg();
        if(last_message != nullptr){
            if(*last_message != nullptr){
                std::string content = (*last_message)->get_payload();
                payload_file.write(content.data());
            }
        }
        payload_file.close();
    } else {
        return 1;
    }

    // Vytvorit slozky pro potomky
    for(auto *child: node->Children){
        QString topic(child->Topic.data());
        dir.mkdir(topic);
        QDir child_dir(dir);
        child_dir.cd(topic);
        int ret = dump_topic(child_dir, child);
        if(ret != 0){
            return ret;
        }
    }

    return 0;
}
