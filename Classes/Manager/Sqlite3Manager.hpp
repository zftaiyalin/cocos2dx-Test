//
//  Sqlite3Manager.hpp
//  HelloWorldDemo
//
//  Created by 曾富田 on 2017/4/6.
//
//

#ifndef Sqlite3Manager_hpp
#define Sqlite3Manager_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "BuildModel.hpp"
#include "ResourcesModel.hpp"
#include "sqlite3.h"

#define RESCOURSETABLE "ResourcesTable"
#define BUILDTABLE "BuildTable"

#define DB_FILE_NAME "game.sqlite"

#define DB_FILE_NAME_ENC "EncryptedDB.db"	// 数据库名称
#define ENCRYPT_DB_PASSWORD "23da3i3kJLale"	// 数据库访问密码




class GameSqlManager
{
public:
    GameSqlManager();
    ~GameSqlManager();
    static GameSqlManager* getInstance();


    
    sqlite3* openDB();
    sqlite3* openDBAndStartTransaction();
    bool closeDB(sqlite3 *db);
    bool commitTransactionAndCloseDB(sqlite3 *db);
    
    void createTable();//创建资源数据库
    
    
    bool addOrUpdateResourcesDataInTable(ResourcesModel *model);//添加或修改资源到资源表格
//    bool updateResourcesDataInTable(ResourcesModel *model);//修改资源表格资源
    
    bool addOrUpdateBuildDataInTable(BuildModel *model);//添加或修改建筑到建筑表格
//    bool updateBuildDataInTable(BuildModel *model);//修改建筑表格资源
    
    cocos2d::Map<std::string,ResourcesModel*> selectResourcesModelList();
    cocos2d::Map<std::string,BuildModel*> selectBuildModelList();
    
    void selectTest();
protected:
    
private:
    int boolToInt(bool bl);
    bool intToBool(int i);
    std::string getDbPath();
    std::chrono::system_clock::time_point _dbOpenTime;//时间要记住，当你打开一个数据库文件（处理时间测量）
    
    
};


#endif /* Sqlite3Manager_hpp */
