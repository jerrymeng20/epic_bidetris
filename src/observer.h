/**
 * @file observer.h
 * @author y3285wan
 * @brief observer interface
 * @date 2019-11-20
 * 
 */


#ifndef _OBSERVER_H_
#define _OBSERVER_H_



template<typename C>
class Subject;

/**
 * @interface Observer - mother of Cell, Displays
 */
template<typename C>
class Observer {
public:
    virtual void notify(Subject<C> &from) = 0;
    virtual ~Observer() = default;
};

#endif
