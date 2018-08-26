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

#include "TextGraphicsItem.hpp"

#include <QCursor>
#include <QDebug>
#include <QFont>
#include <QGraphicsSceneMouseEvent>
#include <QTextCursor>
#include <QTextDocument>

#include "State.hpp"

TextGraphicsItem::TextGraphicsItem(const QString &text, State *parent, QFont&& font)
    : QGraphicsTextItem(text, parent),
      parent_(parent) {
  setFont(font);
  setFlags(ItemIsSelectable | ItemIsFocusable);
  setTextInteractionFlags(Qt::NoTextInteraction);
  connect(document(), &QTextDocument::contentsChanged, this, &TextGraphicsItem::UpdateGeometry);
  setCursor(Qt::SizeAllCursor);
}

void TextGraphicsItem::UpdateGeometry() const {
  parent_->updateStateNamePos();
}

void TextGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
  if (textInteractionFlags() == Qt::TextEditorInteraction) {
    QGraphicsTextItem::mouseDoubleClickEvent(event);
    return;
  }
  EnableTextInteraction();

  std::unique_ptr<QGraphicsSceneMouseEvent> click(new QGraphicsSceneMouseEvent(QEvent::GraphicsSceneMousePress));
  click->setButton(event->button());
  click->setPos(event->pos());
  QGraphicsTextItem::mousePressEvent(click.get());
}

QVariant TextGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
  if ((change == QGraphicsItem::ItemSelectedChange) && (textInteractionFlags() != Qt::NoTextInteraction)
      && !value.toBool()) {
    DisableTextInteraction();
  }
  return QGraphicsTextItem::itemChange(change, value);
}

void TextGraphicsItem::DisableTextInteraction() {
  if (textInteractionFlags() == Qt::TextEditorInteraction) {
    setTextInteractionFlags(Qt::NoTextInteraction);
    // Deselect text (else it keeps gray shade):
    QTextCursor cursor = this->textCursor();
    cursor.clearSelection();
    setTextCursor(cursor);
    clearFocus();
    setCursor(Qt::SizeAllCursor);
  }
}
void TextGraphicsItem::EnableTextInteraction() {
  if (textInteractionFlags() == Qt::NoTextInteraction) {
    setTextInteractionFlags(Qt::TextEditorInteraction);
    setFocus(Qt::MouseFocusReason);
    setSelected(true);
    setCursor(Qt::IBeamCursor);
  }
}
