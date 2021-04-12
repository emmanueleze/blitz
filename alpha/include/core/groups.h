
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


#ifndef ALPHA_INCLUDE_CORE_GROUPS_H
#define ALPHA_INCLUDE_CORE_GROUPS_H

/*  I implement the design patterns here from Gamma et. al.
 *  and modify them if necessacry.
 */

#include "util/stable.h"

#include "core/base.h"
#include <fstream>




namespace blitz{
/* template<typename S>
class Singleton{
    public:
        static Singleton* Instance() {
            if (_instance == nullptr){
                _instance = new Singleton(S{});
                std::cout<<"is_null() = true.\n";
                }
            return _instance;
        }
        Singleton(Singleton &_singleton) = delete;
        void operator=(const Singleton&) = delete;
        S getValue()const{ return _value; }
        Singleton(){}
        Singleton(S value):_value{value}{}
        bool is_null(){
            return (_instance == nullptr);
        }
    private:
        static Singleton* _instance;
        S _value;
};

template<typename S>
Singleton<S>* Singleton<S>::_instance =  0; */

/* class Reader{
    public:
        Reader(){}
        void read()const;
        int open();
        int read();
        std::string path()const{}
        
}; */

class FileReader{
    public:
        FileReader(){}
        FileReader(std::string path) :_path{path}{}
        int open_file(std::ios_base::openmode);
        std::string path()const{return _path;}

        
    private:
        std::string _path;
        std::fstream fs;
        
};
//class to wrap Reader.. for the AdapterClient class. brb

/* class BufferedReader{
    public:
        BufferedReader(){}
        using type = Reader;
        //BufferedReader(Reader& _reader){}
        //BufferedReader(std::string str){}
        inline void setbfsz(uint sz) {BUF_SZ = {sz};}
        uint getSize() {return BUF_SZ.buf_sz;}
        void displayPath(){_file->path();}
    private:
        blitz::buffer_t BUF_SZ {1024};
        FileReader* _file;

}; */


/*     class State;

    class Originator{
        public:
            Memento* CreateMemento();;
            void SetMemento(const Memento*);

        private:
            State* _state;
    };

    class Memento{
        public:
            virtual ~Memento();
        private:
            friend class Originator;
            Memento();
            void SetStatem(State*);
            State* GetState();
        private:
            State* _state;
    }; */











}




#endif