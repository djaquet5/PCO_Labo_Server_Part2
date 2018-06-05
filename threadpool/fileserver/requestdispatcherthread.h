/*
 -----------------------------------------------------------------------------
 Labo        : 6 - Server
 Fichier     : requestdispatcherthread.h
 Auteur(s)   : David Jaquet et Vincent Guidoux
 Date        : 22.05.2018

 But         : le thread de dispatching des requêtes appelle le thread de
               traitement de requête

 Commentaires :
 -----------------------------------------------------------------------------
*/
#ifndef REQUESTDISPATCHERTHREAD_H
#define REQUESTDISPATCHERTHREAD_H

#include "abstractbuffer.h"
#include <QObject>
#include <QThread>
#include <QDebug>

#include "request.h"
#include "requestworker.h"
#include "response.h"


class RequestDispatcherThread : public QThread
{
    Q_OBJECT
public:
    /**
     * @brief RequestDispatcherThread est le constructeur du thread de
     * dispatching des requêtes
     * @param requests      : tampon de requête
     * @param responses     : tampon de réponses
     * @param hasDebugLog   : décrit si DebugLog est initialisé
     */
    RequestDispatcherThread(AbstractBuffer<Request>* requests,
                            AbstractBuffer<Response>* responses,
                            bool hasDebugLog) :
        requests(requests),responses(responses), hasDebugLog(hasDebugLog) {

        if (hasDebugLog)
            qDebug() << "Created requests dispatcher thread";
        qRegisterMetaType<Request>("Request");
    }

protected:

    /**
     * @brief dès qu'une requête est prêt, nous lançons le thread de
     * traitement de requêtes
     */
    void run()
    {
        while(true) {
            if (hasDebugLog)
                qDebug() << "Waiting for request...";

            RequestWorker* tmp =  new RequestWorker(requests->get(),
                                                    responses,
                                                    hasDebugLog);
            tmp->start();
        }
    }

private:
    AbstractBuffer<Request>* requests;
    AbstractBuffer<Response>* responses;
    bool hasDebugLog;
};

#endif // REQUESTDISPATCHERTHREAD_H
