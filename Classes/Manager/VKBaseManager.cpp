//
//  VKBaseManager.cpp
//  SqliteSample
//
//  Created by Kasajima Yasuo on 2013/01/26.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#include "VKBaseManager.h"


using namespace cocos2d;
using namespace std;


bool VKBaseManager::init(){
    if (!checkTable()) {
        if(createTable()){
            runAfterCreateTableOnce();
        }else{
        }
    }
    return true;
}



VKBaseManager::VKBaseManager()
{
}

VKBaseManager::~VKBaseManager()
{
}

bool VKBaseManager::connectDB(){
    // setting to database's path
    std::string dbPath = FileUtils::getInstance()->getWritablePath();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    dbPath.append("databases/");
#endif
    dbPath.append(dbFileName);
    
    //  get database's connection
    int result = sqlite3_open(dbPath.c_str(),&pDB);
    if (result != SQLITE_OK){
        CCLOG("OPENING WRONG, %d, MSG:%s",result);
        return false;
    }else{
        return true;
    }
}

void VKBaseManager::closeDB(){
    sqlite3_close(pDB);
}

bool VKBaseManager::sqlExec(const char *sql, int (*callback)(void *, int, char **, char**)){
    if (!connectDB()) { // connect to database
        return false; // failure to connect database
    }
    
    CCLOG("sqlExec %s",sql);
    char* errMsg = NULL;
    int result = sqlite3_exec( pDB, sql ,callback, NULL, &errMsg );
    
    if(result != SQLITE_OK ){
        CCLOG( "Failure　:%d ，becouse :%s\n" , result, errMsg );
        closeDB();
        return false;
    }else{
        closeDB();
        return true;
    }
    
    
}


cocos2d::Vector<cocos2d::Map<std::string, std::string>> VKBaseManager::sqlPrepare(const char *sql){
    Vector<cocos2d::Map<std::string, std::string>> resultArray;
    
    if (!connectDB()) {
        return resultArray;
    }
    
    CCLOG("sqlPrepare %s",sql);
    sqlite3_stmt *stmt = NULL;
    if(sqlite3_prepare_v2(pDB, sql, -1, &stmt, NULL) == SQLITE_OK){
        while (sqlite3_step(stmt) == SQLITE_ROW) {
//            CCDictionary *dic = CCDictionary::create();
            Map<__String, char> dic;
            int columnNum = sqlite3_column_count(stmt);
            for (int i = 0; i < columnNum; i++) {
                const char* text =  (const char*)sqlite3_column_text(stmt, i);
                if (!text) text = ""; // if column is null , text set "".
                __String* string = __String::create(text);
                const char *key = sqlite3_column_name(stmt, i);
//                dic->setObject(string, key);
                dic.inster(key,string);
            }
            resultArray.pushBack(dic);
        }
    }else{
        CCLOG("not SQLLITE_OK");
    }
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    
    closeDB();
    return resultArray;
}




bool VKBaseManager::checkTable(){
    __String *string = __String::createWithFormat("SELECT count(*) FROM sqlite_master WHERE type='table' AND name='%s'",tableName.c_str());
    cocos2d::Vector<cocos2d::Map<std::string, std::string>> array = sqlPrepare(string -> getCString());
    if (array.size()) {
        cocos2d::Map<std::string, std::string> dic = array.at(0);
        std::string countString = dic.at("count(*)");
        __String *string = __String::createWithFormat("%s", countString.c_str());
        return string->intValue();
    }else{
        return false;
    }
    
}




bool VKBaseManager::createTable(){
    return true;
}

bool VKBaseManager::createTableWithTableSetting(const char *tableSetting){
    __String *sqlString = __String::createWithFormat("create table %s ( %s integer primary key autoincrement, %s )", tableName.c_str(),idKey, tableSetting);
    if(sqlExec(sqlString -> getCString())){
        return addColumn();
    }
}

bool VKBaseManager::addColumn(){
    return true;
}

bool VKBaseManager::addColumnWithArray(CCArray *columnAry){
    Ref *string;
    CCARRAY_FOREACH(columnAry, string){
        __String *sqlString = __String::createWithFormat("alter table %s add column %s", tableName.c_str(), ((__String *)string)->getCString());
        sqlExec(sqlString -> getCString());
    }
    return true;
}

bool VKBaseManager::deleteTable(){
    __String *string = __String::createWithFormat("DROP TABLE '%s'",tableName.c_str());
    CCLog("%s", string->getCString());
    return sqlExec(string->getCString());
}

bool VKBaseManager::runAfterCreateTableOnce(){
    return true;
}

bool VKBaseManager::runSQLFile(const char *fileName){
    // setting to database's path
    std::string copyDbPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
//    unsigned long fileSize = 0;
    ssize_t scount;
    unsigned char *fileContents = CCFileUtils::sharedFileUtils()->getFileData(copyDbPath.c_str(), "r", &scount);
    istringstream fileStringStream( (char *)fileContents );
    
    string thisLine;
    while (getline(fileStringStream, thisLine)) {
        if(thisLine.find(";") != -1){ // if thisLine has not ';' , it be skipped.
            sqlExec(thisLine.c_str());
        }
    }
    
    if (fileContents) {
        delete [] fileContents;
        fileContents = NULL;
    }
    
    return true;
}


VKBaseEntity* VKBaseManager::save(VKBaseEntity *entity)
{
    if (entity == NULL) {
        return NULL;
    }
    // Frist, try to save entity.
    DictElement *element = NULL;
    __String *keys = __String::create("");
    __String *values = __String::create("");
    __String *updates = __String::create("");
    CCDICT_FOREACH(entity, element){
        if (keys -> isEqual(__String::create(""))) {
            keys = __String::createWithFormat("%s",element->getStrKey());
        }else{
            keys = __String::createWithFormat("%s, %s",keys->getCString(), element->getStrKey());
        }
        
        __String *value = (__String *)element -> getObject();
        if (values -> isEqual(__String::create(""))) {
            values = __String::createWithFormat("'%s'",value->getCString());
        }else{
            values = __String::createWithFormat("%s, '%s'", values->getCString(), value->getCString());
        }
        
        if (updates -> isEqual(__String::create(""))) {
            updates = __String::createWithFormat(" %s = '%s' ", element->getStrKey(), value->getCString());
        }else{
            updates = __String::createWithFormat("%s, %s = '%s' ", updates->getCString(), element->getStrKey(), value->getCString());
        }
    }
    __String *insertString = __String::createWithFormat("insert into %s ( %s ) values ( %s ) ", tableName.c_str(), keys->getCString(), values->getCString());
    
    bool result  = sqlExec(insertString->getCString());

    // if entity cannot save, this entity should be saved or has properties more than old entity's definition.
    if (!result) {
        if (entity->getId()) { // if entity has id, this entity already exist, so this entity should be saved
            __String *updateString = __String::createWithFormat("update %s set %s where id = %d",tableName.c_str(), updates->getCString(), entity->getId());
            result = sqlExec(updateString->getCString());
        }else{
            addColumn(); // change table
            save(entity); // Re-save entity
        }
    }else{
        cocos2d::Vector<cocos2d::Map<std::string, std::string>> array = selectWithEntity(entity);
        entity = (VKBaseEntity *)array.back();
    }
    return entity;
    
}


__String* VKBaseManager::createWhereFromEntity(VKBaseEntity *entity){
    if (entity == NULL) {
        return NULL;
    }
    DictElement *element = NULL;
    __String *where = __String::create("");
    CCDICT_FOREACH(entity, element){
        if (where -> isEqual(__String::create(""))) {
            __String *value = (__String *)element -> getObject();
            where = __String::createWithFormat(" %s = '%s' ",element->getStrKey(),value->getCString());
        }else{
            __String *value = (__String *)element -> getObject();
            where = __String::createWithFormat(" %s AND %s = '%s' ",where->getCString(), element->getStrKey(), value->getCString());
        }
    }
    return where;
}


cocos2d::Vector<cocos2d::Map<std::string, std::string>> VKBaseManager::selectWithEntity(VKBaseEntity *entity)
{
    return selectWithWhere(createWhereFromEntity(entity)->getCString());
}

cocos2d::Vector<cocos2d::Map<std::string, std::string>> VKBaseManager::selectAll(){
    __String *sqlString = __String::createWithFormat("select * from %s", tableName.c_str());
    return sqlPrepare(sqlString -> getCString());
}


cocos2d::Vector<cocos2d::Map<std::string, std::string>> VKBaseManager::selectWithWhere(const char *where)
{
    __String *sqlString = __String::createWithFormat("select * from %s where %s ", tableName.c_str(), where);
    return sqlPrepare(sqlString->getCString());
    
}


bool VKBaseManager::deleteWithEntity(VKBaseEntity *entity){
    return deleteWithWhere(createWhereFromEntity(entity)->getCString());
}

bool VKBaseManager::deleteAll(){
    __String *sqlString = __String::createWithFormat("delete from %s", tableName.c_str());
    return sqlExec(sqlString->getCString());
}

bool VKBaseManager::deleteWithWhere(const char *where){
    __String *sqlString = __String::createWithFormat("delete from %s where %s", tableName.c_str(), where);
    return sqlExec(sqlString->getCString());
}




