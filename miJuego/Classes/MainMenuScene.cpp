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

	auto background = Sprite::create("MainMenu.jpg");

	background->setPosition(Point((visibleSize.width / 2),
		(visibleSize.height / 2)));

	addChild(background, 0);


	/*auto menuTitle = MenuItemImage::create("images/MainMenuScreen/Game_Title.png",
		"images/MainMenuScreen/Game_Title.png");*/

	auto playItem = MenuItemImage::create("images/MainMenuScreen/Play_Button.png", 
		"images/MainMenuScreen/Play_Button(Click).png", 
		CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));

	playItem->setPosition(origin);

	auto menu = Menu::create(playItem, NULL);


	//menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);

	addChild(menu, 1);

	/*prota = new Prota();
	prota->posicion = Vec2(0, (visibleSize.height / 2));
	prota->sprite->setPosition(prota->posicion);
	addChild(prota->sprite);

	
	_pressedKey = EventKeyboard::KeyCode::KEY_NONE;

	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(MainMenuScene::onKeyPressed, this);
	
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();*/

	

    return true;
}

void MainMenuScene::GoToGameScene(Ref *pSender) {
	auto scene = GameScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}


/*void MainMenuScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
	_pressedKey = keyCode;

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (prota->getOrientacion() != 'w' && prota->getOrientacion() != 'e') {
			prota->setOrientacion('w');
			removeChild(prota->sprite);
			prota->sprite = Sprite::create("vagonetaIzquierdo.png");
			addChild(prota->sprite);
		}
		break;
		
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (prota->getOrientacion() != 'e' && prota->getOrientacion() != 'w') {
			prota->setOrientacion('e');
			removeChild(prota->sprite);
			prota->sprite = Sprite::create("vagoneta.png");
			addChild(prota->sprite);
		}
		break;
		
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (prota->getOrientacion() != 'n' && prota->getOrientacion() != 's') {
			prota->setOrientacion('n');
			removeChild(prota->sprite);
			prota->sprite = Sprite::create("vagonetaReverso.png");
			addChild(prota->sprite);
		}
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (prota->getOrientacion() != 's' && prota->getOrientacion() != 'n') {
			prota->setOrientacion('s');
			removeChild(prota->sprite);
			prota->sprite = Sprite::create("vagonetaFrontal.png");
			addChild(prota->sprite);

		}
		break;
	
	}

	
}
void MainMenuScene::update(float dt) {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (prota->getOrientacion() == 'e') {
		prota->posicion = Vec2(prota->posicion.x + 5, prota->posicion.y);
		prota->sprite->setPosition(prota->posicion);
	
	} 

	else if (prota->getOrientacion() == 'w') {
		prota->posicion = Vec2(prota->posicion.x - 5, prota->posicion.y);
		prota->sprite->setPosition(prota->posicion);
	
	
	} 
		
	else if (prota->getOrientacion() == 'n') {
		prota->posicion = Vec2(prota->posicion.x, prota->posicion.y + 5);
		prota->sprite->setPosition(prota->posicion);
	
	} 
	
	else if (prota->getOrientacion() == 's') {
		prota->posicion = Vec2(prota->posicion.x, prota->posicion.y - 5);
		prota->sprite->setPosition(prota->posicion);
	}
	
	

}*/
