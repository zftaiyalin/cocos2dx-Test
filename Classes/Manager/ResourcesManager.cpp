//
//  ResourcesManager.cpp
//  HelloWorldDemo
//
//  Created by 曾富田 on 2017/4/6.
//
//

#include "ResourcesManager.hpp"

static ResourcesManager* m_instance = nullptr;

ResourcesManager::~ResourcesManager()
{
}

ResourcesManager::ResourcesManager()
{
}

ResourcesManager* ResourcesManager::getInstance()
{
    if (! m_instance)
    {
        m_instance = new (std::nothrow) ResourcesManager();
    }

    return m_instance;
}

void ResourcesManager::createResTable(){
    
    
    
}

void ResourcesManager::loadResourcesData()
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
        const rapidjson::Value& resArray = document["Resources"];
        
        for (int i = 0; i<resArray.Size(); i++) {
            int id = resArray[i]["id"].GetInt();
            std::string name = resArray[i]["name"].GetString();
            int num = resArray[i]["num"].GetInt();
            bool isShow = resArray[i]["isShow"].GetBool();
            
            auto res = ResourcesModel::create();
            res->setId(id);
            res->setNum(num);
            res->setName(name);
            res->setIsShow(isShow);
            resVec.pushBack(res);
            sqlManager->addOrUpdateResourcesDataInTable(res);
        }
    
    
        auto array = sqlManager->selectResourcesModelList();
    
    
  
//    }else{
//        //直接读取数据库数据
//    }
}