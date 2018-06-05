#ifndef POOLWORKER_H
#define POOLWORKER_H

#include "runnable.h"

class PoolWorker {
    Runnable* run;
    bool isRunning;
    QWaitCondition* isFree;
public:
    PoolWorker(Runnable* run, QWaitCondition* isFree) : run(run),
                    isFree(isFree), isRunning(false){}

    void start(){
        isRunning = true;
        run->run();
        isRunning = false;
        isFree->wakeAll();
    }

    bool getIsRunning(){
        return isRunning;
    }

    void setRun(Runnable* run){
        this->run = run;
    }
};

#endif // POOLWORKER_H
