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

#include "soundinputclient.h"
#include "soundprocessor.h"

#ifdef HAVE_LIBSAMPLERATE_H
#include "resamplesoundprocessor.h"
#endif

#include <QByteArray>

/**
 * \brief Constructor
 */
SoundInputClient::SoundInputClient(const SimonSound::DeviceConfiguration& deviceConfiguration, SoundClient::SoundClientPriority priority) :
SoundClient(deviceConfiguration, priority)
{
#ifdef HAVE_LIBSAMPLERATE_H
  if (deviceConfiguration.resample())
      registerSoundProcessor(new ResampleSoundProcessor(
                deviceConfiguration.channels(),
                deviceConfiguration.sampleRate(),
                deviceConfiguration.resampleSampleRate()));
#endif
}


void SoundInputClient::process(const QByteArray& data, qint64 currentTime)
{
  QByteArray processedData = data;
  foreach (SoundProcessor* p, processors) {
    p->process(processedData, currentTime);
    if (processedData.isEmpty()) return;
  }

  processPrivate(processedData, currentTime);
}


/**
 * \brief Destructor
 */
SoundInputClient::~SoundInputClient()
{
  qDeleteAll(processors);
}
