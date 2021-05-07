#include "topicmodel.h"

#include <iostream>
#include <QFont>
#include <QBrush>

int TopicModel::rowCount(const QModelIndex &parent) const
{
    //std::cout << "rowCount called. parent: " << parent.row() << " : " << parent.column() << " and " << parent.isValid() << "\n";

    if (parent.column() > 0){
        //std::cout << "\treturning (column > 0)" << 0<< "\n";
        return 0;
    }

    if (parent.isValid()){
        return static_cast<TopicNode*>(parent.internalPointer())->number_of_children();
    } else {
        if(cli.sys == nullptr || cli.sys->messages_root.get() == nullptr){
            return 0;
        }
        return cli.sys->messages_root->number_of_children();
    }
}

int TopicModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()){
        return static_cast<TopicNode*>(parent.internalPointer())->number_of_children() > 0 ? 1 : 0;
    } else {
        if(cli.sys == nullptr || cli.sys->messages_root.get() == nullptr){
            return 0;
        }
        return cli.sys->messages_root->number_of_children() > 0 ? 1 : 0;
    }
}

QVariant TopicModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();

    if(role == Qt::FontRole){
        QFont f;

        TopicNode *item = static_cast<TopicNode*>(index.internalPointer());
        if(item != nullptr){
            std::string full_topic = item->fullTopic;
            if(cli.sys != nullptr){
                if(cli.sys->is_subscribed_topic(full_topic)){
                    f.setWeight(QFont::Weight::Bold);
                    return QVariant(f);
                } else if(item->is_start_of_wildcard){
                    f.setWeight(QFont::Weight::Medium);
                    return QVariant(f);
                } else {
                    f.setWeight(QFont::Weight::Light);
                    return QVariant(f);
                }
            }
        }

        f.setWeight(QFont::Weight::Light);
        return QVariant(f);
    }
/*
    if(role == Qt::BackgroundRole){

        TopicNode *item = static_cast<TopicNode*>(index.internalPointer());
        if(item->Msgs.size() == 0){
            return QVariant();
        }
        std::cerr << "bcgrnd: " << item->Topic << " " << item->last_msg_sent << "\n";
        if(item->last_msg_sent){
            QColor green = QColor(171,255,122);
            QBrush br = QBrush(green);
            return QVariant(br);
        } else {
            QColor blue = QColor(148,239,255);
            QBrush br = QBrush(blue);
            return QVariant(br);
        }
    }
*/
    if (role != Qt::DisplayRole){
        return QVariant();
    }

    TopicNode *item = static_cast<TopicNode*>(index.internalPointer());

    std::string str;

    if(index.row() == 0 && index.column() != 0){
        if(index.column() - (unsigned)1 < item->Msgs.size() && index.column() > 0){
            str = item->Msgs[index.column() - 1]->get_payload();
        } else {
            return QVariant();
        }
    } else {
        str = item->Topic;
    }

    return QVariant( QString::fromStdString(str) );
}

QVariant TopicModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);

    if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
        QStringList header = {"Topics", "Messages"};
        return QVariant(header);
    }

    return QVariant();
}

QModelIndex TopicModel::index(int row, int column, const QModelIndex &parent) const
{

    if (!hasIndex(row, column, parent))
            return QModelIndex();

    TopicNode *parentItem;

    if (parent.isValid()){
        parentItem = static_cast<TopicNode*>(parent.internalPointer());
    } else {
        if(cli.sys == nullptr || cli.sys->messages_root.get() == nullptr){
            return QModelIndex();
        }
        parentItem = cli.sys->messages_root.get();
    }

    TopicNode *childItem = parentItem->get_child_by_index(row);

    if(childItem){
        return createIndex(row, column, childItem);
    } else {
        return QModelIndex();
    }

}

//Returns the parent of the model item with the given index.
QModelIndex TopicModel::parent(const QModelIndex &index) const
{

    if (!index.isValid()){
        return QModelIndex();
    }

    TopicNode *childItem = static_cast<TopicNode*>(index.internalPointer());
    if(childItem == nullptr){
        return QModelIndex();
    }

    TopicNode *parentItem = childItem->Parent;

    if (parentItem == cli.sys->messages_root.get()){
        return QModelIndex();
    }

    return createIndex(parentItem->get_own_index(), 0, parentItem); // index na rodice
}

void TopicModel::incoming_data_change(QString topic, QString message)
{
    Q_UNUSED(topic);
    Q_UNUSED(message);
    std::cout << "Slot incoming_data_change active" << std::endl;
    emit layoutChanged();
}





