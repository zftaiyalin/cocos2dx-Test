//
//  BuildModel.hpp
//  HelloWorldDemo
//
//  Created by 曾富田 on 2017/4/6.
//
//

#ifndef BuildModel_hpp
#define BuildModel_hpp

#include <stdio.h>
#include "cocos2d.h"


class BuildModel : public cocos2d::Ref {
private:
    std::string _name; // 建筑名称
    int _productTime;  // 生产周期
    int _id; // id
    int _grade; //建筑等级
    int _num; //建筑数量
    int _productTimeNum; //生产周期产量
    bool _isMax; //是否可到达最大数量
    bool _isShowMaxNum; //是否显示建筑最大开采量
    bool _isShowNum; //是否显示建筑数量
    
public:
    // 静态的create函数
    static BuildModel* create()
    {
        BuildModel *sprite = new BuildModel();
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
    
    void setProductTime(int productTime){ _productTime = productTime; }
    int getProductTime(){ return _productTime; }
    
    void setId(int id){ _id = id; }
    int getId(){ return _id; }
    
    void setGrade(int grade){ _grade = grade; }
    int getGrade(){ return _grade; }
    
    void setNum(int num){ _num = num; }
    int getNum(){ return _num; }
    
    void setIsMax(bool isMax){ _isMax = isMax; }
    bool getIsMax(){ return _isMax; }
    
    void setProductTimeNum(int productTimeNum){ _productTimeNum = productTimeNum; }
    int getProductTimeNum(){ return _productTimeNum; }
    
    void setIsShowMaxNum(bool isShowMaxNum){ _isShowMaxNum = isShowMaxNum; }
    bool getisShowMaxNum(){ return _isShowMaxNum; }
    
    void setIsShowNum(bool isShowNum){ _isShowNum = isShowNum; }
    bool getIsShowNum(){ return _isShowNum; }
    
};


#endif /* BuildModel_hpp */
