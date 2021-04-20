#include "topicmodel.h"

#include <iostream>
#include <QFont>

int TopicModel::rowCount(const QModelIndex &parent) const
{
    //std::cout << "rowCount called. parent: " << parent.row() << " : " << parent.column() << " and " << parent.isValid() << "\n";

    if (parent.column() > 0){
        //std::cout << "\treturning (column > 0)" << 0<< "\n";
        return 0;
    }

    TopicNode *parentItem;
    if (!parent.isValid()){
        if(cli.sys == nullptr){
            //std::cout << "\treturning no sys " << 0 << "\n";
            return 0;
        }
        parentItem = cli.sys->messages_root;
        if(parentItem == nullptr){
            //std::cout << "\treturning no root " << 0 << "\n";
            return 0;
        }
    } else {
        parentItem = static_cast<TopicNode*>(parent.internalPointer());
    }

    //std::cout << "\treturning " << parentItem->get_number_of_children() << "\n";
    return parentItem->get_number_of_children();
}

int TopicModel::columnCount(const QModelIndex &parent) const
{
    //std::cout << "columnCount called. parent: " << parent.row() << " : " << parent.column() << " and " << parent.isValid() << "\n";

    auto *node = static_cast<TopicNode*>(parent.internalPointer());

    if(!parent.isValid()){
        if(cli.sys == nullptr){
            //std::cout << "\treturning no sys " << 0 << "\n";
            return 0;
        }
        node = cli.sys->messages_root;
        if(node == nullptr){
            //std::cout << "\treturning no root " << 0 << "\n";
            return 0;
        }
    }

    int has_children = node->Children.size() > 0 ? 1 : 0;
    return has_children;
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
                }
            }
        }

        f.setWeight(QFont::Weight::Light);
        return QVariant(f);
    }

    if (role != Qt::DisplayRole){
        return QVariant();
    }

    std::cout << "Valid data called. index: " << index.row() << " : " << index.column() << "\n";

    TopicNode *item = static_cast<TopicNode*>(index.internalPointer());

    /*int n_of_msgs = item->Msgs.size();

    if(n_of_msgs < index.column() || index.column() < 0 ){
        std::cout << "\treturning bad column index (" << index.column() << ") size (" << n_of_msgs << ")" << std::endl;
        return QVariant();
    }*/

    std::string str;

    if(index.row() == 0 && index.column() != 0){
        if(index.column() - 1 < item->Msgs.size() && index.column() > 0){
            str = item->Msgs[index.column() - 1]->get_payload();
        } else {
            return QVariant();
        }
    } else {
        str = item->Topic;
    }

    std::cout << "\treturning " << str << std::endl;
    return QVariant( QString::fromStdString(str) );
}

QVariant TopicModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    std::cout << "headerData called. section: " << section << " orientation " << orientation<< " role " << role  << "\n";

    if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
        return QVariant(QStringList("Topics", "Messages"));
    }

    return QVariant();
}

QModelIndex TopicModel::index(int row, int column, const QModelIndex &parent) const
{
    std::cout << "index called. parent: " << parent.row() << " : " << parent.column() <<  " row: " << row << " column: " << column<< "\n";

    if (!hasIndex(row, column, parent))
            return QModelIndex();

    TopicNode *parentItem;

    if (!parent.isValid()){
        parentItem = cli.sys->messages_root;
        if(parentItem == nullptr){
            return QModelIndex();
        }
    } else {
        parentItem = static_cast<TopicNode*>(parent.internalPointer());
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





