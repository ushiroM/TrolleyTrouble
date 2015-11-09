#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"

USING_NS_CC;


void GameOverScene::goToMainMenu(Ref *pSender) {
	auto scene = MainMenuScene::createScene();

	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}
void GameOverScene::retryGameScene(Ref *pSender) {
	auto scene = GameScene::createScene();

	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}
