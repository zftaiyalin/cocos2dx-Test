//
//  BuildScene.hpp
//  HelloWorldDemo
//
//  Created by 曾富田 on 2017/4/6.
//
//

#ifndef BuildScene_hpp
#define BuildScene_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ResourcesModel.hpp"
#include "ResourcesManager.hpp"
#include "BuildManager.hpp"
#include <extensions/cocos-ext.h>
#include "BuildScene.hpp"
#include "HelloWorldScene.h"

USING_NS_CC;
using namespace extension;

class BuildScene : public cocos2d::Layer,cocos2d::extension::TableViewDataSource,cocos2d::extension::TableViewDelegate
{
private:
    void reloadBuildVecs();
    Vector<BuildModel *>buildVecs;
    void Buildbuilding(int idx);
    void judgeBuildText(cocos2d::ui::Layout *layout1,BuildModel *model);
public:
    static cocos2d::Scene* createScene();
    
    void pushMainScene();
    
    virtual bool init();
    
    
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    Size window_size;
    
    cocos2d::extension::TableView *resTableView;
    
    virtual Size cellSizeForTable(TableView* table);
    virtual TableViewCell* tableCellAtIndex(TableView* table,ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    //TableViewDelegateの抽象メソッド
    virtual void tableCellTouched(TableView* table,TableViewCell* cell);
    
    //TableViewDelegateが継承しているScrollViewの抽象メソッド
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view){};
    
    void pushBuildScene();
    
    CREATE_FUNC(BuildScene);
};

#endif /* BuildScene_hpp */
