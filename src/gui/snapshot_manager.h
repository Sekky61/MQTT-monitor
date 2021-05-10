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

/**
 * \brief Ukládá strom MQTT zpráv do adresářového stromu
 */
class snapshot_manager
{
public:
    snapshot_manager();

    /**
     * \brief Vytvoří adrsářový strom
     * \param root_dir kořenová složka, ve které se snapshot vytvoří
     * \param cli client, obsahující ukládaný strom
     */
    int create_snapshot(QDir root_dir, client *cli);

    /**
     * \brief rekurzivně voláno z \ref create_snapshot. Uloží obsah jednoho tématu
     * \param dir složka, do které se obsah uloží
     * \param node uzel tématu
     */
    int dump_topic(QDir dir, TopicNode *node);
};

#endif // SNAPSHOT_MANAGER_H
