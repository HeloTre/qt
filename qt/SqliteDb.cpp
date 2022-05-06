#include "SqliteDb.h"


SqliteDb::SqliteDb()
{
	//QTextCodec::setCodecForTr(QTextCodec::codecForName("Unicode"));
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("Unicode"));
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Unicode"));
}

SqliteDb::~SqliteDb()
{
	delete db;
}
void SqliteDb::SetName(QString &dbName) {
	if (dbName.contains(".db", Qt::CaseInsensitive)) {
		dbName = "//" + dbName;
	}else {
		dbName = "//" + dbName + ".db"; 
	}
	dbName =  QCoreApplication::applicationDirPath() + dbName;
}

void* SqliteDb::ConnectDB (QString DatabaseName)
{
	bool isHaveDriver = false;
	QStringList drig = QSqlDatabase::drivers();
	for (QStringList::iterator iter = drig.begin(); iter != drig.end(); iter++)
	{
		if (*iter == "QSQLITE")
		{ 
			isHaveDriver = true;
			break;
		}
	}

	if(!isHaveDriver)
	{
		m_LastError = "û��SQLITE������";
		return false;
	}
	//GetDBinfo();

	//db->setHostName(DBIP);
	//db->setUserName(UserName);
	//db->setPassword(Password);
	//db->setPort(Port);
	SetName(DatabaseName);
	if (QSqlDatabase::contains("qt_sql_default_connection")) { 
		db = new QSqlDatabase(QSqlDatabase::database("qt_sql_default_connection")); 
	} else { 
		db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));  
		db->setDatabaseName(DatabaseName);
	}
	if (db->open())
	{
		return (void*)db;
	}
	else
	{
		QSqlError er = db->lastError();
		m_LastError = er.text();
		delete db;
		db = nullptr;
	}
	return nullptr;
}


void SqliteDb::DisConnectDB (void* handle)
{
	if (handle != nullptr)
	{
		QSqlDatabase* db = (QSqlDatabase*)handle;
		db->close();
		delete db;
		db = nullptr;
	}
}

bool SqliteDb::ExecuteSql( void* handle,vector<QString> sql )
{
	if (handle != nullptr)
	{
		QSqlDatabase* db = (QSqlDatabase*)handle;
		QSqlQuery transOper(*db);
		if (!transOper.exec("begin"))
		{
			m_LastError = "���￪��ʧ��";
			return false;
		}
		for (vector<QString>::iterator iter = sql.begin(); iter != sql.end(); ++iter)
		{
			QSqlQuery query(*db);
			query.prepare(*iter);
			if (!query.exec())
			{
				QString errstr = "SQL���ִ��ʧ�ܣ�������ʾ��";
				errstr += query.lastError().databaseText();
				errstr += "ִ�лع�����";
				if (!transOper.exec("ROLLBACK"))
				{
					errstr += "����ع�ʧ�ܣ�";
				}
				m_LastError = errstr;
				return false;
			}
		}
		if (!transOper.exec("COMMIT"))
		{
			m_LastError = "�����ύʧ��";
			return false;
		}
		return true;
	}
	return false;
}

bool SqliteDb::SelectSql( void* handle, QString sql, vector<map<QString,QVariant>> &val )
{
	if (handle != nullptr)
	{
		QSqlDatabase* db = (QSqlDatabase*)handle;
		QSqlQuery query = db->exec(sql);

		QSqlRecord myrecordtt = query.record();
		int zduff = myrecordtt.count();//��¼�����ֶ���

		while(query.next())
		{
			int coun = query.size();//���м�¼��
			QSqlRecord myrecord = query.record();
			map<QString,QVariant> colval;

			int zdu = myrecord.count();//��¼�����ֶ���
			for (int i = 0; i < zdu; ++i)
			{
				colval.insert(make_pair(myrecord.fieldName(i),myrecord.value(i)));
				//colval.push_back(myrecord.value(i));
			}
			val.push_back(colval);
		}
		return true;
	}
	return false;
}

bool SqliteDb::SelectSqlEx (void* handle, QString sql, vector<vector<QVariant>> &val)
{
	if (handle != nullptr)
	{
		QSqlDatabase* db = (QSqlDatabase*)handle;
		QSqlQuery query = db->exec(sql);
		while(query.next())
		{
			int coun = query.size();//���м�¼��
			QSqlRecord myrecord = query.record();
			vector<QVariant> colval;

			int zdu = myrecord.count();//��¼�����ֶ���
			for (int i = 0; i < zdu; ++i)
			{
				colval.push_back(myrecord.value(i));
			}
			val.push_back(colval);
		}
	}
	return true;
}

bool SqliteDb::SelectSqlAc (void*handle,QStringList &tables)
{
	if(handle != nullptr)
	{
		QSqlDatabase* db = (QSqlDatabase*)handle;
		tables = db->tables(QSql::Tables);
	}
	return true;
}