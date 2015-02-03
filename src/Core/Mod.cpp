/*
Copyright (C) 2013-2015 by Rafał Soszyński <rsoszynski121 [at] gmail [dot] com>
This file is part of The Chronicles Of Andaria Project.

	The Chronicles of Andaria Project is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	The Chronicles of Andaria Project is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with The Chronicles Of Andaria.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Core/Mod.hpp"

#include "Core/Parsers/BoardParser.hpp"
#include "Core/Parsers/ItemParser.hpp"
#include "Core/Parsers/PrizeParser.hpp"
#include "Core/Parsers/EnemyParser.hpp"
#include "Core/Containers/Bases/ItemBase.hpp"

Mod::Mod()
{
// 	TODO Parsers should be replaced with models

// 	BoardParser boardParser(this);
// 	qDebug() << boardParser.trescBledu << board_.size()
// 	<< "terrains" <<board_.terrains().size();

	ItemParser itemParser(this);
// 	qDebug() << itemParser.trescBledu << "items" << items_.size();

	PrizeParser prizeParser(this);
// 	qDebug() << prizeParser.trescBledu << "prizes" << prizes_.size();

	EnemyParser enemyParser(this);
// 	qDebug() <<enemyParser.trescBledu 	<< "enemies: " << enemies_.size();


// 	QuestParser questParser(this);
// 	qDebug() << questParser.trescBledu 	<< "quests: " << quests_.size();
}

Mod::~Mod()
{
	qDeleteAll(prizes_);
}

bool Mod::unsavedChanges() const
{
	return (itemModel_.isChanged() || enemyModel_.isChanged());
}

bool Mod::load(const QString &path)
{
	if (path.isEmpty())
		return false;

	QFile file(path);
	if (!file.open(QIODevice::ReadOnly))
		return false;

	QDataStream in(&file);

	if (LoadFromTxt) {
		for (auto &item : items_)
			itemModel_.addItemBase(item);

		for (auto &enemy : enemies_)
			enemyModel_.addEnemyBase(enemy);
	}
	else
		in >> itemModel_ >> enemyModel_ >> board_;

		file.close();
	return true;
}

bool Mod::save(const QString &path)
{
	if (path.isEmpty())
		return false;

	QFile file(path);
	if (!file.open(QIODevice::WriteOnly))
		return false;

	QDataStream out(&file);

	out << itemModel_ << enemyModel_ << board_;

	itemModel_.setChanged(false);
	enemyModel_.setChanged(false);

	file.close();
	return true;
}

void Mod::reset()
{
	itemModel_.reset();
	enemyModel_.reset();
}

Board * Mod::board()
{
	return &board_;
}

ItemModel * Mod::itemModel()
{
	return &itemModel_;
}

EnemyModel * Mod::enemyModel()
{
	return &enemyModel_;
}

QuestModel* Mod::questModel()
{
	return &questModel_;
}

const Board & Mod::board() const
{
	return board_;
}

const ItemModel & Mod::itemModel() const
{
	return itemModel_;
}

const EnemyModel & Mod::enemyModel() const
{
	return enemyModel_;
}

const QuestModel& Mod::questModel() const
{
	return questModel_;
}

Coordinates Mod::initialPosition(Race race) const
{
	return board_.initialPosition(race);
}
