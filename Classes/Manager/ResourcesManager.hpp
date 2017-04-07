//
//  ResourcesManager.hpp
//  HelloWorldDemo
//
//  Created by 曾富田 on 2017/4/6.
//
//

#ifndef ResourcesManager_hpp
#define ResourcesManager_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ResourcesModel.hpp"
#include <json/document.h>
#include "Sqlite3Manager.hpp"

class ResourcesManager : public cocos2d::Ref
{
public:
    static ResourcesManager* getInstance();
    
    cocos2d::Vector<ResourcesModel *> resVec;
    void loadResourcesData();
    void createResTable();
    
protected:
    ResourcesManager();
    virtual ~ResourcesManager();
    
    
    
private:
    
//    static bool createXMLFile();
//    static void initXMLFilePath();
    
    
    
//    static ResourcesManager* _resourcesManager;
};
#endif /* ResourcesManager_hpp */
