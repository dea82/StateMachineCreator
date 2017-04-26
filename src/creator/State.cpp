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
#include <QFont>
#include <QGraphicsItem>
#include <QMargins>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QSizeF>
#include <QTextDocument>
#include <forward_list>

#include "ResizeHandle.hpp"

class QString;
class QStyleOptionGraphicsItem;
class QWidget;

State::State(const int w, const int h)
    : OutlineGraphicsItem(OutlineGraphicsItem::ItemType::kState, "State"),
      stateName_(name_),
      stateBorder_(QRect(-w / 2, -h / 2, w, h)),
      resizeHandles_(),
      stateNameText_(new StateNameTextItem(name_, this)),
      outline_pen_() {
  outline_pen_.setWidth(kStateBorderWidth_);
}

QRectF State::boundingRect() const {
  return shape().boundingRect();
}

void State::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  painter->setPen(outline_pen_);
  QPainterPath painterPath;
  painterPath.addRoundedRect(stateBorder_, kRadius_, kRadius_);
  painter->drawPath(painterPath);
  painter->drawLine(-stateBorder_.width() / 2, -stateBorder_.height() / 2 + stateNameText_->document()->size().height(),
                    stateBorder_.width() / 2, -stateBorder_.height() / 2 + stateNameText_->document()->size().height());
}

QPainterPath State::shape() const {
  QPainterPath painterPath;
  painterPath.addRoundedRect(stateBorder_.marginsAdded(QMargins() += outline_pen_.widthF() / 2),
                             kRadius_ + outline_pen_.widthF() / 2, kRadius_ + outline_pen_.widthF() / 2);
  return painterPath;
}

QVariant State::itemChange(GraphicsItemChange change, const QVariant &value) {
  qDebug() << "Itemchange: " << change << " value: " << value;
  if (change == QGraphicsItem::ItemSelectedHasChanged && value.canConvert<bool>() && value.toBool()) {
    if (value.toBool()) {
      resizeHandles_.emplace_front(
          std::unique_ptr<ResizeHandle>(new ResizeHandle(this, ResizeHandle::Position::kTopLeft)));
      resizeHandles_.emplace_front(
          std::unique_ptr<ResizeHandle>(new ResizeHandle(this, ResizeHandle::Position::kTopRight)));
      resizeHandles_.emplace_front(
          std::unique_ptr<ResizeHandle>(new ResizeHandle(this, ResizeHandle::Position::kBottomLeft)));
      resizeHandles_.emplace_front(
          std::unique_ptr<ResizeHandle>(new ResizeHandle(this, ResizeHandle::Position::kBottomRight)));
    } else {
      resizeHandles_.clear();
    }
  }
  return OutlineGraphicsItem::itemChange(change, value);
}

void State::updateStateNamePos() const {
  qDebug() << "Update position of State Name position.";
}

StateNameTextItem::StateNameTextItem(const QString & text, State * parent)
    : parent_(parent),
      QGraphicsTextItem(text, static_cast<QGraphicsItem*>(parent)) {
  setTextInteractionFlags(Qt::TextEditorInteraction);
  QFont fixedSizeFont { font() };
  fixedSizeFont.setPointSize(kStateNameTextSize_);
  setFont(fixedSizeFont);
  connect(document(), &QTextDocument::contentsChanged, this, &StateNameTextItem::updateGeometry);
  updateGeometry();
}
