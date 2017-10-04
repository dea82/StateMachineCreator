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

#include "WorkAreaScene.hpp"

#include <QEvent>
#include <QGraphicsSceneMouseEvent>

#include "EntryPoint.hpp"
#include "State.hpp"
#include "OutlineStroke.hpp"

WorkAreaScene::WorkAreaScene(QObject *parent)
    : QGraphicsScene(parent),
      insertMode_{InsertMode::State::kNotActive, OutlineGraphicsItem::ItemType::kEntryPoint},
      focusElement_{nullptr},
      temporaryInsertItem_{nullptr} {
}

void WorkAreaScene::DeselectAllElements() const {
  for (const auto &item : selectedItems()) {
    item->setSelected(false);
  }
}

void WorkAreaScene::StartInsertMode(const OutlineGraphicsItem::ItemType &element) {
  if (insertMode_.state == InsertMode::State::kMoving) {
    removeItem(temporaryInsertItem_);
  }
  insertMode_.state = InsertMode::State::kReadyToBeCreated;
  insertMode_.element = element;
}

void WorkAreaScene::EndInsertMode() {
  insertMode_.state = InsertMode::State::kNotActive;
}

void WorkAreaScene::AbortInsertMode() {
  if (insertMode_.state == InsertMode::State::kMoving) {
    removeItem(temporaryInsertItem_);
  }
  insertMode_.state = InsertMode::State::kNotActive;
}

void WorkAreaScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if (insertMode_.state == InsertMode::State::kReadyToBeCreated) {
    DeselectAllElements();
    if (insertMode_.element == OutlineGraphicsItem::ItemType::kEntryPoint) {
      temporaryInsertItem_ = new EntryPoint;
    } else if (insertMode_.element == OutlineGraphicsItem::ItemType::kState) {
      temporaryInsertItem_ = new State;
    }
    addItem(temporaryInsertItem_);
    insertMode_.state = InsertMode::State::kMoving;
    new statemachinecreator::gui::OutlineStroke(temporaryInsertItem_->GetHoverPen(), temporaryInsertItem_);
  }
  if (insertMode_.state == InsertMode::State::kMoving) {
    temporaryInsertItem_->setPos(mouseEvent->scenePos());
  }
  QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void WorkAreaScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  // First check if insert mode shall be ended
  if ((insertMode_.state != InsertMode::State::kNotActive) && (mouseEvent->button() == Qt::LeftButton)) {
    EndInsertMode();
    emit InsertModeEnded();
  }
  QGraphicsScene::mousePressEvent(mouseEvent);
}

QGraphicsItem *WorkAreaScene::FocusElement(const QList<QGraphicsItem *> &items) const {
  if (items.isEmpty()) {
    return nullptr;
  }
  QGraphicsItem *focusElement = nullptr;
  for (const auto &item : items) {
    if (!focusElement) {
      focusElement = item;
    } else if ((focusElement->type() == OutlineGraphicsItem::ItemType::kState)
        && (item->type() == OutlineGraphicsItem::ItemType::kEntryPoint)) {
      return item;  // Quick return, highest prio found.
    }
  }
  return focusElement;
}
WorkAreaScene::InsertMode::InsertMode(WorkAreaScene::InsertMode::State insert_state,
                                      OutlineGraphicsItem::ItemType element_type) :
    state(insert_state), element(element_type) {
}
