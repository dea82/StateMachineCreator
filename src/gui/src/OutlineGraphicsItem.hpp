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

#pragma once

#include <QGraphicsRectItem>
#include <QPen>
#include <QString>
#include <map>

class QPainter;

namespace statemachinecreator::gui {

// TODO: Find a better name, this class has no coupling to outline anymore.
class OutlineGraphicsItem : public QGraphicsRectItem {
 public:
  enum ItemType {
    kEntryPoint = UserType + 1,
    kState,
  };

  OutlineGraphicsItem(const ItemType& type, const QString& name);

  QPen GetHoverPen();
  ~OutlineGraphicsItem() override = default;

 protected:
  void PaintBoundingRect(QPainter* painter) const;

  QString name_;
  static constexpr int kHoverPenWidth_{2};
  static std::map<OutlineGraphicsItem::ItemType, int> nameCounter;
};

}  // namespace statemachinecreator::gui

Q_DECLARE_METATYPE(statemachinecreator::gui::OutlineGraphicsItem::ItemType)
