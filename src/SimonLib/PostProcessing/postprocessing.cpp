//
// C++ Implementation: postprocessing
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "postprocessing.h"
#include <QProcess>
#include <KMessageBox>
#include <QFile>
#include <KProgressDialog>
#include <QCoreApplication>
#include <QObject>
#include <KLocalizedString>
#include "../Settings/settings.h"

PostProcessing::PostProcessing()
{
}

/**
 * \brief Takes a input and output filename, applies the postprocessing chain on the input and saves it
 * @param in The input filename
 * @param out Where to save it to
 * @return success
 */
bool PostProcessing::process(QString in, QString out, bool deleteIn)
{
	KProgressDialog *progDialog = new KProgressDialog(0, i18n("Nachbearbeitung"), i18n("Filter werden angewendet..."));
	if (QFile::exists(out) && (!QFile::remove(out)))
	{
		KMessageBox::error(0, i18n("Konnte %1 nicht �berschreiben. Bitte �berpr�fen Sie, ob Sie die n�tigen Rechte besitzen.").arg(out));
		return false;
	}
	
	QStringList filters = Settings::getS("Model/ProcessingFilters").split(" && ", QString::SkipEmptyParts);
	QString filter;
	progDialog->progressBar()->setMaximum(filter.count()+1);
	QCoreApplication::processEvents();
	for (int j=0; j < filters.count(); j++)
	{
		QString execStr = filters.at(j);
		execStr.replace("\%1", in);
		execStr.replace("\%2", out);
		execStr.replace("\%3", Settings::getS("Model/SampleRate"));
		execStr.replace("\%4", Settings::getS("Model/Channels"));
		int ret = QProcess::execute(execStr);
		if (ret)
		{
			//something went wrong
			KMessageBox::error(0, i18n("Konnte %1 nicht nach %2 bearbeiten.\n\nBitte ueberpruefen Sie ob Sie das Programm, installiert haben, der Pfad in den Einstellungen richtig angegeben wurde und ob Sie all die n�tigen Berechtigungen besitzen. (R�ckgabewert %3) (Ausgefuehrtes Kommando: %4)").arg(in).arg(out).arg(ret).arg(execStr));
			return NULL;
		}
		progDialog->progressBar()->setValue(j+1);
		QCoreApplication::processEvents();
	}

	if (!QFile::exists(out)) //if there are no filters or they don't copy it to the output
	{
		if (!QFile::copy(in, out))
		{
			KMessageBox::error(0, i18n("Konnte %1 nicht nach %2 kopieren. Bitte �berpr�fen Sie ihre Berechtigungen auf den Zielort").arg(in).arg(out));
			return false;
		}
	}

	if (deleteIn)
		if (!QFile::remove(in))
		{
			KMessageBox::error(0, i18n("Konnte %1 nicht l�schen").arg(in));
		}

	QCoreApplication::processEvents();
	progDialog->progressBar()->setValue(progDialog->progressBar()->maximum());
	progDialog->close();
	progDialog->deleteLater();

	return true;
}


PostProcessing::~PostProcessing()
{
}


