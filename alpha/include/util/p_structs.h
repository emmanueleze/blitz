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




#ifndef ALPHA_INCLUDE_UTIL_P_STRUCTS_H
#define ALPHA_INCLUDE_UTIL_P_STRUCTS_H

#include "alpha.h"

#include <algorithm>
#include <stack>
#include <memory>
#include "core/controls.h"
#include "core/concurrent.h"
#include "util/exceptional.h"



#pragma once

namespace quark {

    namespace stc {

        template<typename T>
        class NODE {

        public:
            NODE() {}
            NODE(const NODE& n) = default;
            NODE(NODE&& n) = default;
            //template static int valid_NODE<int>(NODE& _NODE);   //explcit instantiation request
            using value_type = T;

        public:
            NODE(T k) :key{ k } {}
            T key;
            NODE<T>* next = nullptr;
            NODE<T>* prev = nullptr;

        };
        
        template<typename T>
        using _node = NODE<T>;

        template<typename T>
        bool operator==(const NODE<T>& n0, const NODE<T>& n1) {
            if (n0.key == n1.key)
                return true;
            else
                return false;
        }

        template<typename T, int sz>
        class naive_stack {

        public:
            naive_stack() = default;
            naive_stack(T* a) {
                arr = a;
            }
            bool is_empty()const {
                if (top < 0)
                    return true;
                else
                    return false;
            }

            void push(T x) {
                try {

                    top = top + 1;
                    if (top == sz)
                        throw except::overflow{ "buffer overflowed." };
                    else {
                        arr[top] = x;
                    }
                }
                catch (except::overflow o) {
                    std::cout << o.what() << '\n';
                }
            }
            void pop() {
                if (top < 0)
                    std::cout << "buffer underflow.\n";
                top = top - 1;
            }
            void show()const {
                std::cout << "[ ";
                for (int i = 0; i <= top; ++i) {
                    std::cout << arr[i] << ' ';
                    if (i < top - 1)
                        std::cout << ", ";
                }
                std::cout << " ]" << '\n';
            }

        private:
            int top = -1;
            T* arr = nullptr;

        };
        /** @brief Stack
         * Thread-Safe implementation of a stack
         * @param T type of element in the stack
        */
        template<typename T>
        class Stack {

        public:
            Stack() {}
            Stack(const Stack& _stack) {
                std::lock_guard<std::mutex> lock(_stack.m);
                data = _stack.data;
            }
            Stack& operator=(const Stack&) = delete;

            void push(T _entry) {
                std::lock_guard<std::mutex> lock(m);
                data.push(_entry);
                ++sz;
            }

            std::shared_ptr<T> pop() {
                std::lock_guard<std::mutex> lock(m);
                if (data.empty()) throw std::runtime_error("empty structure.");
                std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
                data.pop();
                --sz;
                return res;
            }

            T top() {
                std::lock_guard<std::mutex> lock(m);
                //std::cout<<data.top()<<'\n';
                return data.top();
            }

            void pop(T& _entry) {
                std::lock_guard<std::mutex> lock(m);
                if (data.empty()) throw std::runtime_error("empty structure.");
                _entry = data.top();
                data.pop();
                --sz;
            }
            unsigned int size() { return sz; }
            bool is_empty() {
                std::lock_guard<std::mutex> lock(m);
                return data.empty();
            }
        private:
            std::stack<T> data;
            mutable std::mutex m;
            unsigned int sz;

        };


        template<typename  T, int sz>
        class Queue {

        public:
            Queue();
            Queue(T* a) :arr{ a } {

            }

            void enqueue(T t) {
                if (tail == (sz))
                    tail = 0;
                else {
                    if (head == -1)
                        head = 0;
                    ++tail;
                    printf("%d\n", tail);
                    arr[tail] = t;
                }
            }
            T dequeue() {

            }
            bool isempty()const {
                if ((head == -1) && (tail == -1))
                    return true;
                else
                    return false;
            }

            void showfront()const {
                std::cout << arr[head] << '\n';
            }

        private:
            int head = -1;
            int tail = -1;
            T* arr = nullptr;

        };

        // Implementaion of a Doubly-LinkedList
        template<typename L>
        class LinkedList {
        public:

            LinkedList() {
                if (_head)
                    _head = nullptr;
            }
            LinkedList(NODE<L>* n0) {
                _head = n0;
                ++NODE_ct;
            }

            NODE<L>* operator[](L k) {
                NODE<L>* x = _head;
                while ((x != nullptr) && (x->key != k))
                    x = x->next;
                return x;
            }

        public:

            void insert(NODE<L>* NODE) {
                NODE->next = _head;
                if (_head == nullptr) {
                    _head->prev = NODE;
                    ++NODE_ct;
                }
                _head = NODE;
                NODE->prev = nullptr;
                ++NODE_ct;
            }

            void remove(NODE<L>* NODE) {
                if (NODE->prev != nullptr)
                    NODE->prev->next = NODE->next;
                else
                    _head = NODE->next;
                if (NODE->next == nullptr)
                    NODE->next->prev = NODE->prev;
            }


            int size() { return NODE_ct; }




        public:
            L key;
            NODE<L>* _head = nullptr;
            int NODE_ct = 0;

        };


    }




}
#endif
