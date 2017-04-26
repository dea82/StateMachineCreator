// The MIT License (MIT)
//
// Copyright (c) 2017 Andreas L.
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
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "OutlineStroke.hpp"

#include <QDebug>
#include <QMarginsF>
#include <QPainter>
#include <QPainterPathStroker>

namespace statemachinecreator {
namespace gui {

QRectF OutlineStroke::boundingRect() const {
  return parentItem()->boundingRect().marginsAdded(QMarginsF() += GetPen().widthF());
}

void OutlineStroke::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
  auto original_shape = parentItem()->shape();

  QPainterPathStroker painterPathStroker;
  painterPathStroker.setWidth(GetPen().widthF());
  // Create a stroke which is both inside and outside of original shape
  QPainterPath outlinePath = painterPathStroker.createStroke(original_shape);

  painter->setPen(GetPen());
  // Merge outline path with original shape and draw this path
  painter->drawPath(outlinePath.united(original_shape));
}

}  // namespace gui
}  // namespace statemachinecreator

