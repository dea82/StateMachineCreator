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

#ifndef CREATOR_MAINWINDOW_HPP_
#define CREATOR_MAINWINDOW_HPP_

#include <QMainWindow>
#include <QString>

#include "OutlineGraphicsItem.hpp"

class InsertElementToolBar;
class QGraphicsView;
class QStatusBar;
class QWidget;
class WorkAreaScene;

class MainWindow : public QMainWindow {
Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override = default;

 public slots:
  void InsertElementButtonPressed(const OutlineGraphicsItem::ItemType& element, bool checked);
  void InsertModeEnded();

 private:
  void CreateInsertToolBar();
  InsertElementToolBar* insertToolBar_;
  QStatusBar* statusBar_;
  QGraphicsView* graphicsView_;
  WorkAreaScene* activeScene_;
};

#endif  // CREATOR_MAINWINDOW_HPP_
