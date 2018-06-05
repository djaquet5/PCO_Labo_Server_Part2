/*
 -----------------------------------------------------------------------------
 Labo        : 6 - Server
 Fichier     : requestworker.h
 Auteur(s)   : David Jaquet et Vincent Guidoux
 Date        : 22.05.2018

 But         : définission et implémentation du thread de traitement
               de requête.
 -----------------------------------------------------------------------------
*/
#include "requesthandler.h"
#include "response.h"
#include "runnable.h"

#ifndef REQUESTWORKER_H
#define REQUESTWORKER_H

#endif // REQUESTWORKER_H


class RequestWorker : public Runnable
{
private:
    Request request;
    AbstractBuffer<Response>* responses;
    bool hasDebugLog;
    QString m_id;

public:
    RequestWorker(Request request,
                  AbstractBuffer<Response>* responses,
                  QString m_id,
                  bool hasDebugLog):
        request(request), responses(responses), hasDebugLog(hasDebugLog), m_id(m_id) {}

protected:

    /**
     * @brief run : traîte une requête et la place dans le tampon de
     *              réponses
     */
    void run (){
        responses->put((new RequestHandler(request, hasDebugLog))->handle());
    }

    /**
    * @brief id returns the Id of the Runnable
    * @return The Id of the Runnable
    */
    virtual QString id() {
        return m_id;
    }

};
