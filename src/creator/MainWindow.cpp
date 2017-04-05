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

#include "MainWindow.hpp"

#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QGraphicsView>
#include <QActionGroup>

#include "WorkArea.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      currentAction_(nullptr) {
  setWindowTitle(tr("State Machine Creator"));

  auto screenGeometry = QApplication::desktop()->screenGeometry();
  resize(screenGeometry.width() * 0.6, screenGeometry.height() * 0.6);
  // Initialize status bar
  statusBar_ = new QStatusBar(this);
  setStatusBar(statusBar_);

  // Initialize tool bar
  insertToolBar_ = new QToolBar(this);
  insertToolBar_->setMovable(false);

  addToolBar(Qt::LeftToolBarArea, insertToolBar_);
  addToolBar(Qt::TopToolBarArea, new QToolBar(this));

  QActionGroup *insertActions = new QActionGroup(this);

  // Initialize actions
  insertEntryPointAction_ = new QAction(QIcon(":/icons/entrypoint_black.svg"), "Entry Point", insertActions);
  insertEntryPointAction_->setCheckable(true);

  insertStateAction_ = new QAction(QIcon(":/icons/state_black.svg"), "State", insertActions);
  insertStateAction_->setCheckable(true);

  insertToolBar_->addActions(insertActions->actions());

  graphicsView_ = new QGraphicsView(this);
  scene_ = new WorkArea(this);
  scene_->addText("Hello, world!");
  graphicsView_->setScene(scene_);
  graphicsView_->viewport()->installEventFilter(this);
  setCentralWidget(graphicsView_);
  show();

  graphicsView_->viewport()->setMouseTracking(false);
  int h = graphicsView_->size().height();
  qDebug() << "GraphicsView height: " << h;
  int w = graphicsView_->size().width();
  qDebug() << "GraphicsView width: " << w;
  graphicsView_->setSceneRect(QRect(-w / 2, -h / 2, w, h));
  connect(insertActions, &QActionGroup::triggered, this, &MainWindow::InsertActionPressed);
}

MainWindow::~MainWindow() {
}

void MainWindow::InsertActionPressed(QAction *action) {
  if (action == currentAction_) {
    action->setChecked(false);
    graphicsView_->viewport()->setMouseTracking(false);
    currentAction_ = nullptr;
    scene_->AbortInsertMode();
  } else {
    if (currentAction_ != nullptr) {
      // Switched active action. Abort action first to cleanup temporary elements
      scene_->AbortInsertMode();
    }
    graphicsView_->viewport()->setMouseTracking(true);
    currentAction_ = action;
    if (action == insertEntryPointAction_) {
      scene_->StartInsertMode(WorkArea::Element::kEntryPoint);
    } else if (action == insertStateAction_) {
      scene_->StartInsertMode(WorkArea::Element::kState);
    }
  }
}
