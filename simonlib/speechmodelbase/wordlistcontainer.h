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


#ifndef SIMON_WORDLISTCONTAINER_H_7BA7469E84264F738AE104386B969130
#define SIMON_WORDLISTCONTAINER_H_7BA7469E84264F738AE104386B969130

#include "speechmodelbase_export.h"

#include <QByteArray>

class SPEECHMODELBASE_EXPORT WordListContainer
{
	private:
		QByteArray m_simpleVocab;
		QByteArray m_activeVocab;
		QByteArray m_activeLexicon;

	public:
		WordListContainer(const QByteArray& simpleVocab,
				const QByteArray& activeVocab, const QByteArray& activeLexicon);
			       
		~WordListContainer();
		
		QByteArray simpleVocab() { return m_simpleVocab; }
		QByteArray activeVocab() { return m_activeVocab; }
		QByteArray activeLexicon() { return m_activeLexicon; }
		
};

#endif
