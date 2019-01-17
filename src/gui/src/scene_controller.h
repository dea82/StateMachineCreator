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

#include <memory>
#include <utility>

#include <QGraphicsScene>
#include <QUndoStack>

#include "state_graphics_item.h"
#include "i_scene_controller.h"

namespace {
class NewStateCommand : public QUndoCommand {
 public:
  explicit NewStateCommand(statemachinecreator::gui::StateGraphicsItem* state_graphics_item) : state_graphics_item_{
      state_graphics_item} {
    setText("insert state");
  }
  ~NewStateCommand() {

  }
  void redo() override {
    // Would it be possible to remove the item from the scene instead and move ownership
    state_graphics_item_->show();
  }
  void undo() override {
    state_graphics_item_->hide();
  }
 private:
  statemachinecreator::gui::StateGraphicsItem* state_graphics_item_;
};

}

namespace statemachinecreator::gui {

class SceneController : public QObject, public ISceneController {
 Q_OBJECT
 public:
  explicit SceneController(QGraphicsScene* parent) : QObject{parent}, undo_stack_{new QUndoStack()} {
    QObject::connect(undo_stack_, &QUndoStack::canUndoChanged, this, &SceneController::canUndoChanged);
  }

  void AddState(StateGraphicsItem* state_graphics_item) override {
    undo_stack_->push(new NewStateCommand(state_graphics_item));
  }

  Q_SIGNAL void canUndoChanged(bool canRedo);

 private:
  QUndoStack* undo_stack_;
};

}

