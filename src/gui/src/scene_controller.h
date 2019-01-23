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
class NewElementCommand : public QUndoCommand {
 public:
  explicit NewElementCommand(QGraphicsItem* graphics_item) : graphics_item_{
      graphics_item} {
    setText("insert element");
  }
  ~NewElementCommand() = default;

  void redo() override {
    // Would it be possible to remove the item from the scene instead and move ownership
    graphics_item_->show();
  }
  void undo() override {
    graphics_item_->hide();
  }
 private:
  QGraphicsItem* graphics_item_;
};

}

namespace statemachinecreator::gui {

class SceneController : public QObject, public ISceneController {
 Q_OBJECT
 public:
  explicit SceneController(QGraphicsScene* scene, QObject* parent) : QObject{parent},
                                                                     scene_{scene},
                                                                     undo_stack_{new QUndoStack()} {
    QObject::connect(undo_stack_, &QUndoStack::canUndoChanged, this, &SceneController::CanUndoChanged);
    QObject::connect(undo_stack_, &QUndoStack::canRedoChanged, this, &SceneController::CanRedoChanged);
  }

  QGraphicsScene* Scene() const override {
    return scene_;
  }

  void AddElement(QGraphicsItem* graphics_item) override {
    undo_stack_->push(new NewElementCommand(graphics_item));
  }

  void Undo() {
    undo_stack_->undo();
  }
  void Redo() {
   undo_stack_->redo();
 }
  Q_SIGNAL void CanUndoChanged(bool can_undo);
  Q_SIGNAL void CanRedoChanged(bool can_redo);

 private:
  QGraphicsScene* scene_;
  QUndoStack* undo_stack_;
};

}

