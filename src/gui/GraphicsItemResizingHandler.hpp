//
// Created by Andreas Laghamn on 2017-10-09.
//

#ifndef STATEMACHINECREATOR_GRAPHICSITEMRESIZER_HPP
#define STATEMACHINECREATOR_GRAPHICSITEMRESIZER_HPP

#include <QGraphicsItem>

namespace statemachinecreator {
namespace gui {

/**
 * Make it a template class
 */
//template <class T>
class GraphicsItemResizingHandler : public QGraphicsItem {
 public:
  GraphicsItemResizingHandler(QGraphicsItem* parent);

  void resize() {
   // parent_->foo();
  }
  //virtual void resizeToRect(T* const item, const QRectF &rect) = 0;

 private:
  //QGraphicsItem* parent_;
};
}
}

#endif //STATEMACHINECREATOR_GRAPHICSITEMRESIZER_HPP
