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

#include <QRect>
#include <QString>
#include <forward_list>
#include <memory>

#include "GraphicsItemResizingHandler.hpp"
#include "OutlineGraphicsItem.hpp"

class QGraphicsSceneMouseEvent;
class QPainter;
class QRectF;
class QStyleOptionGraphicsItem;
class QVariant;
class QWidget;
class ResizeHandle;
class StateNameTextItem;
class TextGraphicsItem;

class State : public OutlineGraphicsItem {
 public:
  explicit State(int w = kDefaultWidth_, int h = kDefaultHeight_);

  QRectF boundingRect() const override;

  QPainterPath shape() const override;

  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

  void updateStateNamePos() const;

 protected:
  bool sceneEventFilter(QGraphicsItem* watched, QEvent* event) override;
  QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

 private:
  QString stateName_;
  static constexpr int kDefaultWidth_{100};
  static constexpr int kDefaultHeight_{60};
  static constexpr int kRadius_{10};
  static constexpr int kStateBorderWidth_{2};
  QRectF stateBorder_;
  TextGraphicsItem* stateNameText_;
  QPen outline_pen_;
  //GraphicsItemResizingHandler* resizer_;
};

#endif  // CREATOR_STATE_HPP_
