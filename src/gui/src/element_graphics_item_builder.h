/*
The MIT License (MIT)
Copyright (c) 2018-12-06 Andreas
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

#include <QGraphicsItem>

#include "i_element_graphics_item_factory.h"
#include "model/ielement_visitor.h"
#include "model/ielement.h"

class QGraphicsItem;

namespace statemachinecreator::gui {

class ElementGraphicsItemBuilder : public model::IElementVisitor {
 public:
  explicit ElementGraphicsItemBuilder(std::unique_ptr<factory::IElementGraphicsItemFactory> factory) : factory_{
      std::move(factory)}, element_graphics_item_{nullptr} {}

  std::unique_ptr<QGraphicsItem> Build(model::IElement* element);
 private:
  void Visit(model::IState*) override;
  std::unique_ptr<factory::IElementGraphicsItemFactory> factory_;
  std::unique_ptr<QGraphicsItem> element_graphics_item_;
};

}
