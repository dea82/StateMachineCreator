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
#include <memory>

#include <gtest/gtest.h>

#include <QAction>
#include <QtTest>

#include "exclusive_checkable_tool_bar.h"
#include "factory.h"

using namespace ::testing;

namespace statemachinecreator::gui::test {

 struct TestExclusiveToolBar : public Test {
  TestExclusiveToolBar() : toolbar{nullptr},
                           actions{factory::CreateInsertAction(QIcon(), "action0", &toolbar),
                                    factory::CreateInsertAction(QIcon(), "action1", &toolbar)} {
    toolbar.addActions(actions);
  }

  static std::tuple<bool, QWidget*> getWidgetForAction(QAction* action, const char* widget_type) {
    for (const auto action_widget : action->associatedWidgets()) {
      if (!strncmp(action_widget->metaObject()->className(), widget_type, strlen(widget_type))) {
        return {true, action_widget};
      }
    }
    return {false, nullptr};
  }

  static void pressActionButton(QAction* action) {
    auto[match, tool_bar_button_widget] = getWidgetForAction(action, widget_type_for_action);
    ASSERT_TRUE(match);
    QTest::mouseClick(tool_bar_button_widget, Qt::LeftButton);
  }

  ExclusiveCheckableToolBar toolbar;
  QList<QAction*> actions;
  static constexpr const char* widget_type_for_action{"QToolButton"};
};

TEST_F(TestExclusiveToolBar, NoButtonCheckedWhenConstructed) {
  EXPECT_FALSE(actions[0]->isChecked());
  EXPECT_FALSE(actions[1]->isChecked());
}

TEST_F(TestExclusiveToolBar, ActionIsCheckedWhenPressingButton) {
  pressActionButton(actions[0]);
  EXPECT_TRUE(actions[0]->isChecked());
}

TEST_F(TestExclusiveToolBar, UncheckCurrentActionInterfaceWithActiveAction) {
  pressActionButton(actions[0]);
  toolbar.UncheckCurrentAction();
  EXPECT_FALSE(actions[0]->isChecked());
}

TEST_F(TestExclusiveToolBar, UncheckCurrentActionInterfaceWithoutActiveAction) {
  toolbar.UncheckCurrentAction();
  EXPECT_FALSE(actions[0]->isChecked());
  EXPECT_FALSE(actions[1]->isChecked());
}

TEST_F(TestExclusiveToolBar, ActionIsUncheckedWhenPressingOtherButton) {
  pressActionButton(actions[0]);
  pressActionButton(actions[1]);
  EXPECT_FALSE(actions[0]->isChecked());
}

TEST_F(TestExclusiveToolBar, ActionIsUncheckedWhenPressingActiveButton) {
  pressActionButton(actions[0]);
  pressActionButton(actions[0]);
  EXPECT_FALSE(actions[0]->isChecked());
}

TEST_F(TestExclusiveToolBar, ActionIsSwitchedWhenPressingOtherButton) {
  pressActionButton(actions[0]);
  pressActionButton(actions[1]);
  EXPECT_TRUE(actions[1]->isChecked());
}

}  // namespace statemachinecreator::gui::test
