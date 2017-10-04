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

#include "InsertElementToolBar.hpp"

class QIcon;
class QString;
class QWidget;

InsertElementToolBar::InsertElementToolBar(QWidget* parent)
    : QToolBar(parent),
      actionGroup_(new QActionGroup(this)),
      currentCheckedAction_(nullptr) {
  setMovable(false);
  setFloatable(false);
  connect(actionGroup_, &QActionGroup::triggered, this, &InsertElementToolBar::ActionTriggered);
}

void InsertElementToolBar::AddAction(const QIcon& icon, const QString& text,
                                     const OutlineGraphicsItem::ItemType& element) {
  auto action = new QAction(icon, text, actionGroup_);
  action->setCheckable(true);
  action->setData(QVariant::fromValue(element));
  this->addAction(action);
}

void InsertElementToolBar::UncheckCurrentAction() {
  if (currentCheckedAction_) {
    currentCheckedAction_->setChecked(false);
    currentCheckedAction_ = nullptr;
  }
}

void InsertElementToolBar::ActionTriggered(QAction* action) {
  if (action == currentCheckedAction_) {
    UncheckCurrentAction();
  } else {
    currentCheckedAction_ = action;
  }
  const auto& data = action->data();
  if (data.canConvert<OutlineGraphicsItem::ItemType>()) {
    emit Triggered(action->data().value<OutlineGraphicsItem::ItemType>(), action->isChecked());
  } else {
    // TODO: Error output - not possible to convert QVariant to expected data.
  }
}
