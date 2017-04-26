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

#ifndef CREATOR_OUTLINESTROKE_HPP_
#define CREATOR_OUTLINESTROKE_HPP_

#include <QGraphicsItem>
#include <QPainterPath>
#include <QPen>

namespace statemachinecreator {
namespace gui {

class OutlineStroke : public QGraphicsItem {
 public:
  OutlineStroke(const QPen& pen, QGraphicsItem* parent)
      : pen_(pen),
        QGraphicsItem(parent) {
  }

  QRectF boundingRect() const override;

  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = Q_NULLPTR) override;

  QPen getPen() const {
    return pen_;
  }

  void SetPen(const QPen& pen) {
    pen_ = pen;
  }

  QPen GetPen() const {
    return pen_;
  }

 private:
  QPen pen_;
};

}  // namespace gui
}  // namespace statemachinecreator
#endif  // CREATOR_OUTLINESTROKE_HPP_
