#include "personmodel.h"
#include <QTextStream>
#include <QFile>

PersonModel::PersonModel(QObject *parent)
    : QAbstractItemModel{parent}
{
    QVector<QVariant> rootData;
    rootData << "Names" << "Proffession";
    rootPerson = new Person(rootData);
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

            QVector<QVariant> infoList = getNamesAndProfession(line);

            int diffIndent = currentIdentation - lastIdentation;
            if(diffIndent == 0){
                Person * person = new Person(infoList, lastParent);
                lastParent->appendChild(person);
                lastPerson = person;
            } else if(diffIndent > 0){
                lastParent = lastPerson;
                Person * person = new Person(infoList, lastParent);
                lastParent->appendChild(person);
                lastPerson = person;
            } else{
                int iterations = - diffIndent;
                for(int i = 0; i < iterations; i++){
                    lastParent = lastParent->parentPerson();
                }
                Person * person = new Person(infoList, lastParent);
                lastParent->appendChild(person);
                lastPerson = person;
            }

            lastIdentation = currentIdentation;

        }
        inputFile.close();
    }
}

QVector<QVariant> PersonModel::getNamesAndProfession(QString txtString)
{
    QString cleanedUpStr = txtString.trimmed();
    QStringList split = cleanedUpStr.split("(");
    split[1].chop(1);


    QVector<QVariant> data;
    data << split[0] << split[1];
    return data;
}

Person *PersonModel::getPersonFromIndex(const QModelIndex &index) const
{
    if(index.isValid()){
        Person * person = static_cast<Person*>(index.internalPointer());
        if(person)
            return person;
    }
    return rootPerson;
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
    Q_UNUSED(parent);
    return rootPerson->columnCount();
}

QVariant PersonModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if ((role != Qt::DisplayRole) || (role == Qt::EditRole)){
        Person * person = static_cast<Person * > (index.internalPointer());
        return person->data(index.column());
    }
    return QVariant();

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

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

bool PersonModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role != Qt::EditRole)
        return false;

    Person *person = getPersonFromIndex(index);
    bool result = person->setData(index.column(), value);

    if(result)
        emit dataChanged(index, index,{role});

    return result;
}

bool PersonModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if(role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootPerson->setData(section, value);

    if(result)
        emit headerDataChanged(orientation, section, section);
    return result;

}

bool PersonModel::insertColumns(int position, int columns, const QModelIndex &parent)
{

    bool success;
    beginInsertColumns(parent, position, position + columns - 1);
    success = rootPerson->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool PersonModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;
    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootPerson->removeColumns(position, columns);
    endRemoveColumns();

    if(rootPerson->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool PersonModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    Person * personParent = getPersonFromIndex(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = personParent->insertChildren(position, rows, rootPerson->columnCount());
    endInsertRows();

    return success;

}

bool PersonModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    Person * personParent = getPersonFromIndex(parent);
    bool success;

    beginRemoveRows(parent, position, position + rows - 1);
    success = personParent->removeChildren(position, rows);
    endRemoveRows();

    return success;

}
