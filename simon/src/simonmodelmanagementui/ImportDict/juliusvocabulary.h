/*
 *   Copyright (C) 2010 Peter Grasch <peter.grasch@bedahr.org>
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

#ifndef SIMON_JULIUSVOCABULARY_H_D697D184A43A4F81A3139128ACDB541E
#define SIMON_JULIUSVOCABULARY_H_D697D184A43A4F81A3139128ACDB541E

#include "dict.h"

class JuliusVocabulary : public Dict
{
  Q_OBJECT
    signals:
  void loaded();

  public:
    explicit JuliusVocabulary(QObject* parent=0);
    void load(QString path, QString encodingName);

    ~JuliusVocabulary();

};
#endif
