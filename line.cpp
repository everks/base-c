#include "line.h"

#include <QString>





QString Line::getAnnotation() const
{
    return annotation;
}

void Line::setAnnotation(const QString &value)
{
    annotation = value;
}

QString Line::getData() const
{
    return data;
}

void Line::setData(const QString &value)
{
    data = value;
}
Line::Line(QString data, QString annotation)
{
    this->data=data;
    this->annotation=annotation;
    this->next=nullptr;
}
