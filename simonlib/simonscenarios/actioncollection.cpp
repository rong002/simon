/*
 *   Copyright (C) 2009 Peter Grasch <peter.grasch@bedahr.org>
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

#include "actioncollection.h"
#include <KDebug>
#include <simonscenarios/action.h>
#include <simonscenarios/voiceinterfacecommand.h>
#include <simonscenarios/scenario.h>
#include <simonscenarios/createcommandwidget.h>
#include <simonscenarios/commandmanager.h>
#include <simonscenarios/actioncommandmodel.h>
#include "actioncommandmodel.h"

ActionCollection::ActionCollection(Scenario *parent) : ScenarioObject(parent)
{
  proxy = new ActionCommandModel(this);
}

/**
 * Factory function
 * \author Peter Grasch
 */
ActionCollection* ActionCollection::createActionCollection(Scenario *parent, const QDomElement& actionCollectionElem)
{
  ActionCollection *ac = new ActionCollection(parent);
  if (!ac->deSerialize(actionCollectionElem)) {
    ac->deleteLater();
    ac=0;
  }
  return ac;
}


bool ActionCollection::deSerialize(const QDomElement& actionCollectionElem)
{
  if (actionCollectionElem.isNull())
    return false;

  qDeleteAll(listInterfaceCommands);
  listInterfaceCommands.clear();

  QDomElement listsElement = actionCollectionElem.firstChildElement("lists");

  if (listsElement.isNull()) {
    QHash<CommandListElements::Element, VoiceInterfaceCommand*> baseConfig = ScenarioManager::getInstance()->
      getListBaseConfiguration();

    QHashIterator<CommandListElements::Element, VoiceInterfaceCommand*> i(baseConfig);
    while (i.hasNext()) {
      i.next();
      // i.value() is not a valid command
      listInterfaceCommands.insertMulti(i.key(), new VoiceInterfaceCommand(*(i.value())));
    }
  }
  else {
    QDomElement commandElem = listsElement.firstChildElement();

    while (!commandElem.isNull()) {
      VoiceInterfaceCommand *com = VoiceInterfaceCommand::createInstance(commandElem);

      int elementId = commandElem.attribute("element").toInt();

      commandElem = commandElem.nextSiblingElement("voiceInterfaceCommand");

      if (!com) continue;

      listInterfaceCommands.insert((CommandListElements::Element) elementId, com);
    }
  }

  QDomElement autorunElem = actionCollectionElem.firstChildElement("autorun");
  m_autorunActive = autorunElem.attribute("active") == "1";
  m_autorunCommand = autorunElem.firstChildElement("trigger").text();
  m_autorunType = autorunElem.firstChildElement("category").text();

  //clean member
  qDeleteAll(m_actions);
  m_actions.clear();

  QDomElement pluginElem = actionCollectionElem.firstChildElement("plugin");
  while (!pluginElem.isNull()) {
    Action *a = Action::createAction(parentScenario, pluginElem, this);
    if (!a) {
      kDebug() << "Could not load action";
    }
    else {
      //m_actions << a;
      appendAction(a, true /*silent*/);
    }

    pluginElem = pluginElem.nextSiblingElement("plugin");
  }
  proxy->update();
  reset();

  if (m_autorunActive)
  {
    bool succ = triggerCommand(m_autorunType, m_autorunCommand, true /* silent */);
    kDebug() << "Executed autorun command; Success: " << succ;
  }

  return true;
}


QDomElement ActionCollection::createEmpty(QDomDocument *doc)
{
  return doc->createElement("actions");
}


QDomElement ActionCollection::serialize(QDomDocument *doc)
{
  QDomElement actionsElem = createEmpty(doc);

  QDomElement autorunElem = doc->createElement("autorun");
  autorunElem.setAttribute("active", m_autorunActive ? "1" : "0");
  QDomElement autorunCommandElem = doc->createElement("trigger");
  autorunCommandElem.appendChild(doc->createTextNode(m_autorunCommand));
  QDomElement autorunCategoryElem = doc->createElement("category");
  autorunCategoryElem.appendChild(doc->createTextNode(m_autorunType));
  autorunElem.appendChild(autorunCommandElem);
  autorunElem.appendChild(autorunCategoryElem);
  actionsElem.appendChild(autorunElem);

  QDomElement listInterfaceCommandsElem = doc->createElement("lists");

  QHashIterator<CommandListElements::Element, VoiceInterfaceCommand*> i(listInterfaceCommands);
  while (i.hasNext()) {
    i.next();
    QDomElement commandElem = i.value()->serialize(doc);
    commandElem.setTagName("voiceInterfaceCommand");
    commandElem.setAttribute("element", QString::number((int) i.key()));
    listInterfaceCommandsElem.appendChild(commandElem);
  }

  actionsElem.appendChild(listInterfaceCommandsElem);

  foreach (Action *a, m_actions) {
    actionsElem.appendChild(a->serialize(doc));
  }
  proxy->update();
  return actionsElem;
}


QList<CreateCommandWidget*> ActionCollection::getCreateCommandWidgets(QWidget *parent)
{
  QList<CreateCommandWidget*> out;

  foreach (Action* action, m_actions) {
    CreateCommandWidget* widget = (CreateCommandWidget*) action->manager()->getCreateCommandWidget(parent);
    if (widget)
      out << widget;

    CreateCommandWidget* voiceWidget = (CreateCommandWidget*) action->manager()->getCreateVoiceInterfaceCommandWidget(parent);
    if (voiceWidget)
      out << voiceWidget;
  }
  return out;
}


QList<CommandConfiguration*> ActionCollection::getConfigurationPages()
{
  QList<CommandConfiguration*> configs;
  foreach (Action* a, m_actions) {
    CommandConfiguration *cm = a->getConfigurationPage();
    if (cm)
      configs.append(cm);
  }
  return configs;
}


QList<QAction*> ActionCollection::getGuiActions()
{
  QList<QAction*> guiActions;
  foreach (Action* a, m_actions) {
    guiActions << a->manager()->getGuiActions();
  }
  return guiActions;
}


/*bool ActionCollection::addCommand(Command *command)
{
  if (!command) return false;

  int i=0;
  bool added=false;
  while (!added && (i< m_actions.count())) {
    CommandManager *man = m_actions.at(i)->manager();
    added = man->addCommand(command);
    i++;
  }

proxy->update();
return added;
}*/

bool ActionCollection::removeCommand(Command *command)
{
  bool removed=false;
  foreach (Action *a, m_actions) {
    if (a->removeCommand(command)) {
      removed = true;
      break;
    }
  }
  proxy->update();
  return removed;
}

bool ActionCollection::setAutorun(bool active, const QString& type, const QString& trigger)
{
  m_autorunActive = active;
  m_autorunType = type;
  m_autorunCommand = trigger;
  return true;
}

bool ActionCollection::autorunActive()
{
  return m_autorunActive;
}

QString ActionCollection::autorunType()
{
  return m_autorunType;
}

QString ActionCollection::autorunTrigger()
{
  return m_autorunCommand;
}


bool ActionCollection::addAction(Action *action, bool silent, bool save)
{
  action->assignParent(parentScenario);
  action->deSerialize(QDomElement());

  appendAction(action, silent);

  bool succ = (save) ? parentScenario->save() : true;
  proxy->update();
  return succ;
}


bool ActionCollection::deleteAction(Action *action)
{
  for (int i=0; i <m_actions.count(); i++) {
    if (m_actions[i] == action) {
      beginRemoveRows(QModelIndex(), i, i);
      m_actions.takeAt(i);
      endRemoveRows();
    }
  }

  bool succ = parentScenario->save();

  proxy->update();

  if (action)
    action->deleteLater();

  return succ;
}


QHash<CommandListElements::Element, VoiceInterfaceCommand*> ActionCollection::getListInterfaceCommands()
{
  return listInterfaceCommands;
}


void ActionCollection::setListInterfaceCommands(QHash<CommandListElements::Element, VoiceInterfaceCommand*> commands)
{
  listInterfaceCommands = commands;
}


bool ActionCollection::moveActionUp(Action *action)
{
  bool moved = false;

  for (int i=1; i <m_actions.count(); i++) {
    if (m_actions[i] == action) {
      m_actions.takeAt(i);
      m_actions.insert(i-1, action);
      emit dataChanged(index(i-1, 0),
        index(i, columnCount()));
      moved = true;
      break;
    }
  }
  proxy->update();

  return moved;
}


bool ActionCollection::moveActionDown(Action *action)
{
  bool moved = false;

  for (int i=0; i <m_actions.count()-1; i++) {
    if (m_actions[i] == action) {
      m_actions.takeAt(i);
      m_actions.insert(i+1, action);
      emit dataChanged(index(i, 0),
        index(i+1, columnCount()));
      moved = true;
      break;
    }
  }
  proxy->update();

  return moved;
}


bool ActionCollection::processResult(RecognitionResult recognitionResult)
{
  int i=0;
  bool commandFound=false;
  QString currentTrigger;
  QString realCommand;

  while ((i<m_actions.count()) && (!commandFound)) {
    currentTrigger = m_actions[i]->trigger();
    RecognitionResult tempResult = recognitionResult;
    if (tempResult.matchesTrigger(currentTrigger)) {
      tempResult.removeTrigger(currentTrigger);

      if(m_actions.at(i)->manager()->processResult(tempResult))
        commandFound=true;
    }
    i++;
  }

  return commandFound;
}


bool ActionCollection::triggerCommand(const QString& type, const QString& trigger, bool silent)
{
  foreach (Action *a, m_actions)
    if (a->manager()->name() == type)
    return a->manager()->trigger(trigger, silent);

  return false;
}


bool ActionCollection::setTrigger(const QString& trigger)
{
  bool success = true;
  parentScenario->startGroup();
  foreach (Action *a, m_actions)
    success = a->setTrigger(trigger) && success;
  parentScenario->commitGroup();

  return success;
}


CommandList ActionCollection::getCommandList()
{
  CommandList commandList;
  foreach (Action *a, m_actions) {
      commandList.append(a->manager()->getCommands());
  }
  return commandList;
}


void ActionCollection::setPluginFont(const QFont& font)
{
  foreach (Action *a, m_actions)
    a->setPluginFont(font);
}


ActionCollection::~ActionCollection()
{
  finalizeActions();
  delete proxy;
  qDeleteAll(listInterfaceCommands);
}
