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

#include "ExclusiveCheckableToolBar.hpp"

namespace statemachinecreator::gui {

ExclusiveCheckableToolBar::ExclusiveCheckableToolBar(QWidget* parent)
    : tool_bar_(std::make_unique<QToolBar>(parent)),
      action_group_(std::make_unique<QActionGroup>(this)),
      current_checked_action_(
          nullptr) {
  tool_bar_->setMovable(false);
  tool_bar_->setFloatable(false);
  QObject::connect(action_group_.get(), &QActionGroup::triggered, this, &ExclusiveCheckableToolBar::ActionTriggered);
}

void ExclusiveCheckableToolBar::AddAction(QAction* action) noexcept {
  // TODO: Remove this and create a InsertAction subclass which is created by appropriate factory pattern.
  action->setCheckable(true);
  tool_bar_->addAction(action);
  action_group_->addAction(action);
}

void ExclusiveCheckableToolBar::ActionTriggered(QAction* action) noexcept {
  if (action == current_checked_action_) {
    UncheckCurrentAction();
  } else {
    current_checked_action_ = action;
  }
}

void ExclusiveCheckableToolBar::UncheckCurrentAction() noexcept {
  if (current_checked_action_) {
    current_checked_action_->setChecked(false);
    current_checked_action_ = nullptr;
  }
}

}  // namespace statemachinecreator::gui
