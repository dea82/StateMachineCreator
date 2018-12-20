/*
The MIT License (MIT)
Copyright (c) 2018 andreas
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

#include <QObject>

#include "iinsert_controller.h"

class QGraphicsItem;

namespace statemachinecreator::gui {

class InsertController : public QObject, public IInsertController {
 public:
  explicit InsertController() : temporary_element_{nullptr},
                                element_graphics_item_{nullptr},
                                observed_scene_{nullptr} {}

  bool IsInserting() override {
    return temporary_element_ != nullptr;
  }
  void StartInsert(QGraphicsScene* scene, std::unique_ptr<model::IElement> element) override;

  void FinishInsert() override;

  void AbortInsert() override;

  bool eventFilter(QObject* object, QEvent* event) override;

 private:
  //TODO: This should probably be moved to a "SceneController" which can return a pointer to the created element.
  void CreateElementGraphics();

  std::unique_ptr<model::IElement> temporary_element_;
  QGraphicsItem* element_graphics_item_;
  QGraphicsScene* observed_scene_;

};

}