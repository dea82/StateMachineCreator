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
#include "model/factory.h"
#include "model/i_state.h"
#include "factory.h"

#include <QAction>
#include <QDir>
#include <QGraphicsView>
#include <QDebug>

#include "exclusive_checkable_tool_bar.h"
#include "insert_controller.h"
#include "main_window.hpp"
#include "state_machine_scene.h"
#include "scene_controller.h"

// Needs to be declared in global scope
void InitResources() {
  Q_INIT_RESOURCE(icons);
}

namespace statemachinecreator::gui::factory {

namespace {
ExclusiveCheckableToolBar* CreateInsertToolBar(QWidget* parent);
QActionGroup* CreateInsertActions(IInsertController* insert_controller, QObject* parent);

// Ownership is handled by parent return raw pointer
ExclusiveCheckableToolBar* CreateInsertToolBar(QWidget* parent) {
  auto tool_bar = new statemachinecreator::gui::ExclusiveCheckableToolBar(parent);
  tool_bar->setFloatable(false);
  tool_bar->setMovable(false);
  return tool_bar;
}

QActionGroup* CreateInsertActions(IInsertController* insert_controller, QObject* parent) {
  auto action_group = new QActionGroup(parent);
  auto action = factory::CreateInsertAction(QIcon(":/icons/state_black.svg"), "Insert state", action_group);
  QObject::connect(action, &QAction::triggered, [insert_controller](bool /*triggered*/) {
    insert_controller->StartInsert(statemachinecreator::model::factory::CreateState("Bar"));
  });
  action_group->addAction(action);
  return action_group;
}

}

void InitResources() {
  ::InitResources();
}

QMainWindow* CreateMainWindow() {
  auto main_window = new MainWindow();
  auto graphics_view = new QGraphicsView();
  graphics_view->viewport()->setMouseTracking(true);

  auto state_machine_scene = new StateMachineScene(graphics_view);
  auto scene_controller = new SceneController(state_machine_scene);

  state_machine_scene->Controller(scene_controller);

  graphics_view->setScene(state_machine_scene);
  main_window->setCentralWidget(graphics_view);

  auto toolbar = CreateInsertToolBar(main_window);
  auto insert_controller = new InsertController(state_machine_scene);

  // Cancel action
  auto cancel_action = new QAction("Cancel", main_window);
  cancel_action->setShortcuts(QKeySequence::Cancel);
  main_window->addAction(cancel_action);
  QObject::connect(cancel_action, &QAction::triggered, insert_controller, &InsertController::AbortInsert);


  main_window->addToolBar(Qt::LeftToolBarArea, toolbar);
  toolbar->addActions(CreateInsertActions(insert_controller, toolbar)->actions());
  QObject::connect(insert_controller,
                   &InsertController::InsertFinished,
                   toolbar,
                   &ExclusiveCheckableToolBar::UncheckCurrentAction);


  // Main toolbar
  auto main_tool_bar = new QToolBar(main_window);
  // TODO: This action should be added to menu, button and shortcut key
  auto undo_action = new QAction("Undo", main_window);
  undo_action->setShortcuts(QKeySequence::Undo);
  main_tool_bar->addAction(undo_action);
  main_window->addToolBar(Qt::TopToolBarArea, main_tool_bar);

  QObject::connect(scene_controller, &SceneController::canUndoChanged, undo_action, &QAction::setEnabled);

  return main_window;
}

QAction* CreateInsertAction(const QIcon& icon, const QString& text, QObject* parent) {
  auto action = new QAction(icon, text, parent);
  action->setCheckable(true);
  return action;
}

}  // namespace statemachinecreator::gui::factory
