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

#ifndef REQUESTWORKER_H
#define REQUESTWORKER_H

#endif // REQUESTWORKER_H


class RequestWorker : public QThread
{
private:
    Request request;
    AbstractBuffer<Response>* responses;
    bool hasDebugLog;

public:
    RequestWorker(Request request,
                  AbstractBuffer<Response>* responses,
                  bool hasDebugLog):
        request(request), responses(responses), hasDebugLog(hasDebugLog) {}

protected:

    /**
     * @brief run : traîte une requête et la place dans le tampon de
     *              réponses
     */
    void run (){
        responses->put((new RequestHandler(request, hasDebugLog))->handle());
    }

};
