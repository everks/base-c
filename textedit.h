#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QCompleter>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QObject>



class LineNumberArea;

class TextEdit :public QPlainTextEdit
{
    Q_OBJECT

public:
    TextEdit(QWidget *parent=0);
    ~TextEdit();

    void setCompleter(QCompleter *c);
    QCompleter *completer() const;

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

    bool getHasAnnotation() const;
    void setHasAnnotation(bool value);

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void focusInEvent(QFocusEvent *e)override;

    void resizeEvent(QResizeEvent *event)override;

private slots:
    void insertCompletion(const QString &completion);

    void updateLineNumberAreaWidth(int newBlockCount);
    //void highlightCurrentLine();
    void UpdateLineNumberArea(const QRect &, int);
private:
    QString textUnderCursor()const;
private:
    QCompleter *c;

    QWidget *lineNumberArea;

    bool hasAnnotation;

};

class LineNumberArea:public QWidget
{
public:
    LineNumberArea(TextEdit *textEdit)
        :QWidget(textEdit)
    {
        this->textEdit=textEdit;
    }

    QSize sizeHint() const override{
        return QSize(textEdit->lineNumberAreaWidth(),0);
    }

protected:
    void paintEvent(QPaintEvent *event)override{
        textEdit->lineNumberAreaPaintEvent(event);
    }

private:
    TextEdit *textEdit;
};

#endif // TEXTEDIT_H
