//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/5/31
//!	
//!	Tutorial.cpp
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

//----------------------------------------------------------------------------
#include "Tutorial.h"
#include "PlayScene.h"
#include "Stage/StageManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "audio\include\AudioEngine.h"
#include "GameMenu.h"
//----------------------------------------------------------------------------
USING_NS_CC;
using namespace cocostudio::timeline;

//------------------------------------
//@! シーンを作成
//------------------------------------
Scene* Tutorial::createScene()
{
	//----------------------------------------------------------------------------
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Tutorial::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
	//----------------------------------------------------------------------------
}

//------------------------------------
//@! 初期化
//------------------------------------
bool Tutorial::init()
{
	//----------------------------------------------------------------------------
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	m_menu = nullptr;

	//バックグラウンド作成--------------------------------------------
	m_bg = Sprite::create("Stage/Tutorial/tutorial_bg.png");
	m_bg->setAnchorPoint(Vec2::ZERO);
	m_bg->setPosition(Vec2::ZERO);
	this->addChild(m_bg);

	CCParticleSystemQuad* lightleft = CCParticleSystemQuad::create("Menu/light.plist");
	lightleft->resetSystem();
	lightleft->setPosition(Vec2(0, 50));
	this->addChild(lightleft);

	CCParticleSystemQuad* lightright = CCParticleSystemQuad::create("Menu/light.plist");
	lightright->resetSystem();
	lightright->setPosition(Vec2(480, 50));
	this->addChild(lightright);

	//----------------------------------------------------------------
	MenuItemImage* sprTutorial1 = MenuItemImage::create("Stage/Tutorial/1a.png",
		"Stage/Tutorial/1b.png",
		CC_CALLBACK_1(Tutorial::goToTutorial1, this));
	sprTutorial1->setPosition(Vec2(100, 800 - 335));
	//----------------------------------------------------------------
	MenuItemImage* sprTutorial2 = MenuItemImage::create("Stage/Tutorial/2a.png",
		"Stage/Tutorial/2b.png",
		CC_CALLBACK_1(Tutorial::goToTutorial2, this));
	sprTutorial2->setPosition(Vec2(230, 800 - 335));
	//----------------------------------------------------------------
	MenuItemImage* sprTutorial3 = MenuItemImage::create("Stage/Tutorial/3a.png",
		"Stage/Tutorial/3b.png",
		CC_CALLBACK_1(Tutorial::goToTutorial3, this));
	sprTutorial3->setPosition(Vec2(350.0f, 800 - 335));
	//----------------------------------------------------------------
	MenuItemImage* backButton = MenuItemImage::create("menuButton1.png",
		"menuButton2.png",
		CC_CALLBACK_1(Tutorial::backToMenu, this));
	backButton->setPosition(Vec2(100, 185));
	//----------------------------------------------------------------
	
	//メニュー作成
	m_menu = Menu::create(sprTutorial1, sprTutorial2, sprTutorial3, backButton, NULL);
	m_menu->setPosition(Vec2::ZERO);
	this->addChild(m_menu);

	//----------------------------------------------------------------
	return true;
}

//------------------------------------
//@! チュートリアル1に移動
//@! ボタンのRef
//------------------------------------
void Tutorial::goToTutorial1(cocos2d::Ref * pSender)
{
	//音を鳴らす
	int sound = experimental::AudioEngine::play2d("Sounds/select.mp3");

	//----------------------------------------------------------------------------
	//メニューを解除
	m_menu->removeFromParent();
	//----------------------------------------------------------------------------
	//ステージに移動
	auto playScene = PlayScene::create(Tutorial1);
	this->addChild(playScene);
	//----------------------------------------------------------------------------

}
//------------------------------------
//@! チュートリアル2に移動
//@! ボタンのRef
//------------------------------------
void Tutorial::goToTutorial2(cocos2d::Ref * pSender)
{
	//音を鳴らす
	int sound = experimental::AudioEngine::play2d("Sounds/select.mp3");

	//----------------------------------------------------------------------------
	//メニューを解除
	m_menu->removeFromParent();
	//----------------------------------------------------------------------------
	//ステージに移動
	auto playScene = PlayScene::create(Tutorial2);
	this->addChild(playScene);
	//----------------------------------------------------------------------------

}
//------------------------------------
//@! チュートリアル3に移動
//@! ボタンのRef
//------------------------------------
void Tutorial::goToTutorial3(cocos2d::Ref * pSender)
{
	//音を鳴らす
	int sound = experimental::AudioEngine::play2d("Sounds/select.mp3");

	//----------------------------------------------------------------------------
	//メニューを解除
	m_menu->removeFromParent();
	//----------------------------------------------------------------------------
	//ステージに移動
	auto playScene = PlayScene::create(Tutorial3);
	this->addChild(playScene);
	//----------------------------------------------------------------------------
}
//------------------------------------
//@! チュートリアル3に移動
//@! ボタンのRef
//------------------------------------
void Tutorial::backToMenu(cocos2d::Ref * pSender)
{
	//音を鳴らす
	int sound = experimental::AudioEngine::play2d("Sounds/select.mp3");

	//----------------------------------------------------------------------------
	//メニューを解除
	m_menu->removeFromParent();
	//----------------------------------------------------------------------------
	//ステージに移動
	auto nextScene = GameMenu::createScene();
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//----------------------------------------------------------------------------
}
