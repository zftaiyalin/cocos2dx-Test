#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

//    cocos2d::Vector<ResourcesModel *> resVec;
    
//    cocos2d::Vector<ResourcesModel *> resVec = ResourcesManager::getInstance()->resVec;
//    ResourcesManager::getInstance()->loadResourcesData();
//    BuildManager::getInstance()->loadBuildData();  
    
    
    
//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
//    auto label = CCLabelTTF::create("Hello World", "Thonburi", 34);
//    label->setTag(1);
    
    auto buildButton = cocos2d::ui::Button::create("kuang.png","kuang.png","kuang.png");
    buildButton->setTitleText("建造");
    buildButton->setTitleFontSize(7);
    buildButton->setPosition(Vec2(origin.x+30, visibleSize.height + origin.y - 40));
    buildButton->setTitleColor(Color3B::WHITE);
    buildButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->pushBuildScene();
                break;
            default:
                break;
        }
    });
    
    this->addChild(buildButton);
    

    
    resTableView = TableView::create(this, Size(100, 180));
    
    resTableView->setPosition(Vec2(origin.x+65, visibleSize.height + origin.y - 210));
    //展開方向
    resTableView->setDirection(TableView::Direction::VERTICAL);
    //表示順序上からしたへ
    resTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    
    //追加
    resTableView->setDelegate(this);
    addChild(resTableView);
    this->reloadResourcesVecs();
    
    
    auto listener = EventListenerCustom::create("reloadResTableView", [=](EventCustom *event){
        //接受建筑管理类的资源改变时间，刷新tableview;
        this->reloadResourcesVecs();
        
    });
    
    _eventDispatcher->addEventListenerWithFixedPriority(listener, 1);
    
    

    
    return true;
}

void HelloWorld::reloadResourcesVecs(){
    resourcesVecs.clear();
    for (const auto& key: ResourcesManager::getInstance()->resMap.keys()) {
        ResourcesModel *model = ResourcesManager::getInstance()->resMap.at(key);
        if (model->getIsShow()) {
            resourcesVecs.pushBack(model);
        }
    }
    resTableView->reloadData();
}


// セルの大きさを設定する
Size HelloWorld::cellSizeForTable(TableView *table){
    return Size(200, 15);
}

// 1セルに表示させるValueをセット
TableViewCell* HelloWorld::tableCellAtIndex(TableView *table, ssize_t idx){
//    std::string id = StringUtils::format("%zd", idx);
//    std::string text = StringUtils::format("Line %zd", idx);

    auto model = resourcesVecs.at(resourcesVecs.size()-1-idx);
    
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
    
    // ボーダーライン
    Sprite* line = Sprite::create();
    line->setAnchorPoint(Point(0, 0));
    line->setTextureRect(Rect(0, 0, 200, 1));
    line->setColor(Color3B(0,0,0));
    cell->addChild(line);
    
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
ssize_t HelloWorld::numberOfCellsInTableView(TableView *table){
    return resourcesVecs.size();
}

// セルがタッチされた時のcallback
void HelloWorld::tableCellTouched(TableView* table, TableViewCell* cell){
    CCLOG("%ziのセルがタッチされました", cell->getIdx());
}


void HelloWorld::pushBuildScene(){
    //创建场景HelloWorld场景
    Scene* scene = BuildScene::createScene();
    //创建场景切换方式
//    TransitionScene* ts = TransitionSlideInR::create(1, scene);
    //切换场景
    Director::getInstance()->pushScene(scene);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
