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

#ifndef CREATOR_GRAPHICSVIEWZOOM_HPP_
#define CREATOR_GRAPHICSVIEWZOOM_HPP_

#include <QGraphicsView>
#include <QObject>

class QGestureEvent;
class QPinchGesture;
class QWheelEvent;

namespace statemachinecreator {
namespace gui {

class GraphicsViewZoom : public QObject {
Q_OBJECT
 public:
  explicit GraphicsViewZoom(QGraphicsView* view);
  void SetModifierKey(const Qt::KeyboardModifiers modifiers);

 protected:
  bool eventFilter(QObject* object, QEvent* event) override;

 private:
  bool WheelEvent(QWheelEvent* event);
  bool GestureEvent(QGestureEvent* event);
  void PinchTriggered(QPinchGesture* pinch);
  void Zoom(const qreal factor);

  QGraphicsView* const view_;
  Qt::KeyboardModifiers modifier_key_;
  QPointF target_scene_pos_;
  QPointF target_viewport_pos_;

  static constexpr qreal kZoomFactorBase_ { 1.0015 };
};
}  // namespace gui
}  // namespace statemachinecreator

#endif  //  CREATOR_GRAPHICSVIEWZOOM_HPP_
