#ifndef PERSONMODEL_H
#define PERSONMODEL_H

#include <QAbstractItemModel>
#include "person.h"

class PersonModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit PersonModel(QObject *parent = nullptr);
    ~PersonModel() override;

signals:

private:

    void readFile();
    Person * rootPerson;

    QStringList getNamesAndProfession(QString txtString);


    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
};

#endif // PERSONMODEL_H
