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

#include <memory>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "State.hpp"

WorkArea::WorkArea(QObject *parent) :
		QGraphicsScene(parent), insertModeType_(
				InsertModeType::kNoInsert), insertModePhase_(
				InsertModePhase::kNotInserted), temporaryInsertElement_(nullptr) {
}

void WorkArea::AbortInsertMode() {
	insertMode_.phase = InsertPhase::kNotStarted;
	// Cleanup temporary inserted object
	if (temporaryInsertElement_ != nullptr) {
		removeItem(temporaryInsertElement_.get());
		temporaryInsertElement_.reset();
		temporaryInsertElement_ = nullptr;
	}
}

void WorkArea::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
	if (insertMode_.phase != InsertPhase::kNotStarted) {
		if (insertMode_.element == Element::kEntryPoint) {
			if (insertMode_.phase == InsertPhase::kNotInserted) {
				qDebug() << "Insert entry point";
				// TODO: Replace with entry point
				temporaryInsertElement_.reset(new State("foo",
						mouseEvent->scenePos().rx(),
						mouseEvent->scenePos().ry(), 20, 20));
				addItem(temporaryInsertElement_.get());
				insertMode_.phase = InsertPhase::kTemporaryInserted;
			}
			temporaryInsertElement_->setPos(mouseEvent->scenePos());
			qDebug() << "Moving entry point " << ": x: "
					<< temporaryInsertElement_->pos().rx() << " y: "
					<< temporaryInsertElement_->pos().ry();
		} else if (insertMode_.element == Element::kState) {
			if (insertMode_.phase == InsertPhase::kNotInserted) {
				qDebug() << "Insert new state";
				temporaryInsertElement_.reset(new State("foo",
						mouseEvent->scenePos().rx(),
						mouseEvent->scenePos().ry(), 20, 20));
				addItem(temporaryInsertElement_.get());
				insertMode_.phase = InsertPhase::kTemporaryInserted;
			}
			temporaryInsertElement_->setPos(mouseEvent->scenePos());
			qDebug() << "Moving state " << ": x: "
					<< temporaryInsertElement_->pos().rx() << " y: "
					<< temporaryInsertElement_->pos().ry();
		} else {
			qDebug() << "Exception can occur if ending up here!";
		}
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
