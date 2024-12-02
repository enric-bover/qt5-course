#include "personmodel.h"
#include <QDebug>

PersonModel::PersonModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    persons.append(new Person("Jamie Lannister", "red", 33, 4));
    persons.append(new Person("Enric Bover", "yellow", 27, 3));
    persons.append(new Person("Paula Salas", "blue", 27, 2));
    persons.append(new Person("Judit Tomas", "green", 34, 1));

}

PersonModel::~PersonModel()
{
    qDeleteAll(persons);
}


int PersonModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return persons.size();
}

QVariant PersonModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= persons.count())
        return QVariant();

    Person * person = persons[index.row()];

    if(role == Qt::DisplayRole || role == Qt::EditRole){

        if(index.column() == 0){
            return person->names();
        }
        if(index.column() == 1){
            return person->age();
        }
        if(index.column() == 2){
            return person->favoriteColor();
        }
        if(index.column() == 3){
            return person->socialScore();
        }

    }

    if(role == Qt::ToolTipRole){
        return person->names();
    }

    if(role == NamesRole){
        return person->names();
    }

    if(role == FavoriteColorRole){
        return person->favoriteColor();
    }

    if(role == AgeRole){
        return person->age();
    }

    if(role == SocialScoreRole){
        return person->socialScore();
    }

    return QVariant();
}


bool PersonModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid()){
        return false;
    }

    Person * person = persons[index.row()];
    bool somethingChanged = false;

    switch(role){
    case Qt::EditRole:
    {
        if(index.column() == 0){
            //names
            if(person->names() != value.toString()){

                person->setNames(value.toString());
                somethingChanged = true;
            }
        }
        if(index.column() == 1){
            //age
            if(person->age() != value.toInt()){
                person->setAge(value.toInt());
                somethingChanged = true;
            }
        }
        if(index.column() == 2){
            //favorite color
            if(person->favoriteColor() != value.toString()){
                person->setFavoriteColor(value.toString());
                somethingChanged = true;
            }
        }

        if(index.column() == 3){
            //scoail score
            if(person->socialScore() != value.toInt()){
                person->setSocialScore(value.toInt());
                somethingChanged = true;
            }
        }


    }
    break;



    case NamesRole:
    {
        qDebug() << "Names role changing names, index" << index.row();
        if(person->names() != value.toString()){
            person->setNames(value.toString());
            somethingChanged = true;
        }
    }
    break;

    case AgeRole:
    {
        qDebug() << "Age role changing age, index" << index.row();
        if(person->age() != value.toInt()){
            person->setAge(value.toInt());
            somethingChanged = true;
        }
    }
    break;


    case FavoriteColorRole:
    {
        qDebug() << "Favorite Color role changing Favorite Color, index" << index.row();
        if(person->favoriteColor() != value.toString()){
            person->setFavoriteColor(value.toString());
            somethingChanged = true;
        }
    }
    break;
    }



    if(somethingChanged){
        emit dataChanged(index,index);
        return true;
    }

    return false;
}

QVariant PersonModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole){
        return QVariant();
    }
    if(orientation == Qt::Horizontal){
        switch(section){
        case 0:
            return QString("Names");
            break;

        case 1:
            return QString("Age");
            break;

        case 2:
            return QString("Favtorite Color");
            break;

        case 3:
            return QString("Social Score");
            break;
        }



    }

    return QString("Person %1").arg(section);
}

Qt::ItemFlags PersonModel::flags(const QModelIndex &index) const
{
    if(!index.isValid()){
        return QAbstractItemModel::flags(index);
    }
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void PersonModel::addPerson(Person *person)
{
    //    const int index = persons.size();
    //    beginInsertRows(QModelIndex(), index, index);
    //    persons.append(person);
    //    endInsertRows();

    insertRows(persons.size(), 1);
    setData(index(persons.size()-1, 0),person->names(), Qt::EditRole);
    setData(index(persons.size()-1, 1),person->age(), Qt::EditRole);
    setData(index(persons.size()-1, 2),person->favoriteColor(), Qt::EditRole);

}

void PersonModel::addPerson()
{
    Person * person = new Person("Added Person", "yellowgreen", 45, 4, this);
    addPerson(person);
}

void PersonModel::addPerson(const QString &names, const int &age, const int &socialScore)
{
    Person * person = new Person(names, "yellowgreen", age, socialScore);
    addPerson(person);

}

void PersonModel::removePerson(QModelIndex index)
{
    //    beginRemoveRows(QModelIndex(), index.row(), index.row());
    //    persons.removeAt(index.row());
    //    endRemoveRows();

    removeRows(index.row(), 1);

}


bool PersonModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), row, row+count-1);

    for(int i = 0; i < count; i++){
        persons.insert(row,new Person());
    }
    endInsertRows();

    return true;
}

bool PersonModel::removeRows(int row, int count, const QModelIndex &parent)
{

    beginRemoveRows(QModelIndex(), row, row+count-1);

    for(int i = 0; i < count; i++){
        persons.removeAt(row);
    }
    endRemoveRows();

    return true;
}


QHash<int, QByteArray> PersonModel::roleNames() const
{
    QHash<int,QByteArray> roles;

    roles[NamesRole] = "names";
    roles[FavoriteColorRole] = "favoritecolor";
    roles[AgeRole] = "age";
    roles[SocialScoreRole] = "socialscore";

    return roles;

}


int PersonModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4; //
}


bool PersonModel::hasChildren(const QModelIndex &parent) const
{
    if(parent.column() == 0)
        return false;

    return true;
}
