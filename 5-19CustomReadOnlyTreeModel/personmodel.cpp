#include "personmodel.h"
#include <QTextStream>
#include <QFile>

PersonModel::PersonModel(QObject *parent)
    : QAbstractItemModel{parent}
{
    rootPerson = new Person("Names", "Proffession");
    readFile();
}

PersonModel::~PersonModel()
{
    delete rootPerson;
}

void PersonModel::readFile()
{
    QString filename = ":/data/familytree.txt";
    QFile inputFile(filename);
    if(inputFile.open(QIODevice::ReadOnly)){
        int lastIdentation = 0;

        Person * lastParent = rootPerson;
        Person * lastPerson = nullptr;

        QTextStream in(&inputFile);

        while(!in.atEnd()){
            QString line = in.readLine();
            int currentIdentation = line.count("\t");

            QStringList infoList = getNamesAndProfession(line);

            int diffIndent = currentIdentation - lastIdentation;
            if(diffIndent == 0){
                Person * person = new Person(infoList[0], infoList[1], lastParent);
                lastParent->appendChild(person);
                lastPerson = person;
            } else if(diffIndent > 0){
                lastParent = lastPerson;
                Person * person = new Person(infoList[0], infoList[1], lastParent);
                lastParent->appendChild(person);
                lastPerson = person;
            } else{
                int iterations = - diffIndent;
                for(int i = 0; i < iterations; i++){
                    lastParent = lastParent->parentPerson();
                }
                Person * person = new Person(infoList[0], infoList[1], lastParent);
                lastParent->appendChild(person);
                lastPerson = person;
            }

            lastIdentation = currentIdentation;

        }
        inputFile.close();
    }
}

QStringList PersonModel::getNamesAndProfession(QString txtString)
{
    QString cleanedUpStr = txtString.trimmed();
    QStringList split = cleanedUpStr.split("(");
    split[1].chop(1);

    return split;
}


QModelIndex PersonModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    Person * parentPerson;

    if(!parent.isValid()){
        parentPerson = rootPerson;
    } else{
        parentPerson = static_cast<Person*>(parent.internalPointer());
    }

    Person * childPerson = parentPerson->child(row);
    if(childPerson)
        return createIndex(row,column,childPerson);

    return QModelIndex();
}

QModelIndex PersonModel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
        return QModelIndex();

    Person * childPerson = static_cast<Person*>(child.internalPointer());
    Person * parentPerson = childPerson->parentPerson();
    if(parentPerson == rootPerson)
        return QModelIndex();

    return createIndex(parentPerson->row(),0, parentPerson);
}

int PersonModel::rowCount(const QModelIndex &parent) const
{
    Person * parentPerson;
    if(parent.column() > 0)
        return 0;

    if(!parent.isValid())
        parentPerson = rootPerson;
    else{
        parentPerson = static_cast<Person*>(parent.internalPointer());
    }
    return parentPerson->childCount();
}

int PersonModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant PersonModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    Person * person = static_cast<Person*>(index.internalPointer());
    return person->data(index.column());
}

QVariant PersonModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && (role ==Qt::DisplayRole)){
        return rootPerson->data(section);
    }
    return QVariant();
}

Qt::ItemFlags PersonModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return nullptr;

    return QAbstractItemModel::flags(index);
}
