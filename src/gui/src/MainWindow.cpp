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
#include <QStatusBar>
#include <QToolBar>
#include <QObject>

#include "InsertElementToolBar.hpp"
#include "WorkAreaScene.hpp"
#include "GraphicsViewZoom.hpp"
#include "ui/ui_mainwindow.h"

namespace statemachinecreator::gui {

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(std::make_unique<Ui::MainWindow>()) {
  ui_->setupUi(this);

  QObject::connect(ui_->actionOpen, &QAction::triggered, this, &MainWindow::loadTriggered);
  QObject::connect(ui_->actionQuit, &QAction::triggered, QApplication::quit);
  QObject::connect(ui_->actionSave, &QAction::triggered, this, &MainWindow::saveTriggered);
}

MainWindow::~MainWindow() = default;

}  // namespace statemachinecreator::gui
