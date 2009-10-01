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


#ifndef SIMON_GRAMMARVIEW_H_9DC3821C61394228AED5ECE6953DF69A
#define SIMON_GRAMMARVIEW_H_9DC3821C61394228AED5ECE6953DF69A

#include "simonmodelmanagementui_export.h"
#include <speechgui/inlinewidget.h>

/**
	@author Peter Grasch <bedahr@gmx.net>
*/
class GrammarViewPrivate;

class SIMONMODELMANAGEMENTUI_EXPORT GrammarView : public InlineWidget
{
Q_OBJECT
private:
	GrammarViewPrivate *d;


public:
    GrammarView(QWidget* parent=0);
    ~GrammarView();

};

#endif
