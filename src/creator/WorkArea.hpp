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

#ifndef CREATOR_WORKAREA_HPP_
#define CREATOR_WORKAREA_HPP_

#include <QAction>
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class WorkArea : public QGraphicsScene {
Q_OBJECT

 public:
  // TODO: This class should not own this enumeration
  enum class Element {
    kState,
    kEntryPoint
  };
  enum class InsertPhase {
    kNotStarted,
    kNotInserted,
    kTemporaryInserted
  };
  explicit WorkArea(QObject *parent = 0);
  void StartInsertMode(Element element) {
    insertMode_ = {element, InsertPhase::kNotInserted};};
  void AbortInsertMode();

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
  enum class InsertModeType {
    kNoInsert,
    kState,
    kEntryPoint
  };
  enum class InsertModePhase {
    kNotInserted,
    kMoving
  };
  struct InsertMode {
    Element element;
    InsertPhase phase;
  };
  InsertModeType insertModeType_;
  InsertModePhase insertModePhase_;
  std::unique_ptr<QGraphicsItem> temporaryInsertElement_;
  //QGraphicsItem *temporaryInsertElement_;
  InsertMode insertMode_;
};

#endif  // CREATOR_WORKAREA_HPP_
