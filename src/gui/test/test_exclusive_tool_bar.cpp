// The MIT License (MIT)
//
// Copyright (c) 2018 Andreas L.
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

#include <gtest/gtest.h>

#include <QApplication>
#include <QAction>
#include <QtTest>

#include "ExclusiveCheckableToolBar.hpp"

namespace statemachinecreator::gui::test {

struct TestExclusiveToolBar : public ::testing::Test {
  TestExclusiveToolBar() : toolbar_(std::make_unique<ExclusiveCheckableToolBar>()) {}

  static void SetUpTestCase() {
    int argc = 0;
    application_ = std::make_unique<QApplication>(argc, nullptr);
  }

  static void TearDownTestCase() {
    application_ = nullptr;
  }

  std::tuple<bool, QWidget*> getWidgetForAction(const QAction& action, const char* widget_type) {
    for (const auto action_widget : action.associatedWidgets()) {
      if (!strncmp(action_widget->metaObject()->className(), widget_type, strlen(widget_type))) {
        return {true, action_widget};
      }
    }
    return {false, nullptr};
  }

  void pressActionButton(const QAction& action) {
    auto[match, tool_bar_button_widget] = getWidgetForAction(action, "QToolButton");
    ASSERT_TRUE(match);
    QTest::mouseClick(tool_bar_button_widget, Qt::LeftButton);
  }

  static std::unique_ptr<QApplication> application_;

  std::unique_ptr<ExclusiveCheckableToolBar> toolbar_;
};

std::unique_ptr<QApplication> TestExclusiveToolBar::application_ = nullptr;

TEST_F(TestExclusiveToolBar, checkable) {
  QAction action1("action1");
  QAction action2("action2");
  toolbar_->AddAction(&action1);
  toolbar_->AddAction(&action2);
  EXPECT_FALSE(action1.isChecked());
  EXPECT_FALSE(action2.isChecked());
  pressActionButton(action1);
  EXPECT_TRUE(action1.isChecked());
  EXPECT_FALSE(action2.isChecked());
  pressActionButton(action2);
  EXPECT_FALSE(action1.isChecked());
  EXPECT_TRUE(action2.isChecked());
  pressActionButton(action2);
  EXPECT_FALSE(action1.isChecked());
  EXPECT_FALSE(action2.isChecked());
}

}  // namespace statemachinecreator::gui::test
