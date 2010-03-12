/*
 *   Copyright (C) 2008 Peter Grasch <grasch@simon-listens.org>
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

#ifndef SIMON_TRAININGSETTINGS_H_752BF8F5F07F41DAB2291EF3D504832E
#define SIMON_TRAININGSETTINGS_H_752BF8F5F07F41DAB2291EF3D504832E

#include "ui_trainingsettings.h"
#include <KCModule>
#include <QVariantList>

/**
	@author Peter Grasch <bedahr@gmx.net>
*/
class TrainingSettings : public KCModule
{
Q_OBJECT
private:
        Ui::TrainingSettingsWidget trainingUi;

public:
	virtual void save();

public:
        TrainingSettings(QWidget* parent, const QVariantList& args=QVariantList());

        ~TrainingSettings();


};

#endif
