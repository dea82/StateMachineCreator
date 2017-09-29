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

#include <QGraphicsTextItem>
#include <QRect>
#include <QString>
#include <forward_list>
#include <memory>

#include "OutlineGraphicsItem.hpp"

class QPainter;
class QRectF;
class QStyleOptionGraphicsItem;
class QVariant;
class QWidget;
class ResizeHandle;
class StateNameTextItem;

class State : public OutlineGraphicsItem {
 public:
  explicit State(const int w = kDefaultWidth_, const int h = kDefaultHeight_);

  QRectF boundingRect() const override;

  QPainterPath shape() const override;

  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = Q_NULLPTR) override;

  QString getName() const {
    return name_;
  }

  QRectF getStateBorder() {
    return stateBorder_;
  }
  void updateStateNamePos() const;

 private:
  QString stateName_;
  static constexpr int kDefaultWidth_ { 100 };
  static constexpr int kDefaultHeight_ { 60 };
  static constexpr int kRadius_ { 10 };
  static constexpr int kTextPadding_ { 1 };
  static constexpr int kStateBorderWidth_ { 2 };
  QRectF stateBorder_;
  StateNameTextItem * stateNameText_;
  QPen outline_pen_;
};


class StateNameTextItem : public QGraphicsTextItem {
  Q_OBJECT
 public:
  StateNameTextItem(const QString &text, State *parent);
 public slots:
  void updateGeometry() {
    parent_->updateStateNamePos();
  }
 private:
  State * parent_;
  static constexpr int kStateNameTextSize_ { 16 };
};
#endif  // CREATOR_STATE_HPP_
