#include "algosqltablemodel.h"
#include <QDebug>
#include <QSqlError>

AlgoSqlTableModel::AlgoSqlTableModel(QObject* parent,QSqlDatabase db):QSqlTableModel(parent,db)
{

}

QVariant AlgoSqlTableModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= rowCount())
        {
            return QString("");
        }
        if(role < Qt::UserRole)
        {
            return QSqlTableModel::data(index, role);
        }
        else
        {

        return QSqlTableModel::data(this->index(index.row(), role - Qt::UserRole - 1), Qt::DisplayRole);

                    }

}

bool AlgoSqlTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    QSqlTableModel::setData(index,value,role);
}

bool AlgoSqlTableModel::insertRow(int row, const QModelIndex &parent)
{
    QSqlTableModel::insertRow(row,parent);
}

void AlgoSqlTableModel::generateRoleNames()
{
    roles.clear();

        int nbCols = this->columnCount();

        for (int i = 0; i < nbCols; i++)
        {
            roles[Qt::UserRole + i + 1] = QVariant(this->headerData(i, Qt::Horizontal).toString()).toByteArray();
        }

}

void AlgoSqlTableModel::setSort(int column, Qt::SortOrder order)
{
    QSqlTableModel::setSort(column,order);
}

void AlgoSqlTableModel::setFilter(const QString &filter)
{

    QSqlTableModel::setFilter(filter);
}

bool AlgoSqlTableModel::submitAll()
{
    QSqlDatabase db=this->database();
    if (!db.isOpen())
    {
            qDebug()<<"DB's not open";

            db.open();

    }
    if(QSqlTableModel::submitAll())
        return true;
    else
    {
        qDebug() << "Database Write Error" <<"The database reported an error: " \
                 << this->lastError().text();
        return false;

    }

}

bool AlgoSqlTableModel::commit()
{
    if(QSqlTableModel::database().commit())
        return true;
    else
    {
        qDebug() << "Database Write Error" <<"The database reported an error: " \
                 << this->lastError().text();
        return false;
    }
}

bool AlgoSqlTableModel::removeRow(int row, const QModelIndex &parent)
{
    QSqlTableModel::removeRow(row,parent);
}


