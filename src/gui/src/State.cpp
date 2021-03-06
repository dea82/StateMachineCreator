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

#include <QCursor>
#include <QFont>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QTextDocument>

#include "TextGraphicsItem.hpp"

class QString;
class QStyleOptionGraphicsItem;
class QWidget;

namespace statemachinecreator::gui {

State::State(const int w, const int h)
    : OutlineGraphicsItem(OutlineGraphicsItem::ItemType::kState, "State"),
      stateName_(name_),
      stateBorder_(QRect(-w / 2, -h / 2, w, h)),
      stateNameText_{new TextGraphicsItem{name_, this, QFont{"Verdana", 14, QFont::Bold}}},
      outline_pen_() {
  outline_pen_.setWidth(kStateBorderWidth_);
  updateStateNamePos();
  setCursor(Qt::SizeAllCursor);
  //resizer_ = nullptr;//new statemachinecreator::gui::GraphicsItemResizingHandler<State>(this);
}

bool State::sceneEventFilter(QGraphicsItem* watched, QEvent* event) {
  // Propagate mouse move event from state heading text item to state item. This enables moving of both objects even
  // with mouse pointer above state heading test item.
  if ((watched == stateNameText_) && (event->type() == QEvent::GraphicsSceneMouseMove)) {
    if (stateNameText_->textInteractionFlags() == Qt::NoTextInteraction) {
      mouseMoveEvent(dynamic_cast<QGraphicsSceneMouseEvent*>(event));
      return true;
    }
  }
  return false;
}

QRectF State::boundingRect() const {
  return shape().boundingRect();
}

void State::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/) {
  painter->setRenderHint(QPainter::Antialiasing);
  painter->setPen(outline_pen_);
  QPainterPath painterPath;
  painterPath.addRoundedRect(stateBorder_, kRadius_, kRadius_);
  painter->drawPath(painterPath);
  painter->drawLine(QPointF(-stateBorder_.width() / 2,
                            -stateBorder_.height() / 2 + outline_pen_.widthF() / 2
                                + stateNameText_->document()->size().height()),
                    QPointF(stateBorder_.width() / 2,
                            -stateBorder_.height() / 2 + outline_pen_.widthF() / 2
                                + stateNameText_->document()->size().height()));
}

QPainterPath State::shape() const {
  QPainterPath painterPath;
  painterPath.addRoundedRect(stateBorder_ + (QMarginsF() + outline_pen_.widthF() / 2.0F),
                             kRadius_ + outline_pen_.widthF() / 2, kRadius_ + outline_pen_.widthF() / 2);
  return painterPath;
}

void State::updateStateNamePos() const {
  stateNameText_->setPos(-stateNameText_->document()->size().width() / 2,
                         -(stateBorder_.height() - outline_pen_.widthF() / 2) / 2);
}

QVariant State::itemChange(GraphicsItemChange change, const QVariant& value) {
  if (change == QGraphicsItem::ItemSceneHasChanged) {
    // Event listener not possible to add until state is added to scene.
    stateNameText_->installSceneEventFilter(this);
  }
  if (change == QGraphicsItem::ItemSelectedHasChanged) {

  }
  return QGraphicsItem::itemChange(change, value);
}

}  // namespace statemachinecreator::gui
