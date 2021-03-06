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
#include "PeerModel.h"
#include <QFileIconProvider>
#include <QJsonArray>
#include <util/human_size.h>
#include <librevault/Secret.h>
#include "../gui/FolderProperties.h"

PeerModel::PeerModel(QWidget* parent) :
		QAbstractListModel() {}

PeerModel::~PeerModel() {}

int PeerModel::rowCount(const QModelIndex &parent) const {
	return folder_state_json_["peers"].toArray().size();
}
int PeerModel::columnCount(const QModelIndex &parent) const {
	return (int)Column::COLUMN_COUNT;
}
QVariant PeerModel::data(const QModelIndex &index, int role) const {
	auto column = (Column)index.column();

	auto peer_object = folder_state_json_["peers"].toArray().at(index.row()).toObject();

	if(role == Qt::DisplayRole) {
		switch(column) {
			case Column::CLIENT_NAME: return peer_object["client_name"].toString();
			case Column::ENDPOINT: return peer_object["endpoint"].toString();
			case Column::USER_AGENT: return peer_object["user_agent"].toString();
			case Column::DOWN_SPEED: return human_bandwidth(peer_object["down_bandwidth"].toDouble());
			case Column::UP_SPEED: return human_bandwidth(peer_object["up_bandwidth"].toDouble());
			case Column::DOWN_BYTES: return human_size(peer_object["down_bytes"].toDouble());
			case Column::UP_BYTES: return human_size(peer_object["up_bytes"].toDouble());

			default: return QVariant();
		}
	}

	return QVariant();
}

QVariant PeerModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if(orientation == Qt::Horizontal) {
		if(role == Qt::DisplayRole) {
			switch((Column)section) {
				case Column::CLIENT_NAME: return tr("Name");
				case Column::ENDPOINT: return tr("Address");
				case Column::USER_AGENT: return tr("Client");
				case Column::DOWN_SPEED: return tr("Down speed");
				case Column::UP_SPEED: return tr("Up speed");
				case Column::DOWN_BYTES: return tr("Downloaded");
				case Column::UP_BYTES: return tr("Uploaded");
				default: return QVariant();
			}
		}
	}
	return QVariant();
}

void PeerModel::update(const QJsonObject& control_json, const QJsonObject& folder_config_json, const QJsonObject& folder_state_json) {
	control_json_ = control_json;
	folder_config_json_ = folder_config_json;
	folder_state_json_ = folder_state_json;

	emit dataChanged(createIndex(0,0), createIndex(rowCount(), columnCount()));
	emit layoutChanged();
}
