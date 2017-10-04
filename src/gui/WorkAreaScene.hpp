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

#ifndef CREATOR_WORKAREASCENE_HPP_
#define CREATOR_WORKAREASCENE_HPP_

#include <QGraphicsScene>
#include <QString>

#include "OutlineGraphicsItem.hpp"

class QGraphicsItem;
class QGraphicsSceneMouseEvent;
template <typename T> class QList;

class WorkAreaScene : public QGraphicsScene {
Q_OBJECT

 public:
  explicit WorkAreaScene(QObject *parent);
  void StartInsertMode(const OutlineGraphicsItem::ItemType& element);
  void EndInsertMode();
  void AbortInsertMode();
  void DeselectAllElements() const;

 signals:
  void InsertModeEnded();

 protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

 private:
  QGraphicsItem* FocusElement(const QList<QGraphicsItem *>& items) const;
  struct InsertMode {
    enum class State {
      kNotActive,
      kReadyToBeCreated,
      kMoving
    } state;
    OutlineGraphicsItem::ItemType element;
    InsertMode(State insert_state, OutlineGraphicsItem::ItemType element_type);
  };
  InsertMode insertMode_;
  QGraphicsItem* focusElement_;
  // TODO: Change to QGraphicsItem when a painter toolbox is in place
  OutlineGraphicsItem* temporaryInsertItem_;
};

#endif  // CREATOR_WORKAREASCENE_HPP_
