//
//  BuildScene.cpp
//  HelloWorldDemo
//
//  Created by 曾富田 on 2017/4/6.
//
//

#include "BuildScene.hpp"


USING_NS_CC;

Scene* BuildScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = BuildScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool BuildScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    window_size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    resTableView = TableView::create(this, Size(window_size.width, 180));
    
    resTableView->setPosition(Vec2(origin.x, window_size.height + origin.y - 210));
    //展開方向
    resTableView->setDirection(TableView::Direction::VERTICAL);
    //表示順序上からしたへ
    resTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    
    //追加
    resTableView->setDelegate(this);
    addChild(resTableView);
    resTableView->reloadData();
    
    return true;
}


// セルの大きさを設定する
Size BuildScene::cellSizeForTable(TableView *table){
    return Size(window_size.width, 15);
}

// 1セルに表示させるValueをセット
TableViewCell* BuildScene::tableCellAtIndex(TableView *table, ssize_t idx){
    //    std::string id = StringUtils::format("%zd", idx);
    //    std::string text = StringUtils::format("Line %zd", idx);
    auto resManager = BuildManager::getInstance();
    auto model = resManager->buildVec.at(resManager->buildVec.size()-1-idx);
    
    TableViewCell *cell = table->dequeueCell();
    
    cell = new TableViewCell();
    cell->autorelease();
    
    // セルの背景は交互に色を変更する
    //    auto background_color = Color3B(255,255,255);
    //    if (idx%2) {
    //        background_color = Color3B(200,200,200);
    //    }
    
    Sprite* bg = Sprite::create();
    bg->setAnchorPoint(Point(0, 0));
    bg->setTextureRect(Rect(0, 0, 200, 15));
    bg->setColor(Color3B(0,0,0));
    bg->setTag(100);
    cell->addChild(bg);
    
//    // ボーダーライン
//    Sprite* line = Sprite::create();
//    line->setAnchorPoint(Point(0, 0));
//    line->setTextureRect(Rect(0, 0, 200, 1));
//    line->setColor(Color3B(0,0,0));
//    cell->addChild(line);
    
    // ID部分
    auto *label_1 = cocos2d::ui::Text::create(model->getName(), "Arial", 7);
    label_1->setAnchorPoint(Point(0, 0));
    label_1->setPosition(Point(10, 0));
    label_1->setColor(Color3B(255,255,255));
    cell->addChild(label_1);
    
    
    //    auto numString = __String::createWithFormat("%d",model->getNum());
    std::string numText = StringUtils::format("%d", model->getNum());
    // テキスト部分
    auto *label_2 = cocos2d::ui::Text::create(numText.c_str(), "Arial", 7);
    label_2->setAnchorPoint(Point(0, 0));
    label_2->setPosition(Point(50, 0));
    label_2->setColor(Color3B(255,255,255));
    cell->addChild(label_2);
    
    return cell;
}

// セル数
ssize_t BuildScene::numberOfCellsInTableView(TableView *table){
    return BuildManager::getInstance()->buildVec.size();
}

// セルがタッチされた時のcallback
void BuildScene::tableCellTouched(TableView* table, TableViewCell* cell){
    CCLOG("%ziのセルがタッチされました", cell->getIdx());
}
