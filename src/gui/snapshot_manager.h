/*!
 *  \file      snapshot_manager.h
 *  \brief     Ukládání stromové struktury do adresářů
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 03.05.2021
 */

#ifndef SNAPSHOT_MANAGER_H
#define SNAPSHOT_MANAGER_H

#include <QDir>
#include "client.h"

class snapshot_manager
{
public:
    snapshot_manager();

    int create_snapshot(QDir root_dir, client *cli);

    int dump_topic(QDir dir, TopicNode *node);
};

#endif // SNAPSHOT_MANAGER_H
