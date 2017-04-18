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

#include "WorkArea.hpp"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <memory>

#include "State.hpp"

WorkArea::WorkArea(QObject *parent)
    : QGraphicsScene(parent),
      insertMode_ { Element::kEntryPoint, InsertPhase::kNotInserted } {
}

// TODO: Move to View?
void WorkArea::AbortInsertMode() {
  if (insertMode_.phase == InsertPhase::kTemporaryInserted) {
    // Cleanup temporary inserted object
    removeItem(items().first());
  }
  insertMode_.phase = InsertPhase::kNotStarted;
}

void WorkArea::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if (insertMode_.phase != InsertPhase::kNotStarted) {
    if (insertMode_.phase == InsertPhase::kNotInserted) {
      if (insertMode_.element == Element::kEntryPoint) {
        qDebug() << "Insert entry point";
        // TODO: Replace with entry point
        addItem(new State("foo", mouseEvent->scenePos().rx(), mouseEvent->scenePos().ry(), 20, 20));
        insertMode_.phase = InsertPhase::kTemporaryInserted;
      } else if (insertMode_.phase == InsertPhase::kNotInserted) {
        qDebug() << "Insert new state";
        addItem(new State("foo", mouseEvent->scenePos().rx(), mouseEvent->scenePos().ry(), 20, 20));
        insertMode_.phase = InsertPhase::kTemporaryInserted;
      }
    }
    items().first()->setPos(mouseEvent->scenePos());
    qDebug() << "Moving entry point " << ": x: " << items().first()->pos().rx() << " y: "
             << items().first()->pos().ry();
  }

  for (auto &view : views()) {
    if (view->viewport()->hasMouseTracking()) {
      qDebug() << "With mouse tracking.";
    } else {
      qDebug() << "Without mouse tracking.";
    }
  }
  QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void WorkArea::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  qDebug() << "WorkArea clicked";
  insertMode_.phase = InsertPhase::kNotStarted;
  if (insertMode_.phase != InsertPhase::kNotStarted) {
//    insertMode_.phase = InsertPhase::kNotStarted;
//    currentAction_->setChecked(false);
//    currentAction_ = nullptr;
  }
  QGraphicsScene::mousePressEvent(mouseEvent);
}
