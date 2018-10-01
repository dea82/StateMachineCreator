/*
The MIT License (MIT)
Copyright (c) 2018 andreas
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#pragma once

#include <memory>

#include <QActionGroup>
#include <QObject>
#include <QToolBar>

class QAction;
class QWidget;

namespace statemachinecreator::gui {

class ExclusiveCheckableToolBar : public QObject {
 Q_OBJECT

 public:
  explicit ExclusiveCheckableToolBar(QWidget* parent = nullptr);

  void AddAction(QAction *action) noexcept;

  void UncheckCurrentAction() noexcept;

 private:
  void ActionTriggered(QAction* action) noexcept;

  std::unique_ptr<QToolBar> tool_bar_;
  std::unique_ptr<QActionGroup> action_group_;
  QAction * current_checked_action_;
};

}  // namespace statemachinecreator::gui
