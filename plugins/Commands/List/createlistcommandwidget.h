/*
 *   Copyright (C) 2008 Peter Grasch <peter.grasch@bedahr.org>
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

#ifndef SIMON_CREATELISTCOMMANDWIDGET_H_EBCB1D84FCCB496290F4664A4759E20F
#define SIMON_CREATELISTCOMMANDWIDGET_H_EBCB1D84FCCB496290F4664A4759E20F

#include <QWidget>
#include <simonscenarios/createcommandwidget.h>
#include <simonscenarios/command.h>
#include "ui_createlistcommandwidget.h"

class Command;
class CommandTableModel;
class ImportProgramWizard;

/**
 *	@class CreateListCommandWidget
 *	@brief Provides a widget to modify the specific attributes of an ListCommand
 *
 *	@version 0.1
 *	@date 8.10.2008
 *	@author Peter Grasch
 */
class CreateListCommandWidget : public CreateCommandWidget
{
  Q_OBJECT

    private:
    CommandList allCommands;
    QList<Command*> commandsToDelete;
    Ui::CreateListCommandWidget ui;
    CommandTableModel *model;

  private slots:
    void addCommandToList();
    void removeCommand();
    void moveUp();
    void moveDown();
    void enableButtons(const QModelIndex& index);

  public:
    Command* createCommand(const QString& name, const QString& iconSrc, const QString& description);

    bool init(Command* command);
    bool isComplete();

    /**
     * @brief Constructor
     *
     *	@author Peter Grasch
     */
    explicit CreateListCommandWidget(CommandManager *manager, QWidget *parent=0);

    virtual ~CreateListCommandWidget();

};
#endif
