/**
  Classe crée par Vincent Guidoux et David Jaquet reprise du cours de PCO
  */

#ifndef BUFFER_H
#define BUFFER_H

#include "abstractbuffer.h"
#include <QSemaphore>

const int NoInitTamponN = 10;

template<typename T> class Buffer : public AbstractBuffer<T> {

protected:
    T *elements;
    int writePointer;
    int readPointer;
    int bufferSize;
    QSemaphore mutex, waitNotFull, waitNotEmpty;

public:
    Buffer(unsigned int size) : mutex(1), waitNotFull(size) {
        if ((elements = new T[size]) != 0) {
            writePointer = readPointer = 0;
            bufferSize = size;
            return;
        }
        throw NoInitTamponN;
    }

     ~Buffer() {
        delete[] elements;
    }

    virtual void put(T item) {
        waitNotFull.acquire();
        mutex.acquire();
        elements[writePointer] = item;
        writePointer = (writePointer + 1) % bufferSize;
        waitNotEmpty.release();
        mutex.release();
    }

    virtual bool tryPut(T item){

        return true;
    }

    virtual T get(void) {
        T item;
        waitNotEmpty.acquire();
        mutex.acquire();
        item = elements[readPointer];
        readPointer = (readPointer + 1) % bufferSize;
        waitNotFull.release();
        mutex.release();
        return item;
    }
};


#endif // BUFFER_H
