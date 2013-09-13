#include "tablemodel.h"

TableModel::TableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_headers << "Row 1";
    m_headers << "Row 2";
    m_headers << "Row 3";
    m_headers << "Row 4";
    m_headers << "Row 5";
    m_headers << "Row 6";
    m_headers << "Row 7";
    m_headers << "Row 8";
    m_headers << "Row 9";
    m_headers << "Row 10";

    m_column1 << "Col1 1";
    m_column1 << "Col1 2";
    m_column1 << "Col1 3";
    m_column1 << "Col1 4";
    m_column1 << "Col1 5";
    m_column1 << "Col1 6";
    m_column1 << "Col1 7";
    m_column1 << "Col1 8";
    m_column1 << "Col1 9";
    m_column1 << "Col1 10";

    m_column2 << "Col2 1";
    m_column2 << "Col2 2";
    m_column2 << "Col2 3";
    m_column2 << "Col2 4";
    m_column2 << "Col2 5";
    m_column2 << "Col2 6";
    m_column2 << "Col2 7";
    m_column2 << "Col2 8";
    m_column2 << "Col2 9";
    m_column2 << "Col2 10";

    m_column3 << "Col3 1";
    m_column3 << "Col3 2";
    m_column3 << "Col3 3";
    m_column3 << "Col3 4";
    m_column3 << "Col3 5";
    m_column3 << "Col3 6";
    m_column3 << "Col3 7";
    m_column3 << "Col3 8";
    m_column3 << "Col3 9";
    m_column3 << "Col3 10";

    m_column4 << "Col4 1";
    m_column4 << "Col4 2";
    m_column4 << "Col4 3";
    m_column4 << "Col4 4";
    m_column4 << "Col4 5";
    m_column4 << "Col4 6";
    m_column4 << "Col4 7";
    m_column4 << "Col4 8";
    m_column4 << "Col4 9";
    m_column4 << "Col4 10";

    m_column5 << "Col4 1";
    m_column5 << "Col4 2";
    m_column5 << "Col4 3";
    m_column5 << "Col4 4";
    m_column5 << "Col4 5";
    m_column5 << "Col4 6";
    m_column5 << "Col4 7";
    m_column5 << "Col4 8";
    m_column5 << "Col4 9";
    m_column5 << "Col4 10";
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return 10;
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(index.row() >= 0 && index.row() < 10)
        {
            switch(index.column())
            {
            case 0:
                return m_column1[index.row()];
            case 1:
                return m_column2[index.row()];
            case 2:
                return m_column3[index.row()];
            case 3:
                return m_column4[index.row()];
            case 4:
                return m_column5[index.row()];
            }
        }
    }
    return(QVariant());
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch(section)
            {
            case 0:
                return("Column 1");
                break;
            case 1:
                return("Column 2");
                break;
            case 2:
                return("Column 3");
                break;
            case 3:
                return("Column 4");
                break;
            case 4:
                return("Column 5");
                break;
            }
        }
        else
        {
            if(section >=0 && section < 10)
            {
                return m_headers[section];
            }
        }
    }

    return(QVariant());
}
