/**
 * @file subject.h
 * @author y3285wan
 * @brief subject interface
 * @date 2019-11-20
 * 
 */


#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <algorithm>
#include <vector>


#include "observer.h"


/**
 * @interface Subject - mother of Cells
 */
template<typename C>
class Subject {
    std::vector<Observer<C>*> observers;

//protected:
//   InfoType myInfoStored;

public:
    void attach(Observer<C> *o);
    void detach(Observer<C> *o);
    void notifyObservers();
    virtual C getInfo() = 0;
};


template<typename C>
void Subject<C>::attach(Observer<C> *o) {
    observers.emplace_back(o);
}


template<typename C>
void Subject<C>::detach(Observer<C> *o) {
    observers.erase(
        std::remove(observers.begin(), observers.end(), o),
        observers.end()
    );
}


template<typename C>
void Subject<C>::notifyObservers() {
    for (auto &ob: observers) ob->notify(*this);
}


#endif

