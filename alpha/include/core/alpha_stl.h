
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




#ifndef BLITZ_ALPHA_INCLUDE_CORE_ALPHA_STL_H
#define BLITZ_ALPHA_INCLUDE_CORE_ALPHA_STL_H

#include "alpha.h"

#include <set>
#include <iterator>
#include <algorithm>
#include <type_traits>
#include <unordered_set>
#include <list>
#include <functional>

using namespace std::placeholders;
namespace blitz {

    namespace gen {

        class Name {
        public:
            
            Name() {}
            Name(std::string, std::string);
            
        public:
            std::string FirstName() const;
            std::string LastName() const;
            Name& operator=(const Name&);
            bool operator==(Name& n1)const;
        private:
            std::string firstName;
            std::string lastName;
        };

       /*   void NameAccess(Name& _name, const Name n1) {
            _name.firstName = n1.firstName;
            _name.lastName = n1.lastName;
        } 

        std::ostream& operator<<(std::ostream& ost, const Name& name) {
            return ost << name.firstName << " " << name.lastName << std::endl;
        }
 */
        class NameAscending {
        public:
            bool operator()(const Name&, const Name&) const;
        };

        class NameDescending {
        public:
            bool operator()(const Name&, const Name&) const;
        };

        template<typename T, typename SortCriterion>
        using NameSet = std::set<T, SortCriterion>;


        class IntSequence {
        public:
            friend int GetIntValue();
            IntSequence(int init) :value(init) {}
            int operator()() {
                return ++value;
            }
        private:
            int value;
        };

        


        class MeanValue {
        public:
            MeanValue() :num(0), sum(0) {}

            void operator()(long int elem) {
                ++num;
                sum += elem;
            }

            double value() {
                return static_cast<double>(sum) / static_cast<double>(num);
            }

        private:
            long int num;
            long int sum;
        };


        template<typename T>
        bool fn(const T& t) {
            if (std::is_pointer_v<T>) {
                std::cout << "is_pointer == true" << '\n';
            }
            else { std::cout << "is_pointer == false" << '\n'; }
            return std::is_pointer_v<T>;
        }


























        /* template <class T, class A = std::allocator<T> >
        class pod {
        public:
            using A allocator_type;
            using typename A::value_type value_type;
            using typename A::reference reference;
            using typename A::const_reference const_reference;
            using typename A::difference_type difference_type;
            using typename A::size_type size_type;

            class iterator {
            public:
                using typename A::difference_type difference_type;
                using typename A::value_type value_type;
                using typename A::reference reference;
                using typename A::pointer pointer;
                using std::random_access_iterator_tag iterator_category; //or another tag

                iterator();
                iterator(const iterator&);
                ~iterator();

                iterator& operator=(const iterator&);
                bool operator==(const iterator&) const;
                bool operator!=(const iterator&) const;
                bool operator<(const iterator&) const; //optional
                bool operator>(const iterator&) const; //optional
                bool operator<=(const iterator&) const; //optional
                bool operator>=(const iterator&) const; //optional

                iterator& operator++();
                iterator operator++(int); //optional
                iterator& operator--(); //optional
                iterator operator--(int); //optional
                iterator& operator+=(size_type); //optional
                iterator operator+(size_type) const; //optional
                friend iterator operator+(size_type, const iterator&); //optional
                iterator& operator-=(size_type); //optional
                iterator operator-(size_type) const; //optional
                difference_type operator-(iterator) const; //optional

                reference operator*() const;
                pointer operator->() const;
                reference operator[](size_type) const; //optional
            };
            class const_iterator {
            public:
                using typename A::difference_type difference_type;
                using typename A::value_type value_type;
                using typename const A::reference reference;
                using typename const A::pointer pointer;
                using std::random_access_iterator_tag iterator_category; //or another tag

                const_iterator();
                const_iterator(const const_iterator&);
                const_iterator(const iterator&);
                ~const_iterator();

                const_iterator& operator=(const const_iterator&);
                bool operator==(const const_iterator&) const;
                bool operator!=(const const_iterator&) const;
                bool operator<(const const_iterator&) const; //optional
                bool operator>(const const_iterator&) const; //optional
                bool operator<=(const const_iterator&) const; //optional
                bool operator>=(const const_iterator&) const; //optional

                const_iterator& operator++();
                const_iterator operator++(int); //optional
                const_iterator& operator--(); //optional
                const_iterator operator--(int); //optional
                const_iterator& operator+=(size_type); //optional
                const_iterator operator+(size_type) const; //optional
                friend const_iterator operator+(size_type, const const_iterator&); //optional
                const_iterator& operator-=(size_type); //optional
                const_iterator operator-(size_type) const; //optional
                difference_type operator-(const_iterator) const; //optional

                reference operator*() const;
                pointer operator->() const;
                reference operator[](size_type) const; //optional
            };

            using std::reverse_iterator<iterator> reverse_iterator; //optional
            using std::reverse_iterator<const_iterator> const_reverse_iterator; //optional

            pod();
            pod(const pod&);
            ~pod();

            pod& operator=(const pod&);
            bool operator==(const pod&) const;
            bool operator!=(const pod&) const;
            bool operator<(const pod&) const; //optional
            bool operator>(const pod&) const; //optional
            bool operator<=(const pod&) const; //optional
            bool operator>=(const pod&) const; //optional

            iterator begin();
            const_iterator begin() const;
            const_iterator cbegin() const;
            iterator end();
            const_iterator end() const;
            const_iterator cend() const;
            reverse_iterator rbegin(); //optional
            const_reverse_iterator rbegin() const; //optional
            const_reverse_iterator crbegin() const; //optional
            reverse_iterator rend(); //optional
            const_reverse_iterator rend() const; //optional
            const_reverse_iterator crend() const; //optional

            reference front(); //optional
            const_reference front() const; //optional
            reference back(); //optional
            const_reference back() const; //optional
            template<class ...Args>
            void emplace_front(Args&&...); //optional
            template<class ...Args>
            void emplace_back(Args&&...); //optional
            void push_front(const T&); //optional
            void push_front(T&&); //optional
            void push_back(const T&); //optional
            void push_back(T&&); //optional
            void pop_front(); //optional
            void pop_back(); //optional
            reference operator[](size_type); //optional
            const_reference operator[](size_type) const; //optional
            reference at(size_type); //optional
            const_reference at(size_type) const; //optional

            template<class ...Args>
            iterator emplace(const_iterator, Args&&...); //optional
            iterator insert(const_iterator, const T&); //optional
            iterator insert(const_iterator, T&&); //optional
            iterator insert(const_iterator, size_type, T&); //optional
            template<class iter>
            iterator insert(const_iterator, iter, iter); //optional
            iterator insert(const_iterator, std::initializer_list<T>); //optional
            iterator erase(const_iterator); //optional
            iterator erase(const_iterator, const_iterator); //optional
            void clear(); //optional
            template<class iter>
            void assign(iter, iter); //optional
            void assign(std::initializer_list<T>); //optional
            void assign(size_type, const T&); //optional

            void swap(pod&);
            size_type size() const;
            size_type mapod_size() const;
            bool empty() const;

            A get_allocator() const; //optional
        };
        template <class T, class A = std::allocator<T> >
        void swap(pod<T, A>&, pod<T, A>&); //optional

 */








    }
}
















#endif