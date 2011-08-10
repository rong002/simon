/*
 *   Copyright (C) 2011 Peter Grasch <grasch@simon-listens.org>
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

#ifndef SIMON_GRAPHEMETOPHONEME_H_DA7C3A7BA63E42D7A49216FBDDA84C6D
#define SIMON_GRAPHEMETOPHONEME_H_DA7C3A7BA63E42D7A49216FBDDA84C6D

#include "simongraphemetophoneme_export.h"
#include <QObject>

class KProcess;

class SIMONGRAPHEMETOPHONEME_EXPORT GraphemeToPhoneme : public QObject
{
Q_OBJECT

signals:
  void state(const QString& state, int now, int max);
  void success(const QString& path);
  void failed();
  
public:
  enum GraphemeToPhonemeState {
    Idle=0,
    Initial=1,
    RampUp1=2,
    RampUp2=3,
    RampUp3=4,
    RampUp4=5,
    Finished=6,
    Error=6
  };
  
private:
  KProcess *sequitur;
  QString sequiturExe;
  QString error;
  
  GraphemeToPhonemeState m_state;
  
  
private slots:
  void parseErrorLog();
  
  void nextStep();
  
public:
  GraphemeToPhoneme(QObject *parent=0);

  bool createProfile();
  
  /**
   * \return True if the transcription was successful
   * \param transcription The transcription, if true is returned - otherwise an error string
   */
  static bool transcribe(const QString& word, const QString& pathToModel, QString& transcription);
  
  void abort();
  GraphemeToPhonemeState getState();
  QString getError();
};
#endif
