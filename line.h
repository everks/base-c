#ifndef LINE_H
#define LINE_H

#include <QString>



class Line
{
private:
    QString data;
    QString annotation;
    Line* next;
public:
    Line(QString data,QString annotation);
    QString getData() const;
    void setData(const QString &value);
    QString getAnnotation() const;
    void setAnnotation(const QString &value);
};



#endif // LINE_H




