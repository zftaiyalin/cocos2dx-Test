//
//  BuildManager.cpp
//  HelloWorldDemo
//
//  Created by 曾富田 on 2017/4/6.
//
//

#include "BuildManager.hpp"

static BuildManager* _buildManager = nullptr;

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
        _buildManager->loadBuildData();
    }
    
    return _buildManager;
}


void BuildManager::loadBuildData()
{
    
    
    bool isLoadJson = cocos2d::UserDefault::getInstance()->getBoolForKey("isLoadBuild");
    auto sqlManager = GameSqlManager::getInstance();
    
    //读取JSON配置数据，建立表格数据，把数据存入数据库
    rapidjson::Document document;
    
    std::string filePath = cocos2d::FileUtils::getInstance()->fullPathForFilename(cocos2d::StringUtils::format("game.json"));
    std::string contentStr = cocos2d::FileUtils::getInstance()->getStringFromFile(filePath);
    document.Parse<0>(contentStr.c_str());
    
    if (!isLoadJson) {
    
    cocos2d::UserDefault::getInstance()->setBoolForKey("isLoadBuild", true);
    
    //获取建筑数据
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
        int productResId = resArray[i]["productResId"].GetInt();
        
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
        res->setProductResId(productResId);
 
        sqlManager->addOrUpdateBuildDataInTable(res);
        }
    }
    
    buildMap = sqlManager->selectBuildModelList();
    
    //获取建筑增加条件数据
    const rapidjson::Value& requireArray = document["UpBuildRequire"];
    
    for (int i = 0; i<requireArray.Size(); i++) {
        
        
        int resid = requireArray[i]["resid"].GetInt();
        std::string upbuildname = requireArray[i]["upbuildname"].GetString();
        int num = requireArray[i]["num"].GetInt();
        int buildnum = requireArray[i]["buildnum"].GetInt();
        
        
        auto res = BuildRequireModel::create();
        res->setResid(resid);
        res->setNum(num);
        res->setBuildnum(buildnum);
        res->setUpbuildname(upbuildname);
        
        buildRequireVec.pushBack(res);
    }
    
    reloadResourcesNum();
}

void BuildManager::reloadResourcesNum(){
    
    unschedule(schedule_selector(BuildManager::updateRes));
    
    productBuildMap.clear();
    Node::onEnter();
    for (const auto& key: buildMap.keys()) {
        auto build = buildMap.at(key);
        if (build->getNum()>0&&build->getProductNum()>0) {
            if (build->getisShowMaxNum()) {
                if (build->getMaxProduct()>0) {
                    productBuildMap.insert(key, build);
                }
            }else{
                productBuildMap.insert(key, build);
            }
        }
    }
    if (productBuildMap.size()>0) {
        
        schedule(schedule_selector(BuildManager::updateRes), 5.0f, kRepeatForever, 0.0f);
    }
    
}

void BuildManager::updateRes(float dt){
    //添加资源到数据库
    
    for (const auto& key: productBuildMap.keys()) {

        auto build = productBuildMap.at(key);
        std::string reskey = cocos2d::StringUtils::format("%d", build->getProductResId());
        
        ResourcesModel *resource = ResourcesManager::getInstance()->resMap.at(reskey);
        
        resource->setNum(resource->getNum() + build->getProductNum());
        
        GameSqlManager::getInstance()->addOrUpdateResourcesDataInTable(resource);
    }
    
    cocos2d::EventCustom event("reloadResTableView");
    //    event.setUserData(value);
    _eventDispatcher->dispatchEvent(&event);
    
}

