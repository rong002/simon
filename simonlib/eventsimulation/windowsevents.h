/*
 *   Copyright (C) 2008 Peter Grasch <peter.grasch@bedahr.org>
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

#ifndef SIMON_WINDOWSEVENTS_H_648808A9BE984CC98FF8681C9BF5D4F9
#define SIMON_WINDOWSEVENTS_H_648808A9BE984CC98FF8681C9BF5D4F9

#include "pcevents.h"
#include "pressmode.h"
#include "clickmode.h"
#include <QString>
#include <windows.h>
#include <QHash>

/**
 *	@class WindowsEvents
 *	@brief The WinAPI Event Backend
 *
 *	Implements CoreEvents
 *
 *	@version 0.1
 *	@date 4.03.2007
 *	@author Phillip Goriup
 */
class WindowsEvents : public PCEvents
{

  private:
    enum MouseButton
    {
      Left=1,
      Right=2,
      Middle=3
    };
    void pressVk(BYTE vK, EventSimulation::PressMode mode);
    void moveMouse(int x, int y);
    void activateMouseButton(MouseButton btn, EventSimulation::PressMode mode);

    void setModifierKeyPrivate(int virtualKey);
    void unsetModifierKeyPrivate(int virtualKey);
    void sendKeyPrivate(unsigned int key /*unicode representation*/, EventSimulation::PressMode mode);
  public:
    WindowsEvents();
    void click(int x, int y, EventSimulation::ClickMode clickMode);
    void dragAndDrop(int xStart, int yStart, int x, int y);
    ~WindowsEvents();

};
#endif
