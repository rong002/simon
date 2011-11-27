/*
 *   Copyright (C) 2011 Peter Grasch <grasch@simon-listens.org>
 *   Copyright (C) 2011 Adam Nash <adam.t.nash@gmail.com>
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

#include "dbuscondition.h"
#include <KDE/KDebug>
#include "createdbusconditionwidget.h"
#include <QWidget>
#include <QDBusInterface>
#include <QDBusConnection>

//could be made into proper methods if conditions are refactored to use the 
//qt property system to store configuration values (makes attributes 
//accessible by name)

#define deSerializeTextElem(tagName, elementName) \
    {QDomElement qElem = elem.firstChildElement(tagName); \
    if (qElem.isNull()) { \
        kDebug() << "No element " << tagName << " found!  Deserialization failure!"; \
        return false; \
    } \
    elementName = qElem.text();}
    
#define serializeTextElem(tagName, elementName) \
    {QDomElement pathElem = doc->createElement(tagName); \
    pathElem.appendChild(doc->createTextNode(elementName)); \
    elem.appendChild(pathElem);}

K_PLUGIN_FACTORY( DBusConditionPluginFactory,
registerPlugin< DBusCondition >();
)

K_EXPORT_PLUGIN( DBusConditionPluginFactory("simondbuscondition") )


DBusCondition::DBusCondition(QObject *parent, const QVariantList &args) :
    Condition(parent, args), m_connection(0)
{
  m_pluginName = "simondbusconditionplugin.desktop";
}

CreateConditionWidget* DBusCondition::getCreateConditionWidget(CompoundCondition *compoundCondition, QWidget* parent)
{
    return new CreateDBusConditionWidget(compoundCondition, parent);
}

QDomElement DBusCondition::privateSerialize(QDomDocument *doc, QDomElement elem)
{
    serializeTextElem("serviceName", m_serviceName);
    serializeTextElem("path", m_path);
    serializeTextElem("interface", m_interface);
    serializeTextElem("checkMethod", m_checkMethod);
    serializeTextElem("notificationSignal", m_notificationSignal);
    serializeTextElem("value", m_value);

    return elem;
}

QString DBusCondition::name()
{
    return i18n("Method '%1' of service '%2' %3 '%4'", m_checkMethod, m_serviceName, 
                (isInverted() ? i18n("does not evaluate to") : i18n("evaluates to")), m_value);
}

void DBusCondition::check()
{
    kDebug() << "Checking";
    QDBusMessage m = QDBusMessage::createMethodCall(m_serviceName, m_path,
                                                    m_interface, m_checkMethod);
    QList<QVariant> ret = QDBusConnection::sessionBus().call(m).arguments();
    
    bool newSatisfied = false;
    if (ret.length() == 1)
      newSatisfied = (ret.first().toString() == m_value);
    
    bool changed = (newSatisfied != m_satisfied);
    m_satisfied = newSatisfied;
    kDebug() << "Satisfied: " << m_satisfied;
    if (changed)
        emit conditionChanged();
}

bool DBusCondition::privateDeSerialize(QDomElement elem)
{
    deSerializeTextElem("serviceName", m_serviceName);
    deSerializeTextElem("path", m_path);
    deSerializeTextElem("interface", m_interface);
    deSerializeTextElem("checkMethod", m_checkMethod);
    deSerializeTextElem("notificationSignal", m_notificationSignal);
    deSerializeTextElem("value", m_value);
    
    delete m_connection;
    m_connection = new  QDBusInterface(m_serviceName, m_path, m_interface, QDBusConnection::sessionBus(), this);
    connect(m_connection, m_notificationSignal.toAscii(), this, SLOT(check()));
    
//     m_conn.connect(m_service, "", "org.a11y.atspi.Event.Object", "StateChanged", this, 
//                               SLOT(slotStateChanged(QString, int, int, QDBusVariant, QSpiObjectReference)));
    
    return true;
}