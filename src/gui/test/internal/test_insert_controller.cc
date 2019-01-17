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

#include <gmock/gmock.h>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPointF>
#include <QGraphicsItem>

#include "model/factory.h"
#include "model/i_state.h"
#include "insert_controller.h"
#include "test-helpers/qt/printers.h"
#include "test-helpers/qt/mouse_events.h"

using namespace ::testing;

namespace statemachinecreator::gui::test {

struct TestInsertController : Test {
  TestInsertController() :
      observed_scene{},
      graphics_view{&observed_scene},
      insert_controller{std::make_unique<InsertController>(&observed_scene)} {
    graphics_view.viewport()->setMouseTracking(true);
  }
  QGraphicsScene observed_scene;
  QGraphicsView graphics_view;
  std::unique_ptr<IInsertController> insert_controller;
};

struct InsertStateHasBeenPressed : TestInsertController {
  InsertStateHasBeenPressed() {
    insert_controller->StartInsert(model::factory::CreateState("Name"));
  }
};

TEST_F(TestInsertController, DefaultInsertStatus) {
  EXPECT_THAT(insert_controller->IsInserting(), Eq(false));
}

TEST_F(InsertStateHasBeenPressed, StartInsert) {
  EXPECT_THAT(insert_controller->IsInserting(), Eq(true));
}

TEST_F(InsertStateHasBeenPressed, NoElementCreated) {
  EXPECT_THAT(observed_scene.items().size(), Eq(0));
}

TEST_F(InsertStateHasBeenPressed, OneTemporaryElementCreated) {
  testhelpers::qt::MouseMoveToScenePos(&graphics_view, {80, 80});
  EXPECT_THAT(observed_scene.items().size(), Eq(1));
}

TEST_F(InsertStateHasBeenPressed, TemporaryElementCreatedAtCorrectPosition) {
  testhelpers::qt::MouseMoveToScenePos(&graphics_view, {80, 80});
  EXPECT_THAT(observed_scene.items()[0]->scenePos(), Eq(QPointF(80.0, 80.0)));
}

TEST_F(InsertStateHasBeenPressed, OnlyOneTemporaryElementIsCreatedWhenMovingMouse) {
  testhelpers::qt::MouseMoveToScenePos(&graphics_view, {80, 80});
  testhelpers::qt::MouseMoveToScenePos(&graphics_view, {20, 20});
  EXPECT_THAT(observed_scene.items().size(), Eq(1));
}

TEST_F(InsertStateHasBeenPressed, TemporaryElementCreatedFollowsMouse) {
  testhelpers::qt::MouseMoveToScenePos(&graphics_view, {80, 80});
  testhelpers::qt::MouseMoveToScenePos(&graphics_view, {20, 20});
  EXPECT_THAT(observed_scene.items()[0]->scenePos(), Eq(QPointF(20.0, 20.0)));
}

TEST_F(InsertStateHasBeenPressed, TemporaryElementCreatedStopsFollowingMouseWhenClicking) {
  testhelpers::qt::MouseMoveToScenePos(&graphics_view, {80, 80});
  testhelpers::qt::MouseClickAndReleaseScenePos(&graphics_view, {80, 80});
  testhelpers::qt::MouseMoveToScenePos(&graphics_view, {20, 20});
  EXPECT_THAT(observed_scene.items()[0]->scenePos(), Eq(QPointF(80.0, 80.0)));
}

TEST_F(InsertStateHasBeenPressed, TemporaryElementInsertAborted) {
  testhelpers::qt::MouseMoveToScenePos(&graphics_view, {80, 80});
  insert_controller->AbortInsert();
  EXPECT_THAT(observed_scene.items().size(), Eq(0));
}

TEST_F(InsertStateHasBeenPressed, AbortIsPossibleWithoutTemporaryElement) {
  insert_controller->AbortInsert();
  EXPECT_THAT(observed_scene.items().size(), Eq(0));
}

}