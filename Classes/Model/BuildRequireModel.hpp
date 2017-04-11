//
//  BuildRequireModel.hpp
//  HelloWorldDemo
//
//  Created by 曾富田 on 2017/4/11.
//
//

#ifndef BuildRequireModel_hpp
#define BuildRequireModel_hpp

#include <stdio.h>
#include "cocos2d.h"

class BuildRequireModel : public cocos2d::Ref {
private:
    std::string _upbuildname; // 增加的建筑名称
    int _resid; // 所需的资源ID
    int _num; //所需的资源数量
    int _buildnum; //当前所需资源的建筑数量
    
    
public:
    
//    "upbuildname":"耕地",
//    "resid": 11110,
//    "num": 30,
//    "buildnum":3

    
    // 静态的create函数
    static BuildRequireModel* create()
    {
        BuildRequireModel *sprite = new BuildRequireModel();
        if (sprite)
        {
            sprite->autorelease();
            return sprite;
        }
        CC_SAFE_DELETE(sprite);
        return nullptr;
    }
    // setter和getter函数
    void setUpbuildname(std::string name){ _upbuildname = name; }
    std::string getUpbuildname(){ return _upbuildname; }
    
    void setResid(int id){ _resid = id; }
    int getResid(){ return _resid; }
    
    void setNum(int num){ _num = num; }
    int getNum(){ return _num; }
    
    void setBuildnum(int isShow){ _buildnum = isShow; }
    int getBuildnum(){ return _buildnum; }
    
    
    
};

#endif /* BuildRequireModel_hpp */
