//
// C++ Implementation: firstruncreatedictionarypage
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "firstruncreatedictionarypage.h"
#include <QHBoxLayout>
#include <QLabel>
#include "wordlistmanager.h"
#include "trainingmanager.h"

/**
 * \brief Constructor
 * \author Peter Grasch
 * @param addWordView The member will be set to the given AddWordView;
 * @param parent The parent to set the QWizardPage to
 */
FirstRunCreateDictionaryPage::FirstRunCreateDictionaryPage(AddWordView* addWordView, QWidget* parent): QWizardPage(parent)
{
	this->setTitle(tr("Lese Konfiguration..."));
    this->addWordView = addWordView;
}

/**
 * \brief Initializes the Page - creates a new trainingManager and wordlistManager and publishes them
 * 
 * Emits trainingManagerCreated(), wordListManagerCreated() and done()
 * 
 * \author Peter Grasch
 */
void FirstRunCreateDictionaryPage::initializePage()
{
	TrainingManager *trainingManager = new TrainingManager();
	WordListManager *wordListManager = new WordListManager();
    
	emit trainingManagerCreated(trainingManager);
	emit wordListManagerCreated(wordListManager);
	emit done();
}
