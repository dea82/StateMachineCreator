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

#include "ResizeHandle.hpp"

#include <QDebug>
#include <QPainter>
#include <QPointF>

#include "OutlineGraphicsItem.hpp"

class QGraphicsItem;
class QGraphicsSceneHoverEvent;
class QGraphicsSceneMouseEvent;
class QStyleOptionGraphicsItem;
class QWidget;

ResizeHandle::ResizeHandle(OutlineGraphicsItem* const parent, const Position& position)
    : QGraphicsItem(static_cast<QGraphicsItem*>(parent)),
      position_ { position },
      parent_ { parent },
      hovered_ { false } {
  this->setZValue(2);
  setAcceptHoverEvents(true);
  qDebug() << this->pos();
}

QRectF ResizeHandle::boundingRect() const {
  QRectF boundingRect = parentItem()->boundingRect();
  switch (position_) {
    case Position::kTopLeft:
      return QRectF(boundingRect.topLeft().x(), boundingRect.topLeft().y(), getSize(), kSize_);
      break;
    case Position::kTopRight:
      return QRectF(boundingRect.topRight().x() - kSize_, boundingRect.topRight().y(), kSize_, kSize_);
      break;
    case Position::kBottomLeft:
      return QRectF(boundingRect.bottomLeft().x(), boundingRect.bottomLeft().y() - kSize_, kSize_, kSize_);
      break;
    case Position::kBottomRight:
      return QRectF(boundingRect.bottomRight().x() - kSize_, boundingRect.bottomRight().y() - kSize_, kSize_, kSize_);
      break;
    default:
      break;
  }
  return QRectF(0, 0, kSize_, kSize_);
}

void ResizeHandle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  if (hovered_) {
    painter->setBrush(Qt::SolidPattern);
  }
  painter->drawRect(boundingRect().adjusted(0, 0, 0, 0));
}

void ResizeHandle::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  qDebug() << "Foo";
}

void ResizeHandle::hoverEnterEvent(QGraphicsSceneHoverEvent*mouseEvent) {
  qDebug() << "Gurka";
  hovered_ = true;
  this->update(boundingRect());
}

void ResizeHandle::hoverLeaveEvent(QGraphicsSceneHoverEvent*mouseEvent) {
  hovered_ = false;
  this->update(boundingRect());
}

