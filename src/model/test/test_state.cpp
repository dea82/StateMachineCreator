#include <gtest/gtest.h>

#include "model/factory.h"
#include "model/i_state.h"

namespace statemachinecreator::model {
struct TestState : public ::testing::Test {
  TestState() : state(factory::CreateState("initial")) {}
  IStateUP state;
};

TEST_F(TestState, constructor_name) {  // NOLINT(cert-err58-cpp)
  EXPECT_EQ(state->Name(), "initial");
}

TEST_F(TestState, clone) {  // NOLINT(cert-err58-cpp)
  IStateUP clone_state = state->Clone();
  EXPECT_EQ(clone_state->Name(), "initial");
}

TEST_F(TestState, set_name) {  // NOLINT(cert-err58-cpp)
  state->Name("change");
  EXPECT_EQ(state->Name(), "change");
}
}  // namespace statemachinecreator::model
