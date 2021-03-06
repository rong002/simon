/*
 *   Copyright (C) 2012 Peter Grasch <peter.grasch@bedahr.org>
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


#include "createbasemodel.h"
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <KTar>
#include <KStandardDirs>
#include <KMessageBox>
#include <KLocalizedString>

CreateBaseModel::CreateBaseModel ( QWidget* parent, Qt::WFlags flags ) : KDialog ( parent, flags)
{
  QWidget *w = new QWidget(this);
  ui.setupUi(w);
  setMainWidget(w);
  slotCompleteChanged();
  connect(ui.leName, SIGNAL(textChanged(const QString&)), this, SLOT(slotCompleteChanged()));
  connect(ui.urHMM, SIGNAL(textChanged(const QString&)), this, SLOT(slotCompleteChanged()));
  connect(ui.urTiedlist, SIGNAL(textChanged(const QString&)), this, SLOT(slotCompleteChanged()));
  connect(ui.urMacros, SIGNAL(textChanged(const QString&)), this, SLOT(slotCompleteChanged()));
  connect(ui.urStats, SIGNAL(textChanged(const QString&)), this, SLOT(slotCompleteChanged()));

  connect(ui.urBFEAT, SIGNAL(textChanged(const QString&)), this, SLOT(slotCompleteChanged()));
  connect(ui.urMdef, SIGNAL(textChanged(const QString&)), this, SLOT(slotCompleteChanged()));
  connect(ui.urMeans, SIGNAL(textChanged(const QString&)), this, SLOT(slotCompleteChanged()));
  connect(ui.urMWeights, SIGNAL(textChanged(const QString&)), this, SLOT(slotCompleteChanged()));
  connect(ui.urNoiseDict, SIGNAL(textChanged(const QString&)), this, SLOT(slotCompleteChanged()));
  connect(ui.urTMatrix, SIGNAL(textChanged(const QString&)), this, SLOT(slotCompleteChanged()));
  connect(ui.urVariances, SIGNAL(textChanged(const QString&)), this, SLOT(slotCompleteChanged()));
}

void CreateBaseModel::slotCompleteChanged()
{
  bool status = false;
  if(ui.twModelType->currentIndex() == 0)
  {
    status = !ui.leName->text().isEmpty() &&
             QFile::exists(ui.urBFEAT->url().toLocalFile()) &&
             QFile::exists(ui.urMdef->url().toLocalFile()) &&
             QFile::exists(ui.urMeans->url().toLocalFile()) &&
             QFile::exists(ui.urMWeights->url().toLocalFile()) &&
             QFile::exists(ui.urNoiseDict->url().toLocalFile()) &&
             QFile::exists(ui.urTMatrix->url().toLocalFile()) &&
             QFile::exists(ui.urVariances->url().toLocalFile());
  }
  else
  {
    status = !ui.leName->text().isEmpty() &&
             QFile::exists(ui.urHMM->url().toLocalFile()) &&
             QFile::exists(ui.urTiedlist->url().toLocalFile()) &&
             QFile::exists(ui.urMacros->url().toLocalFile()) &&
             QFile::exists(ui.urStats->url().toLocalFile());
  }
  button(Ok)->setEnabled(status);
}

QString CreateBaseModel::buildModel()
{
  if (!exec()) return QString();
  
  QDomDocument doc;
  QDomElement rootElem = doc.createElement("baseModel");
  
  QDomElement nameElem = doc.createElement("name");
  nameElem.appendChild(doc.createTextNode(ui.leName->text()));
  
  QDomElement creationDateElem = doc.createElement("creationDate");
  creationDateElem.appendChild(doc.createTextNode(ui.dcbCreationDate->dateTime().toString(Qt::ISODate)));
  
  QDomElement typeElem = doc.createElement("type");
  if(ui.twModelType->currentIndex() == 0)
    typeElem.appendChild(doc.createTextNode("SPHINX"));
  else
    typeElem.appendChild(doc.createTextNode("HTK")); //htk specific... duh
  
  rootElem.appendChild(nameElem);
  rootElem.appendChild(creationDateElem);
  rootElem.appendChild(typeElem);
  doc.appendChild(rootElem);
  
  QString dest = KStandardDirs::locateLocal("tmp", "basemodel.sbm");
  KTar archive(dest, "application/x-gzip");
  if (!archive.open(QIODevice::WriteOnly)) {
    KMessageBox::sorry(this, i18nc("%1 is path", "Failed to create temporary archive at %1", dest));
    return QString();
  }
  
  QByteArray metadata = doc.toByteArray();
  archive.writeFile("metadata.xml", "nobody", "nobody", metadata.constData(), metadata.length());
  

  if(ui.twModelType->currentIndex() == 0)
  {
    archive.addLocalFile(ui.urBFEAT->url().toLocalFile(), "feat.params");
    archive.addLocalFile(ui.urMdef->url().toLocalFile(), "mdef");
    archive.addLocalFile(ui.urMeans->url().toLocalFile(), "means");
    archive.addLocalFile(ui.urMWeights->url().toLocalFile(), "mixture_weights");
    archive.addLocalFile(ui.urNoiseDict->url().toLocalFile(), "noisedict");
    archive.addLocalFile(ui.urTMatrix->url().toLocalFile(), "transition_matrices");
    archive.addLocalFile(ui.urVariances->url().toLocalFile(), "variances");
  }
  else
  {
    archive.addLocalFile(ui.urHMM->url().toLocalFile(), "hmmdefs");
    archive.addLocalFile(ui.urTiedlist->url().toLocalFile(), "tiedlist");
    archive.addLocalFile(ui.urMacros->url().toLocalFile(), "macros");
    archive.addLocalFile(ui.urStats->url().toLocalFile(), "stats");
  }
  
  if (!archive.close()) {
    KMessageBox::sorry(this, i18nc("%1 is path", "Failed to store temporary base model archive at %1", dest));
    return QString();
  }
  return dest;
}
