//
// C++ Interface: logentry
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef LOGENTRY_H
#define LOGENTRY_H


#include <QDate>
#include <QVector>


#define ERR 1
#define INF 2
#define UPD 4
#define SET 8
class LogEntry;
class QTime;
typedef QVector <LogEntry*> LogEntryList;


/**
	@author Peter Grasch <bedahr@gmx.net>
*/
class LogEntry{
	
private:
	QTime time;
	QDate date;
	QString message;
	//todo
	int type;

public:
    LogEntry(QDate date, QTime time, QString message, int type);

    ~LogEntry();
//Set-Methoden
void setTime(QTime time) {this->time = time;}
void setDate(QDate date) {this->date = date;}
void setType(int type) {this->type = type;}
void setMessage(QString message) {this->message = message;}

//Get-Methoden
QDate getDate(){return this->date;}
QTime getTime(){return this->time;}
int getType(){return this->type;}
QString getMessage(){return this->message;}

};

#endif
