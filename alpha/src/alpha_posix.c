// MIT License
//
// Copyright (c) 2021 Emmanuel Godwin
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "alpha/util/alpha_posix.h"



void* worker(void* arg){
  int value = *((int*) arg);
  printf("value passed: %d\n", value);
  return 0;
}


int thread_runner() {
  pthread_t threads[NUM_THREADS];
  int thread_args[NUM_THREADS];
  for (unsigned int i = 0; i < NUM_THREADS; ++i) {
    thread_args[i] = i;
    pthread_create(&threads[i], 0, worker, (void*)
      &thread_args[i]); }
  
  for (int i = 0; i < NUM_THREADS; ++i) {
    pthread_join(threads[i], 0);
  }

  exit(0);
}