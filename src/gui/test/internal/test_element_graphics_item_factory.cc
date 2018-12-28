/*
The MIT License (MIT)
Copyright (c) 2018-12-26 Andreas
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

#include <gmock/gmock.h>

#include <QGraphicsItem>

#include "element_graphics_item_factory.h"

namespace statemachinecreator::gui::factory::test {

using namespace ::testing;

struct TestElementGraphicsItemFactory : public Test {
  TestElementGraphicsItemFactory() : element_graphics_item_factory_{CreateElementGraphicsFactory()} {};

  std::unique_ptr<IElementGraphicsItemFactory> element_graphics_item_factory_;
};

TEST_F(TestElementGraphicsItemFactory, CreateElementGraphicsFactory) {
  EXPECT_THAT(element_graphics_item_factory_, NotNull());
}

TEST_F(TestElementGraphicsItemFactory, CreateStateGraphicsItem) {
  EXPECT_THAT(element_graphics_item_factory_->CreateStateGraphicsItem(nullptr), NotNull());
}

}  // namespace statemachinecreator::gui::factory::test