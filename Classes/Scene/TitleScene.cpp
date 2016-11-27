//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/4/27
//!	
//!	TitleScene.cpp
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//--------------------------------------------
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TitleScene.h"
#include "GameMenu.h"
#include "../EventListenerGesture.h"
#include "audio\include\AudioEngine.h"

//--------------------------------------------
USING_NS_CC;

using namespace cocostudio::timeline;
//--------------------------------------------
//------------------------------------
//@! ステージの作成
//------------------------------------
Scene* TitleScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = TitleScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

//------------------------------------
//@! ステージの初期化
//------------------------------------
bool TitleScene::init()
{
	//--------------------------------------------
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//バックグラウンド作成--------------------------------------------------

	Sprite* background = Sprite::create("Title/bg.png");
	background->setPosition(Vec2(480.0f / 2, 800.0f / 2));
	this->addChild(background);


	//パーティクルの作成-----------------------------------------------------------------------

	CCParticleSystemQuad* titleStar = CCParticleSystemQuad::create("Title/particlestar.plist");
	titleStar->resetSystem();
	titleStar->setPosition(Vec2(480 / 2, 600));
	titleStar->setScale(0.5);
	this->addChild(titleStar);

	CCParticleFireworks* par = CCParticleFireworks::create();
	par->setPosition(Vec2(0.0f, 650.0f));
	par->setRotation(30.0f);
	par->setScale(1.5);
	this->addChild(par);

	CCParticleFireworks* par2 = CCParticleFireworks::create();
	par2->setPosition(Vec2(480.0f, 650.0f));
	par2->setRotation(-30.0f);
	par2->setScale(1.5);
	this->addChild(par2);



	//スプライト作成--------------------------------------------------

	//スタートボタンを作成
	m_pTitle = Sprite::create("Title/start.png");
	m_pTitle->setPosition(Vec2(240.0f, 300.0f));
	this->addChild(m_pTitle);

	//スタートボタンにパーティクルをつける
	CCParticleSystemQuad* particle = CCParticleSystemQuad::create("star.plist");
	particle->resetSystem();
	//particle->setPosition(Vec2(0.0f, 650.0f));
	particle->setScale(0.25);
	particle->setAnchorPoint(Vec2::ZERO);
	particle->setPosition(Vec2(100,20));
	m_pTitle->addChild(particle);

	//上下に動かす--------------------------------------------------
	MoveBy* moveUp = MoveBy::create(0.3, Vec2(0, 10));
	MoveBy* moveDown = MoveBy::create(0.3, Vec2(0, -10));
	Sequence* seq_move = Sequence::create(moveUp, moveDown, nullptr);
	Repeat* rep_move = Repeat::create(seq_move, -1);
	m_pTitle->runAction(rep_move);
	//--------------------------------------------------------------
	
	m_bgm = experimental::AudioEngine::play2d("Sounds/bgm.mp3");
	experimental::AudioEngine::setVolume(m_bgm, 0.5);
	experimental::AudioEngine::setLoop(m_bgm, true);

	//Event Listenerの作成-----------------------------------------------------------
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TitleScene::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//------------------------------------------------------------------
	return true;

}
//------------------------------------
//@! タッチをする
//@! タッチとイベント
//------------------------------------
bool TitleScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	experimental::AudioEngine::stop(m_bgm);

	//音を鳴らす
	int clickSound = experimental::AudioEngine::play2d("Sounds/select.mp3");

	//----------------------------------------------------------
	auto nextScene = GameMenu::createScene();
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	
	//-----------------------------------------------------------
	return false;

}


