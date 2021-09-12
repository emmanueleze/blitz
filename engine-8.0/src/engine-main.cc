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

#include "engine/engine.h"


using namespace engine;
using namespace std;
using namespace cv;

void func(Point2i& _point){
  message(_point);
}

int main(int argc, char** argv) {

  printf("Enter index.\n");
  int a, b, c;
  cin >> a;
  cin >> b;
  cin >> c;
  Mat m1 = Mat::eye(3,4, CV_32FC3);
  randu(m1,0,9);
  message(m1);
  printf("Element at (%d,%d,%d) is [%f, %f, %f]\n",
    a, b, c,
    m1.at<Vec3f>(a,b,c)[0],
    m1.at<Vec3f>(a,b,c)[1],
    m1.at<Vec3f>(a,b,c)[2] );
  




}