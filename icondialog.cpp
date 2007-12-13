//
// C++ Implementation: icondialog
//
// Description:
//
//
// Author: Susanne Tschernegg
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "icondialog.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QListView>
#include <QHBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QFileDialog>

#ifdef __WIN32
#include <windows.h>
#include "qwindowsstyle.h"
#endif

#include <QLibrary>
#include <QMessageBox>

#include "windowsresourcehandler.h"

/**
*   \brief constructor which creates the dialog
*   @author Susanne Tschernegg
*/
IconDialog::IconDialog(QWidget *parent): QDialog(parent)
{
    setWindowTitle(tr("Change Icon"));
    
    QVBoxLayout *vbLayout = new QVBoxLayout();
    vbLayout->addWidget(new QLabel(tr("W�hlen Sie ein beliebiges Icon und best�tigen Sie mit ok.\n")));
    
    QRadioButton *rbIconView = new QRadioButton("Systemicons", this);
    QRadioButton *rbIconFromFile = new QRadioButton("Icon from file", this);
    QHBoxLayout *hbRbLayout = new QHBoxLayout();
    
    hbRbLayout->addWidget(rbIconView);
    hbRbLayout->addWidget(rbIconFromFile);
    vbLayout->addLayout(hbRbLayout);
    
    leFromFile = new QLineEdit();
    pbFromFile = new QPushButton();
    pbFromFile->setIcon(QIcon(":/images/icons/folder.svg"));
    QHBoxLayout *hbFileLayout = new QHBoxLayout();
    leFromFile->setEnabled(false);
    pbFromFile->setEnabled(false);
    
    vbLayout->addLayout(hbFileLayout);
    
    hbFileLayout->addWidget(leFromFile);
    hbFileLayout->addWidget(pbFromFile);
    
    iconView = new QListView();
    iconView->setViewMode(QListView::IconMode);
    model = new QStandardItemModel(iconView);
    iconView->setModel(model);
    iconView->setEnabled(false);
    
    vbLayout->addWidget(iconView);
    
    QHBoxLayout *hbLayout = new QHBoxLayout();
    
    QPushButton *pbOk = new QPushButton();
    pbOk->setText(tr("Ok"));
    
    QPushButton *pbCancel = new QPushButton();
    pbCancel->setText(tr("Abbrechen"));
    
    hbLayout->addWidget(pbOk);
    hbLayout->addWidget(pbCancel);
    vbLayout->addLayout(hbLayout);
    
    setLayout(vbLayout);
    
    connect(pbOk, SIGNAL(clicked()), this, SLOT(safeIconInformation()));
    connect(pbCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(rbIconView, SIGNAL(clicked()), this, SLOT(enableSystemIcons()));
    connect(rbIconFromFile, SIGNAL(clicked()), this, SLOT(enableLineEdit()));
    connect(pbFromFile, SIGNAL(clicked()), this, SLOT(openFileDialog()));
}

/**
*   \brief This method puts the icons into a QStandardView.
*   @author Susanne Tschernegg
*/
void IconDialog::showIcons(QString currentIcon)
{
    resourceIdStr = currentIcon;
    #ifdef __WIN32
    QStringList iconResources;
    if(resourceIdStr!="")
        iconResources = currentIcon.split(",");
    
    for(int i = 0; i<50; i++)
    {
        int x = i;
        if(resourceIdStr!="")
        {
            if(i == iconResources.at(1).toInt())
                continue;
            if(i==0)
                x = iconResources.at(1).toInt();
        }
        WindowsResourceHandler *windowsResourceHandler = new WindowsResourceHandler();
        QIcon icon = windowsResourceHandler->retrieveIcon("shell32.dll",x);
        
        QStandardItem *item = new QStandardItem();
        item->setIcon(icon);
        item->setEditable(true);
        item->setData(QVariant(i));
        model->appendRow(item);
    }
    #endif
}

/**
*   \brief The filename and the Id of the icon will be concated to the resourceIdStr.
*   @author Susanne Tschernegg
*/
void IconDialog::safeIconInformation()
{   
    if(leFromFile->text()!="")
    {
        resourceIdStr = leFromFile->text();
    }
    else
    {
        QModelIndex index = iconView->currentIndex();
        QStandardItem *item = model->itemFromIndex(index);
        int resourceId = item->data().toInt();    
        resourceIdStr = "shell32.dll,"+qvariant_cast<QString>(resourceId);
        //setIconName(resourceIdStr);
        emit iconSelected(resourceIdStr);
    }
    accept();
}

void IconDialog::enableSystemIcons()
{
    iconView->setEnabled(true);
    leFromFile->clear();
    leFromFile->setEnabled(false);
    pbFromFile->setEnabled(false);
}
    
void IconDialog::enableLineEdit()
{
    iconView->setEnabled(false);
    leFromFile->setEnabled(true);
    pbFromFile->setEnabled(true);
}

/**
*   \brief openFileDialog
*   @author Susanne Tschernegg
*/
void IconDialog::openFileDialog()
{
    QFileDialog *dialog = new QFileDialog();
    dialog->setFileMode(QFileDialog::ExistingFile);
    dialog->setViewMode(QFileDialog::List);
    QStringList fileList;
    QString file;    
    QDir dir;
    dir.setPath("C:/");
    dialog->setDirectory(dir);
    dialog->setReadOnly(true);
    
   int success = dialog->exec();
   if(success!=0)  // ! cancel
   {
        fileList = dialog->selectedFiles();
        if(!fileList.isEmpty())
        {
            file = fileList.at(0);
            leFromFile->setText(file);
        }
   }
}

