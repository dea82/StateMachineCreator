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

#include "WorkArea.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
  setWindowTitle(tr("State Machine Creator"));

  auto screenGeometry = QApplication::desktop()->screenGeometry();
  resize(screenGeometry.width() * 0.6, screenGeometry.height() * 0.6);
  // Initialize status bar
  statusBar_ = new QStatusBar(this);
  setStatusBar(statusBar_);

  // Initialize tool bar
  insertToolBar_ = new InsertElementToolBar(this);
  insertToolBar_->AddAction(QIcon(":/icons/entrypoint_black.svg"), tr("Entry Point"),
                            InsertElementToolBar::Elements::kEntryPoint);
  insertToolBar_->AddAction(QIcon(":/icons/state_black.svg"), tr("State"), InsertElementToolBar::Elements::kState);

  addToolBar(Qt::LeftToolBarArea, insertToolBar_);
  addToolBar(Qt::TopToolBarArea, new QToolBar(this));

  graphicsView_ = new WorkAreaView(this);
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

  //
  connect(insertToolBar_, &InsertElementToolBar::Triggered, this, &MainWindow::ActionPressed);
  connect(graphicsView_, &WorkAreaView::Clicked, insertToolBar_, &InsertElementToolBar::UncheckCurrentAction);
}

MainWindow::~MainWindow() {
}

void MainWindow::ActionPressed(InsertElementToolBar::Elements element, bool checked) {
  if (checked) {
    qDebug() << "Checked";
  } else {
    qDebug() << "Unchecked";
  }
  if (element == InsertElementToolBar::Elements::kEntryPoint) {
    qDebug() << "EntryPoint";
  }
}
