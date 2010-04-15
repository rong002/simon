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


#ifndef SIMON_SOUNDCLIENT_H_BAC60251BE6A419EA1236280815A2AAD
#define SIMON_SOUNDCLIENT_H_BAC60251BE6A419EA1236280815A2AAD

#include <QtGlobal>
#include "simonsound_export.h"

class QByteArray;

class SIMONSOUND_EXPORT SoundClient {

public:
	enum SoundClientFlags
	{
		None=0,
		Exclusive=1 // if set this client demands exclusive use of the in/output device
			    // (all other clients have to be suspended)
	};

	SoundClient(SoundClientFlags options=None);
	virtual ~SoundClient();

	virtual void resume() {}
	virtual void suspend() {}

private:
	SoundClientFlags m_options;

public:
	bool isExclusive()
	{ return m_options & Exclusive; }
};

#endif


