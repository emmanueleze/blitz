
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


#ifndef BLITZ_ALPHA_INCLUDE_CORE_GENERIC_H
#define BLITZ_ALPHA_INCLUDE_CORE_GENERIC_H


#pragma once


#include <map>
#include <queue>
#include <array>
#include <utility>
#include <ostream>
#include <iterator>
#include <functional>
#include <type_traits>



namespace blitz {

    namespace gen {


        template<typename T, typename Cont = std::vector<T>>
        class QStack {
        public:
            QStack() {
                std::cout << "Primary Specialization of Stack_1.\n";
            }
            void push(T _t) {
                elems.push(_t);
            }

        private:
            Cont elems;
        };

        //  Explicit specialization of Stack_1.
        template<>
        class QStack<std::string, std::queue<std::string>> {};


        template<typename T>
        using DequeStack = QStack<T, std::deque<T>>;



        // *** alias template for member types.

        template<typename T>
        class node {
        public:
            node() :data{} {}
            node(T _data) :data{ _data } {}
            using _Val = T;
            _Val get() { return data; }
        private:
            T data;
        };

        //  ******* variadic_templates *********

        //binary tree structure and traversal helpers:
        struct Node {
            int value;
            Node* left;
            Node* right;

            Node(int i = 0) : value{ i }, left{ nullptr }, right{ nullptr }{}
        };

        template<typename T, typename... TP>
        Node* traverse(T* np, TP... paths) {
            return (np ->* ...->*paths);
        }

        template<typename T>
        class Spacer {
        public:
            Spacer(T const& r) :ref(r) {}
            friend std::ostream operator<<(std::ostream&& os, Spacer<T> s) {
                return os << s.ref << ' ';
            }
        private:
            T const& ref;
        };

        /* void print() {}

        template<typename... Types>
        void print(Types const&... args) {
            (std::cout << ... << Spacer(args)) << '\n';
        }
 */
 //variadic templates
        
        /* template<typename T1, typename... TN>
        constexpr bool isHomogeneous(T1, TN...) {
            return (std::is_same_v<T1, TN>&& ...);
        } */

        template<typename T>
        void print_coll(T const& coll) {
            typename T::const_iterator pos;   //iterate over coll
            typename T::const_iterator end(coll.end());   //end position

            for (pos = coll.begin(); pos != end; ++pos) {
                std::cout << *pos << ' ';
            }
            std::cout << '\n';
        }
        template<typename T>
        void var_fn(T arg) { std::cout << arg << ' '; }
        //  variadic template var_fn()
        template<typename T, typename... Args>
        void var_fn(T fst, Args... rst) {
            var_fn(fst);
            var_fn(rst...);

        }

        template<typename K, typename V,
            template<class, class...> class Cont = std::map>
        class Mapper {
        public:
            Mapper() {}

        private:
            Cont<K, V> _cont;

        };

        template<class V, class A,
            template<class, class...> class Container = std::map>
        class BaseContainer {
        public:
            BaseContainer() {}
        private:
            Container<V, A> _cont;
        };

        /* template<typename T, template<class, class...> class C, class... Args>
        std::ostream& operator<<(std::ostream& os, const C<T, Args...>& objs){
            os << __PRETTY_FUNCTION__ << '\n';
            for(auto const& obj : objs)
                os << obj <<' ';
            return os;
        } */

        template<typename T, template<typename... Args> class Cont = std::vector>
        class Vector {
        public:
            Vector() {}



        private:
            Cont<T> cont;
        };

        template<typename T = long double>
        constexpr T e = T{ 2.7182818284529 };


        template<typename X>
        void g(X&) {
            std::cout << "g() for value.\n";
        }
        template<typename X>
        void g(const X&) {
            std::cout << "g() for constant.\n";
        }
        template<typename X>
        void g(X&&) {
            std::cout << "g() for moveable object.\n";
        }

        /*  @brief Perfect Forwarding.
         *  @tparam T declares a forwarding reference
         *  @param val value to be forwarded.
         *  Perfect forwarding val to g()
        */
        template<typename T>
        void f(T&& val) {
            g(std::forward<T>(val));
        }


       /*  class Person {
        public: */
            /* //  constructor for passed initial name.
            explicit Person(std::string const& n) :name(n ){
                std::cout<<"copying string_CONSTR for "<< name<< '\n';
            }
            explicit Person(std::string&& n) :name(std::move(n)){
                std::cout<<"moving string_CONSTR for "<<name<<'\n';
            } */

            /* // generic constructor for passed initial name.
            template<typename STR>
            explicit Person(STR&& n) :name( std::forward<STR>(n) ){
                std::cout<< "TMPL_CNSTR for"<< name<<'\n';
            } */

            /* template<typename T>
            using EnableIfString = std::enable_if_t<std::is_convertible_v<T, std::string>>;
            // generic constructor for passed initial name.
            template<typename STR, typename = EnableIfString<STR>>
            explicit Person(STR&& n) :name(std::forward<STR>(n)) {
                std::cout << "TMPL_CNSTR for " << name << '\n';
            }

            //  copy/move constructors  
            Person(Person const& p) :name(p.name) {
                std::cout << "copy_CONSTR for " << name << '\n';
            }

            Person(Person&& p) :name(std::move(p.name)) {
                std::cout << "move_CONSTR for " << name << '\n';
            }



        private:
            std::string name;

        }; */

        template<typename T>
        auto print = [](T const& n) {std::cout << n << ' ';};


        /* template<typename T, typename... Args>
        auto print = [](T const& n, Args const& args) {std::cout << n << ' ';}; */

        template<typename Cont>
        void reverse_elems(Cont _cont) {

            typedef typename Cont::value_type T;

            std::for_each(_cont.rbegin(), _cont.rend(), print<T>);
            std::cout << '\n';
        }
        template<typename T>
        using EnableType = std::enable_if_t<!std::is_const_v<T>>;
        //  This template is intantiated for only nonconstant objects passed to the function.
        template<typename T, typename = EnableType<T>>
        void outR(T arg) {
            std::cout << &arg << '\n';
        }

        template<unsigned p, unsigned d>    //p: number to check, d: current divisor.
        struct DoIsPrime {
            static constexpr bool value = (p % d != 0) && DoIsPrime<p, d - 1>::value;
        };

        template<unsigned p>        //end recursion if divisor is 2.
        struct DoIsPrime<p, 2> {
            static constexpr bool value = (p % 2 != 0);
        };

        template<unsigned p>    // primary template.
        struct IsPrime {
            static constexpr bool value = DoIsPrime<p, p / 2>::value;
        };
        //  special cases (to avoid endless recursion with template instantiation):
        template<>
        struct IsPrime<0> { static constexpr bool value = false; };
        template<>
        struct IsPrime<1> { static constexpr bool value = false; };
        template<>
        struct IsPrime<2> { static constexpr bool value = true; };
        template<>
        struct IsPrime<3> { static constexpr bool value = true; };


        constexpr bool is_prime(unsigned int p) {
            for (unsigned int d = 2; d <= p / 2; ++d) {
                if (p % d == 0) return false;
            }
            return p > 1;
        }



        template<typename T>
        class FuncObj {
        public:
            void operator()(T _t)const {
                std::cout << _t << ' ';
            }
        };

        template<typename Tp>
        void func(Tp t) {
            std::cout << t << " ";
        }

        /** @brief Surrorgate call function
         *  @tparam _Fn1
         *  @tparam _Fn2
         *
         */
        template<typename _Fn1, typename _Fn2>
        class Surrogate {
        public:
            Surrogate(_Fn1* _f1, _Fn2* _f2) :f1(_f1), f2(_f2) {}

            operator _Fn1* () { return f1; }
            operator _Fn2* () { return f2; }
        private:
            _Fn1* f1;
            _Fn2* f2;
        };



        /* template<typename Iter, typename Callable>
        void foreach(Iter begin, Iter end, Callable oper){
            while(begin != end){
                oper(*begin);
                ++begin;
            }
            std::cout<<"\n";
        } */


        template<typename Iter, typename Callable, typename... Args>
        void foreach(Iter begin, Iter end, Callable op, Args const&... args) {
            while (begin != end) {
                std::invoke(op, args..., *begin);
                ++begin;
            }
            std::cout << '\n';
        }

        template<typename T>
        class QClass {
        public:
            void mem_func(T t)const {
                std::cout << "QClass::mem_func() called for " << t << '\n';
            }
        };

        template<typename Callable, typename... Args>
        decltype(auto) call (Callable&& op, Args&&... args){
            return std::invoke(std::forward<Callable>(op),
             std::forward<Args>(args)...);
        }

        
//      ********************************************************************************

        template<typename Type>
        class Data{
            public:
                Data() = default;   //  Ensures that Data<Type> is default constructible.
                template<typename SubType>
                Data();
                //NonTemplate Members

                void Display()const;
                bool IsValid()const;
                static constexpr bool copyable = true;
                inline static double xunit = 0.0;
                template<typename Tp>
                class Handle;
                template<typename Tp>
                void ProcessData(Tp& data_ref)const;
        };

        template<typename _Tp>
        bool dataCopyable = Data<_Tp>::copyable;

        template<typename T>
            template<typename U>
        class Data<T>::Handle{
            public:
                Handle(){}
                virtual void LinkData(){}
                virtual ~Handle();

        };

        template<typename T>
            template<typename U>
        void Data<T>::ProcessData(U& data_ref)const{
            std::cout<<"Processing data for "<<data_ref<<'\n';
        }

        template<typename _T>
          template<typename _St>
        Data<_T>::Data(){}

        
        template<template<typename T,
                        typename A = Data<T> > class Base>
        class DataHolder{};













    }
}




#endif