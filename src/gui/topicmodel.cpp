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
                }
            }
        }

        f.setWeight(QFont::Weight::Light);
        return QVariant(f);
    }

    if (role != Qt::DisplayRole){
        return QVariant();
    }

    TopicNode *item = static_cast<TopicNode*>(index.internalPointer());

    //std::cout << "Valid data called. index: " << index.row() << " : " << index.column() << "\n";

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

    //std::cout << "\treturning " << str << std::endl;
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
    //std::cout << "index called. parent: " << parent.row() << " : " << parent.column() <<  " row: " << row << " column: " << column<< "\n";

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
    //std::cout << "parent called. index: " << index.row() << " : " << index.column() << "\n";

    if (!index.isValid()){
        //std::cout << "null child invalid\n";
        return QModelIndex();
    }

    TopicNode *childItem = static_cast<TopicNode*>(index.internalPointer());
    if(childItem == nullptr){
        //std::cout << "null child null\n";
        return QModelIndex();
    }

    TopicNode *parentItem = childItem->Parent;

    if (parentItem == cli.sys->messages_root.get()){
        return QModelIndex();
    }

    //std::cout << "child " << parentItem->get_own_index() << " : " << 0 << "\n";
    return createIndex(parentItem->get_own_index(), 0, parentItem); // index na rodice
}

void TopicModel::incoming_data_change()
{
    std::cout << "Slot incoming_data_change active" << std::endl;
    emit layoutChanged();
}





