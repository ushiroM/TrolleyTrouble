#include "PauseScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* PauseScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PauseScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void PauseScene::resumeGameScene(Ref *pSender) {
	Director::getInstance()->popScene();
}
void PauseScene::goToMainMenu(Ref *pSender) {
	auto scene = MainMenuScene::createScene();

	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}
void PauseScene::retryGameScene(Ref *pSender) {
	auto scene = GameScene::createScene();

	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}

bool PauseScene::init() {

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create("menus/PauseScreen/MenuPausa.png");

	background->setPosition(Vec2((visibleSize.width) / 2, (visibleSize.height) / 2));

	addChild(background, 0);


	auto ResumeGame = MenuItemImage::create("menus/PauseScreen/continuar.png",
		"menus/PauseScreen/continuar_pulsado.png",
		CC_CALLBACK_1(PauseScene::resumeGameScene, this));

	auto MainMenu = MenuItemImage::create("menus/PauseScreen/salir.png",
		"menus/PauseScreen/salir_pulsado.png",
		CC_CALLBACK_1(PauseScene::goToMainMenu, this));

	ResumeGame->setPosition(Vec2(-20, -25));
	MainMenu->setPosition(Vec2(-20, -100));
	auto menu = Menu::create(ResumeGame, MainMenu, NULL);
	addChild(menu, 1);

	return true;

}
