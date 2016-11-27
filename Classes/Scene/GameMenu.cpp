//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/6/11
//!	
//!	GameMenu.cpp
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//-----------------------------------------------------------------------------
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "StageSelectScene.h"
#include "PlayScene.h"
#include "Stage/StageManager.h"
#include "Tutorial.h"
#include "../EventListenerGesture.h"
#include "audio\include\AudioEngine.h"
#include "GameMenu.h"
#include "RuleScene.h"
//----------------------------------------------------------------------------
USING_NS_CC;

using namespace cocostudio::timeline;
//------------------------------------
//@! シーンを作成
//------------------------------------
Scene* GameMenu::createScene()
{
	//----------------------------------------------------------------------------
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
	//----------------------------------------------------------------------------
}

//------------------------------------
//@! 初期化
//------------------------------------
bool GameMenu::init()
{
	//----------------------------------------------------------------------------
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//-----------------------------------------
	this->setKeyboardEnabled(true);
	//-----------------------------------------

	experimental::AudioEngine::stopAll();

	//音を鳴らす-----------------------------------------------------------
	int bgm = experimental::AudioEngine::play2d("Sounds/menu.mp3");
	experimental::AudioEngine::setVolume(bgm, 0.5);
	experimental::AudioEngine::setLoop(bgm, true);


	//バックグラウンド作成--------------------------------------------------

	Sprite* bg = Sprite::create("stage_bg.png");
	bg->setPosition(Vec2(480.0f / 2, 800.0f / 2));
	this->addChild(bg);
	//----------------------------------------------------------------------

	//パーティクルの作成---------------------------------------------------
	CCParticleSystemQuad* titleStar = CCParticleSystemQuad::create("Title/particlestar.plist");
	titleStar->resetSystem();
	titleStar->setPosition(Vec2(480 / 2, 600));
	titleStar->setScale(0.5f);
	titleStar->setScaleY(1.5f);
	this->addChild(titleStar);

	CCParticleSystemQuad* lightleft = CCParticleSystemQuad::create("Menu/light.plist");
	lightleft->resetSystem();
	lightleft->setPosition(Vec2(0, 50));
	this->addChild(lightleft);

	CCParticleSystemQuad* lightright = CCParticleSystemQuad::create("Menu/light.plist");
	lightright->resetSystem();
	lightright->setPosition(Vec2(480, 50));
	this->addChild(lightright);
	//----------------------------------------------------------------------



	//チュートリアルボタン---------------------------------------------------
	MenuItemImage* stageSelect = MenuItemImage::create("Menu/play1.png",
		"Menu/play2.png",
		CC_CALLBACK_1(GameMenu::showStageSelectScene, this));
	stageSelect->setPosition(Vec2(240.0f, 480.0f));
	stageSelect->setScale(0.0001);
	//ステージ１--------------------------------------------------------------
	MenuItemImage* tutorial = MenuItemImage::create("Menu/tutorial1.png",
		"Menu/tutorial2.png",
		CC_CALLBACK_1(GameMenu::showTutorialScene, this));
	tutorial->setPosition(Vec2(240.0f, 600.0f));
	tutorial->setScale(0.0001);
	//ステージ２--------------------------------------------------------------
	MenuItemImage* rule = MenuItemImage::create("Menu/rule1.png",
		"Menu/rule2.png",
		CC_CALLBACK_1(GameMenu::showRules, this));
	rule->setPosition(Vec2(240.0f,360.0f));
	rule->setScale(0.0001);
	//ステージ３---------------------------------------------------------------
	MenuItemImage* close = MenuItemImage::create("Menu/quit1.png",
		"Menu/quit2.png",
		CC_CALLBACK_1(GameMenu::closeGame, this));
	close->setPosition(Vec2(240.0f, 240.0f));
	close->setScale(0.0001);
	//-----------------------------------------------------------------

	//アクション-------------------------------------------------------

	ScaleTo* playScale1 = ScaleTo::create(0.5, 1.0f, 0.0f);
	ScaleTo* playScale2 = ScaleTo::create(0.5, 1.0f, 1.0f);
	DelayTime* delay1 = DelayTime::create(0.5);
	Sequence* seq1 = Sequence::create(playScale1, delay1, playScale2, nullptr);
	stageSelect->runAction(seq1);

	ScaleTo* tutorialScale1 = ScaleTo::create(0.5, 1.0f, 0.0f);
	ScaleTo* tutorialScale2 = ScaleTo::create(0.5, 1.0f, 1.0f);
	Sequence* seq2 = Sequence::create(tutorialScale1, delay1, tutorialScale2, nullptr);
	tutorial->runAction(seq2);

	ScaleTo* ruleScale1 = ScaleTo::create(0.5, 1.0f, 0.0f);
	ScaleTo* ruleScale2 = ScaleTo::create(0.5, 1.0f, 1.0f);
	Sequence* seq3 = Sequence::create(ruleScale1, delay1, ruleScale2, nullptr);
	rule->runAction(seq3);

	ScaleTo* quitScale1 = ScaleTo::create(0.5, 1.0f, 0.0f);
	ScaleTo* quitScale2 = ScaleTo::create(0.5, 1.0f, 1.0f);
	Sequence* seq4 = Sequence::create(quitScale1, delay1, quitScale2, nullptr);
	close->runAction(seq4);

	//-----------------------------------------------------------------
	Menu* menuStage = Menu::create(stageSelect, tutorial, rule,
		close, NULL);// sprStage7, NULL);
	menuStage->setPosition(Vec2::ZERO);
	this->addChild(menuStage);
	//-----------------------------------------------------------------
	return true;
}

//-----------------------------------------
//@!ステージ選択を移動する
//@!Ref
//-----------------------------------------
void GameMenu::showStageSelectScene(cocos2d::Ref * pSender)
{
	//音を鳴らす
	int sound = experimental::AudioEngine::play2d("Sounds/select.mp3");
	//チュートリアルステージ作成-------------------------------------------------------------------
	this->removeAllChildren();
	//----------------------------------------------------------------------------
	auto nextScene = StageSelectScene::createScene();
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//----------------------------------------------------------------------------

}
//-----------------------------------------
//@!チュートリアルを移動する
//@!Ref
//-----------------------------------------
void GameMenu::showTutorialScene(cocos2d::Ref * pSender)
{
	//音を鳴らす
	int sound = experimental::AudioEngine::play2d("Sounds/select.mp3");
	//チュートリアルステージ作成-------------------------------------------------------------------
	this->removeAllChildren();
	//----------------------------------------------------------------------------
	auto nextScene = Tutorial::createScene();
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//----------------------------------------------------------------------------

}
//-----------------------------------------
//@!ルール画面に移動する
//@!Ref
//-----------------------------------------
void GameMenu::showRules(cocos2d::Ref * pSender)
{
	//音を鳴らす
	int sound = experimental::AudioEngine::play2d("Sounds/select.mp3");
	//ルール画面に移動-----------------------------------------------------
	auto nextScene = RuleScene::createScene();
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//---------------------------------------------------------------------
}
//-----------------------------------------
//@!ゲームを正常終了
//@!Ref
//-----------------------------------------
void GameMenu::closeGame(cocos2d::Ref * pSender)
{
	//正常終了-----------------------------------------------------
	Director::getInstance()->end();
	//---------------------------------------------------------
}
//-----------------------------------
//@!キーボードの押す
//@!キーコード,イベント
//-----------------------------------
void GameMenu::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	//正常終了---------------------------------------------------
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		Director::getInstance()->end();
	}
	//---------------------------------------------------------
}
