#include "textedit.h"

#include <QKeyEvent>
#include <QAbstractItemView>
#include <QAbstractItemModel>
#include <QScrollBar>
#include <QtWidgets>

TextEdit::TextEdit(QWidget *parent)
    :QPlainTextEdit(parent),c(0)
{
    hasAnnotation=true;

    lineNumberArea=new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(UpdateLineNumberArea(QRect,int)));
    //connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);
    //highlightCurrentLine();

}

TextEdit::~TextEdit()
{

}

int TextEdit::lineNumberAreaWidth()
{
    int digits=1;
    int max=qMax(1,blockCount());
    while(max>=10){
        max/=10;
        ++digits;
    }

    int space=3+fontMetrics().width(QLatin1Char('9'))*digits;

    return space;
}

void TextEdit::updateLineNumberAreaWidth(int)
{
    setViewportMargins(lineNumberAreaWidth(),0,0,0);
}

void TextEdit::UpdateLineNumberArea(const QRect &rect, int dy)
{
    if(dy)
        lineNumberArea->scroll(0,dy);
    else
        lineNumberArea->update(0,rect.y(),lineNumberArea->width(),rect.height());

    if(rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);

}

void TextEdit::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr=contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(),cr.top(),lineNumberAreaWidth(),cr.height()));
}

//void TextEdit::highlightCurrentLine()
//{
//    QList<QTextEdit::ExtraSelection> extraSelections;

//    if(!isReadOnly()){
//        QTextEdit::ExtraSelection selection;

//        QColor lineColor=QColor(Qt::yellow).lighter(160);

//        selection.format.setBackground(lineColor);
//        selection.format.setProperty(QTextFormat::FullWidthSelection,true);
//        selection.cursor=textCursor();
//        selection.cursor.clearSelection();
//        extraSelections.append(selection);
//    }

//    setExtraSelections(extraSelections);
//}

void TextEdit::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

//![extraAreaPaintEvent_0]

//![extraAreaPaintEvent_1]
    QTextBlock block=firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
//![extraAreaPaintEvent_1]

//![extraAreaPaintEvent_2]
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void TextEdit::setCompleter(QCompleter *completer)
{
    if(c)
        QObject::disconnect(c,0,this,0);

    c=completer;

    if(!c)
      return;

    c->setWidget(this);
    c->setCompletionMode(QCompleter::PopupCompletion);
    c->setCaseSensitivity(Qt::CaseInsensitive);
    QObject::connect(c,SIGNAL(activated(QString)),
                     this,SLOT(insertCompletion(QString)));
}

QCompleter *TextEdit::completer() const{
    return c;
}

void TextEdit::insertCompletion(const QString &completion){
    if(c->widget()!=this)
        return;
    QTextCursor tc=textCursor();
    int extra=completion.length()-c->completionPrefix().length();
    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion.right(extra));
    setTextCursor(tc);
}

QString TextEdit::textUnderCursor()const{
    QTextCursor tc=textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}

bool TextEdit::getHasAnnotation() const
{
    return hasAnnotation;
}

void TextEdit::setHasAnnotation(bool value)
{
    hasAnnotation = value;
}

void TextEdit::focusInEvent(QFocusEvent *e){
    if(c)
        c->setWidget(this);
    QPlainTextEdit::focusInEvent(e);
}

void TextEdit::keyPressEvent(QKeyEvent *e){
    if(c && c->popup()->isVisible()){
        switch(e->key()){
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Escape:
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
            e->ignore();
            return;
        default:
            break;
        }
    }

    bool isShortcut=(e->modifiers()&Qt::ControlModifier)&&e->key()==Qt::Key_E;
    if(!c||!isShortcut){
        QPlainTextEdit::keyPressEvent(e);
    }

    const bool ctrlOrShift=e->modifiers()&(Qt::ControlModifier|Qt::ShiftModifier);
    if(!c||(ctrlOrShift&&e->text().isEmpty()))
        return;

    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-=");
    bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();

    if (!isShortcut && (hasModifier || e->text().isEmpty()|| completionPrefix.length() < 3
                      || eow.contains(e->text().right(1)))) {
        c->popup()->hide();
        return;
    }

    if (completionPrefix != c->completionPrefix()) {
        c->setCompletionPrefix(completionPrefix);
        c->popup()->setCurrentIndex(c->completionModel()->index(0, 0));
    }
    QRect cr = cursorRect();
    cr.setWidth(c->popup()->sizeHintForColumn(0)
                + c->popup()->verticalScrollBar()->sizeHint().width());
    c->complete(cr); // popup it up!
}

