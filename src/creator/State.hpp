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

#ifndef CREATOR_STATE_HPP_
#define CREATOR_STATE_HPP_

#include <QGraphicsItem>
#include <QPainter>

class State : public QGraphicsItem {
 public:
  State(const QString& name_, const qreal x, const qreal y, const qreal w = kDefaultWidth_, const qreal h =
            kDefaultHeight_);
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
  QString getName() const {
    return name_;
  }

 protected:
//  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

 private:
  QString name_;
  qreal x_;
  qreal y_;
  qreal w_;
  qreal h_;
  static constexpr qreal kDefaultWidth_ = 20;
  static constexpr qreal kDefaultHeight_ = 20;
};

#endif  // CREATOR_STATE_HPP_
