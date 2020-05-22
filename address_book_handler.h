#ifndef ADDRESS_BOOK_HANDLER_H
#define ADDRESS_BOOK_HANDLER_H

#include <QAbstractTableModel>

class address_book_handler : public QAbstractTableModel
{
public:
    address_book_handler(QObject *parent);

    // QAbstractItemModel interface
public:
    struct Contact {
        QString firstName;
        QString lastName;
        QString number;
    };

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void openFile(QString);
    QString getPhoneNumber(int index);
    void setFilterString(QString fStr);
private:
    std::vector<Contact> contacts;
    std::vector<int> filteredIndex;
};

#endif // ADDRESS_BOOK_HANDLER_H
