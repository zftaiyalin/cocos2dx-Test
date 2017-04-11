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

class UpBuildRequireResModel : public cocos2d::Ref {
private:
    //    "selfNum":1,
    //    "upRequire":
    int _resid;//资源id
    int _num;//资源数量
    std::string _upbuildname;//建筑名称
    int _buildnum;//建筑数量
    
public:
    // 静态的create函数
    static UpBuildRequireResModel* create()
    {
        UpBuildRequireResModel *sprite = new UpBuildRequireResModel();
        if (sprite)
        {
            sprite->autorelease();
            return sprite;
        }
        CC_SAFE_DELETE(sprite);
        return nullptr;
    }
    // setter和getter函数
    void setResid(int resid){ _resid = resid; }
    int getResid(){ return _resid; }
    
    void setNum(int num){ _num = num; }
    int getNum(){ return _num; }
};

//class RequireNumModel : public cocos2d::Ref {
//private:
////    "selfNum":1,
////    "upRequire":
//    int _selfNum;//建筑数量
//    cocos2d::Vector<RequireResModel *> _upRequire;
//    
//    public:
//    static RequireNumModel* create()
//    {
//        RequireNumModel *sprite = new RequireNumModel();
//        if (sprite)
//        {
//            sprite->autorelease();
//            return sprite;
//        }
//        CC_SAFE_DELETE(sprite);
//        return nullptr;
//    }
//    // setter和getter函数
//    void setSelfNum(int selfNum){ _selfNum = selfNum; }
//    int getSelfNum(){ return _selfNum; }
//    
//    void setUpRequire(cocos2d::Vector<RequireResModel *> upRequire){ _upRequire = upRequire; }
//    cocos2d::Vector<RequireResModel *> getUpRequire(){ return _upRequire; }
//};

class BuildModel : public cocos2d::Ref {
private:
    std::string _name; // 建筑名称
    int _productTime;  // 生产周期
    int _id; // id
    int _grade; //建筑等级
    int _num; //建筑数量
    int _productNum; //生产周期产量
    bool _isMax; //是否可到达最大数量
    bool _isShowMaxNum; //是否显示建筑最大开采量
    bool _isShowNum; //是否显示建筑数量
    bool _isShow;//是否展示在界面
    int _maxProduct;//建筑最大开采量
    int _productResId;//建筑产出资源ID
    
//    cocos2d::Vector<RequireNumModel *> _upNums;
    
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
    
    void setMaxProduct(int maxProduct){ _maxProduct = maxProduct; }
    int getMaxProduct(){ return _maxProduct; }
    
    void setNum(int num){ _num = num; }
    int getNum(){ return _num; }
    
    void setIsMax(bool isMax){ _isMax = isMax; }
    bool getIsMax(){ return _isMax; }
    
    void setProductNum(int productTimeNum){ _productNum = productTimeNum; }
    int getProductNum(){ return _productNum; }
    
    void setProductResId(int productTimeNum){ _productResId = productTimeNum; }
    int getProductResId(){ return _productResId; }
    
    void setIsShowMaxNum(bool isShowMaxNum){ _isShowMaxNum = isShowMaxNum; }
    bool getisShowMaxNum(){ return _isShowMaxNum; }
    
    void setIsShowNum(bool isShowNum){ _isShowNum = isShowNum; }
    bool getIsShowNum(){ return _isShowNum; }
    
    void setIsShow(bool isShow){ _isShow = isShow; }
    bool getIsShow(){ return _isShow; }
  
//    void setUpNums(cocos2d::Vector<RequireNumModel *> upNums){ _upNums = upNums; }
//    cocos2d::Vector<RequireNumModel *> getUpNums(){ return _upNums; }
};


#endif /* BuildModel_hpp */
