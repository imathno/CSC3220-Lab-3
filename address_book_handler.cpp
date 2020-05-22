#include "address_book_handler.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>

address_book_handler::address_book_handler(QObject *parent) : QAbstractTableModel(parent)
{

}

int address_book_handler::rowCount(const QModelIndex &parent) const
{
    return filteredIndex.size();
}

int address_book_handler::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant address_book_handler::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0:
                return contacts.at(filteredIndex[index.row()]).firstName;
            case 1:
                return contacts.at(filteredIndex[index.row()]).lastName;
            case 2:
                return contacts.at(filteredIndex[index.row()]).number;
        }
    }
    return QVariant();
}

void address_book_handler::openFile(QString filePath)
{
    QFile file(filePath);
        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", file.errorString());
            return;
        }

        QTextStream in(&file);

        contacts.clear();

        for(int i = 0; !in.atEnd(); i++) {
            QString line = in.readLine();
            QStringList fields = line.split(",");

            if (i == 0) continue;

            contacts.push_back(Contact{fields[0], fields[1], fields[7]});

            filteredIndex.push_back(i);
        }

        file.close();

        emit layoutChanged();
}


QString address_book_handler::getPhoneNumber(int index)
{
    return contacts.at(filteredIndex[index]).number;
}

void address_book_handler::setFilterString(QString fStr)
{
    filteredIndex.clear();

    for (size_t i = 0; i < contacts.size(); i++) {
        if (contacts[i].number.startsWith(fStr)) {
            filteredIndex.push_back(i);
        }
    }
    emit layoutChanged();
}
