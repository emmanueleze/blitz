
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



#ifndef BLITZ_ALPHA_INCLUDE_CORE_BASE_H
#define BLITZ_ALPHA_INCLUDE_CORE_BASE_H

#include "util/stable.h"
#include "core/bstructs.h"
#include "core/controls.h"


namespace blitz {


    

    class RawData{
        public:
            RawData(){}
            virtual void ReadData(){
                std::cout<<"RawData::ReadData()\n";}
    };

    class DataObject : public RawData{
        public:
            DataObject(){}
            DataObject(std::string, double, int){}
            void ReadData()override{
                std::cout<<"DataObject::ReadData()\n";
                RawData::ReadData();}
    };

    template<typename T1, typename T2>
    auto max(T1 a, T2 b) -> std::decay_t<decltype(true ? a : b)>
    {
        return b < a ? a : b;
    }

    template<typename T, int N>
    struct Array_type {
        using type = T;
        static const int dim;
    };

    constexpr int MAX_ONSTSCK = sizeof(std::string);


    template<typename T>
    class Scoped {
    public:
        T& operator*() { return x; }
        T* operator->() { return &x; }

        Scoped(const Scoped&) = delete;
        Scoped operator=(const Scoped&) = delete;

    private:
        T x;
    };

    template<typename T>
    class On_heap {
    public:
        On_heap() :p{ new T } {}   // allocate
        ~On_heap() { delete p; }   //de-allocate

        T& operator*() { return *p; }
        T* operator->() { return p; }

        On_heap(const On_heap&) = delete;
        On_heap operator()(const On_heap&) = delete;

    private:
        T* p;

    };

    template<typename T>
    struct Obj_holder {
        using type = typename std::conditional<(sizeof(T) <= MAX_ONSTSCK),
            Scoped<T>,
            On_heap<T>>::type;
    };


    template<bool _Cond, typename T, typename F>
    using Conditional = typename std::conditional<_Cond, T, F>::type;


    /* template<auto Val, typename T = decltype(Val)>
    T add_val(T& t) {
        return t + Val;
        std::cout << t << '\n';
    } */
    




}   //namespace blitz


#endif