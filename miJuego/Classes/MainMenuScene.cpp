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
void MainMenuScene::GoToGameScene(Ref *pSender) {
	auto scene = GameScene::createScene();

	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
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

	/*auto background = Sprite::create("images/MainMenuScreen/Background.png");

	background->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));

	addChild(background, 0);


	auto menuTitle = MenuItemImage::create("images/MainMenuScreen/Game_Title.png",
		"images/MainMenuScreen/Game_Title.png");

	auto playItem = MenuItemImage::create("images/MainMenuScreen/Play_Button.png", 
		"images/MainMenuScreen/Play_Button(Click).png", 
		CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));

	auto menu = Menu::create(menuTitle, playItem, NULL);

	menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);

	addChild(menu, 1);*/

	prota = new Prota();
	prota->sprite->setPosition(Vec2(0, (visibleSize.height / 2)));
	addChild(prota->sprite);

	
	_pressedKey = EventKeyboard::KeyCode::KEY_NONE;

	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();

	

    return true;
}


void MainMenuScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
	_pressedKey = keyCode;

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (prota->getOrientacion() != 'w' && prota->getOrientacion() != 'e')
			prota->setOrientacion('w');
		break;
	/*case EventKeyboard::KeyCode::KEY_A:
		event->getCurrentTarget()->setPosition(--loc.x, loc.y); // cambiar orientacion(todavia sin hacer)
		break;*/
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (prota->getOrientacion() != 'e' && prota->getOrientacion() != 'w')
			prota->setOrientacion('e');
		break;
	/*case EventKeyboard::KeyCode::KEY_D:
		event->getCurrentTarget()->setPosition(++loc.x, loc.y);
		break;*/
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (prota->getOrientacion() != 'n' && prota->getOrientacion() != 's')
			prota->setOrientacion('n');
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (prota->getOrientacion() != 's' && prota->getOrientacion() != 'n')
			prota->setOrientacion('s');
		break;
	/*case EventKeyboard::KeyCode::KEY_S:
		event->getCurrentTarget()->setPosition(loc.x, --loc.y);
		break;*/
	/*case EventKeyboard::KeyCode::KEY_SPACE:
		prota->embestir();
		break;*/
	}

	
}
void MainMenuScene::update(float dt) {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (prota->getOrientacion() == 'e') prota->sprite->setPosition(Vec2(prota->sprite->getPosition().x + 5, prota->sprite->getPosition().y));
	else if (prota->getOrientacion() == 'w') prota->sprite->setPosition(Vec2(prota->sprite->getPosition().x - 5, prota->sprite->getPosition().y));
	else if (prota->getOrientacion() == 'n') prota->sprite->setPosition(Vec2(prota->sprite->getPosition().x, prota->sprite->getPosition().y + 5));
	else if (prota->getOrientacion() == 's') prota->sprite->setPosition(Vec2(prota->sprite->getPosition().x, prota->sprite->getPosition().y - 5));


}
