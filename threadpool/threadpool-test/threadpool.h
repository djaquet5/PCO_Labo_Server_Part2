#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>

#include "runnable.h"
#include "poolworker.h"
#include <QWaitCondition>
#include <QMutex>

using namespace std;

class ThreadPool
{
    QWaitCondition isFree;
    QMutex mutex;
    int nbThreadWorking,
        maxThreadCount;
    PoolWorker* workers;
public:
    ThreadPool(int maxThreadCount) : maxThreadCount(maxThreadCount) {

    }

    /* Start a runnable.  If no &
!thread is available and the pool is at max capacity, block the &
!caller until a thread becomes available again. */
    void start(Runnable* runnable) {
        mutex.lock();
        int nbThreadFree = getFirstThreadFree();

        if(nbThreadFree != -1){
            workers[nbThreadFree] = PoolWorker(runnable, &isFree);
            workers[nbThreadFree].start();
        } else {
            isFree.wait(&mutex);
        }
        mutex.unlock();
    }

private:
    // Si aucun thread n'est libre, retourne -1
    // Si n'est pas initialisé ou s'il ne travaille pas. retourne l'indice
    int getFirstThreadFree(){
        for(int i = 0; i < maxThreadCount; i++){
            if(&workers[i] == nullptr || !workers[i].getIsRunning()){
                return i;
            }
        }

        return -1;
    }
};

#endif // THREADPOOL_H
