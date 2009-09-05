/*
 *   Copyright (C) 2009 Mario Strametz <strmam06@htl-kaindorf.ac.at>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2,
 *   or (at your option) any later version, as published by the Free
 *   Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "keyboardset.h"
#include <QString>
#include <QList>


KeyboardSet::KeyboardSet(QString name)
	: setName(name)
{
}


KeyboardSet::KeyboardSet(QString name, QList<KeyboardTab *>* tList)
	: tabList(*tList),
	setName(name)
{
}

void KeyboardSet::addTab(KeyboardTab* t)
{
	tabList.append(t);
}

void KeyboardSet::delTab(int index)
{
	tabList.removeAt(index);
}

void KeyboardSet::tabLeft(int index)
{	
	tabList.insert((index-1),tabList.takeAt(index));
}

void KeyboardSet::tabRight(int index)
{
	tabList.insert((index+1),tabList.takeAt(index));
}

QString KeyboardSet::getSetName()
{
	return setName;
}

QList<KeyboardTab *>* KeyboardSet::getTabList()
{
	return &tabList;
}