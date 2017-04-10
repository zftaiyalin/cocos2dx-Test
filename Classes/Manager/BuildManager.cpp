//
//  BuildManager.cpp
//  HelloWorldDemo
//
//  Created by 曾富田 on 2017/4/6.
//
//

#include "BuildManager.hpp"


BuildManager::~BuildManager()
{
}

BuildManager::BuildManager()
{
}

BuildManager* BuildManager::getInstance()
{
    if (! _buildManager)
    {
//#ifdef KEEP_COMPATABILITY
//        initXMLFilePath();
//#endif
        _buildManager = new (std::nothrow) BuildManager();
    }
    
    return _buildManager;
}


void BuildManager::loadBuildData()
{
    
    
    //    bool isLoadJson = cocos2d::UserDefault::getInstance()->getBoolForKey("isLoadRes");
    //
    //    if (!isLoadJson) {
    
    //        GameSqlManager->getInstance()::createResTable();
    
    auto sqlManager = GameSqlManager::getInstance();
    sqlManager->createTable();
    
    cocos2d::UserDefault::getInstance()->setBoolForKey("isLoadRes", true);
    
    //读取JSON配置数据，建立表格数据，把数据存入数据库
    rapidjson::Document document;
    
    std::string filePath = cocos2d::FileUtils::getInstance()->fullPathForFilename(cocos2d::StringUtils::format("game.json"));
    std::string contentStr = cocos2d::FileUtils::getInstance()->getStringFromFile(filePath);
    document.Parse<0>(contentStr.c_str());
    
    //获取资源数据
    const rapidjson::Value& resArray = document["builds"];
    
    for (int i = 0; i<resArray.Size(); i++) {
        

        int id = resArray[i]["id"].GetInt();
        std::string name = resArray[i]["name"].GetString();
        int num = resArray[i]["num"].GetInt();
        bool isShow = resArray[i]["isShow"].GetBool();
        int productNum = resArray[i]["productNum"].GetInt();
        bool isShowMaxNum = resArray[i]["isShowMaxNum"].GetBool();
        bool isShowNum = resArray[i]["isShowNum"].GetBool();
        bool isMax = resArray[i]["isMax"].GetBool();
        int productTime = resArray[i]["productTime"].GetInt();
        int grade = resArray[i]["grade"].GetInt();
        
        auto res = BuildModel::create();
        res->setId(id);
        res->setNum(num);
        res->setName(name);
        res->setIsShow(isShow);
        res->setIsMax(isMax);
        res->setIsShowNum(isShowNum);
        res->setIsShowMaxNum(isShowMaxNum);
        res->setProductNum(productNum);
        res->setProductTime(productTime);
        res->setGrade(grade);
        //            resVec.pushBack(res);
        sqlManager->addOrUpdateBuildDataInTable(res);
    }
    
    buildVec = sqlManager->selectBuildModelList();
    
    
    
    //    }else{
    //        //直接读取数据库数据
    //    }
}
