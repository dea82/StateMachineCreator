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

#include "State.hpp"

#include <QDebug>

State::State(const QString& name, const qreal x, const qreal y, const qreal w, const qreal h)
    : name_(name),
      x_(x),
      y_(y),
      w_(w),
      h_(h) {
}

QRectF State::boundingRect() const {
  return QRectF(x_, y_, w_, h_);
}

void State::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  painter->drawRect(x_, y_, kDefaultWidth_, kDefaultHeight_);
  qDebug() << "Draw rect: " << x_ << " " << y_ << " " << w_ << " " << h_;
}

// void State::mousePressEvent(QGraphicsSceneMouseEvent *event) {
//  qDebug() << "Clicked state: " << name_;
//  QGraphicsItem::mousePressEvent(event);
// }
