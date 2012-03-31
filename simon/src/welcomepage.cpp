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


#include "welcomepage.h"
#include "version.h"

#include <simonscenarioui/scenariomanagementdialog.h>
#include <simonscenarios/scenariomanager.h>
#include <simonscenarios/scenario.h>

#include <KDebug>
#include <KLocalizedString>
#include <KCMultiDialog>
#include <KColorScheme>
#include <KMessageBox>

WelcomePage::WelcomePage(QWidget* parent) : InlineWidget(i18n("Welcome"), KIcon("simon"), i18n("Welcome to Simon"), parent)
{
  ui.setupUi(this);
  ui.lbWelcome->setText(i18nc("%1: simon version", "Welcome to simon %1", simon_version));
  
  ui.wgVolumeWidget->enablePrompt(false);
  ui.wgVolumeWidget->init();

  connect(ScenarioManager::getInstance(), SIGNAL(scenarioSelectionChanged()), this, SLOT(displayScenarios()));
  connect(ScenarioManager::getInstance(), SIGNAL(deactivatedScenarioListChanged()), this, SLOT(displayScenarios()));
  
  connect(ui.pbScenarioConfiguration, SIGNAL(clicked()), this, SLOT(scenarioConfig()));
  connect(ui.pbAcousticConfiguration, SIGNAL(clicked()), this, SLOT(baseModelConfig()));
  connect(ui.pbAudioConfiguration, SIGNAL(clicked()), this, SLOT(audioConfig()));
  
  connect(ui.lwScenarios, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(updateScenarioDisplays()));
  
  displayScenarios();
  displayAcousticModelInfo();
}

void WelcomePage::displayAcousticModelInfo()
{
  //TODO
  ui.lbBaseModelDescription->setText(/*i18n(*/"I have no idea what kind of model you are using but if I did, I'd display it here.")/*)*/;
}

QString WelcomePage::getCurrentlySelectedScenarioId()
{
  if (ui.lwScenarios->currentItem())
    return ui.lwScenarios->currentItem()->data(Qt::UserRole).toString();
  
  return QString();
}

void WelcomePage::displayScenarios()
{
  kDebug() << "Displaying scenarios";
  setUpdatesEnabled(false);
  
  QString currentData = getCurrentlySelectedScenarioId();

  QFont deactivatedFont = QFont();
  deactivatedFont.setItalic(true);
  QBrush deactivatedColor = KColorScheme(QPalette::Active).foreground(KColorScheme::InactiveText);

  QListWidgetItem *toSelect = 0;
  QList<Scenario*> scenarioList = ScenarioManager::getInstance()->getScenarios();
  foreach (Scenario* s, scenarioList) {
    QListWidgetItem *i = new QListWidgetItem(s->icon(), s->name());
    i->setData(Qt::UserRole, s->id());
    
    if (!s->isActive()) {
      i->setFont(deactivatedFont);
      i->setForeground(deactivatedColor);
    }
    ui.lwScenarios->addItem(i);
    
    if (s->id() == currentData)
      toSelect = i;
  }
  
  if (toSelect)
    ui.lwScenarios->setCurrentItem(toSelect);
  
  setUpdatesEnabled(true);
}

void WelcomePage::updateScenarioDisplays()
{
  QString currentId = getCurrentlySelectedScenarioId();
  Scenario *scenario = ScenarioManager::getInstance()->getScenario(currentId);

  kDebug() << "Scenario " << scenario;
  if (!scenario) {
    KMessageBox::error(this, i18nc("%1 is scenario id", "Could not retrieve Scenario \"%1\"", currentId));
    return;
  }
  ScenarioManager::getInstance()->updateDisplays(scenario, true);
}

void WelcomePage::displayScenarioPrivate ( Scenario* scenario )
{
  QListWidgetItem *item;
  int currentRow = 0;
  while ((item = ui.lwScenarios->item(currentRow++)) != 0) {
    if (item->data(Qt::UserRole) == scenario->id()) {
      ui.lwScenarios->setCurrentItem(item);
      break;
    }
  }
  
  ui.pbEditScenario->setText(i18nc("%1 is the item to change", "Edit \"%1\"", scenario->name()));
}

void WelcomePage::showEvent(QShowEvent* event)
{
  QWidget::showEvent(event);
  kDebug() << "Shown";
  ui.wgVolumeWidget->start();
}

void WelcomePage::hideEvent(QHideEvent* event)
{
  QWidget::hideEvent(event);
  kDebug() << "Hidden";
  ui.wgVolumeWidget->stop();
}

void WelcomePage::audioConfig()
{
  KCMultiDialog configDialog(this);
  configDialog.addModule("simonsoundconfig");
  configDialog.exec();
}

void WelcomePage::baseModelConfig()
{
  KCMultiDialog configDialog(this);
  configDialog.addModule("simonspeechmodelmanagementconfig");
  configDialog.exec();
}

void WelcomePage::scenarioConfig()
{
  ScenarioManagementDialog *dlg = new ScenarioManagementDialog("simon/", this);
  if (dlg->updateScenarioConfiguration())
  {
    //reload scenario information
    kDebug() << "Reloading Scenario Information";

    if (!ScenarioManager::getInstance()->setupScenarios(true /* force change */))
      KMessageBox::sorry(this, i18n("Could not re-initialize scenarios. Please restart simon!"));

    displayScenarios();
    //FIXME:
//     updateScenarioDisplays();
  }
  dlg->deleteLater();
}
