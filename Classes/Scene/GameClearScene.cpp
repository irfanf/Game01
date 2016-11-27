//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/5/20
//!	
//!	GameClearScene.cpp
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//---------------------------------------------------------
#include "GameClearScene.h"
#include "cocostudio/CocoStudio.h"
#include "TitleScene.h"
#include "ui/CocosGUI.h"
#include "../EventListenerGesture.h"
#include "GameMenu.h"
#include "Stage/StageManager.h"
#include "PlayScene.h"
#include "audio\include\AudioEngine.h"
//---------------------------------------------------------
USING_NS_CC;

using namespace cocostudio::timeline;
//---------------------------------------------------------
//------------------------------------
//@! クラスの作成
//------------------------------------
GameClearScene* GameClearScene::create()
{
	//------------------------------------------------------------------
	GameClearScene *sprite = new (std::nothrow) GameClearScene();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	else
	{
		delete sprite;
		sprite = nullptr;
		return nullptr;
	}
	//------------------------------------------------------------------
}

//------------------------------------
//@! クラスの初期化
//------------------------------------
bool GameClearScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//バックグラウンド作成--------------------------------------------------
	//experimental::AudioEngine::stopAll();

	int sound = experimental::AudioEngine::play2d("Sounds/iyopon.mp3");

	//背景の作成
	Sprite* gameClearBG = Sprite::create("gameClearBG.png");
	gameClearBG->setAnchorPoint(Vec2::ZERO);
	this->addChild(gameClearBG);

	//パーティクル
	CCParticleSystemQuad* clearPar = CCParticleSystemQuad::create("clearPar.plist");
	clearPar->resetSystem();
	clearPar->setScale(0.5f);
	clearPar->setRotation(-15.0f);
	clearPar->setPosition(Vec2(480.0f/2, 650.0f));
	this->addChild(clearPar);

	//クリアの表示
	Sprite* clear = Sprite::create("gameClear.png");
	clear->setPosition(Vec2(480.0f / 2, 650.0f));
	this->addChild(clear);

	//氷のパーティクル
	CCParticleFlower* flowerPar = CCParticleFlower::create();
	flowerPar->setPosition(Vec2(480 / 2, 750 / 2));
	flowerPar->setScale(1.75);
	this->addChild(flowerPar);

	//かき氷を出す
	m_sprIce = Sprite::create("Stage/stage1_1.png");
	m_sprIce->setPosition(Vec2(480.0f / 2, 800.0f / 2));
	m_sprIce->setScale(0.0001);
	this->addChild(m_sprIce);


	//アクション-------------------------------------------------------
	
	//かき氷のアクション
	ScaleTo* scale = ScaleTo::create(0.5f, 2.0f);
	DelayTime* delay = DelayTime::create(0.5f);
	CallFunc* callFun = CallFunc::create(CC_CALLBACK_0(GameClearScene::showButton, this));
	Sequence* seq = Sequence::create(scale, delay, callFun, nullptr);
	m_sprIce->runAction(seq);

	//クリア字のアクション
	MoveBy* moveUp = MoveBy::create(0.3, Vec2(0.0f, 30.0f));
	MoveBy* moveDown = MoveBy::create(0.3, Vec2(0.0f, -30.0f));
	Sequence* seqMove = Sequence::create(moveUp, moveDown, nullptr);
	RepeatForever* rep = RepeatForever::create(seqMove);
	clear->runAction(rep);

	//------------------------------------------------------------------

	this->scheduleUpdate();

	return true;
}
//------------------------------------
//@! ステージを設定し、かき氷の味を変える
//@! ステージ
//------------------------------------
void GameClearScene::setSelectedStage(int stage)
{
	//ステージを代入する
	m_stageNow = stage;

	switch (m_stageNow)
	{
	case Tutorial1:
		m_sprIce->setTexture("Ice/green3.png");
		break;
	case Tutorial2:
		m_sprIce->setTexture("Ice/green3.png");
		
		break;
	case Tutorial3:
		m_sprIce->setTexture("Stage/tutorial3_2.png");
		break;
	case Stage1:
		m_sprIce->setTexture("Ice/blue3.png");
		break;
	case Stage2:
		m_sprIce->setTexture("Ice/yellow3.png");
		m_sprIce->setScale(0.25);
		break;
	case Stage3:
		m_sprIce->setTexture("Ice/orange3.png");
		m_sprIce->setScale(0.25);
		break;
	case Stage4:
		m_sprIce->setTexture("Stage/stage4_2.png");
		break;
	case Stage5:
		m_sprIce->setTexture("Stage/stage5_2.png");
		break;
	case Stage6:
		m_sprIce->setTexture("Stage/stage6_2.png");
		break;
	case Stage7:
		m_sprIce->setTexture("Stage/stage7_2.png");
		break;
	case Stage8:
		m_sprIce->setTexture("Stage/stage8_2.png");
		break;
	case Stage9:
		m_sprIce->setTexture("Stage/stage9_2.png");
		break;
	case Stage10:
		m_sprIce->setTexture("Ice/nattou3.png");
		m_sprIce->setScale(0.25);
		break;
	}
}
//------------------------------------
//@! バックボタンの描画
//------------------------------------
void GameClearScene::showButton()
{
	//ボタンの作成--------------------------------------------
	
	//メニューボタン
	MenuItemImage* backButton = MenuItemImage::create("menuButton1.png", "menuButton2.png",
		CC_CALLBACK_0(GameClearScene::backToStageSelectScene, this));
	backButton->setPosition(Vec2(100.0f, 100.0f));
	backButton->setScale(0.0001f);
	
	//次のステージのボタン
	m_nextButton = MenuItemImage::create("nextStage1.png", "nextStage2.png",
		CC_CALLBACK_0(GameClearScene::moveNextStage, this));
	m_nextButton->setPosition(Vec2(400.0f, 100.0f));
	m_nextButton->setScale(0.0001f);

	//ボタンのアクション---------------------------------------------------------------
	ScaleTo* backScale = ScaleTo::create(0.3f, 1);
	m_nextButton->runAction(backScale);

	DelayTime* wait = DelayTime::create(0.5f);
	ScaleTo* nextScale = ScaleTo::create(0.3f, 1);
	Sequence* nextSeq = Sequence::create(wait, nextScale, nullptr);
	backButton->runAction(nextSeq);
	//----------------------------------------------------------------------------------

	//ボタンを管理するメニューを作成
	auto menu = Menu::create(backButton, m_nextButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	//--------------------------------------------------------
}
//------------------------------------
//@! 更新
//------------------------------------
void GameClearScene::update(float dt)
{
	if (m_nextButton)
	{
		if (m_stageNow >= Stage10)
		{
			m_nextButton->setVisible(false);
		}
		else
		{
			m_nextButton->setVisible(true);
		}
	}
}
//------------------------------------
//@! StageSelectSceneに移動
//------------------------------------
void GameClearScene::backToStageSelectScene()
{
	//シーン移動-------------------------------------------------
	auto nextScene = GameMenu::createScene();
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//-----------------------------------------------------------

}
//------------------------------------
//@! StageSelectSceneに移動
//------------------------------------
void GameClearScene::moveNextStage()
{
	
	//次のステージに移動--------------------------------------------
	auto nextScene = PlayScene::createScene(m_stageNow + 1);
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//--------------------------------------------------------------

}
//-----------------------------------------------------------------

