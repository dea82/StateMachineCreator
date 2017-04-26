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
#include <QDebug>
#include <QDesktopWidget>
#include <QGraphicsView>
#include <QIcon>
#include <QPainter>
#include <QRect>
#include <QSize>
#include <QStatusBar>
#include <QToolBar>
#include <QWidget>

#include "InsertElementToolBar.hpp"
#include "WorkAreaScene.hpp"
#include "ZoomableGraphicsView.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
  setWindowTitle(tr("State Machine Creator"));

  auto screenGeometry = QApplication::desktop()->screenGeometry();
  resize(screenGeometry.width() * 0.6, screenGeometry.height() * 0.6);

  setContextMenuPolicy(Qt::NoContextMenu);

  // Initialize status bar
  statusBar_ = new QStatusBar(this);
//  zmq::context_t context(1);
//  zmq::socket_t socket(context, ZMQ_REQ);
//  socket.connect("tcp://localhost:5555");
//  zmq::message_t request(5);
//  memcpy(request.data(), "Hello", 5);
//  socket.send(request);
//  //  Get the reply.
//  zmq::message_t reply;
//  socket.recv(&reply);

  setStatusBar(statusBar_);

  CreateInsertToolBar();

  addToolBar(Qt::TopToolBarArea, new QToolBar(this));

  activeScene_ = new WorkAreaScene(this);

  graphicsView_ = new ZoomableGraphicsView(activeScene_, this);
  graphicsView_->viewport()->installEventFilter(this);
  setCentralWidget(graphicsView_);
  show();

  graphicsView_->viewport()->setMouseTracking(true);
  int h = graphicsView_->size().height();
  qDebug() << "GraphicsView height: " << h;
  int w = graphicsView_->size().width();
  qDebug() << "GraphicsView width: " << w;
  graphicsView_->setRenderHint(QPainter::Antialiasing);
  graphicsView_->setSceneRect(QRect(0, 0, w, h));

  //
  connect(insertToolBar_, &InsertElementToolBar::Triggered, this, &MainWindow::InsertElementButtonPressed);
  connect(activeScene_, &WorkAreaScene::InsertModeEnded, this, &MainWindow::InsertModeEnded);
}

void MainWindow::InsertElementButtonPressed(const OutlineGraphicsItem::ItemType& element, const bool checked) {
  if (checked) {
    activeScene_->StartInsertMode(element);
  } else {
    activeScene_->AbortInsertMode();
  }
}

void MainWindow::InsertModeEnded() {
  insertToolBar_->UncheckCurrentAction();
}

void MainWindow::CreateInsertToolBar() {
  // Initialize tool bar
  insertToolBar_ = new InsertElementToolBar(this);
  insertToolBar_->AddAction(QIcon(":/icons/entrypoint_black.svg"), tr("Entry Point"),
                            OutlineGraphicsItem::ItemType::kEntryPoint);
  insertToolBar_->AddAction(QIcon(":/icons/state_black.svg"), tr("State"), OutlineGraphicsItem::ItemType::kState);

  addToolBar(Qt::LeftToolBarArea, insertToolBar_);
}
