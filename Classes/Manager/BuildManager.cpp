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
