//
//  ResourcesModel.hpp
//  HelloWorldDemo
//
//  Created by 曾富田 on 2017/4/6.
//
//

#ifndef ResourcesModel_hpp
#define ResourcesModel_hpp

#include <stdio.h>
#include "cocos2d.h"

class ResourcesModel : public cocos2d::Ref {
private:
    std::string _name; // 建筑名称
    int _id; // id
    int _num; //建筑数量
    bool _isShow; //是否显示建筑数量
    
public:
    // 静态的create函数
    static ResourcesModel* create()
    {
        ResourcesModel *sprite = new ResourcesModel();
        if (sprite)
        {
            sprite->autorelease();
            return sprite;
        }
        CC_SAFE_DELETE(sprite);
        return nullptr;
    }
    // setter和getter函数
    void setName(std::string name){ _name = name; }
    std::string getName(){ return _name; }
    
    void setId(int id){ _id = id; }
    int getId(){ return _id; }

    void setNum(int num){ _num = num; }
    int getNum(){ return _num; }
    
    void setIsShow(bool isShow){ _isShow = isShow; }
    bool getIsShow(){ return _isShow; }
    
};
#endif /* ResourcesModel_hpp */
