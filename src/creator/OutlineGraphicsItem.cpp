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

#include "OutlineGraphicsItem.hpp"

#include <QColor>
#include <QDebug>
#include <QGraphicsItem>
#include <QPainter>

class QGraphicsSceneHoverEvent;
class QGraphicsSceneMouseEvent;
class QVariant;

std::map<OutlineGraphicsItem::ItemType, int> OutlineGraphicsItem::nameCounter;

OutlineGraphicsItem::OutlineGraphicsItem(const ItemType& type, const QString& name)
    : type_ { type },
      hoverGraphicsItem_ { new statemachinecreator::gui::OutlineStroke(GetHoverPen(), this) } {
  setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
  setAcceptHoverEvents(true);
  if (OutlineGraphicsItem::nameCounter.count(type) > 0) {
    nameCounter[type]++;
  } else {
    nameCounter[type] = 1;
  }
  name_ = name + " " + QString::number(nameCounter[type]);
}

void OutlineGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) {
  QGraphicsItem::mousePressEvent(mouseEvent);
}

void OutlineGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent*mouseEvent) {
  qDebug() << "Enter " << name_;
  hoverGraphicsItem_->show();
}

void OutlineGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent*mouseEvent) {
  qDebug() << "Leave " << name_;
  hoverGraphicsItem_->hide();
}

QPen OutlineGraphicsItem::GetHoverPen() {
  QPen pen(QColor::fromRgb(0x66, 0xB2, 0xFF));
  pen.setWidth(kHoverPenWidth_);
  return pen;
}

QVariant OutlineGraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value) {
  return QGraphicsItem::itemChange(change, value);
}

void OutlineGraphicsItem::PaintBoundingRect(QPainter *painter) const {
  QPen pen(QColor::fromRgb(0xFF, 0x00, 0x00));
  pen.setWidth(1);
  painter->setPen(pen);
  painter->drawRect(boundingRect());
}
