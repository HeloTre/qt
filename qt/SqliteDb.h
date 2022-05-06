#ifndef SQLITEDB_H
#define SQLITEDB_H

#include <vector>
#include <map>
#include <QString>
#include <QVariant>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QtXml/QDomDocument>
#include <QFile>
#include <QDir>
#include <map>
#include <QString>
#include <QTextCodec>
#include <QCoreApplication>


using namespace std;

class  SqliteDb
{
private:
	SqliteDb();

public:
	static SqliteDb *getInstance()
	{
		static SqliteDb *dbo = nullptr;
		if( !dbo )
		{
			dbo = new SqliteDb;
		}
		return dbo;
	}
	~SqliteDb();

	void SetName(QString &dbName);
	void* ConnectDB(QString DatabaseName);
	void DisConnectDB(void* handle);
	bool ExecuteSql(void* handle,vector<QString> sql);
	bool SelectSql(void* handle, QString sql, vector<map<QString,QVariant>> &val);
	bool SelectSqlEx(void* handle, QString sql, vector<vector<QVariant> > &val);
	QString GetLastError(){return m_LastError;};
	bool SelectSqlAc(void* handle,QStringList &tables);

	void SetBundlePath(QString path){m_BundlePath = path;};

private:
	QSqlDatabase* db;
	QString m_BundlePath;
	QString m_LastError;
	QString m_DBIP;
	QString m_DatabaseName;
	QString m_UserName;
	QString m_Password;
	QString m_Port;
};

#endif