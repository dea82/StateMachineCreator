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

#ifndef GUI_TEXTGRAPHICSITEM_HPP_
#define GUI_TEXTGRAPHICSITEM_HPP_

#include <QGraphicsTextItem>

class State;
class QFont;

class TextGraphicsItem : public QGraphicsTextItem {
Q_OBJECT
 public:
  TextGraphicsItem(const QString &text, State *parent, QFont&& font);
 public slots:
  void UpdateGeometry() const;
 protected:
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *evt) override;
  QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;
 private:
  void SetTextInteraction(bool enable_text_interaction);
  State * parent_;
  void DisableTextInteraction();
  void EnableTextInteraction();
};

#endif  // GUI_TEXTGRAPHICSITEM_HPP_
