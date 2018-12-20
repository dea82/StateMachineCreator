#pragma once

#include "i_state_fwd.h"

namespace statemachinecreator::model {

class IElementVisitor {
 public:
  virtual ~IElementVisitor() = default;
  virtual void Visit(IState*) = 0;

};
}