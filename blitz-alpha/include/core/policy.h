
/**
 *  MIT License

 *  Copyright (c) 2021 Emmanuel Godwin

 *  Permission is hereby granted, free of charge, to any person obtaining a copy of 
 *  this software and associated documentation files (the "Software"), to deal in 
 *  the Software without restriction, including without limitation the rights to use, 
 *  copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
 *  Software, and to permit persons to whom the Software is furnished to do so, 
 *  subject to the following conditions:

 *  The above copyright notice and this permission notice shall be included in all 
 *  copies or substantial portions of the Software.

 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 *  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
 *  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 *  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#ifndef BLITZ_ALPHA_INCLUDE_CORE_POLICY_H
#define BLITZ_ALPHA_INCLUDE_CORE_POLICY_H


#include "alpha.h"


namespace blitz {

    template<bool> struct CompileTimeError;
    template<> struct CompileTimeError<true> {};

#define STATIC_CHECK(expr) (CompileTimeError<(expr) != 0>())

    template<typename _To, typename _From>
    _To safe_reinterpret_cast(_From from) {
        STATIC_CHECK(sizeof(_From) <= sizeof(_To));

        return reinterpret_cast<_To>(from);
    }

    template<typename T>
    class NewCreator {
    public:
        static T* Create() {
            return new T;
        }
    };

    template<typename T>
    class MallocCreator {
    public:
        static T* Create() {
            void* buf = std::malloc(sizeof(T));
            if (!buf) return 0;
            return new(buf) T;
        }
    };

    template<typename T>
    class PrototypeCreator {
    public:
        PrototypeCreator(T* p_obj = 0) :_prototype(p_obj) {}
        T* Create() {
            return _prototype ? _prototype->Clone : 0;
        }
        T* GetPrototype() { return _prototype; }
        void SetPrototype(T* p_obj) { _prototype = p_obj; }
    private:
        T* _prototype;
    };

    class Widget {
    public:
        Widget() {
            std::cout << "Widget::Created.\n";
        }
    };

    template<template <typename> class CreationPolicy>
    class WidgetManager : CreationPolicy<Widget> {
    public:
        WidgetManager() {

        }
    };

    typedef WidgetManager<NewCreator> NewWidgetMgr;
    typedef WidgetManager<MallocCreator> MalWidgetMgr;
    typedef WidgetManager<PrototypeCreator> ProWidgetMgr;


    class Singleton{
        public:
            static Singleton* Instance(){
                if(!_instance){
                    if(_destroyed){
                        OnDeadReference();
                    }
                    else{ Create();  }
                }
                return _instance;
            }

            void dumb(){}

        private:
            static Singleton* _instance;
            static bool _destroyed;
            Singleton();
            Singleton(const Singleton&);
            Singleton& operator=(const Singleton&);
        private:
            static void Create(){
                static Singleton theInstance;
                _instance = &theInstance;
            }
            static void OnDeadReference(){
                throw std::runtime_error("Dead Reference Detected.");
            }
            virtual ~Singleton(){
                _instance = 0;
                _destroyed = true;
            }
    };






























































}



#endif

