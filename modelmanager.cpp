//
// C++ Implementation: modelmanager
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "modelmanager.h"
#include "settings.h"
#include "logger.h"
#include <QCoreApplication>

#include <QMessageBox>
#include <QVariant>
#include <QProgressDialog>
#include <QDebug>


ModelManager* ModelManager::instance;


ModelManager::ModelManager(QWidget *parent) : QThread(parent)
{
	processDialog = new QProgressDialog();
	connect(processDialog, SIGNAL(canceled()), this, SLOT(terminate()));
	connect(this, SIGNAL(status(QString)), this, SLOT(setStatus(QString)));
	connect(this, SIGNAL(progress(int,int)), this, SLOT(setProgress(int,int)));
	connect(this, SIGNAL(error(QString)), this, SLOT(displayError(QString)));

	processDialog->setWindowTitle(tr("Generiere Sprachmodell..."));
}


bool ModelManager::compileGrammar()
{	
	emit status(tr("Generiere Umkehr-Grammatik..."));
	if (!generateReverseGrammar())
	{
		emit error(tr("Konnte Umkehr-Grammatik nicht erstellen.\n\nBitte �berpr�fen Sie die Pfade zur Grammatikdatei (%1).").arg(Settings::getS("Model/PathToGrammar")));
		return false;
	}
	
	emit progress(2050);

	emit status(tr("Generiere tempor�re Vokabeln..."));
	if (!generateTempVoca())
	{
		emit error(tr("Konnte Tempor�re Vokabeln nicht erstellen.\n\nBitte �berpr�fen Sie die Pfade zur Vokabulardatei (%1).").arg(Settings::getS("Model/PathToVocab")));
		return false;
	}
	emit progress(2100);

	emit status(tr("Generiere DFA..."));
	if (!makeDfa())
	{
		emit error(tr("Konnte dfa nicht generieren.\n\nBitte �berpr�fen Sie die Pfade zur dfa und dfa_minimize Datei (%1, %2).").arg(Settings::getS("Programs/Julius/mkfa")).arg(Settings::getS("Programs/Julius/dfa_minimize")));
		return false;
	}
	emit progress(2250);
	
	emit status(tr("Generiere Grammatikalisches W�rterbuch..."));
	if (!generateDict())
	{
		emit error(tr("Konnte das grammatikalische W�rterbuch nicht generieren. \nBitte �berpr�fen Sie die Pfade zur Vocabeldatei und zum grammatikalischen W�rterbuch selbst. (%1, %2).").arg(Settings::getS("Model/PathToVoca")).arg(Settings::getS("Model/PathToDict")));
		return false;
	}
	emit progress(2299);
	
	return true;
}


bool ModelManager::generateTempVoca()
{
	QString vocabPath = Settings::getS("Model/PathToVocab");
	QFile vocab(vocabPath);
	
	QString terminal;

	if (!vocab.open(QFile::ReadOnly)) return false;
	QFile tmpVocab(tmpDir+"tempvoca");
	if (!tmpVocab.open(QFile::WriteOnly)) return false;
	
	QFile term(tmpDir+"term");
	if (!term.open(QFile::WriteOnly)) return false;
	
	QString vocabEntry;
	
	int termid=0;
	while (!vocab.atEnd())
	{
		vocabEntry = vocab.readLine(1024);
		vocabEntry.remove(QRegExp("\r+$"));
		vocabEntry.remove(QRegExp("#.*"));
		if (vocabEntry.trimmed().isEmpty()) continue;
		
		if (vocabEntry.startsWith("%"))
		{
			terminal = vocabEntry.mid(1).trimmed();
			tmpVocab.write("#"+terminal.toLatin1()+"\n");
		
			term.write(termid+"\t"+terminal.toLatin1()+"\n");
			termid++;
		}
		
	}
	vocab.close();
	tmpVocab.close();
	term.close();
	return true;
}

bool ModelManager::makeDfa()
{
	QString mkfa = Settings::getS("Programs/Julius/mkfa");
	QString dfaMinimize= Settings::getS("Programs/Julius/dfa_minimize");
	
	QString execStr = mkfa+" -e1 -fg "+tmpDir+"reverseGrammar -fv "+tmpDir+"tempvoca -fo "+tmpDir+"dfaTemp.tmp -fh "+tmpDir+"dfaTemp.h";
	if (QProcess::execute(execStr)!= 0) 
		return false;

	if (QProcess::execute(dfaMinimize+" "+tmpDir+"dfaTemp.tmp -o "+Settings::getS("Model/PathToDfa"))!= 0) 
		return false;

	return true;	
}

bool ModelManager::generateReverseGrammar()
{
	QFile grammar(Settings::getS("Model/PathToGrammar"));
	if (!grammar.open(QFile::ReadOnly)) return false;

	QFile reverseGrammar(tmpDir+"reverseGrammar");
	if (!reverseGrammar.open(QFile::WriteOnly)) return false;

	QString reverseGrammarEntry;
	QStringList parts;
	QString grammarEntry;
	QStringList terminals;

	while (!grammar.atEnd())
	{
		grammarEntry = grammar.readLine(1024);
		grammarEntry.remove(QRegExp("\r+$"));
		grammarEntry.remove(QRegExp("#.*"));
		if (grammarEntry.trimmed().isEmpty()) continue;
		
		parts = grammarEntry.split(QRegExp("\\:"));
		
		reverseGrammarEntry = parts[0]+": ";
		terminals = parts[1].split(" ");
		for (int i=terminals.count()-1; i >= 0; i--)
			reverseGrammarEntry += terminals[i].trimmed()+" ";
		
		reverseGrammar.write(reverseGrammarEntry.toLatin1()+"\n");
	}
	reverseGrammar.close();
	grammar.close();
	return true;
}

bool ModelManager::generateDict()
{
	int nowId = -1;
	QFile vocab(Settings::getS("Model/PathToVocab"));
	if (!vocab.open(QFile::ReadOnly)) return false;
	QFile dict(Settings::getS("Model/PathToDict"));
	if (!dict.open(QFile::WriteOnly)) return false;
	QString vocabEntry;
	QStringList entryPart;
	
	while (!vocab.atEnd())
	{
		vocabEntry = vocab.readLine(1024);
		vocabEntry.remove(QRegExp("\r+$"));
		vocabEntry.remove(QRegExp("#.*"));
		if (vocabEntry.trimmed().isEmpty()) continue;
		
		if (vocabEntry.startsWith("%"))
		{
			nowId++;
			continue;
		} else
		{
			entryPart = vocabEntry.split(QRegExp("[\t ]*"), 
					QString::SkipEmptyParts);
			if (entryPart.count() < 2) continue;
			
			dict.write(QString::number(nowId).toLatin1()+"\t"+"["+entryPart[0].toLatin1()+"]"+entryPart[1].toLatin1());
		}
	}
	
	vocab.close();
	dict.close();
	return true;
}

void ModelManager::cancel()
{
	
}

void ModelManager::setStatus(QString status)
{
	processDialog->setLabelText(status);
}

void ModelManager::setProgress(int now, int max)
{
	processDialog->setMaximum(max);
	processDialog->setValue(now);
}

void ModelManager::displayError(QString error)
{
	QMessageBox::critical(0, tr("Fehler"), tr("Beim Kompilieren des Modells ist ein Fehler aufgetreten:\n\n%1").arg(error));
	processDialog->hide();
}

bool ModelManager::startCompilation()
{
	if (isRunning()) return false;
	
	processDialog->show();
	start();
	return true;
}

bool ModelManager::generateDirectoryStructure()
{
	bool success=true;
	QDir dir(Settings::get("TempDir").toString());
	//remove if it exists
	
	if (!dir.exists("modeltmp"))
		success = dir.mkdir("modeltmp");

	dir.cd ("modeltmp");
	
	for (int i=0; i < 16; i++)
		dir.mkdir("hmm"+QString::number(i));

	return success;
}

bool ModelManager::codeAudioData()
{
	emit status(tr("Kodiere Audiodaten..."));
	
	//creating codetrain
	if (!generateCodetrainScp())
	{
		emit error(tr("Konnte CodeTrain-Datei nicht erstellen."));
		return false;
	}

	emit progress(160);
	QString codetrainPath = tmpDir+"/codetrain.scp";

	//TODO: implement some sort of caching (maybe with an file/hash combination?)
	if (!proc->execute(Settings::getS("Programs/HTK/HCopy")+" -A -D -T 1 -C "+Settings::getS("Model/PathToWavConfig")+
			" -S "+codetrainPath)==0)
	{
		emit error(tr("Fehler beim kodieren der samples! Bitte �berpr�fen Sie den Pfad zu HCopy (%1) und der wav config (%2)").arg(Settings::getS("Programs/HTK/HCopy")).arg(Settings::getS("Model/PathToWavConfig")));
		return false;
	}
	emit progress(550);

	return true;
}

bool ModelManager::generateCodetrainScp()
{
	QString samplePath = Settings::getS("Model/PathToSamples");
	QString codetrainPath = tmpDir+"codetrain.scp";
	QString trainPath = tmpDir+"train.scp";

	QDir wavDir(samplePath);
	QStringList wavs = wavDir.entryList(QStringList() << ("*.wav"));
	
	QString pathToMFCs =tmpDir+"mfcs";
	wavDir.mkpath(pathToMFCs);
	
	QString file;
	QFile scpFile(codetrainPath);
	QFile trainScpFile(trainPath);
	if (!scpFile.open(QIODevice::WriteOnly|QIODevice::Truncate) || !trainScpFile.open(QIODevice::WriteOnly|QIODevice::Truncate))
	{
		return false;
	}

	QString fileBase;
	QString mfcFile;
	for (int i=0; i < wavs.count();i++)
	{
		file = wavs[i];
		fileBase = file.left(file.lastIndexOf("."));
		mfcFile = pathToMFCs+"/"+fileBase+".mfc";

		scpFile.write(QString(samplePath+"/"+file + " " + mfcFile +"\n").toLatin1());
		trainScpFile.write(mfcFile.toLatin1()+"\n");
	}
	scpFile.close();
	trainScpFile.close();
	return true;
}

void ModelManager::run()
{
	Logger::log(tr("[INF] Modell wird generiert..."));
	emit status(tr("Vorbereitung"));
	emit progress(0,2000);
	
	proc = new QProcess();
	connect(proc, SIGNAL(readyReadStandardError()), this, SLOT(logError()));
	connect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(logInfo()));
	
	if (!generateDirectoryStructure())
	{
		emit error(tr("Fehler beim Erstellen der Ordnerstruktur. Bitte �berpr�fen Sie die Berechtigungen f�r den Tempor�ren Ordner (%1)").arg(Settings::getS("TempDir")));
		return;
	}
	emit progress(2);
	this->tmpDir = Settings::getS("TempDir")+"/modeltmp/";
	if (!generateInputFiles()) return;
	if (!makeTranscriptions()) return;
	if (!codeAudioData()) return;
	if (!buildHMM()) return;
	if (!compileGrammar()) return;
	
	emit status(tr("Abgeschlossen"));
	emit progress(2300);
}

bool ModelManager::generateInputFiles()
{	
	emit status(tr("Generiere Wordliste..."));
	//wlist
	if (!generateWlist())
	{
		emit error(tr("Erstellen der Wordliste fehlgeschlagen. Bitte �berpr�fen Sie die Berechtigungen f�r den Tempor�ren Pfad (%1) und ob die Prompts-File richtig gesetzt ist (%2)")
				.arg(Settings::getS("TempDir")).arg(Settings::getS("Model/PathToPrompts")));
		return false;
	}
	emit progress(35);

	//monophones
	emit status(tr("Erstelle Monophone..."));

	
	if (!makeMonophones())
	{
		emit error(tr("Erstellen der Monophone fehlgeschlagen. Bitte �berpr�fen Sie ob das Programm HDMan richtig eingerichtet ist und der Pfad zum Lexikon richtig konfiguriert wurde (%1), und diese alle verwendeten W�rter beinhaltet.").arg(Settings::getS("Model/PathToLexicon")));
		return false;
	}
	
	emit progress(40);

	return true;
}

bool ModelManager::makeTranscriptions()
{
	//mlf
	qDebug() << "hier";
	emit status(tr("Erstelle Master Label File..."));
	if (!generateMlf())
	{
		emit error(tr("Erstellen der Master Label File fehlgeschlagen. Bitte �berpr�fen Sie, ob die prompts-Datei (%1)").arg(Settings::getS("Model/PathToPrompts")));
		return false;
	}
	emit progress(55);

	qDebug() << "hier2";
	
	if ((proc->execute(Settings::getS("Programs/HTK/HLEd")+" -A -D -T 1 -l \"*\" -d "+tmpDir+"/dict -i "+tmpDir+"/phones0.mlf "+Settings::getS("Model/PathToMkPhones0")+" "+tmpDir+"/words.mlf") != 0) || (proc->execute(Settings::getS("Programs/HTK/HLEd")+" -A -D -T 1 -l \"*\" -d "+tmpDir+"/dict -i "+tmpDir+"/phones1.mlf "+Settings::getS("Model/PathToMkPhones1")+" "+tmpDir+"/words.mlf") != 0) )
	{
		emit error(tr("Erstellen der Transcriptions files fehlgeschlagen. Bitte �berpr�fen Sie ob Sie den Pfad f�r die Dateien mkphones0.led und mkphones1.led richtig angegeben haben. (%1, %2)").arg(Settings::getS("Model/PathToMkPhones0")).arg(Settings::getS("Model/PathToMkPhones1")));
		return false;
	}
	emit progress(155);
	return true;
}

bool ModelManager::createMonophones()
{
	emit status(tr("Erstelle hmm0..."));
	if (!buildHMM0())
	{
		emit error(tr("Fehler beim Generieren des HMM0. \n\nBitte �berpr�fen Sie, ob ausreichend Trainingsmaterial vorhanden ist.\n\nSollten Sie sicher sein, das Modell wurde ausreichend trainiert, �berpr�fen Sie bitte den Pfad zu HCompV (%1), der config (%2) und des Prototypen (%3).").arg(Settings::getS("Programs/HTK/HCompV")).arg(Settings::getS("Model/PathToConfig")).arg(Settings::getS("Model/PathToProto")));
		return false;
	}
	emit progress(550);
	emit status(tr("Erstelle hmm1..."));
	if (!buildHMM1())
	{
		emit error(tr("Fehler beim Generieren des HMM1. Bitte �berpr�fen Sie den Pfad zu HERest (%1) und der config (%2").arg(Settings::getS("Programs/HTK/HERest")).arg(Settings::getS("Model/PathToConfig")));
		return false;
	}
	emit progress(800);
	emit status(tr("Erstelle hmm2..."));
	if (!buildHMM2())
	{
		emit error(tr("Fehler beim Generieren des HMM2. Bitte �berpr�fen Sie den Pfad zu HERest (%1) und der config (%2").arg(Settings::getS("Programs/HTK/HERest")).arg(Settings::getS("Model/PathToConfig")));
		return false;
	}
	emit progress(850);
	emit status(tr("Erstelle hmm3..."));
	if (!buildHMM3())
	{
		emit error(tr("Fehler beim Generieren des HMM3. Bitte �berpr�fen Sie den Pfad zu HERest (%1) und der config (%2").arg(Settings::getS("Programs/HTK/HERest")).arg(Settings::getS("Model/PathToConfig")));
		return false;
	}
	emit progress(900);
	return true;
}

bool ModelManager::fixSilenceModel()
{
	emit status(tr("Erstelle Pausenmodell (hmm4)..."));
	if (!buildHMM4())
	{
		emit error(tr("Fehler beim Generieren des HMM4. Bitte �berpr�fen Sie das HMM3"));
		return false;
	}
	emit progress(950);
	emit status(tr("Erstelle hmm5..."));
	if (!buildHMM5())
	{
		emit error(tr("Fehler beim Generieren des HMM5. Bitte �berpr�fen Sie den Pfad zu HHEd (%1) und  des Silence-Modells (%2)").arg(Settings::getS("Programs/HTK/HHEd")).arg(Settings::getS("Model/PathToSilHed")));
		return false;
	}
	emit progress(1000);
	emit status(tr("Erstelle hmm6..."));
	if (!buildHMM6())
	{
		emit error(tr("Fehler beim Generieren des HMM6. Bitte �berpr�fen Sie den Pfad zu HERest (%1) und der config (%2").arg(Settings::getS("Programs/HTK/HERest")).arg(Settings::getS("Model/PathToConfig")));
		return false;
	}
	emit progress(1080);
	emit status(tr("Erstelle hmm7..."));
	if (!buildHMM7())
	{
		emit error(tr("Fehler beim Generieren des HMM7. Bitte �berpr�fen Sie den Pfad zu HERest (%1) und der config (%2").arg(Settings::getS("Programs/HTK/HERest")).arg(Settings::getS("Model/PathToConfig")));
		return false;
	}
	emit progress(1150);
	
	return true;
}

bool ModelManager::realign()
{
	emit status(tr("Erstellte dict1..."));
	if (!makeDict1())
	{
		emit error(tr("Fehler beim erstellen des dict1"));
		return false;
	}
	emit progress(1160);

	emit status(tr("Hmm7 neu ausrichten..."));
	if (!realignHMM7())
	{
		emit error(tr("Konnte HMM7 nicht neu ausrichten. Bitte �berpr�fen Sie den Pfad zu HVite (%1), der config (%2) und das HMM7.").arg(Settings::getS("Programs/HTK/HVite")).arg(Settings::getS("Model/PathToConfig")));
		return false;
	}
	emit progress(1160);

	emit status(tr("Erstelle hmm8..."));
	if (!buildHMM8())
	{
		emit error(tr("Fehler beim Generieren des HMM8. Bitte �berpr�fen Sie den Pfad zu HERest (%1) und der config (%2").arg(Settings::getS("Programs/HTK/HERest")).arg(Settings::getS("Model/PathToConfig")));
		return false;
	}
	emit progress(1230);

	emit status(tr("Erstelle hmm9..."));
	if (!buildHMM9())
	{
		emit error(tr("Fehler beim Generieren des HMM9. Bitte �berpr�fen Sie den Pfad zu HERest (%1) und der config (%2").arg(Settings::getS("Programs/HTK/HERest")).arg(Settings::getS("Model/PathToConfig")));
		return false;
	}
	emit progress(1300);
	
	return true;
}

bool ModelManager::tieStates()
{
	emit status(tr("Erstelle triphone..."));
	

	if ((proc->execute(Settings::getS("Programs/HTK/HDMan")+" -A -D -T 1 -b sp -n "+tmpDir+"fulllist -g "+Settings::getS("Model/PathToGlobalDed")+" "+tmpDir+"dict-tri "+Settings::getS("Model/PathToLexicon")) != 0))
	{
		emit error(tr("Konnte Triphone nicht binden. Bitte �berpr�fen Sie den Pfad zu HDMan (%1), global.ded (%2) und dem Lexikon (%3).").arg(Settings::getS("Programs/HTK/HDMan")).arg(Settings::getS("Model/PathToGlobalDed")).arg(Settings::getS("Model/PahtToLexicon")));
		return false;
	}
	emit progress(1700);

	emit status(tr("Erstelle Liste der Triphone..."));
	if (!makeFulllist())
	{
		emit error(tr("Konnte Liste der Triphone nicht erstellen."));
		return false;
	}
	emit progress(1705);
	emit status(tr("Erstelle tree.hed..."));
	if (!makeTreeHed())
	{
		emit error(tr("Konnte tree.hed nicht erstellen."));
		return false;
	}
	emit progress(1750);
	
	emit status(tr("Erstelle hmm13..."));
	if (!buildHMM13())
	{
		emit error(tr("Fehler beim Generieren des HMM13. Bitte �berpr�fen Sie den Pfad zu HHEd (%1).").arg(Settings::getS("Programs/HTK/HHEd")));
		return false;
	}
	emit progress(1830);
	
	
	emit status(tr("Erstelle hmm14..."));
	if (!buildHMM14())
	{
		emit error(tr("Fehler beim Generieren des HMM14. Bitte �berpr�fen Sie den Pfad zu HERest (%1), der config (%2), und die stats-Datei (%3)").arg(Settings::getS("Programs/HTK/HERest")).arg(Settings::getS("Model/PathToConfig")).arg(tmpDir+"stats"));
		return false;
	}
	emit progress(1900);
	
	emit status(tr("Erstelle hmm15..."));
	if (!buildHMM15())
	{
		emit error(tr("Fehler beim Generieren des HMM15. Bitte �berpr�fen Sie den Pfad zu HERest (%1), der config (%2), und die stats-Datei (%3)").arg(Settings::getS("Programs/HTK/HERest")).arg(Settings::getS("Model/PathToConfig")).arg(tmpDir+"stats"));
		return false;
	}
	emit progress(1990);

	
	return true;
}

bool ModelManager::buildHMM13()
{
	return (proc->execute(Settings::getS("Programs/HTK/HHEd")+" -A -D -T 1 -H "+tmpDir+"hmm12/macros -H "+tmpDir+"hmm12/hmmdefs -M "+tmpDir+"hmm13 "+tmpDir+"tree.hed "+tmpDir+"triphones1")==0);
}


bool ModelManager::buildHMM14()
{
	if (!proc->execute(Settings::getS("Programs/HTK/HERest")+" -A -D -T 1 -C "+Settings::getS("Model/PathToConfig")+" -I "+tmpDir+"wintri.mlf -t 250.0 150.0 3000.0 -s "+tmpDir+"stats -S "+tmpDir+"train.scp -H "+tmpDir+"hmm13/macros -H "+tmpDir+"hmm13/hmmdefs -M "+tmpDir+"hmm14 "+tmpDir+"tiedlist")==0) return false;
	return true;
}


bool ModelManager::buildHMM15()
{
	if (!proc->execute(Settings::getS("Programs/HTK/HERest")+" -A -D -T 1 -C "+Settings::getS("Model/PathToConfig")+" -I "+tmpDir+"wintri.mlf -t 250.0 150.0 3000.0 -s "+tmpDir+"stats -S "+tmpDir+"train.scp -H "+tmpDir+"hmm14/macros -H "+tmpDir+"hmm14/hmmdefs -M "+tmpDir+"hmm15 "+tmpDir+"tiedlist")==0) return false;
	return true;
}

bool ModelManager::makeFulllist()
{	
	QFile::remove(tmpDir+"fulllist-original");
	if (!QFile::copy(tmpDir+"fulllist", tmpDir+"fulllist-original")) return false;
	
	QFile triphones1(tmpDir+"triphones1");
	QFile fulllist(tmpDir+"fulllist");
	
	
	//copy the triphones from triphones1 to fulllist
	//BUT: omit duplicates!
	
	QStringList fulllistEntries;
	if (!fulllist.open(QIODevice::ReadWrite)) return false;
	while (!fulllist.atEnd()) fulllistEntries << fulllist.readLine(150);
	
	if (!triphones1.open(QIODevice::ReadOnly)) return false;
	
	while (!triphones1.atEnd())
	{
		QByteArray triphone = triphones1.readLine(500);
		if (!fulllistEntries.contains(triphone))
			fulllist.write(triphone);
	}
	triphones1.close();
		
	return true;
}

bool ModelManager::makeTreeHed()
{	
	QFile::remove(tmpDir+"tree.hed");
	if (!QFile::copy(Settings::getS("Model/PathToTreeHed"), tmpDir+"tree.hed")) return false;
	
	QFile treeHed(tmpDir+"tree.hed");
	if (!treeHed.open(QIODevice::WriteOnly|QIODevice::Append)) return false;
	
	QString command = "TB";
	int threshold = 350;
	QFile hmmlist(tmpDir+"monophones0");
	if (!hmmlist.open(QIODevice::ReadOnly)) return false;
	
	QStringList phonemeList;
	while (!hmmlist.atEnd())
	{ phonemeList << hmmlist.readLine().trimmed(); }
	hmmlist.close();
	
	for (int i=0; i < phonemeList.count(); i++)
		treeHed.write(QString("%1 %2 \"ST_%3_2_\" {(\"%3\",\"*-%3+*\",\"%3+*\",\"*-%3\").state[2]}\n").arg(command).arg(threshold).arg(phonemeList[i]).toLatin1());
	
	for (int i=0; i < phonemeList.count(); i++)
		treeHed.write(QString("%1 %2 \"ST_%3_3_\" {(\"%3\",\"*-%3+*\",\"%3+*\",\"*-%3\").state[3]}\n").arg(command).arg(threshold).arg(phonemeList[i]).toLatin1());
	
	for (int i=0; i < phonemeList.count(); i++)
		treeHed.write(QString("%1 %2 \"ST_%3_4_\" {(\"%3\",\"*-%3+*\",\"%3+*\",\"*-%3\").state[4]}\n").arg(command).arg(threshold).arg(phonemeList[i]).toLatin1());	
	
	treeHed.write(QString(" \nTR 1\n \nAU \""+tmpDir+"fulllist\" \nCO \""+tmpDir+"tiedlist\" \n \nST "+tmpDir+"trees \n").toLatin1());
	
	treeHed.close();
	
	return true;
}

bool ModelManager::buildHMM()
{
	if (!createMonophones()) return false;
	if (!fixSilenceModel()) return false;
	if (!realign()) return false;
	if (!makeTriphones()) return false;
	if (!tieStates()) return false;
	

	//TODO: Make a Backup!
	emit status(tr("�bernehme Modell..."));

	if (QFile::exists(Settings::getS("Model/PathToHmm")))
		if (!QFile::remove(Settings::getS("Model/PathToHmm"))) return false;
	if (!QFile::copy(tmpDir+"hmm15/hmmdefs", Settings::getS("Model/PathToHmm")))
		return false;

	if (QFile::exists(Settings::getS("Model/PathToTiedlist")))
		if (!QFile::remove(Settings::getS("Model/PathToTiedlist"))) return false;
	if (!QFile::copy(tmpDir+"tiedlist", Settings::getS("Model/PathToTiedlist")))
		return false;

	return true;
}

bool ModelManager::makeTriphones()
{
	emit status(tr("Erstelle triphone..."));
	if ((proc->execute(Settings::getS("Programs/HTK/HLEd")+" -A -D -T 1 -n "+tmpDir+"/triphones1 -l * -i "+tmpDir+"/wintri.mlf "+Settings::getS("Model/PathToMktriLed")+" "+tmpDir+"/aligned.mlf") != 0))
	{
		emit error(tr("Erstellen der Triphone files fehlgeschlagen. Bitte �berpr�fen Sie ob Sie den Pfad f�r die Datei mktri.led richtig angegeben haben (%1) und �berpr�fen Sie den Pfad zu HLEd (%2)").arg(Settings::getS("Model/PathToMktriLed")).arg(Settings::getS("Programs/HTK/HLEd")));
		return false;
	}
	emit progress(1380);
	
	emit status(tr("Erstelle mktri.hed..."));
	if (!makeMkTriHed())
	{
		emit error(tr("Fehler beim generieren der mktri.hed"));
		return false;
	}
	emit progress(1400);
	
	emit status(tr("Erstelle hmm10..."));
	if (!buildHMM10())
	{
		emit error(tr("Fehler beim Generieren des HMM10. Bitte �berpr�fen Sie den Pfad zu HHEd (%1).").arg(Settings::getS("Programs/HTK/HHEd")));
		return false;
	}
	emit progress(1470);
	
	emit status(tr("Erstelle hmm11..."));
	if (!buildHMM11())
	{
		emit error(tr("Fehler beim Generieren des HMM11. Bitte �berpr�fen Sie den Pfad zu HERest (%1) und der config (%2)").arg(Settings::getS("Programs/HTK/HERest")).arg(Settings::getS("Model/PathToConfig")));
		return false;
	}
	emit progress(1550);
	
	emit status(tr("Erstelle hmm12..."));
	if (!buildHMM12())
	{
		emit error(tr("Fehler beim Generieren des HMM12. Bitte �berpr�fen Sie den Pfad zu HERest (%1), der config (%2), und die stats-Datei (%3)").arg(Settings::getS("Programs/HTK/HERest")).arg(Settings::getS("Model/PathToConfig")).arg(tmpDir+"stats"));
		return false;
	}
	emit progress(1620);
	
	return true;
}


bool ModelManager::buildHMM12()
{
	if (!proc->execute(Settings::getS("Programs/HTK/HERest")+" -A -D -T 1 -C "+Settings::getS("Model/PathToConfig")+" -I "+tmpDir+"wintri.mlf -t 250.0 150.0 3000.0 -s "+tmpDir+"stats -S "+tmpDir+"train.scp -H "+tmpDir+"hmm11/macros -H "+tmpDir+"hmm11/hmmdefs -M "+tmpDir+"hmm12 "+tmpDir+"triphones1")==0) return false;
	return true;
}


bool ModelManager::buildHMM11()
{
	if (!proc->execute(Settings::getS("Programs/HTK/HERest")+" -A -D -T 1 -C "+Settings::getS("Model/PathToConfig")+" -I "+tmpDir+"wintri.mlf -t 250.0 150.0 3000.0 -S "+tmpDir+"train.scp -H "+tmpDir+"hmm10/macros -H "+tmpDir+"hmm10/hmmdefs -M "+tmpDir+"hmm11 "+tmpDir+"triphones1")==0) return false;
	return true;
}


bool ModelManager::buildHMM10()
{
	if (!proc->execute(Settings::getS("Programs/HTK/HHEd")+" -A -D -T 1 -H "+tmpDir+"hmm9/macros -H "+tmpDir+"hmm9/hmmdefs -M "+tmpDir+"hmm10 "+tmpDir+"mktri.hed "+tmpDir+"monophones1")==0) return false;
	return true;
}


bool ModelManager::makeMkTriHed()
{
	QFile monophones1(tmpDir+"monophones1");
	if (!monophones1.open(QIODevice::ReadOnly))
		return false;
		
	
	QFile mktriHed(tmpDir+"mktri.hed");
	if (!mktriHed.open(QIODevice::WriteOnly)) return false;
	
	mktriHed.write("CL "+tmpDir.toLatin1()+"triphones1\n");
	QByteArray phone="";
	while (!monophones1.atEnd())
	{
		phone = monophones1.readLine(150).trimmed();
		mktriHed.write("TI T_"+phone+" {(*-"+phone+"+*,"+phone+"+*,*-"+phone+").transP}\n");
	}
	
	monophones1.close();
	mktriHed.close();
	return true;
}


bool ModelManager::buildHMM9()
{
	if (!proc->execute(Settings::getS("Programs/HTK/HERest")+" -A -D -T 1 -C "+Settings::getS("Model/PathToConfig")+" -I "+tmpDir+"aligned.mlf -t 250.0 150.0 3000.0 -S "+tmpDir+"train.scp -H "+tmpDir+"hmm8/macros -H "+tmpDir+"hmm8/hmmdefs -M "+tmpDir+"hmm9 "+tmpDir+"monophones1")==0) return false;
	return true;
}


bool ModelManager::buildHMM8()
{
	if (!proc->execute(Settings::getS("Programs/HTK/HERest")+" -A -D -T 1 -C "+Settings::getS("Model/PathToConfig")+" -I "+tmpDir+"aligned.mlf -t 250.0 150.0 3000.0 -S "+tmpDir+"train.scp -H "+tmpDir+"hmm7/macros -H "+tmpDir+"hmm7/hmmdefs -M "+tmpDir+"hmm8 "+tmpDir+"monophones1")==0) return false;
	return true;
}

bool ModelManager::realignHMM7()
{
	if (!proc->execute(Settings::getS("Programs/HTK/HVite")+" -A -D -T 1 -l *  -o SWT -b silence -C "+Settings::getS("Model/PathToConfig")+" -H "+tmpDir+"hmm7/macros -H "+tmpDir+"hmm7/hmmdefs -i "+tmpDir+"aligned.mlf -m -t 250.0 150.0 1000.0 -y lab -a -I "+tmpDir+"words.mlf -S "+tmpDir+"train.scp "+tmpDir+"dict1 "+tmpDir+"monophones1")==0) return false;
	return true;
}

bool ModelManager::makeDict1()
{
	QFile::remove(tmpDir+"dict1");
	if (!QFile::copy(tmpDir+"dict", tmpDir+"dict1")) return false;
	QFile dict1(tmpDir+"dict1");
	if (!dict1.open(QIODevice::WriteOnly|QIODevice::Append)) return false;

	dict1.write("silence  []  sil\n");
	dict1.close();
	return true;
}

bool ModelManager::buildHMM7()
{
	if (!proc->execute(Settings::getS("Programs/HTK/HERest")+" -A -D -T 1 -C "+Settings::getS("Model/PathToConfig")+" -I "+tmpDir+"phones1.mlf -t 250.0 150.0 3000.0 -S "+tmpDir+"train.scp -H "+tmpDir+"hmm6/macros -H "+tmpDir+"hmm6/hmmdefs -M "+tmpDir+"hmm7 "+tmpDir+"monophones1")==0) return false;
	return true;
}

bool ModelManager::buildHMM6()
{
	if (!proc->execute(Settings::getS("Programs/HTK/HERest")+" -A -D -T 1 -C "+Settings::getS("Model/PathToConfig")+" -I "+tmpDir+"phones1.mlf -t 250.0 150.0 3000.0 -S "+tmpDir+"train.scp -H "+tmpDir+"hmm5/macros -H "+tmpDir+"hmm5/hmmdefs -M "+tmpDir+"hmm6 "+tmpDir+"monophones1")==0) return false;
	return true;
}

bool ModelManager::buildHMM5()
{
	if (!proc->execute(Settings::getS("Programs/HTK/HHEd")+" -A -D -T 1 -H "+tmpDir+"hmm4/macros -H "+tmpDir+"hmm4/hmmdefs -M "+tmpDir+"hmm5 "+Settings::getS("Model/PathToSilHed")+" "+tmpDir+"monophones1")==0) return false;
	return true;
}

bool ModelManager::buildHMM4()
{
	QFile::copy(tmpDir+"hmm3/macros", tmpDir+"hmm4/macros");

	QStringList  tmp2;

	QFile hmmdefs3(tmpDir+"hmm3/hmmdefs");
	if (!hmmdefs3.open(QIODevice::ReadOnly)) return false;
	QFile hmmdefs4(tmpDir+"hmm4/hmmdefs");
	if (!hmmdefs4.open(QIODevice::WriteOnly)) return false;

	QByteArray line;
	while (!hmmdefs3.atEnd())
	{
		line = hmmdefs3.readLine(3000);
		if (line.contains("\"sil\""))
		{
			while ((line != "<ENDHMM>\n") && (true /*!hmmdefs3.atEnd()*/))
			{
				hmmdefs4.write(line);
				tmp2 << line;
				line = hmmdefs3.readLine(3000);
			}
			hmmdefs4.write(line);
			hmmdefs4.write(tmp2[0].replace("~h \"sil\"", "~h \"sp\"").toLatin1());
			hmmdefs4.write(tmp2[1].toLatin1());
			hmmdefs4.write(tmp2[2].replace("5", "3").toLatin1());
			hmmdefs4.write(tmp2[9].replace("3", "2").toLatin1());
			hmmdefs4.write(tmp2[10].toLatin1());
			hmmdefs4.write(tmp2[11].toLatin1());
			hmmdefs4.write(tmp2[12].toLatin1());
			hmmdefs4.write(tmp2[13].toLatin1());
			hmmdefs4.write(tmp2[14].toLatin1());
			hmmdefs4.write(tmp2[21].replace("5", "3").toLatin1());
			hmmdefs4.write("0.000000e+000 1.000000e+000 0.000000e+000\n");
			hmmdefs4.write("0.000000e+000 0.900000e+000 0.100000e+000\n");
			hmmdefs4.write("0.000000e+000 0.000000e+000 0.000000e+000\n");
		}
		hmmdefs4.write(line);
	}
	return true;
}

bool ModelManager::buildHMM3()
{
	if (!proc->execute(Settings::getS("Programs/HTK/HERest")+" -A -D -T 1 -C "+Settings::getS("Model/PathToConfig")+" -I "+tmpDir+"phones0.mlf -t 250.0 150.0 1000.0 -S "+tmpDir+"train.scp -H "+tmpDir+"hmm2/macros -H "+tmpDir+"hmm2/hmmdefs -M "+tmpDir+"hmm3 "+tmpDir+"monophones0")==0) return false;
	return true;
}

bool ModelManager::buildHMM2()
{
	if (!proc->execute(Settings::getS("Programs/HTK/HERest")+" -A -D -T 1 -C "+Settings::getS("Model/PathToConfig")+" -I "+tmpDir+"phones0.mlf -t 250.0 150.0 1000.0 -S "+tmpDir+"train.scp -H "+tmpDir+"hmm1/macros -H "+tmpDir+"hmm1/hmmdefs -M "+tmpDir+"hmm2 "+tmpDir+"monophones0")==0) return false;
	return true;
}

bool ModelManager::buildHMM1()
{
	if (!proc->execute(Settings::getS("Programs/HTK/HERest")+" -A -D -T 1 -C "+Settings::getS("Model/PathToConfig")+" -I "+tmpDir+"phones0.mlf -t 250.0 150.0 1000.0 -S "+tmpDir+"train.scp -H "+tmpDir+"hmm0/macros -H "+tmpDir+"hmm0/hmmdefs -M "+tmpDir+"hmm1 "+tmpDir+"monophones0")==0) return false;
	return true;
}

bool ModelManager::buildHMM0()
{
	if (!proc->execute(Settings::getS("Programs/HTK/HCompV")+" -A -D -T 1 -C "+Settings::getS("Model/PathToConfig")+" -f 0.01 -m -S "+tmpDir+"train.scp -M "+tmpDir+"hmm0 "+Settings::getS("Model/PathToProto"))==0) return false;

	QString protoBody="";
	QString protoHead="";
	QString line;
	QFile protoFile(tmpDir+"hmm0/proto");
	if (!protoFile.open(QIODevice::ReadOnly)) return false;
	
	//extracting proto
	QString protoPreamble="";
	while (!protoFile.atEnd())
	{
		line = protoFile.readLine(3000);
		if (line.startsWith("~h")) { protoHead = line; break; }
		else protoPreamble += line;
	}
	while (!protoFile.atEnd())
		protoBody += protoFile.readLine(3000);
	protoFile.close();

	QStringList monophones;
	QFile monophones0(tmpDir+"monophones0");
	if (!monophones0.open(QIODevice::ReadOnly)) return false;

	while (!monophones0.atEnd())
		monophones.append(monophones0.readLine(50).trimmed());
	monophones0.close();
	
	Logger::log(tr("[INF] Verwendete Monophone des Modells: %1").arg(monophones.join(", ")));

	QFile hmmdefs(tmpDir+"hmm0/hmmdefs");
	if (!hmmdefs.open(QIODevice::WriteOnly)) return false;
	QString phoneHead;
	QString currentHead="";
	for (int i=0; i < monophones.count(); i++)
	{
		currentHead = protoHead;
		hmmdefs.write(currentHead.replace("proto", monophones[i]).toLatin1());
		hmmdefs.write(protoBody.toLatin1());
	}
	hmmdefs.close();

	//generating macros
	QFile macros(tmpDir+"hmm0/macros");
	if (!macros.open(QIODevice::WriteOnly)) return false;
	macros.write(protoPreamble.toLatin1());

	QFile vFloors(tmpDir+"hmm0/vFloors");
	if (!vFloors.open(QIODevice::ReadOnly)) return false;
	while (!vFloors.atEnd()) macros.write(vFloors.readLine(1000));
	vFloors.close();

	macros.close();

	return true;
}

bool ModelManager::makeMonophones()
{
	//make monophones1
	if (proc->execute(Settings::getS("Programs/HTK/HDMan")+" -A -D -T 1 -m -w "+tmpDir+"/wlist -g "+Settings::getS("Model/PathToGlobalDed")+" -n "+tmpDir+"/monophones1 -i "+tmpDir+"/dict "+Settings::getS("Model/PathToLexicon"))!=0) return false;

	//make monophones0
	//ditch the "sp" phoneme

	QFile monophones1(tmpDir+"/monophones1");
	QFile monophones0(tmpDir+"/monophones0");
	if (!monophones1.open(QIODevice::ReadOnly))
		return false;
	if (!monophones0.open(QIODevice::WriteOnly|QIODevice::Truncate))
		return false;

	QString phoneme;
	while (!monophones1.atEnd())
	{
		phoneme = monophones1.readLine(50);
		if ((phoneme.trimmed() != "sp") && (phoneme.trimmed() != ""))
			monophones0.write(phoneme.toLatin1());
	}
	monophones1.close();
	monophones0.close();
	return true;
}

void ModelManager::logInfo()
{
	Logger::log(tr("[INF]")+" "+proc->readAllStandardOutput());
}

void ModelManager::logError()
{
	Logger::log(tr("[ERR]")+" "+proc->readAllStandardError());
}

bool ModelManager::generateWlist()
{
	QFile promptsFile(Settings::getS("Model/PathToPrompts"));
	if (!promptsFile.open(QIODevice::ReadOnly))
		return false;
	
	QStringList words;
	QStringList lineWords;
	QString line;
	while (!promptsFile.atEnd())
	{
		line = promptsFile.readLine(3000);
		lineWords = line.split(QRegExp("( |\n)"), QString::SkipEmptyParts);
		lineWords.removeAt(0); //ditch the file-id
		words << lineWords;
	}
	promptsFile.close();
	
	words << "SENT-END" << "SENT-START";
	words.sort();
	
	//remove doubles
	int i=1;
	while (i < words.count())
	{
		if (words[i] == words[i-1])
			words.removeAt(i);
		else i++;
	}
	
	QFile wlistFile(Settings::getS("TempDir")+"/modeltmp/wlist");
	if (!wlistFile.open(QIODevice::WriteOnly))
		return false;
	for (int i=0; i < words.count(); i++)
	{
		wlistFile.write(words[i].toLatin1()+"\n");
	}
	wlistFile.close();
	return true;
}

bool ModelManager::generateMlf()
{
	QFile promptsFile(Settings::getS("Model/PathToPrompts"));
	QFile mlf(tmpDir+"words.mlf");

	if (!promptsFile.open(QIODevice::ReadOnly))
		return false;
	if (!mlf.open(QIODevice::WriteOnly))
		return false;
	
	mlf.write("#!MLF!#\n");
	QStringList lineWords;
	QString line;
	while (!promptsFile.atEnd())
	{
		line = promptsFile.readLine(3000);
		if (line.trimmed().isEmpty()) continue;
		lineWords = line.split(QRegExp("( |\n)"), QString::SkipEmptyParts);
		QString labFile = "\"*/"+lineWords.takeAt(0)+".lab\""; //ditch the file-id
		mlf.write(labFile.toLatin1()+"\n");
		for (int i=0; i < lineWords.count(); i++)
			mlf.write(lineWords[i].toLatin1()+"\n");
		mlf.write(".\n");
	}
	promptsFile.close();
	mlf.close();
	return true;
}

ModelManager::~ModelManager()
{
}


