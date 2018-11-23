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

#include "gui/Factory.hpp"
#include "Factory.hpp"

#include <QAction>
#include <QDir>

#include "MainWindow.hpp"

// Needs to be declared in global scope
void InitResources() {
  Q_INIT_RESOURCE(icons);
}

namespace statemachinecreator::gui::factory {

void InitResources() {
  ::InitResources();
}

QMainWindow* createMainWindow() {
  auto main_window = new MainWindow();
  main_window->addToolBar(Qt::LeftToolBarArea, CreateInsertToolBar(main_window));
  return main_window;
}

QToolBar* CreateInsertToolBar(QWidget* parent) {
  auto tool_bar = new ExclusiveCheckableToolBar(parent);
  tool_bar->addAction(new QAction("State", tool_bar));
  tool_bar->setFloatable(false);
  return tool_bar;
}

QAction* CreateInsertAction(const QIcon& icon, const QString& text, QObject* parent) {
  auto action = new QAction(icon, text, parent);
  action->setCheckable(true);
  return action;
}

}  // namespace statemachinecreator::gui::factory
