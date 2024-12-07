#include "person.h"
#include <QDebug>

Person::Person(QString names, QString proffession, Person *parent)
{

    this->names = names;
    this->proffession = proffession;
    this->parent = parent;
}

Person::~Person()
{
    qDeleteAll(children);
}

void Person::appendChild(Person *childParam)
{
    children.append(childParam);
}

Person *Person::child(int row)
{
    return children.value(row);
}

int Person::childCount() const
{
    return children.count();
}

QVariant Person::data(int column) const
{
    if(column == 0)
        return names;
    if(column == 1)
        return proffession;
    return QVariant();
}

int Person::row() const
{
    if(parent){
        parent->children.indexOf(const_cast<Person*>(this));
    }

    return 0;
}

Person *Person::parentPerson()
{
    return parent;
}

void Person::showInfo()
{
    qDebug() << "Person : " << names << " " << proffession << "(" << childCount() << " children)";

    foreach(Person * child, children){
        child->showInfo();
    }
}
