/* Double Contact
 *
 * Module: Contact book visualization model
 *
 * Copyright 2016 Mikhail Y. Zvyozdochkin aka DarkHobbit <pub@zvyozdochkin.ru>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version. See COPYING file for more details.
 *
 */

#include <QtAlgorithms>
#include <QMessageBox>
#include "contactmodel.h"
#include <QDebug>

// Visible columns headers
QString contactColumnHeaders[ccLast] = {
    QObject::tr("Name 1"),
    QObject::tr("Name 2"),
    QObject::tr("Full name"),
    QObject::tr("Phone"),
    QObject::tr("eMail")
};

ContactModel::ContactModel(QObject *parent, const QString& source) :
    QAbstractTableModel(parent), _source(source), _changed(false)
{
    // Default visible columns
    visibleColumns.clear();
    visibleColumns.push_back(ccFirstName);
    visibleColumns.push_back(ccSecondName);
    visibleColumns.push_back(ccPhone);
    // TODO read visible columns from config
}

ContactModel::~ContactModel()
{
}

QString ContactModel::source()
{
    // TODO may be return short filename, if source is full filepath
    return _source;
}

bool ContactModel::changed()
{
    return _changed;
}

Qt::ItemFlags ContactModel::flags(const QModelIndex &) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

int ContactModel::rowCount(const QModelIndex &) const
{
    return items.count();
}

int ContactModel::columnCount(const QModelIndex &) const
{
    return visibleColumns.count();
}

QVariant ContactModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((role == Qt::DisplayRole) && (orientation==Qt::Horizontal))
        return contactColumnHeaders[visibleColumns[section]];
    else
        return QAbstractItemModel::headerData(section, orientation, role);
}

QVariant ContactModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
          return QVariant();
      if (index.row() >= items.count())
          return QVariant();
    if (role==Qt::DisplayRole) {
        const ContactItem& c = items[index.row()];
        // Detect column
        ContactColumn col = visibleColumns[index.column()];
        switch (col) {
            case ccFirstName:  if (c.names.count()>0) return c.names[0]; else return QVariant();
            case ccSecondName: if (c.names.count()>1) return c.names[1]; else return QVariant();
            case ccFullName: return c.fullName;
            case ccPhone: return c.prefPhone;
            case ccEMail: return c.prefEmail;
            case ccLast: { return QVariant(); } // Boundary case
            default: return QVariant();
        }
    }
    return QVariant();
}

bool ContactModel::save() // false if user cancel
{
    QMessageBox::information(0, "Debug", "Under construction");
    // TODO
    return true;
}

void ContactModel::addRow(const ContactItem& c)
{
    beginInsertRows(QModelIndex(), 0, 0);
    items.push_back(c);
    endInsertRows();
    _changed = true;
}

ContactItem& ContactModel::beginEditRow(QModelIndex& index)
{
    return items[index.row()];
}

void ContactModel::endEditRow(QModelIndex& index)
{
    _changed = true;
    emit dataChanged(index, index);
}

void ContactModel::copyRows(QModelIndexList& indices, ContactModel* target)
{
    foreach(QModelIndex index, indices)
        target->addRow(items[index.row()]);
}

void ContactModel::removeAnyRows(QModelIndexList& indices)
{
    qSort(indices.begin(), indices.end());
    // foreach not usable here - reverse order needed
    beginRemoveRows (QModelIndex(), 0, indices.count()-1);
    for (int i=indices.count()-1; i>=0; i--)
        items.removeAt(indices[i].row());
    endRemoveRows();
    _changed = true;
}

void ContactModel::swapNames(const QModelIndexList& indices)
{
    foreach(QModelIndex index, indices)
        items[index.row()].swapNames();
    emit dataChanged(QModelIndex(), QModelIndex());
    _changed = true;
}

void ContactModel::testList()
{
    ContactItem c;
    Phone ph;
    Email em;
    _source = "Test list";
    beginInsertRows(QModelIndex(), 0, 3);

    // Example with ASCII names and multy-type phone
    c.fullName = "John Doe";
    c.names.clear();
    c.names.push_back("John");
    c.names.push_back("Doe");
    c.phones.clear();
    ph.number = "+1-213-555-1234"; // example from  RFC 2426
    ph.tType = Phone::TelType(Phone::Work | Phone::Pref);
    c.phones.push_back(ph);
    c.emails.clear();
    c.calculateFields();
    items.push_back(c);

    // Example with UTF8 (Russian) names and email
    c.fullName = QString::fromUtf8("Александр Попов");
    c.names.clear();
    c.names.push_back(QString::fromUtf8("Александр"));
    c.names.push_back(QString::fromUtf8("Попов"));
    c.phones.clear();
    ph.number = "+79101234567"; // example for any cellular operator
    ph.tType = Phone::Cell;
    c.phones.push_back(ph);
    c.emails.clear();
    em.address = "alexpopov@spb.ru";
    em.emTypes.push_back("internet");
    c.emails.push_back(em);
    c.calculateFields();
    items.push_back(c);

    // Example with UTF8 (German) names
    c.fullName = QString::fromUtf8("Hans Köster");
    c.names.clear();
    c.names.push_back(QString::fromUtf8("Hans"));
    c.names.push_back(QString::fromUtf8("Köster"));
    c.phones.clear();
    ph.number = "233";
    ph.tType = Phone::Home;
    c.phones.push_back(ph);
    ph.number = "322";
    ph.tType = Phone::Work;
    c.phones.push_back(ph);
    c.emails.clear();
    c.calculateFields();
    items.push_back(c);

    // Example with 4 names and without phones
    c.fullName = QString::fromUtf8("Ernst Theodor Amadeus Hoffmann");
    c.names.
            clear();
    c.names.push_back(QString::fromUtf8("Ernst"));
    c.names.push_back(QString::fromUtf8("Theodor"));
    c.names.push_back(QString::fromUtf8("Amadeus"));
    c.names.push_back(QString::fromUtf8("Hoffmann"));
    c.phones.clear();
    c.emails.clear();
    c.calculateFields();
    items.push_back(c);

    endInsertRows();
}