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

#include "promptsview.h"
#include "promptsviewprivate.h"
#include <QWidget>

PromptsView::PromptsView(QWidget *parent)
: KDialog(parent),
  d(new PromptsViewPrivate(this))
{
  QWidget *w = new QWidget(parent);
  QVBoxLayout *lay = new QVBoxLayout(w);
  lay->addWidget(d);
  setMainWidget(w);
  setButtons(KDialog::Ok);
  setWindowTitle(i18n("Training Samples"));
}
