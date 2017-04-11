//
//  BuildManager.hpp
//  HelloWorldDemo
//
//  Created by 曾富田 on 2017/4/6.
//
//

#ifndef BuildManager_hpp
#define BuildManager_hpp

#include <stdio.h>
#include "cocos2d.h"
#include <json/document.h>
#include "Sqlite3Manager.hpp"
#include "BuildModel.hpp"
#include "BuildRequireModel.hpp"
#include "ResourcesManager.hpp"
#include "Sqlite3Manager.hpp"
class BuildManager : public cocos2d::Node
{
    public:
        static BuildManager* getInstance();
        void loadBuildData();
//        cocos2d::Vector<BuildModel *> buildVec;//全部建筑数组
        cocos2d::Map<std::string,BuildModel *> buildMap;//全部建筑字典
        cocos2d::Map<std::string,BuildModel *> productBuildMap;//已有的生产建筑数组
        cocos2d::Vector<BuildRequireModel *> buildRequireVec;//建筑添加数量的条件数组
        void reloadResourcesNum();
        void updateRes(float dt);
protected:
    BuildManager();
    virtual ~BuildManager();
    
private:
    

};

#endif /* BuildManager_hpp */
