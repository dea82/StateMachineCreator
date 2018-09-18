#include <gtest/gtest.h>

#include "model/Factory.hpp"
#include "model/IState.hpp"

namespace statemachinecreator::model {
struct TestState : public ::testing::Test {
  TestState() : state_(factory::createState("initial")) {}
  std::shared_ptr<IState> state_;

};

TEST_F(TestState, constructor_name) {
  EXPECT_EQ(state_->name(), "initial");
}

TEST_F(TestState, clone) {
  IState* clone_state = state_->clone();
  EXPECT_EQ(clone_state->name(), "initial");
}

TEST_F(TestState, set_name) {
  EXPECT_EQ(state_->name(), "initial");
  state_->name("change");
  EXPECT_EQ(state_->name(), "change");
}
}  // namespace statemachinecreator::model