//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/5/19
//!	
//!	StageSelectScene.cpp
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//-----------------------------------------------------------------------------
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "StageSelectScene.h"
#include "PlayScene.h"
#include "Stage/StageManager.h"
#include "Tutorial.h"
#include "GameMenu.h"
#include "../EventListenerGesture.h"
#include "audio\include\AudioEngine.h"
//----------------------------------------------------------------------------
USING_NS_CC;

using namespace cocostudio::timeline;
//------------------------------------
//@! シーンを作成
//------------------------------------
Scene* StageSelectScene::createScene()
{
	//----------------------------------------------------------------------------
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StageSelectScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
	//----------------------------------------------------------------------------
}

//------------------------------------
//@! 初期化
//------------------------------------
bool StageSelectScene::init()
{
	//----------------------------------------------------------------------------
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//バックグラウンド作成--------------------------------------------------
	
	Sprite* bg = Sprite::create("Stage/stage_bg.png");
	bg->setPosition(Vec2(480.0f / 2, 800.0f / 2));
	this->addChild(bg);

	CCParticleSystemQuad* lightleft = CCParticleSystemQuad::create("Menu/light.plist");
	lightleft->resetSystem();
	lightleft->setPosition(Vec2(0, 50));
	this->addChild(lightleft);

	CCParticleSystemQuad* lightright = CCParticleSystemQuad::create("Menu/light.plist");
	lightright->resetSystem();
	lightright->setPosition(Vec2(480, 50));
	this->addChild(lightright);




	//ステージ１--------------------------------------------------------------
	MenuItemImage* sprStage1 = MenuItemImage::create("Stage/stage1_1.png",
		"Stage/stage1_b.png",
		CC_CALLBACK_1(StageSelectScene::goToStage1, this));
	sprStage1->setPosition(Vec2(110, 800-220));
	//ステージ２--------------------------------------------------------------
	MenuItemImage* sprStage2 = MenuItemImage::create("Stage/stage2_1.png",
		"Stage/stage2_2.png",
		CC_CALLBACK_1(StageSelectScene::goToStage2, this));
	sprStage2->setPosition(Vec2(240, 800 - 220));
	//ステージ３---------------------------------------------------------------
	MenuItemImage* prStage3 = MenuItemImage::create("Stage/stage3_1.png",
		"Stage/stage3_2.png",
		CC_CALLBACK_1(StageSelectScene::goToStage3, this));
	prStage3->setPosition(Vec2(370.0f, 800 - 220));
	//-----------------------------------------------------------------
	MenuItemImage* sprStage4 = MenuItemImage::create("Stage/stage4_1.png",
		"Stage/stage4_b.png",
		CC_CALLBACK_1(StageSelectScene::goToStage4, this));
	sprStage4->setPosition(Vec2(110, 800-355));
	//-----------------------------------------------------------------
	MenuItemImage* sprStage5 = MenuItemImage::create("Stage/stage5_1.png",
		"Stage/stage5_b.png",
		CC_CALLBACK_1(StageSelectScene::goToStage5, this));
	sprStage5->setPosition(Vec2(240, 800 - 355));
	//-----------------------------------------------------------------
	MenuItemImage* sprStage6 = MenuItemImage::create("Stage/stage6_1.png",
		"Stage/stage6_b.png",
		CC_CALLBACK_1(StageSelectScene::goToStage6, this));
	sprStage6->setPosition(Vec2(370, 800 - 355));
	//-----------------------------------------------------------------
	MenuItemImage* sprStage7 = MenuItemImage::create("Stage/stage7_1.png",
		"Stage/stage7_b.png",
		CC_CALLBACK_1(StageSelectScene::goToStage7, this));
	sprStage7->setPosition(Vec2(110, 800 - 490));
	//-----------------------------------------------------------------
	MenuItemImage* sprStage8 = MenuItemImage::create("Stage/stage8_1.png",
		"Stage/stage8_b.png",
		CC_CALLBACK_1(StageSelectScene::goToStage8, this));
	sprStage8->setPosition(Vec2(240, 800 - 490));
	//-----------------------------------------------------------------
	MenuItemImage* sprStage9 = MenuItemImage::create("Stage/stage9_1.png",
		"Stage/stage9_b.png",
		CC_CALLBACK_1(StageSelectScene::goToStage9, this));
	sprStage9->setPosition(Vec2(370, 800 - 490));
	//-----------------------------------------------------------------
	MenuItemImage* sprStage10 = MenuItemImage::create("Stage/stage10_1.png",
		"Stage/stage10_2.png",
		CC_CALLBACK_1(StageSelectScene::goToStage10, this));
	sprStage10->setPosition(Vec2(240, 800 - 490 - 142));
	//----------------------------------------------------------------
	MenuItemImage* backToMenu = MenuItemImage::create("menuButton1.png",
		"menuButton2.png",
		CC_CALLBACK_1(StageSelectScene::backToMenu, this));
	backToMenu->setPosition(Vec2(100, 185));
	//-----------------------------------------------------------------
	Menu* menuStage = Menu::create(sprStage1,sprStage2,
							prStage3,sprStage4,sprStage5,
		sprStage6,sprStage7, sprStage8, sprStage9,sprStage10,backToMenu, NULL);// sprStage7, NULL);
	menuStage->setPosition(Vec2::ZERO);
	this->addChild(menuStage);

	//-----------------------------------------------------------------
	return true;
}


//------------------------------------
//@! ステージ1に移動
//@! ボタンのRef
//------------------------------------
void StageSelectScene::goToStage1(cocos2d::Ref * pSender)
{

	//音を鳴らす
	int sound = experimental::AudioEngine::play2d("Sounds/select.mp3");

	//----------------------------------------------------------------------------
	auto nextScene = PlayScene::createScene(Stage1);
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//----------------------------------------------------------------------------
}

//------------------------------------
//@! ステージ2に移動
//@! ボタンのRef
//------------------------------------
void StageSelectScene::goToStage2(cocos2d::Ref * pSender)
{

	//音を鳴らす
	int sound = experimental::AudioEngine::play2d("Sounds/select.mp3");

	//----------------------------------------------------------------------------
	auto nextScene = PlayScene::createScene(Stage2);
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//----------------------------------------------------------------------------
}
//------------------------------------
//@! ステージ3に移動
//@! ボタンのRef
//------------------------------------
void StageSelectScene::goToStage3(cocos2d::Ref * pSender)
{
	//音を鳴らす
	int sound = experimental::AudioEngine::play2d("Sounds/select.mp3");

	//----------------------------------------------------------------------------
	auto nextScene = PlayScene::createScene(Stage3);
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//----------------------------------------------------------------------------
}
//------------------------------------
//@! ステージ4に移動
//@! ボタンのRef
//------------------------------------
void StageSelectScene::goToStage4(cocos2d::Ref * pSender)
{
	//音を鳴らす
	int sound = experimental::AudioEngine::play2d("Sounds/select.mp3");

	//----------------------------------------------------------------------------
	auto nextScene = PlayScene::createScene(Stage4);
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//----------------------------------------------------------------------------

}
//------------------------------------
//@! ステージ5に移動
//@! ボタンのRef
//------------------------------------
void StageSelectScene::goToStage5(cocos2d::Ref * pSender)
{
	//音を鳴らす
	int sound = experimental::AudioEngine::play2d("Sounds/select.mp3");
	//----------------------------------------------------------------------------
	auto nextScene = PlayScene::createScene(Stage5);
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//----------------------------------------------------------------------------
}
//------------------------------------
//@! ステージ6に移動
//@! ボタンのRef
//------------------------------------
void StageSelectScene::goToStage6(cocos2d::Ref * pSender)
{
	//音を鳴らす
	int sound = experimental::AudioEngine::play2d("Sounds/select.mp3");

	//----------------------------------------------------------------------------
	auto nextScene = PlayScene::createScene(Stage6);
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//----------------------------------------------------------------------------
}
//------------------------------------
//@! ステージ7に移動
//@! ボタンのRef
//------------------------------------
void StageSelectScene::goToStage7(cocos2d::Ref * pSender)
{
	//音を鳴らす
	int sound = experimental::AudioEngine::play2d("Sounds/select.mp3");

	//----------------------------------------------------------------------------
	auto nextScene = PlayScene::createScene(Stage7);
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//----------------------------------------------------------------------------
}
//------------------------------------
//@! ステージ8に移動
//@! ボタンのRef
//------------------------------------
void StageSelectScene::goToStage8(cocos2d::Ref * pSender)
{
	//音を鳴らす
	int sound = experimental::AudioEngine::play2d("Sounds/select.mp3");

	//----------------------------------------------------------------------------
	auto nextScene = PlayScene::createScene(Stage8);
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//----------------------------------------------------------------------------
}
//------------------------------------
//@! ステージ9に移動
//@! ボタンのRef
//------------------------------------
void StageSelectScene::goToStage9(cocos2d::Ref * pSender)
{
	//音を鳴らす
	int sound = experimental::AudioEngine::play2d("Sounds/select.mp3");

	//----------------------------------------------------------------------------
	auto nextScene = PlayScene::createScene(Stage9);
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//----------------------------------------------------------------------------
}
//------------------------------------
//@! ステージ10に移動
//@! ボタンのRef
//------------------------------------
void StageSelectScene::goToStage10(cocos2d::Ref * pSender)
{
	//音を鳴らす
	int sound = experimental::AudioEngine::play2d("Sounds/select.mp3");

	//----------------------------------------------------------------------------
	auto nextScene = PlayScene::createScene(Stage10);
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//----------------------------------------------------------------------------
}
//------------------------------------
//@! メニューに戻る
//@! ボタンのRef
//------------------------------------
void StageSelectScene::backToMenu(cocos2d::Ref * pSender)
{
	//----------------------------------------------------------------------------
	auto nextScene = GameMenu::createScene();
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//----------------------------------------------------------------------------
}
//-----------------------------------------------------------------