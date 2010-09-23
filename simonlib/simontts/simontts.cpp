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

#include "simontts.h"
#include "simonttsprivate.h"
#include <QString>
#include <KDebug>

SimonTTSPrivate* SimonTTS::d = 0;

/**
 * \brief Singleton method
 * Returns a new instance of SimonTTSPrivate if there isn't already one
 * \return a valid instance of SimonTTSPrivate
 */
SimonTTSPrivate* SimonTTS::getInstance()
{
  if (!d) d = new SimonTTSPrivate();
  return d;
}

/**
 * \brief Will force the sytem to performe the initialization
 *
 * Normally the tts subsystem will be initialized during the first call
 * to \sa say() but this can be done earlier by calling this method
 *
 * Once initialized this will do nothing (and return true)
 *
 * \return Success
 */
bool SimonTTS::initialize()
{
  getInstance()->initialize();
}


/**
 * \brief Says the given text using the text to speech engine
 *
 * Will call \sa initialize() if the system has not yet been initialized
 *
 * \param text The text to say
 * \return True if successful
 */
bool SimonTTS::say(const QString& text, SimonTTS::TTSFlags flags)
{
  getInstance()->say(text, flags);
}


/**
 * \brief Interrupts the current spoken text
 * \return true if successfully sent interrupt request or if service seems unavailable
 */
bool SimonTTS::interrupt()
{
  getInstance()->interrupt();
}


/**
 * \brief Uninitializes the TTS system. 
 * \note It's safe to call this anytime because the system will be re-initialized automatically if needed 
 *
 * Call \sa interrupt() if you want to stop the TTS immediatly
 */
bool SimonTTS::uninitialize()
{
  getInstance()->uninitialize();
}
