//
// Created by Andreas Laghamn on 2017-10-09.
//

#include "GraphicsItemResizingHandler.hpp"

namespace statemachinecreator {
namespace gui {

//template <class T>
GraphicsItemResizingHandler::GraphicsItemResizingHandler(QGraphicsItem* parent) : QGraphicsItem(parent) {
  parent->installSceneEventFilter(this);
}

}
}