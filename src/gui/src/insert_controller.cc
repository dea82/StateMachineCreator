/*
The MIT License (MIT)
Copyright (c) 2018-12-14 Andreas
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

#include "insert_controller.h"

#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QEvent>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneEvent>

#include "element_graphics_item_builder.h"
#include "element_graphics_item_factory.h"
#include "state_graphics_item.h"

namespace statemachinecreator::gui {

void InsertController::StartInsert(std::unique_ptr<model::IElement> element) {
  ObserveredScene()->installEventFilter(this);
  temporary_element_ = std::move(element);
}

void InsertController::FinishInsert() {
  ObserveredScene()->removeEventFilter(this);
  scene_controller_->AddElement(element_graphics_item_);
  element_graphics_item_ = nullptr;
  emit InsertFinished();
  // TODO: Move ownership of temporary element to correct state in main model
}

void InsertController::AbortInsert() {
  auto observed_scene = ObserveredScene();
  observed_scene->removeEventFilter(this);
  if (element_graphics_item_) {
    observed_scene->removeItem(element_graphics_item_);
    delete element_graphics_item_;
    element_graphics_item_ = nullptr;
  }
  temporary_element_.reset(nullptr);
  emit InsertFinished();
}

bool InsertController::eventFilter(QObject* /*object*/, QEvent* event) {
  if (event->type() == QEvent::GraphicsSceneMouseMove) {
    if (!element_graphics_item_)
      CreateElementGraphics();
    element_graphics_item_->setPos(dynamic_cast<QGraphicsSceneMouseEvent*>(event)->scenePos());
  } else if (event->type() == QEvent::GraphicsSceneMousePress) {
    FinishInsert();
  }
  return false;
}

void InsertController::CreateElementGraphics() {
  ElementGraphicsItemBuilder builder(graphics_factory_.get());
  auto element_graphics_item = builder.Build(temporary_element_.get());
  element_graphics_item_ = element_graphics_item.get();
  // Takes ownership of graphics item
  ObserveredScene()->addItem(element_graphics_item.release());
}

}  // namespace statemachinecreator::gui
