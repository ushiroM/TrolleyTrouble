#include "VictoryScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* VictoryScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = VictoryScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void VictoryScene::goToMainMenu(Ref *pSender) {
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

bool VictoryScene::init() {

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create("menus/VictoryScreen/MenuVictoria.png");
	background->setPosition(Vec2((visibleSize.width) / 2, (visibleSize.height) / 2));
	addChild(background, 0);

	auto MainMenu = MenuItemImage::create("menus/VictoryScreen/cara.png",
		"menus/VictoryScreen/cara.png",
		CC_CALLBACK_1(VictoryScene::goToMainMenu, this));
	MainMenu->setPosition(Vec2(0, -150));
	auto menu = Menu::create(MainMenu, NULL);
	//menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	addChild(menu, 1);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/victory.mp3", true);

	return true;
}
