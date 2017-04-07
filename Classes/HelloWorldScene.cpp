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
    auto resManager = ResourcesManager::getInstance();
    resManager->loadResourcesData();
    
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
//    auto label = CCLabelTTF::create("Hello World", "Thonburi", 34);
//    label->setTag(1);
    
    auto buildButton = cocos2d::ui::Button::create("kuang.png","kuang.png","kuang.png");
//    buildButton->setContentSize(CCSizeMake(100, 50));
    buildButton->setTitleText("建造");
    buildButton->setTitleFontSize(7);
    buildButton->setPosition(Vec2(origin.x+30, visibleSize.height + origin.y - 40));
//    buildButton->setColor(Color3B::ORANGE);
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
    
//    UserDefault::getInstance()
    
//    auto button = Button::create("","","");
    
    
//    auto red = LayerColor::create(Color4B(255, 100, 100, 255), visibleSize.width/2, visibleSize.height/2);
//    red->ignoreAnchorPointForPosition(false);
//    red->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
//    
//    auto green = LayerColor::create(Color4B(100, 255, 100, 255), visibleSize.width/4, visibleSize.height/4);
//    green->ignoreAnchorPointForPosition(false);
//    green->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 100));
//    red->setPositionZ(1);
//    green->setPositionZ(0);
//    this->addChild(red, 1);
//    this->addChild(green, 0);
//    
    return true;
}


void HelloWorld::pushBuildScene(){
    
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
