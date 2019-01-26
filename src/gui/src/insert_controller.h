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

#include "factory.h"
#include "i_element_graphics_item_factory.h"
#include "i_scene_controller.h"
#include "i_insert_controller.h"
#include "model/ielement.h"
#include "state_machine_scene.h"

class QGraphicsItem;

namespace statemachinecreator::gui {

class InsertController : public QObject, public IInsertController {
 Q_OBJECT
 public:
  explicit InsertController(ISceneController* scene_controller,
                            std::unique_ptr<factory::IElementGraphicsItemFactory> graphics_factory,
                            QObject* parent) :
      QObject{parent},
      temporary_element_{nullptr},
      element_graphics_item_{nullptr},
      scene_controller_{scene_controller},
      graphics_factory_{std::move(graphics_factory)} {}
  void StartInsert(std::unique_ptr<model::IElement> element) override;

  void AbortInsert() override;

  // TODO: Rename or duplicate
  Q_SIGNAL void InsertFinished();

 private:
  void FinishInsert();

  bool eventFilter(QObject* object, QEvent* event) override;
  // TODO: This should probably be moved to a "SceneController" which can return a pointer to the created element.
  void CreateElementGraphics();

  QGraphicsScene* ObserveredScene() const {
    return scene_controller_->Scene();
  }

  std::unique_ptr<model::IElement> temporary_element_;
  QGraphicsItem* element_graphics_item_;
  ISceneController* scene_controller_;
  std::unique_ptr<factory::IElementGraphicsItemFactory> graphics_factory_;
};

}