//Created by Petar Ostojic
//Thu Mar 19 13:24:14 2015
//This class us used to callback functions
#include "defines.h"
#ifndef CSTORMCALLBACKER_H
#define CSTORMCALLBACKER_H
//!TODO: Needs total rewrite

//TODO: This class in C++ 11 format, if compiler suports it

class cStormCallbacker
{
private:
    // Abstract interface for all callbacks
    class Callback
    {
    public:
        virtual ~Callback() { }
        virtual Callback* clone() const = 0;
        virtual void call() = 0;
    };
    
    // Implementation for member functions
    template <typename T>
    class ClassCallback : public Callback
    {
    private:
        T*      object;
        void (T::*callback)();
            
    public:
        ClassCallback(T* obj, void (T::*clbk)()) : object(obj), callback(clbk) {}
        virtual Callback* clone() const { return new ClassCallback<T>(object,callback); }
        virtual void call() { (object->*callback)(); }
    };
    
    // Implementation for global functions
    class GlobalCallback : public Callback
    {
    private:
        void (*callback)();
            
    public:
        GlobalCallback( void (*clbk)() ) : callback(clbk) {}
        virtual Callback* clone() const { return new GlobalCallback(callback); }
        virtual void call() { (*callback)(); }
    };
    
private:
    // Data member for the cStormCallbacker class
    Callback*       callback;
    
public:
    int interval;
    Uint32 lastTick;

    // basic construct/destruct
    cStormCallbacker() { callback = NULL; }
    ~cStormCallbacker() { delete callback; }

    // copy ctor/assign
    cStormCallbacker(const cStormCallbacker& rhs) : callback(0)
    {
        if(rhs.callback)    callback = rhs.callback->clone();
    }
    cStormCallbacker& operator = (const cStormCallbacker& rhs)
    {
        delete callback;
        if(rhs.callback)        callback = rhs.callback->clone();
        else                    callback = 0;
        return *this;
    }

    // construct with an actual callback
    cStormCallbacker(void (*clbk)())
    {
        callback = new GlobalCallback(clbk);
    }

    template <typename T>
    cStormCallbacker(T* obj, void (T::*clbk)())
    {
        callback = new ClassCallback<T>(obj,clbk);
        interval = 0;
        lastTick = 0;
    }

    template <typename T>
    cStormCallbacker(T* obj, void (T::*clbk)(), int _interval)
    {
        callback = new ClassCallback<T>(obj,clbk);
        interval = _interval;
        lastTick = 0;
    }

    // actually calling the function
    void operator () (){
        if(callback != NULL)
            callback->call();
    }
    void Call (){
        if(callback != NULL)
            callback->call();
    }

    int GetInterval() { return interval; }
    void SetInterval(int _interval) { interval = _interval; }
    Uint32 GetLastTick() { return lastTick; }
    void SetLastTick(Uint32 lt) { lastTick = lt; }
};

#endif