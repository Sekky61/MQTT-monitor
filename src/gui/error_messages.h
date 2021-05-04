/*!
 *  \file      error_messages.h
 *  \brief     Vyskakovací okno hlásící chybu
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 03.05.2021
 */

#ifndef ERROR_MESSAGES_H
#define ERROR_MESSAGES_H

#include <QString>

 /*! 
  *  \brief     Funkce otevře nové okno značící error
  *  \details   Otevřené okno v sobě obsahuje informaci a nastalém problému
  *  \param     text důvod problému, nebo jeho popis
  */
void error_message(QString text);

#endif // ERROR_MESSAGES_H