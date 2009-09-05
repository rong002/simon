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

#ifndef KEYBOARDTAB_H
#define KEYBOARDTAB_H

#include "keyboardbutton.h"
#include <QList>
#include <QString>

class KeyboardTab
{
	private:
		QList<KeyboardButton *> buttonList;
		QString tabName;
		void addButton(KeyboardButton* b);
		void delButton(int index);
		
		
	public:
		KeyboardTab(QString name, QList<KeyboardButton *>* bList);
		KeyboardTab(QString name);
		QString getTabName();
		QList<KeyboardButton *>* getButtonList();
		void buttonLeft(int index);
		void buttonRight(int index);

};

#endif