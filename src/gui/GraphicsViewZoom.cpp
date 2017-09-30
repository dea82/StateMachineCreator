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

#include "GraphicsViewZoom.hpp"

#include <QApplication>
#include <qmath.h>
#include <QEvent>
#include <QGestureEvent>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPinchGesture>
#include <QPointF>
#include <QWheelEvent>

namespace statemachinecreator {
namespace gui {

GraphicsViewZoom::GraphicsViewZoom(QGraphicsView* view)
    : QObject(view),
      view_(view),
      modifier_key_(Qt::NoModifier) {
  // Viewport is the painting area in the middle (scrollbars not included) of QGraphicsView
  view->viewport()->installEventFilter(this);
  view->viewport()->setMouseTracking(true);
  view->viewport()->grabGesture(Qt::PinchGesture);
}

void GraphicsViewZoom::SetModifierKey(const Qt::KeyboardModifiers modifiers) {
  modifier_key_ = modifiers;
}

bool GraphicsViewZoom::eventFilter(QObject* /*object*/, QEvent* event) {
  if (event->type() == QEvent::MouseMove) {
    QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
    target_viewport_pos_ = mouse_event->pos();
    target_scene_pos_ = view_->mapToScene(mouse_event->pos());
  } else if (event->type() == QEvent::Wheel) {
    return WheelEvent(static_cast<QWheelEvent*>(event));
  } else if (event->type() == QEvent::Gesture) {
    return GestureEvent(static_cast<QGestureEvent*>(event));
  }
  return false;
}

bool GraphicsViewZoom::WheelEvent(QWheelEvent* event) {
  if ((event->source() == Qt::MouseEventNotSynthesized) && (QApplication::keyboardModifiers() == modifier_key_)
      && (event->orientation() == Qt::Vertical)) {
    double angle = event->angleDelta().y();
    double factor = qPow(kZoomFactorBase_, angle);
    Zoom(factor);
    return true;
  }

  return false;
}

bool GraphicsViewZoom::GestureEvent(QGestureEvent* event) {
  QGesture* pinch = event->gesture(Qt::PinchGesture);
  if (pinch) {
    PinchTriggered(static_cast<QPinchGesture*>(pinch));
  }
  return true;
}

void GraphicsViewZoom::PinchTriggered(QPinchGesture* pinch) {
  if (pinch->changeFlags() & QPinchGesture::ScaleFactorChanged) {
    Zoom(pinch->scaleFactor());
  }
}

void GraphicsViewZoom::Zoom(const qreal factor) {
  view_->scale(factor, factor);
  view_->centerOn(target_scene_pos_);
  QPointF deltaview_port_pos = target_viewport_pos_
      - QPointF(view_->viewport()->width() / 2.0, view_->viewport()->height() / 2.0);
  QPointF viewport_center = view_->mapFromScene(target_scene_pos_) - deltaview_port_pos;
  view_->centerOn(view_->mapToScene(viewport_center.toPoint()));
}
}  // namespace gui
}  // namespace statemachinecreator
