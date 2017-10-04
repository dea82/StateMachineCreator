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

#ifndef CREATOR_ENTRYPOINT_HPP_
#define CREATOR_ENTRYPOINT_HPP_

#include <QString>

#include "OutlineGraphicsItem.hpp"

class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QRectF;

class EntryPoint : public OutlineGraphicsItem {
 public:
  explicit EntryPoint(qreal diameter = kDefaultDiameter_)
      : OutlineGraphicsItem(OutlineGraphicsItem::ItemType::kEntryPoint, "Entry point"),
        entryPointBorder_(QRectF(-diameter / 2.0F, -diameter / 2.0F, diameter, diameter)),
        outline_pen_() {
    this->setZValue(1);
    outline_pen_.setWidth(2);
  }

  QRectF boundingRect() const override;

  QPainterPath shape() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

 private:
  QRectF entryPointBorder_;
  static constexpr qreal kDefaultDiameter_ = 22;
  QPen outline_pen_;
};

#endif  // CREATOR_ENTRYPOINT_HPP_
