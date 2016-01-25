#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameOverScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void GameOverScene::goToMainMenu(Ref *pSender) {
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
void GameOverScene::retryGameScene(Ref *pSender) {
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

bool GameOverScene::init() {

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create("menus/GameOverScreen/gameOver.png");
	background->setPosition(Vec2((visibleSize.width) / 2, (visibleSize.height) / 2));
	addChild(background, 0);

	auto RetryGame = MenuItemImage::create("menus/GameOverScreen/reintentar.png",
		"menus/GameOverScreen/reintentar_pulsado.png",
		CC_CALLBACK_1(GameOverScene::retryGameScene, this));

	auto MainMenu = MenuItemImage::create("menus/PauseScreen/salir.png",
		"menus/PauseScreen/salir_pulsado.png",
		CC_CALLBACK_1(GameOverScene::goToMainMenu, this));

	RetryGame->setPosition(Vec2(250,-75));
	MainMenu->setPosition(Vec2(250, -150));

	auto menu = Menu::create(RetryGame, MainMenu, NULL);
	//menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	addChild(menu, 1);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/gameover.mp3", true);

	return true;
}
