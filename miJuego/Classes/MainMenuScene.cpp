#include "MainMenuScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("menus/MainMenuScreen/MainMenu.jpg");
	background->setPosition(Vec2((visibleSize.width)/2, (visibleSize.height)/2));
	addChild(background, 0);

	auto playItem = MenuItemImage::create("menus/MainMenuScreen/Play_Button.png", 
		"menus/MainMenuScreen/Play_Button(Click).png", 
		CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));

	playItem->setPosition(Vec2(0, -200));

	auto menu = Menu::create(playItem, NULL);
	addChild(menu, 1);

    return true;
}

void MainMenuScene::GoToGameScene(Ref *pSender) {
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}


