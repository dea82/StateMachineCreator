#pragma once

#include "model/ielement_visitor_fwd.h"

namespace statemachinecreator::model {

class IElement {
 public:
  virtual ~IElement() = default;
  virtual void Accept(IElementVisitor * element_visitor) = 0;
};

}