/*
The MIT License (MIT)
Copyright (c) 2018-12-06 Andreas
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

#include <memory>

#include <gtest/gtest.h>

#include "model/factory.h"
#include "model/i_state.h"
#include "element_graphics_item_builder.h"

using namespace ::testing;

namespace statemachinecreator::gui::test {

struct TestElementGraphicsItemBuilder : public Test {
  TestElementGraphicsItemBuilder() : state{model::factory::CreateState("default")}, builder{} {}
  model::IStateUP state;
  ElementGraphicsItemBuilder builder;
};

TEST_F(TestElementGraphicsItemBuilder, StateGraphicsItemReturned) {
  auto state_graphics_item = builder.Build(state.get());
  EXPECT_NE(state_graphics_item, nullptr);
}

}