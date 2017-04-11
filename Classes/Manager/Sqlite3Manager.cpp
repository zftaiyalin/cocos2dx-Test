//
//  Sqlite3Manager.cpp
//  HelloWorldDemo
//
//  Created by 曾富田 on 2017/4/6.
//
//

#include "Sqlite3Manager.hpp"
#include "sqlite3.h"


//#include "Sample.h"

using namespace cocos2d;
using namespace std;

static GameSqlManager* m_instance = nullptr;
sqlite3* pdb = nullptr; // 创建sqlite数据库
int ret;         // 执行结果，SQLITE_OK表示成功执行

GameSqlManager::GameSqlManager()
{
    
}

GameSqlManager::~GameSqlManager()
{
    
}

GameSqlManager* GameSqlManager::getInstance()
{
    if (!m_instance) {
        m_instance = new GameSqlManager();
    }
    return m_instance;
}










// DBをオープン
sqlite3* GameSqlManager::openDB()
{
   
    _dbOpenTime = std::chrono::system_clock::now();
    
 
    std::string dbPath = FileUtils::getInstance()->getWritablePath() + DB_FILE_NAME_ENC;
    
    sqlite3 *db = nullptr;
    // DBファイルオープン
    auto status = sqlite3_open(dbPath.c_str(), &db);
    if(status != SQLITE_OK)
    {
        CCLOG("▼sqlite3_open failed.");
        return nullptr;
    }
    // 暗号化する
//    status = sqlite3_key(db, ENCRYPT_DB_PASSWORD, (int)strlen(ENCRYPT_DB_PASSWORD));
//    if(status != SQLITE_OK)
//    {
//        CCLOG("▼sqlite3_key failed.");
//        return nullptr;
//    }
    
    CCLOG("○DB opened successfully. File : %s",dbPath.c_str());
    
    return db;
}
// DBをオープンしてトランザクションをスタートする
sqlite3* GameSqlManager::openDBAndStartTransaction()
{
    sqlite3 *db = this->openDB();
    
    if(db)
    {
        // トランザクション開始
        auto status = sqlite3_exec(db, "BEGIN;", nullptr, nullptr, nullptr);
        if(status != SQLITE_OK)
        {
            CCLOG("▼Starting transaction failed.");
            return nullptr;
        }
    }
    
    return db;
}
// DBをクローズ
bool GameSqlManager::closeDB(sqlite3 *db)
{
    auto status = sqlite3_close(db);
    if(status != SQLITE_OK)
    {
        CCLOG("▼Closing DB failed.");
        return false;
    }
    
    auto duration = std::chrono::system_clock::now() - _dbOpenTime;
    CCLOG("○DB Closed. time : %dms.",(int)std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
    
    return true;
}
// トランザクションをコミットしてDBをクローズする
bool GameSqlManager::commitTransactionAndCloseDB(sqlite3 *db)
{
    // トランザクションコミット
    auto status = sqlite3_exec(db, "COMMIT;", nullptr, nullptr, nullptr);
    if(status != SQLITE_OK)
    {
        CCLOG("▼Commiting transaction failed.");
        return false;
    }
    
    return this->closeDB(db);
}

// テーブルを作成する
void GameSqlManager::createTable()
{
    // エラーメッセージ格納用
    char* errorMessage = NULL;
    
    sqlite3 *db = this->openDB();	// トランザクションなし接続にする
    int status;
    
    // SQLファイル読み込み
    std::string createDBSQL = FileUtils::getInstance()->getStringFromFile("res/createTable.sql");
    // テーブル作成
    status = sqlite3_exec(db,createDBSQL.c_str(),nullptr,nullptr,&errorMessage);
    if(status != SQLITE_OK)
    {
        cocos2d::log("▼Creating table failed. Message : %s",errorMessage);
        CCASSERT(false, errorMessage);
    }
    
    // DBファイルクローズ
    this->closeDB(db);
}

//// データを検索する

Map<std::string,ResourcesModel*> GameSqlManager::selectResourcesModelList()
{
    Map<std::string,ResourcesModel*> unitDataList;
    
    sqlite3 *db = this->openDB();
    
    // Select
    sqlite3_stmt *stmt = nullptr;
    auto selectSQL = "select id,name,num,isShow from ResourcesTable order by id desc";
    if(sqlite3_prepare_v2(db,selectSQL,-1,&stmt,nullptr) == SQLITE_OK)
    {
        while(sqlite3_step(stmt) == SQLITE_ROW)
        {
            ResourcesModel *unitData = ResourcesModel::create();
            unitData->setId((int)sqlite3_column_int(stmt, 0));
            unitData->setName(StringUtils::format("%s",sqlite3_column_text(stmt, 1)));
            unitData->setNum((int)sqlite3_column_int(stmt, 2));
            unitData->setIsShow(intToBool((int)sqlite3_column_int(stmt, 3)));
            
            unitDataList.insert(StringUtils::format("%d", unitData->getId()), unitData);
        }
    }
    else
    {
        CCASSERT(false,"Select UnitDataList error.");
    }
    
    // Statementをクローズ
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    
    this->closeDB(db);
    
    return unitDataList;
}





bool GameSqlManager::addOrUpdateResourcesDataInTable(ResourcesModel *model){

    
    sqlite3 *db = this->openDBAndStartTransaction();
    int status = 0;
    // エラーメッセージ格納用
    char* errorMessage = NULL;
    
    // InsertSQL
    auto insertSQL = sqlite3_mprintf("insert or replace into ResourcesTable(id,name,num,isShow) values(%d,%Q,%d,%d)",
                                     model->getId(),model->getName().c_str(),model->getNum(),boolToInt(model->getIsShow())
                                     );
    status = sqlite3_exec(db, insertSQL, nullptr, nullptr, &errorMessage);
    if(status != SQLITE_OK)
    {
        CCLOG("▼Inserting UnitData data failed. Message : %s",errorMessage);
        CCASSERT(false, errorMessage);
    }
    else
    {
        CCLOG("○UnitData data successfully updated. no : %d",model->getId());
    }
    
    // 解放（忘れてはいけない）
    sqlite3_free(insertSQL);
    
   return this->commitTransactionAndCloseDB(db);
}


bool GameSqlManager::addOrUpdateBuildDataInTable(BuildModel *model){
    sqlite3 *db = this->openDBAndStartTransaction();
    int status = 0;
    // エラーメッセージ格納用
    char* errorMessage = NULL;
//    std::string _name; // 建筑名称
//    int _productTime;  // 生产周期
//    int _id; // id
//    int _grade; //建筑等级
//    int _num; //建筑数量
//    int _productNum; //生产周期产量
//    bool _isMax; //是否可到达最大数量
//    bool _isShowMaxNum; //是否显示建筑最大开采量
//    bool _isShowNum; //是否显示建筑数量
//    bool _isShow;//是否展示在界面
//    int _,maxProduct;//建筑最大开采量
    // InsertSQL
    auto insertSQL = sqlite3_mprintf("insert or replace into BuildTable(id,name,num,isShow,isMax,isShowMaxNum,isShowNum,grade,productNum,productTime,maxProduct,productResId) values(%d,%Q,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)",
                                     model->getId(),model->getName().c_str(),model->getNum(),boolToInt(model->getIsShow()),boolToInt(model->getIsMax()),boolToInt(model->getisShowMaxNum()),boolToInt(model->getIsShowNum()),model->getGrade(),model->getProductNum(),model->getProductTime(),model->getMaxProduct(),model->getProductResId()
                                     );
    status = sqlite3_exec(db, insertSQL, nullptr, nullptr, &errorMessage);
    if(status != SQLITE_OK)
    {
        CCLOG("▼Inserting UnitData data failed. Message : %s",errorMessage);
        CCASSERT(false, errorMessage);
    }
    else
    {
        CCLOG("○UnitData data successfully updated. no : %d",model->getId());
    }
    
    // 解放（忘れてはいけない）
    sqlite3_free(insertSQL);
    
    return this->commitTransactionAndCloseDB(db);
    
}//添加或修改建筑到建筑表格


Map<std::string,BuildModel*> GameSqlManager::selectBuildModelList(){
    Map<std::string,BuildModel*> unitDataList;
    
    sqlite3 *db = this->openDB();
    
    // Select
    sqlite3_stmt *stmt = nullptr;
    auto selectSQL = "select id,name,num,isShow,isMax,isShowMaxNum,isShowNum,grade,productNum,productTime,maxProduct,productResId from BuildTable order by id desc";
    if(sqlite3_prepare_v2(db,selectSQL,-1,&stmt,nullptr) == SQLITE_OK)
    {
        while(sqlite3_step(stmt) == SQLITE_ROW)
        {
            BuildModel *unitData = BuildModel::create();
            unitData->setId((int)sqlite3_column_int(stmt, 0));
            unitData->setName(StringUtils::format("%s",sqlite3_column_text(stmt, 1)));
            unitData->setNum((int)sqlite3_column_int(stmt, 2));
            unitData->setIsShow(intToBool((int)sqlite3_column_int(stmt, 3)));
            unitData->setIsMax(intToBool((int)sqlite3_column_int(stmt, 4)));
            unitData->setIsShowMaxNum(intToBool((int)sqlite3_column_int(stmt, 5)));
            unitData->setIsShowNum(intToBool((int)sqlite3_column_int(stmt, 6)));
            unitData->setGrade((int)sqlite3_column_int(stmt, 7));
            unitData->setProductNum((int)sqlite3_column_int(stmt, 8));
            unitData->setProductTime((int)sqlite3_column_int(stmt, 9));
            unitData->setMaxProduct((int)sqlite3_column_int(stmt, 10));
            unitData->setProductResId((int)sqlite3_column_int(stmt, 11));
            
            unitDataList.insert(StringUtils::format("%d", unitData->getId()), unitData);
        }
    }
    else
    {
        CCASSERT(false,"Select UnitDataList error.");
    }
    
    // Statementをクローズ
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    
    this->closeDB(db);
    
    return unitDataList;
}


int GameSqlManager::boolToInt(bool bl){
    if (bl) {
        return 1;
    }else{
        return 0;
    }
}


bool GameSqlManager::intToBool(int i){
    if (i==1) {
        return true;
    }else{
        return false;
    }
}


