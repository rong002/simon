//
// C++ Implementation: importtrainingdata
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "importtrainingdata.h"
#include "../../../SimonLib/Settings/settings.h"
#include "../../../SimonLib/PostProcessing/postprocessing.h"
#include "../trainingmanager.h"
#include <QDir>
#include <QDate>
#include <QTime>
#include <KLocalizedString>

ImportTrainingData::ImportTrainingData(QObject* parent): QThread(parent)
{
	this->pp = new PostProcessing();
}


void ImportTrainingData::run()
{
	prog=0;
	emit progress(0,0); //waiting...
	emit status(i18n("Durchsuche Ordner..."));
	QString wavDestdir = Settings::getS("Model/PathToSamples")+"/";

	QDir d(wavDestdir);
	if (!d.exists())
		if (!d.mkpath(wavDestdir))
	{
		emit error(i18n("Konnte Ausgabeordner %1 nicht erstellen").arg(wavDestdir));
	}
	
	QStringList *dataFiles = this->searchDir(directory);
	if (!dataFiles) return;
	

	emit progress(0, dataFiles->count());
	emit status(i18n("Importiere %1 Dateien...").arg(dataFiles->count()));

	dataFiles = processSounds(*dataFiles, wavDestdir);
	
	if (!dataFiles) return;
	
	emit status(i18n("Erstelle automatische Transkription..."));
	
	if (!createPrompts(*dataFiles)) return;
	emit status(i18n("Fertig"));
	emit done();
}

bool ImportTrainingData::import(QString directory)
{
	this->directory = directory;
	start();
	return true;
}

/**
 * \brief Walks the given dir. recursively and returns all ,wav files
 * @param dir The dir to walk
 * @return All files found
 */
QStringList* ImportTrainingData::searchDir(QString dir)
{
	QDir *dirHandle = new QDir(dir);
	if ((!dirHandle) || (!dirHandle->isReadable())) return NULL;

	QStringList dirsToCheck;
	QStringList *dataFiles = new QStringList();
	dirsToCheck<<dir;

	QStringList allowedFileTypes;
	allowedFileTypes << "*.wav";
	allowedFileTypes << "*.mp3";
	allowedFileTypes << "*.ogg";
	allowedFileTypes << "*.flac";
	QStringList dirs;
	QStringList files;

	while (!dirsToCheck.isEmpty())
	{
		dirHandle->setPath(dirsToCheck.takeAt(0));
		dirs = dirHandle->entryList(QDir::Dirs);
		for (int i=2; i < dirs.count(); i++)
			dirsToCheck.append(dirHandle->path()+"/"+dirs[i]);

		files = dirHandle->entryList(allowedFileTypes,  QDir::Files);
		for (int i=0; i < files.count(); i++)
			dataFiles->append(dirHandle->path()+"/"+files[i]);
	}
	return dataFiles;
}




/**
 * \brief Creates the promptsfile from the given stringlist
 * Using extractSaid()
 * \author Peter Grasch
 * \see extractSaid()
 * @param dataFiles The dataFiles to include in the prompts-file
 * @param destDir The destination file
 * @return success
 */
bool ImportTrainingData::createPrompts(QStringList dataFiles)
{
	TrainingManager *train = TrainingManager::getInstance();
	

	PromptsTable *prompts = new PromptsTable();
	QFileInfo fileInfo;
	QString fileName, said;

	for (int i=0; i <dataFiles.count(); i++)
	{
		fileInfo.setFile(dataFiles[i]);
		fileName = fileInfo.fileName();

		said = extractSaid(fileName);
		prompts->insert(fileName.left(fileName.lastIndexOf(".")), said.toUpper());
	}
	train->addSamples(prompts);
	train->savePrompts(true);
	delete prompts;
	return true;
}


/**
 * \brief Extracts the information that has been said out of the source
 * 
 * Returns the cleaned fielname without the extension and in uppercase
 * 
 * \author Peter Grasch
 * 
 * @param source The string to parse
 * @return cleaned string
 */
QString ImportTrainingData::extractSaid(QString source)
{
	QString said = source.left(source.lastIndexOf("."));
	said.remove(QRegExp("([0-9]|\\.|\\(|\\)|\\[|\\]|\\-)"));
	said.replace("_", " ");
	return said.trimmed();
}


/**
 * \brief Process the sound files from given in the list to the destDir
 * 
 * Resamples the audio to 16khz and normalizes it afterwards.
 * 
 * @param dataFiles The given datafiles
 * @param destDir The destination directory
 * @return the datafiles - if not successful it returns NULL
 */
QStringList* ImportTrainingData::processSounds(QStringList dataFiles, 
		QString destDir)
{
	QString newFileName;
	QFileInfo fInfo;
	QStringList *newFiles = new QStringList();
	
	for (int i=0; i < dataFiles.count(); i++)
	{
		fInfo.setFile(dataFiles[i]);
		QString dateTime = QDate::currentDate().toString ( "yyyy-MM-dd" ) +"_"+QTime::currentTime().toString("hh-mm-ss");
		newFileName = destDir+"/"+fInfo.fileName().left(fInfo.fileName().lastIndexOf(".")).replace(" ", "_")+"_"+dateTime+".wav";


		if (!pp->process(dataFiles[i], newFileName))
		{
			emit error(i18n("Konnte Tondaten nicht verarbeiten"));
			return NULL;
		}
		newFiles->append(newFileName);
		emit progress(++prog);
	}
	
	return newFiles;
}

ImportTrainingData::~ImportTrainingData()
{
	delete pp;
}


