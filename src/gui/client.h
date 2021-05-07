/*!
 *  \file      client.h
 *  \brief     MQTT klient - QT adaptér
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 03.05.2021
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

#include "../logic/message_system.hpp"

/*!
 * \brief Klient
 * Obálka třídy \ref MessageSystem. Přidává komunikaci pomocí
 * signálů a slotů, což umožňuje lepší práci v prostředí QT.
 */
class client : public QObject
{
    Q_OBJECT
public:

    /*!
     * \brief status připojení
     */
    bool connected;

    /*!
     * \brief MQTT klient
     */
    MessageSystem *sys;

    /*!
     * \brief Konstruktor
     * \param parent předek v hierarchii QT objektů
     */
    explicit client(QObject *parent = nullptr);

    /*!
     * \brief Připojí se na server
     * Připojí se na server, nastaví callback pro příchozí zprávy
     * \param client_name jméno klienta
     * \param server_address adresa serveru
     * \return status připojení
     */
    int connect_to_server(QString client_name, QString server_address);

signals:

    /*!
     * \brief signál úspěšného připojení
     * Využit pro zavření připojovacího okna \ref new_connection
     */
    void connection_succesful();

    /*!
     * \brief signál změny ve strukturách zpráv
     * Přidání nového tématu, nová příchozí zpráva.
     * Parametry nemusí být využity, pokud cílem signálu je pouze upozornit na změnu a vyvolat překreslení.
     * \param topic téma příchozí zprávy (pokud je relevantní)
     * \param message obsah příchozí zprávy (pokud je relevantní)
     */
    void mqtt_data_changed(QString topic, QString message);

public slots:

    /*!
     * \brief Pokus o připojení
     * Slot je spojen se signálem tlačítka "connect" v \ref new_connection
     * \param client_name řetězec který se má použít jako jméno klienta
     * \param password heslo pro přístup na server
     * \param server_address adresa serveru
     */
    void user_clicked_connect(QString client_name, QString password, QString server_address);

    /*!
     * \brief Odpojení ze serveru, vymazání záznamů o zprávách
     */
    void user_clicked_disconnect();

    /*!
     * \brief Klient začne odebírat téma
     * Podporuje "wildcards".
     * \param topic_string téma, které uživatel zadal
     */
    void add_topic_slot(QString topic_string);

    /*!
     * \brief Klient přestane odebírat téma
     * \param topic_string téma, které přestane být odebíráno
     */
    void delete_topic_slot(QString topic_string);

    /*!
     * \brief Publikuje zprávu
     * \param topic_string téma zprávy
     * \param content obsah zprávy
     */
    void publish_slot(QString topic_string, QString content); //todo void *

    /*!
     * \brief Nastaví nový limit historie zpráv
     * Limit platí pro každé téma zvlášť. Ke každému tématu bude tedy uloženo maximálně \ref limit zpráv.
     * \param limit
     */
    void change_limit_slot(int limit);

};

#endif // CLIENT_H
