/*
 *   Copyright (C) 2012 Vladislav Sitalo <root@stvad.org>
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

#ifndef SPHINXCONTROL_H
#define SPHINXCONTROL_H

#define DEFAULT_SAMPRATE 16000
#include "recognitioncontrol.h"

class SphinxControl : public RecognitionControl
{
Q_OBJECT
public:
  SphinxControl(const QString &username, QObject *parent = 0);

  bool initializeRecognition(const QString& modelPath);

protected:
  RecognitionConfiguration* setupConfig();
  void emitError(const QString& error);
  QString modelName;
};

#endif // SPHINXCONTROL_H
