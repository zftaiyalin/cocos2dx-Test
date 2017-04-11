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
    
    
    auto buildButton = cocos2d::ui::Button::create("kuang.png","kuang.png","kuang.png");
    buildButton->setTitleText("返回");
    buildButton->setTitleFontSize(7);
    buildButton->setPosition(Vec2(origin.x+30, window_size.height + origin.y - 10));
    buildButton->setTitleColor(Color3B::WHITE);
    buildButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->pushMainScene();
                break;
            default:
                break;
        }
    });
    
    this->addChild(buildButton);
    
    
    resTableView = TableView::create(this, Size(window_size.width, 180));
    
    resTableView->setPosition(Vec2(origin.x, window_size.height + origin.y - 210));
    //展開方向
    resTableView->setDirection(TableView::Direction::VERTICAL);
    //表示順序上からしたへ
    resTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    
    //追加
    resTableView->setDelegate(this);
    addChild(resTableView);
    this->reloadBuildVecs();
    
    return true;
}




// セルの大きさを設定する
Size BuildScene::cellSizeForTable(TableView *table){
    return Size(window_size.width, 20);
}

// 1セルに表示させるValueをセット
TableViewCell* BuildScene::tableCellAtIndex(TableView *table, ssize_t idx){
    //    std::string id = StringUtils::format("%zd", idx);
    //    std::string text = StringUtils::format("Line %zd", idx);

    auto model = buildVecs.at(idx);
    
    TableViewCell *cell = table->dequeueCell();
    
    cell = new TableViewCell();
    cell->autorelease();
    
    // セルの背景は交互に色を変更する
    //    auto background_color = Color3B(255,255,255);
    //    if (idx%2) {
    //        background_color = Color3B(200,200,200);
    //    }
    
//    Sprite* bg = Sprite::create();
//    bg->setAnchorPoint(Point(0, 0));
//    bg->setTextureRect(Rect(0, 0, 200, 15));
//    bg->setColor(Color3B(0,0,0));
//    bg->setTag(100);
//    cell->addChild(bg);
    
    
    
    //布局1*****************************************
    cocos2d::ui::Layout *layout1 = cocos2d::ui::Layout::create();
    ////纯色
    layout1->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    layout1->setBackGroundColor(Color3B::BLACK);
    layout1->setContentSize(Size(window_size.width, 20));
    layout1->setPosition(Vec2(0, 0));
    layout1->setLayoutType(cocos2d::ui::Layout::Type::HORIZONTAL);//水平布局，所有组件在一行
    
    ////此时对layout1设定布局属性无效，因为布局属性是其作为组件时，相对容器的属性！
    //LinearLayoutParameter *linerP = LinearLayoutParameter::create();
    //linerP->setGravity(LinearLayoutParameter::LinearGravity::RIGHT);
    //layout1->setLayoutParameter(linerP);
    
    cell->addChild(layout1);

    
    
    
    
    auto buildButton = cocos2d::ui::Button::create("buildKuang.png","buildKuang.png","buildKuang.png");
    buildButton->setTitleText(model->getName());
    buildButton->setTitleFontSize(7);
    buildButton->setTitleColor(Color3B::WHITE);
    buildButton->setTag((int)idx);
    buildButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                auto button =(cocos2d::ui::Button *) sender;
                this->Buildbuilding(button->getTag());
                break;

        }
    });
    
    //设定button1组件在layout中的布局位置属性
    cocos2d::ui::LinearLayoutParameter *linerP1 = cocos2d::ui::LinearLayoutParameter::create();
    linerP1->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);//垂直居中
    linerP1->setMargin(cocos2d::ui::Margin(10, 0, 0, 0));
    buildButton->setLayoutParameter(linerP1);//按钮1使用该线形布局属性
    layout1->addChild(buildButton);
    
    
    
    
    
    auto buildNum = cocos2d::ui::Button::create("buildNum.png","buildNum.png","buildNum.png");
    buildNum->setTitleText(StringUtils::format("%d", model->getNum()));
    buildNum->setTitleFontSize(10);
    buildNum->setScale(0.3);
    buildNum->setTitleColor(Color3B::WHITE);
    
    //设定button1组件在layout中的布局位置属性
    cocos2d::ui::LinearLayoutParameter *linerP2 = cocos2d::ui::LinearLayoutParameter::create();
    linerP2->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);//垂直居中
    linerP2->setMargin(cocos2d::ui::Margin(-(buildNum->getContentSize().width/2), -(buildButton->getContentSize().height/2)+(buildNum->getContentSize().height/2)+(buildNum->getContentSize().height/4), 0, 0));
    buildNum->setLayoutParameter(linerP2);//按钮1使用该线形布局属性
    layout1->addChild(buildNum);
    
    
    if (model->getIsShowNum()&&model->getNum()>0) {
        buildNum->setVisible(true);
    }else{
         buildNum->setVisible(false);//消失
    }
    
    
    auto buttonGou = cocos2d::ui::Button::create("buildGou.png","buildGou.png","buildGou.png");
    cocos2d::ui::LinearLayoutParameter *linerP5 = cocos2d::ui::LinearLayoutParameter::create();
    linerP5->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);//垂直居中
    linerP5->setMargin(cocos2d::ui::Margin(3, 0, 0, 0));
    buttonGou->setLayoutParameter(linerP5);//按钮1使用该线形布局属性
    layout1->addChild(buttonGou);
    
    if (model->getIsShowNum()==false&&model->getNum()>0) {
        buttonGou->setVisible(true);
    }else{
        buttonGou->setVisible(false);//消失
    }
    
    
    this->judgeBuildText(layout1, model);
    
    
    auto tanButton = cocos2d::ui::Button::create("buildyou.png","buildyou.png","buildyou.png");
    tanButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
//                this->Buildbuilding(idx);
                break;
            default:
                break;
        }
    });
    
    cell->addChild(tanButton);
    
    tanButton->setPosition(Vec2(window_size.width-20, 10));
    //设定button1组件在layout中的布局位置属性
//    cocos2d::ui::LinearLayoutParameter *linerP4 = cocos2d::ui::LinearLayoutParameter::create();
//    linerP4->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);//垂直居中
//    linerP4->setMargin(cocos2d::ui::Margin(30, 0, 0, 0));
//    tanButton->setLayoutParameter(linerP4);//按钮1使用该线形布局属性
//    layout1->addChild(tanButton);
//
//    
//    //    auto numString = __String::createWithFormat("%d",model->getNum());
//    std::string numText = StringUtils::format("%d", model->getNum());
//    // テキスト部分
//    auto *label_2 = cocos2d::ui::Text::create(numText.c_str(), "Arial", 7);
//    label_2->setAnchorPoint(Point(0, 0));
//    label_2->setPosition(Point(50, 0));
//    label_2->setColor(Color3B(255,255,255));
//    cell->addChild(label_2);
    
    return cell;
}

void BuildScene::Buildbuilding(int idx){
    auto model = buildVecs.at(idx);
    auto build = BuildManager::getInstance()->buildMap.at(StringUtils::format("%d", model->getId()));
    build->setNum(build->getNum()+1);
    GameSqlManager::getInstance()->addOrUpdateBuildDataInTable(build);
    this->reloadBuildVecs();
    //重新刷新资源添加事件
    BuildManager::getInstance()->reloadResourcesNum();
    
}
// セル数
ssize_t BuildScene::numberOfCellsInTableView(TableView *table){
    return buildVecs.size();
}

// セルがタッチされた時のcallback
void BuildScene::tableCellTouched(TableView* table, TableViewCell* cell){
    CCLOG("%ziのセルがタッチされました", cell->getIdx());
}


void BuildScene::reloadBuildVecs(){
    buildVecs.clear();
    for (const auto& key: BuildManager::getInstance()->buildMap.keys()) {
        BuildModel *model = BuildManager::getInstance()->buildMap.at(key);
        if (model->getIsShow()) {
            buildVecs.pushBack(model);
        }
    }
    resTableView->reloadData();
}

void BuildScene::pushMainScene(){
    //创建场景HelloWorld场景
//    Scene* scene = HelloWorld::createScene();
    //创建场景切换方式
//    TransitionScene* ts = TransitionSlideInL::create(1, scene);
    //切换场景
    Director::getInstance()->popScene();
}

void BuildScene::judgeBuildText(cocos2d::ui::Layout *layout1,BuildModel *model){
    
    Vector<BuildRequireModel *> reVec;
    
    for (int i = 0; i<BuildManager::getInstance()->buildRequireVec.size(); i++) {
 
        BuildRequireModel *reModel = BuildManager::getInstance()->buildRequireVec.at(i);
        
        if ((reModel->getUpbuildname() == model->getName())&&(reModel->getBuildnum()== (model->getNum()+1))) {
            reVec.pushBack(reModel);
        }
    }
    
    for (int i = 0; i<reVec.size(); i++) {
        
        BuildRequireModel *reModel = reVec.at(i);

        auto resModel= ResourcesManager::getInstance()->resMap.at(StringUtils::format("%d", reModel->getResid()));
        
       
        std::string text = StringUtils::format("%s%d",resModel->getName().c_str(), reModel->getNum());
        // ID部分
        auto *label_1 = cocos2d::ui::Text::create(text, "Arial", 7);
        label_1->setAnchorPoint(Point(0, 0));
        
        
        if (resModel->getNum()<reModel->getNum()) {
            label_1->setColor(Color3B(128,128,128));
        }else{
            label_1->setColor(Color3B(255,255,255));
        }
        
        
        cocos2d::ui::LinearLayoutParameter *linerP3 = cocos2d::ui::LinearLayoutParameter::create();
        linerP3->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);//垂直居中
        linerP3->setMargin(cocos2d::ui::Margin(5, 0, 0, 0));
        label_1->setLayoutParameter(linerP3);//按钮1使用该线形布局属性
        layout1->addChild(label_1);
    }
    

}
