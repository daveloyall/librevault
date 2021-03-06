/* Copyright (C) 2015-2016 Alexander Shishenko <GamePad64@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include "pch.h"
#include <QAbstractTableModel>
#include <QJsonObject>

class FolderProperties;

class FolderModel : public QAbstractListModel {
Q_OBJECT

public:
	FolderModel(QWidget* parent);
	~FolderModel();

	static const int SecretRole = Qt::UserRole;
	static const int HashRole = Qt::UserRole+1;

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

	FolderProperties* getFolderDialog(const QByteArray& hash) {return properties_dialogs_[hash];}

public slots:
	void handleControlJson(QJsonObject control_json);

private:
	QWidget* parent_widget_;
	QJsonObject state_json_;

	QMap<QByteArray, FolderProperties*> properties_dialogs_;

	enum class Column {
		NAME,
		STATUS,
		PEERS,
		SIZE,

		COLUMN_COUNT
	};
};
