//
//  VKBaseManager.h
//  SqliteSample
//
//  Created by Kasajima Yasuo on 2013/01/26.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef SqliteSample_VKBaseManager_
#define SqliteSample_VKBaseManager_

#include "cocos2d.h"
#include "sqlite3.h"
#include "VKBaseEntity.h"

class VKBaseManager : public cocos2d::Ref
{

public:
    virtual bool init();
	VKBaseManager();
	virtual ~VKBaseManager();
    bool connectDB();
    bool sqlExec(const char *sql, int (*callback)(void *, int, char **, char**) = NULL);
    cocos2d::Vector<cocos2d::Map<std::string, std::string>> sqlPrepare(const char *sql);
    bool runSQLFile(const char *fileName);
    void closeDB();
    CREATE_FUNC(VKBaseManager);
    
protected:
    const char* dbFileName = "myGame.db";
//    const char* tableName = "";
    std::string tableName;
    sqlite3 *pDB = NULL;
    
private:
    bool checkTable();
    
public: // protocol
    virtual bool createTable();
    virtual bool addColumn();
    virtual bool runAfterCreateTableOnce();
    bool deleteTable();
    
public:
    cocos2d::__String* createWhereFromEntity(VKBaseEntity *entity);
    VKBaseEntity* save(VKBaseEntity *entity);
    cocos2d::Vector<cocos2d::Map<std::string, std::string>> selectWithEntity(VKBaseEntity *entity);
    cocos2d::Vector<cocos2d::Map<std::string, std::string>> selectAll();
    cocos2d::Vector<cocos2d::Map<std::string, std::string>> selectWithWhere(const char *where);
    bool deleteWithEntity(VKBaseEntity *entity);
    bool deleteAll();
    bool deleteWithWhere(const char *where);
    void setTableName(std::string name){ tableName = name; }
    std::string getTableName(){ return tableName; }
    
protected:
    bool createTableWithTableSetting(const char *tableSetting);
    bool addColumnWithArray(cocos2d::CCArray *columnAry);
};



#endif
