#include "PauseScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"

USING_NS_CC;


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
