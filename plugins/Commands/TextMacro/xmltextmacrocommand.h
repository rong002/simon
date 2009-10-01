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

#ifndef SIMON_XMLTEXTMACROCOMMAND_H_0A4CCBA5B44341FB88A6E37FDEEEC189
#define SIMON_XMLTEXTMACROCOMMAND_H_0A4CCBA5B44341FB88A6E37FDEEEC189
#include <commandpluginbase/command.h>
#include <simonxml/xmldomreader.h>

/**
 *  @class XMLTextMacroCommand
 *  @brief Extends the XMLDomReader class to handle the commands
 *
 *  @version 0.1
 *  @date 20.05.2008
 *  @author Peter Grasch
 */

class XMLTextMacroCommand : public XMLDomReader {
	
public:
	XMLTextMacroCommand(QString path="conf/commands.xml");
	
	bool save(CommandList *list, QString path="conf/commands.xml");
	
	CommandList* load(bool &ok, QString path="");
	
	~XMLTextMacroCommand();
};


#endif
