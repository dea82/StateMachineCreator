/*
The MIT License (MIT)
Copyright (c) 2018-12-21 Andreas
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#pragma once

#include <QGraphicsScene>

#include "i_scene_controller_fwd.h"
#include "i_scene_controller.h"

namespace statemachinecreator::gui {

class StateMachineScene : public QGraphicsScene {
 public:
  explicit StateMachineScene(QObject* parent) : QGraphicsScene{parent}, scene_controller_{nullptr} {
  }
  // TODO: Are these necessary?
  ISceneController* Controller() const {
    return scene_controller_;
  }
  // TODO: Are these necessary?
  void Controller(ISceneController* controller) {
    scene_controller_ = controller;
  }
 private:
  ISceneController* scene_controller_; // Non ownership
};

}
