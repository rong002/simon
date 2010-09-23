/*
 *   Copyright (C) 2010 Peter Grasch <grasch@simon-listens.org>
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

#ifndef SIMON_SIMONTTSPRIVATE_H_7A7B9100FF5245329569C1B540119C37
#define SIMON_SIMONTTSPRIVATE_H_7A7B9100FF5245329569C1B540119C37

#include <QList>
#include "simontts.h"

class QString;
class SimonTTSProvider;

/**
 * \class SimonTTSPrivate
 * \author Peter Grasch
 * \since 0.4
 * \brief Provides access to text to speech functionality: Implementation
 */
class SimonTTSPrivate
{
  protected:
    QList<SimonTTSProvider*> providers;
    QString processString(QString text, SimonTTS::TTSFlags flags=SimonTTS::StripHTML);

  public:
    SimonTTSPrivate();
    bool initialize();
    bool uninitialize();
    bool say(const QString& text, SimonTTS::TTSFlags flags=SimonTTS::StripHTML);
    bool interrupt();
   ~SimonTTSPrivate();
};

#endif

