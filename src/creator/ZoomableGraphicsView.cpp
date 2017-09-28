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

#include "ZoomableGraphicsView.hpp"

#include <QGestureEvent>
#include <QPinchGesture>
#include <QWheelEvent>

ZoomableGraphicsView::ZoomableGraphicsView(QGraphicsScene* defaultScene, QWidget* parent)
    : QGraphicsView(defaultScene, parent) {
  grabGesture(Qt::PinchGesture);
}

void ZoomableGraphicsView::wheelEvent(QWheelEvent* event) {
  // To inhibit Mac touchpad from zooming when panning up/down
  if (event->source() == Qt::MouseEventNotSynthesized) {
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    // Scrolling in y direction corresponds to zooming
    const int zoom_angle = event->angleDelta().y();
    if (zoom_angle > 0) {
      scale(kZoomFactor_, kZoomFactor_);
    } else if (zoom_angle < 0) {
      scale(1 / kZoomFactor_, 1 / kZoomFactor_);
    }
  }
  event->accept();
}

bool ZoomableGraphicsView::event(QEvent* event) {
  if (event->type() == QEvent::Gesture) {
    return gestureEvent(static_cast<QGestureEvent*>(event));
  }
  return QGraphicsView::event(event);
}

bool ZoomableGraphicsView::gestureEvent(QGestureEvent* event) {
  if (QGesture *pinch = event->gesture(Qt::PinchGesture)) {
    pinchTriggered(static_cast<QPinchGesture *>(pinch));
  }
  return true;
}

void ZoomableGraphicsView::pinchTriggered(QPinchGesture* pinch) {
  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  scale(pinch->scaleFactor(), pinch->scaleFactor());
}