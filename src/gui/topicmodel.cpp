#include "topicmodel.h"

#include <iostream>

int TopicModel::rowCount(const QModelIndex &parent) const
{
    std::cout << "rowCount called. parent: " << parent.row() << " : " << parent.column() << " and " << parent.isValid() << "\n";

    if (parent.column() > 0){
        std::cout << "\treturning (column > 0)" << 0<< "\n";
        return 0;
    }

    TopicNode *parentItem;
    if (!parent.isValid()){
        if(cli.sys == nullptr){
            std::cout << "\treturning no sys " << 0 << "\n";
            return 0;
        }
        parentItem = cli.sys->messages_root;
        if(parentItem == nullptr){
            std::cout << "\treturning no root " << 0 << "\n";
            return 0;
        }
    } else {
        parentItem = static_cast<TopicNode*>(parent.internalPointer());
    }

    std::cout << "\treturning " << parentItem->get_number_of_children() << "\n";
    return parentItem->get_number_of_children();
}

int TopicModel::columnCount(const QModelIndex &parent) const
{
    std::cout << "columnCount called. parent: " << parent.row() << " : " << parent.column() << " and " << parent.isValid() << "\n";
    //return 1;

    auto *node = static_cast<TopicNode*>(parent.internalPointer());

    if(!parent.isValid()){
        if(cli.sys == nullptr){
            std::cout << "\treturning no sys " << 0 << "\n";
            return 0;
        }
        node = cli.sys->messages_root;
        if(node == nullptr){
            std::cout << "\treturning no root " << 0 << "\n";
            return 0;
        }
    }

    auto n = node->Msgs.size();
    int has_children = node->Children.size() > 0 ? 1 : 0;
    std::cout << "\treturning " << n + has_children << "\n";
    return n + has_children;



    //std::cout << "\treturning " << cli.sys->messages_root->get_number_of_children() << "\n";
    //return cli.sys->messages_root->get_number_of_children();
}

QVariant TopicModel::data(const QModelIndex &index, int role) const
{
    std::cout << "data called. index: " << index.row() << " : " << index.column() << " role " << role << " isvalid " << index.isValid() << "\n";


    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole){
        return QVariant();
    }

    TopicNode *item = static_cast<TopicNode*>(index.internalPointer());

    int n_of_msgs = item->Msgs.size();

    if(n_of_msgs < index.column() || index.column() < 0 ){
        std::cout << "\treturning bad column index (" << index.column() << ") size (" << n_of_msgs << ")" << std::endl;
        return QVariant();
    }

    std::string str;

    if(index.column() == 0){
        str = item->Topic;
    } else {
        str = item->Msgs[index.column()]->get_payload();
    }

    std::cout << "\treturning " << str << std::endl;
    return QVariant( QString::fromStdString(str) );
}

QVariant TopicModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    std::cout << "headerData called. section: " << section << " orientation " << orientation<< " role " << role  << "\n";

    return QVariant("vv1");
}

QModelIndex TopicModel::index(int row, int column, const QModelIndex &parent) const
{
    std::cout << "index called. parent: " << parent.row() << " : " << parent.column() <<  " row: " << row << " column: " << column<< "\n";

    if (!hasIndex(row, column, parent))
            return QModelIndex();

    TopicNode *parentItem;

    if (!parent.isValid())
        parentItem = cli.sys->messages_root;
    else
        parentItem = static_cast<TopicNode*>(parent.internalPointer());

    TopicNode *childItem = parentItem->get_child_by_index(row);

    if(childItem){
        return createIndex(row, column, childItem);
    } else {
        return QModelIndex();
    }

}

QModelIndex TopicModel::parent(const QModelIndex &index) const
{
    std::cout << "parent called. index: " << index.row() << " : " << index.column() << "\n";

    if (!index.isValid()){
        std::cout << "null child invalid\n";
        return QModelIndex();
    }

    TopicNode *childItem = static_cast<TopicNode*>(index.internalPointer());
    if(childItem == nullptr){
        std::cout << "null child null\n";
        return QModelIndex();
    }

    TopicNode *parentItem = childItem->Parent;

    if (parentItem == cli.sys->messages_root){
        std::cout << "null child root\n";
        return QModelIndex();
    }

    std::cout << "child " << parentItem->get_own_index() << " : " << 0 << "\n";
    return createIndex(parentItem->get_own_index(), 0, parentItem); // index na rodice
}

void TopicModel::incoming_data_change()
{
    std::cout << "Slot incoming_data_change active" << std::endl;
    emit layoutChanged();
}





