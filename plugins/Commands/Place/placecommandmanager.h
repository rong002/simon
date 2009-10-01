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


#ifndef SIMON_PLACECOMMANDMANAGER_H_13E3BA6102F247948BED6157FD9FFDA8
#define SIMON_PLACECOMMANDMANAGER_H_13E3BA6102F247948BED6157FD9FFDA8

#include <commandpluginbase/commandmanager.h>

class XMLPlaceCommand;
class CreateCommandWidget;
/**
 *	@class PlaceCommandManager
 *	@brief Manager for the place-commands
 *
 *	@version 0.1
 *	@date 20.05.2008
 *	@author Peter Grasch
 */
class PlaceCommandManager : public CommandManager{
Q_OBJECT
private:
	XMLPlaceCommand* xmlPlaceCommand;
public:
	const QString name() const;
	const KIcon icon() const;
	bool load();
	bool save();
	bool addCommand(Command *command);

	bool deSerializeCommands(const QDomElement& elem, Scenario *parent);

	CreateCommandWidget* getCreateCommandWidget(QWidget *parent);

    /**
    * @brief Constructor
    * 
    *	@author Peter Grasch
    */
    PlaceCommandManager(QObject *parent, const QVariantList& args);

    
    ~PlaceCommandManager();

};

#endif
