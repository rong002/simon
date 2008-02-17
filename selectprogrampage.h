//
// C++ Interface: selectprogrampage
//
// Description:
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef SELECTPROGRAMPAGE_H
#define SELECTPROGRAMPAGE_H

#include <QWizardPage>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QListWidget>
#include <QVBoxLayout>
#include <QWidget>

#ifdef __WIN32
#include "registrymanager.h"
#include "windowsprogrammanager.h"
#endif
#include "programmanager.h"
#include "programcategory.h"

class ProgramManager;


/**
 * \class $CLASSNAME
 * \author Peter Grasch
 * \date 16.08.2007
 * \version 0.1
 * \brief This is a page of the ImportProgramWizard. The user must choose a category, to display the corresponding programs, where he also must choose one to continue.
 */
class SelectProgramPage : public QWizardPage
{
    Q_OBJECT

private:
	ProgramManager *programManager;
	ProgramCategoryList categoryList;

// #ifdef __WIN32
        //RegistryManager *regMan;
//         WindowsProgramManager *programManager;
// #endif

public:
        SelectProgramPage(QWidget* parent);
        ~SelectProgramPage();

        void insertCategories(ProgramCategoryList categorieList);
        void insertPrograms(ProgramList *programList);

	void initializePage();

        QString getExecPath();
        QString getName();
        QString getIcon();
	    QString getWorkingDirectory();

        QVBoxLayout *vboxLayout;
        QListWidget *lwCategories;
        QListWidget *lwPrograms;
        QHBoxLayout *hboxLayout;


    public slots:
        void searchForPrograms();
};

#endif
