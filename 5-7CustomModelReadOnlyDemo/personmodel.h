#ifndef PERSONMODEL_H
#define PERSONMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "person.h"

class PersonModel : public QAbstractListModel
{
    Q_OBJECT

    enum PersonRoles{
        NamesRole = Qt::UserRole +1,
        FavoriteColorRole,
        AgeRole
    };

public:
    explicit PersonModel(QObject *parent = nullptr);
    ~PersonModel() override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;


    void addPerson(Person * person);
    void addPerson();
    void addPerson(const QString & names, const int &age);
    void removePerson(QModelIndex index);

signals:


private:
    QList<Person*> persons;


    // QAbstractItemModel interface


    // QAbstractItemModel interface


    // QAbstractItemModel interface
public:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // QAbstractItemModel interface
public:
    QHash<int, QByteArray> roleNames() const override;
};

#endif // PERSONMODEL_H
