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

int g_slider_position = 0;
int g_run = 1, g_dontset = 0; //start out in single step mode
cv::VideoCapture g_cap;


Cv::NamedWindow::NamedWindow(string name, cv::WindowFlags size) :
  _name(name), _size(size){}

void Cv::NamedWindow::operator()(){
  cv::namedWindow(_name, _size);
  cv::waitKey(0);
  
}

Cv::NamedWindow::~NamedWindow(){
  cv::destroyWindow(_name);
}

int engine::Cv::display_image(std::string file) {
  cv::Mat img = cv::imread(file, -1);
  if (img.empty()) return -1;
  cv::namedWindow("Example1", cv::WINDOW_KEEPRATIO);
  cv::imshow("Example1", img);
  cv::waitKey(0);
  cv::destroyWindow("Example1");

  return 0;
}

void Cv::onTrackBarSlide(int pos, void* ){
  g_cap.set( cv::CAP_PROP_POS_FRAMES, pos );
  if( !g_dontset )
    g_run = 1;
  g_dontset = 0;

}

int Cv::playVideo(string path) {
  cv::namedWindow("Example2_4", cv::WINDOW_AUTOSIZE);
  g_cap.open(path);
  int frames = (int)g_cap.get(cv::CAP_PROP_FRAME_COUNT);
  int tmpw
    = (int)g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
  int tmph
    = (int)g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
  cout << "Video has " << frames << " frames of dimensions("
    << tmpw << ", " << tmph << ")." << endl;
  cv::createTrackbar("Position", "Example2_4", &g_slider_position, frames,
    Cv::onTrackBarSlide);
  cv::Mat frame;
  for (;;) {
    if (g_run != 0) {
      g_cap >> frame;
      if (frame.empty()) break;
      int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES);
      g_dontset = 1;
      cv::setTrackbarPos("Position", "Example2_4", current_pos);
      cv::imshow("Example2_4", frame);
      g_run -= 1;
    }
    char c = (char)cv::waitKey(10);
    if (c == 's') // single step
      if (c =='s') // single step
      {
        g_run = 1;
        cout << "Single step, run = " << g_run << endl;
      }
    if (c == 'r') // run mode
    {
      g_run = -1; cout << "Run mode, run = " << g_run << endl;
    }
    if (c == 27)
      break;
  }
  return(0);

}