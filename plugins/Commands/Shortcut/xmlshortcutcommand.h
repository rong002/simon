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


#ifndef SIMON_XMLSHORTCUTCOMMAND_H_23BD0A67B6C044958C228BB928D8BBFB
#define SIMON_XMLSHORTCUTCOMMAND_H_23BD0A67B6C044958C228BB928D8BBFB

#include <simonxml/xmldomreader.h>
#include <commandpluginbase/commandmanager.h>
#include <commandpluginbase/command.h>


/**
 * \class XMLShortcutCommand
 * \brief Reads the shortcuts from the xml file
 * \author Peter Grasch
 * \version 0.1
 * \date 28.8.2007
 */
class XMLShortcutCommand : public XMLDomReader
{
public:
    explicit XMLShortcutCommand(const QString& path="conf/shortcuts.xml", QObject* parent=0);

    CommandList* load(bool &ok, const QString& path="");

    bool save(const CommandList *commands, const QString& path="");

    ~XMLShortcutCommand();

};

#endif
