/*
 *   Copyright (C) 2014 Peter Grasch <peter.grasch@bedahr.org>
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

#include "coreaudiobackend.h"
#include <simonsound/soundbackendclient.h>
#include <simonlogging/logger.h>
#include <CoreAudio/AudioHardware.h>
#include <Foundation/NSString.h>
#include <KDebug>

/*
 * Roughly based on:
 * http://stackoverflow.com/questions/1983984/how-to-get-audio-device-uid-to-pass-into-nssounds-setplaybackdeviceidentifier
 */
QStringList getDevices(bool inputDevices)
{
  QStringList devices;
  AudioObjectPropertyAddress propertyAddress;
  AudioObjectID *deviceIDs;
  UInt32 propertySize;
  NSInteger numDevices;

  propertyAddress.mSelector = kAudioHardwarePropertyDevices;
  propertyAddress.mScope = (inputDevices) ? kAudioDevicePropertyScopeInput : kAudioDevicePropertyScopeOutput;
  propertyAddress.mElement = kAudioObjectPropertyElementMaster;
  if (AudioObjectGetPropertyDataSize(kAudioObjectSystemObject, &propertyAddress, 0, NULL, &propertySize) != noErr) {
    kWarning() << "Failed to get property data size";
    return devices;
  }

  numDevices = propertySize / sizeof(AudioDeviceID);
  deviceIDs = (AudioDeviceID *)calloc(numDevices, sizeof(AudioDeviceID));

  if (AudioObjectGetPropertyData(kAudioObjectSystemObject, &propertyAddress, 0, NULL, &propertySize, deviceIDs) != noErr) {
    kWarning() << "Failed to get device list";
    return devices;
  }
  CFStringRef deviceName;
  CFStringRef manufacturerName;
  CFStringRef uidString;
  QString qDeviceName;
  QString qManufacturerName;
  QString qAddress;

  for (NSInteger idx=0; idx<numDevices; idx++) {
    //device name
    propertySize = sizeof(deviceName);
    propertyAddress.mSelector = kAudioObjectPropertyName;
    if (AudioObjectGetPropertyData(deviceIDs[idx], &propertyAddress, 0, NULL, &propertySize, &deviceName) != noErr) {
      kWarning() << "Failed to get device name for device";
      continue;
    }
    qDeviceName = QString::fromLocal8Bit(CFStringGetCStringPtr(deviceName, CFStringGetSystemEncoding()));
    CFRelease(deviceName);

    //manufacturer name
    propertySize = sizeof(manufacturerName);
    propertyAddress.mSelector = kAudioObjectPropertyManufacturer;
    if (AudioObjectGetPropertyData(deviceIDs[idx], &propertyAddress, 0, NULL, &propertySize, &manufacturerName) != noErr) {
      kWarning() << "Failed to get manufacturer name for device " << qDeviceName;
      continue;
    }
    qManufacturerName = QString::fromLocal8Bit(CFStringGetCStringPtr(manufacturerName, CFStringGetSystemEncoding()));
    CFRelease(manufacturerName);

    //address
    propertySize = sizeof(uidString);
    propertyAddress.mSelector = kAudioDevicePropertyDeviceUID;
    if (AudioObjectGetPropertyData(deviceIDs[idx], &propertyAddress, 0, NULL, &propertySize, &uidString) != noErr) {
      kWarning() << "Failed to get address for device " << qDeviceName;
      continue;
    }
    qAddress  = QString::fromLocal8Bit(CFStringGetCStringPtr(uidString, CFStringGetSystemEncoding()));
    CFRelease(uidString);

    //channels
    propertyAddress.mSelector = kAudioDevicePropertyStreamConfiguration;
    if (AudioObjectGetPropertyDataSize(deviceIDs[idx], &propertyAddress, 0, NULL, &propertySize) != noErr) {
      kWarning() << "Failed to get channel information size for device " << qDeviceName;
      continue;
    }
    AudioBufferList *bufferList = static_cast<AudioBufferList *>(malloc(propertySize));
    if (AudioObjectGetPropertyData(deviceIDs[idx], &propertyAddress, 0, NULL, &propertySize, bufferList) != noErr) {
      kWarning() << "Failed to get channel information for device " << qDeviceName;
      delete bufferList;
      continue;
    }
    kDebug() << "Input channels for " << qDeviceName << " = " << bufferList->mNumberBuffers;
    if (bufferList->mNumberBuffers > 0)
      devices << i18nc("%1 is device name, %2 is manufacturer name and %3 is the id (which needs to be at "
                       "the end and wrapped in paranthesis", "%1 by %2 (%3)", qDeviceName,
                       qManufacturerName, qAddress);

    delete bufferList;
  }
  free(deviceIDs);
  return devices;
}

QStringList CoreAudioBackend::getAvailableInputDevices()
{
  return getDevices(true);
}

QStringList CoreAudioBackend::getAvailableOutputDevices()
{
  return getDevices(false);
}

bool CoreAudioBackend::check(SimonSound::SoundDeviceType type, const QString& device, int channels, int samplerate)
{
  return false;
}


QString CoreAudioBackend::getDefaultInputDevice()
{
  return QString();
}

QString CoreAudioBackend::getDefaultOutputDevice()
{
  return QString();
}


int CoreAudioBackend::bufferSize()
{
  return 0;
}


//recording
bool CoreAudioBackend::prepareRecording(const QString& device, int& channels, int& samplerate)
{
  return false;
}

bool CoreAudioBackend::startRecording(SoundBackendClient *client)
{
  return false;
}

bool CoreAudioBackend::stopRecording()
{
  return false;
}


//playback
bool CoreAudioBackend::preparePlayback(const QString& device, int& channels, int& samplerate)
{
  return false;
}

bool CoreAudioBackend::startPlayback(SoundBackendClient *client)
{
  return false;
}

bool CoreAudioBackend::stopPlayback()
{
  return false;
}


