//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/5/26
//!	
//!	GameSystem.cpp
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#pragma execution_character_set("utf-8")
//---------------------------------------------------------------------
#include "GameSystem.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Stage/StageManager.h"
#include "Scene/PlayScene.h"
#include "Scene/GameMenu.h"
#include "audio\include\AudioEngine.h"
//---------------------------------------------------------------------
USING_NS_CC;

using namespace cocostudio::timeline;

//---------------------------------------------------------------------
//------------------------------------
//@! クラス作成
//------------------------------------
Scene* GameSystem::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameSystem::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

//------------------------------------
//@! クラスの初期化
//------------------------------------
bool GameSystem::init()
{

	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//-----------------------------------------
	this->setKeyboardEnabled(true);
	//-----------------------------------------

	//リセットの初期化
	m_reset = false;
	m_explode = false;

	//初期化値
	m_timeCount = 10;
	m_lineLimit = 0;


	//メニューボタンの作成------------------------------------------------

	//選択画面移動するボタン
	MenuItemImage* menuButton = MenuItemImage::create("menuButton1.png",
		"menuButton2.png",
		CC_CALLBACK_1(GameSystem::backToStageSelect, this));
	menuButton->setPosition(Vec2(420.0f, 720.0f));
	menuButton->setScale(0.6);
	//-----------------------------------------------------------------
	//リセットボタン
	MenuItemImage* resetButton = MenuItemImage::create("reset.png",
		"reset2.png",
		CC_CALLBACK_1(GameSystem::reset, this));
	resetButton->setPosition(Vec2(350.0f, 720.0f));
	resetButton->setScale(0.6);
	//-----------------------------------------------------------------
	//爆発ボタン
	MenuItemImage* explodeButton = MenuItemImage::create("launchButton1.png",
		"launchButton2.png",
		CC_CALLBACK_1(GameSystem::explode, this));
	explodeButton->setPosition(Vec2(270.0f, 720.0f));
	explodeButton->setScale(0.6);

	//-----------------------------------------------------------------
	//メニューの作成
	auto menu = Menu::create(menuButton,resetButton, explodeButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	//-----------------------------------------------------------------
	
	//カウントラベル
	m_countLabel = Label::create("", "fonts/Marker Felt.ttf", 30);
	m_countLabel->setPosition(Vec2(270, 720.0f));
	m_countLabel->setColor(Color3B::WHITE);
	this->addChild(m_countLabel);

	//残りの線
	m_sliderLabel = Label::create("", "fonts/KodomoRounded.otf", 30);
	m_sliderLabel->setPosition(Vec2(100, 660));
	m_sliderLabel->setColor(Color3B::WHITE);
	this->addChild(m_sliderLabel);

	this->scheduleUpdate();

	//-----------------------------------------------------------------
	return true;
}
//-------------------------------------
//@! メッセージボックスを消す
//@! pSender
//------------------------------------
void GameSystem::cancelMenu(cocos2d::Ref * pSender)
{
	//---------------------------------------------
	//メッセージボックスを消す
	m_bg->removeFromParent();
	m_msgsBox->removeFromParent();
	m_menu->removeFromParent();
	//---------------------------------------------
}
//------------------------------------
//@! メッセージボックスを表示
//@! Ref
//------------------------------------
void GameSystem::backToStageSelect(cocos2d::Ref * pSender)
{
	//----------------------------------------------
	//背景
	m_bg = Sprite::create("gameClearBG.png");
	m_bg->setAnchorPoint(Vec2(0, 0));
	this->addChild(m_bg);

	//メッセージボックス
	m_msgsBox = Sprite::create("backtomenu.png");
	m_msgsBox->setPosition(480 / 2, 800 / 2);
	this->addChild(m_msgsBox);

	//-------------------------------------------------------------------
	//ボタンの作成
	MenuItemImage* yesButton = MenuItemImage::create("yes.png", 
				"yes2.png", CC_CALLBACK_1(GameSystem::backToGameMenu, this));
	yesButton->setPosition(Vec2(180,370));

	MenuItemImage* noButton = MenuItemImage::create("no.png",
		"no2.png", CC_CALLBACK_1(GameSystem::cancelMenu, this));
	noButton->setPosition(Vec2(300, 370));

	m_menu = Menu::create(yesButton,noButton, NULL);
	m_menu->setPosition(Vec2::ZERO);
	this->addChild(m_menu);
	//-------------------------------------------------------------------
}
//------------------------------------
//@! メッセージボックスを表示
//@! Ref
//------------------------------------
void GameSystem::backToGameMenu(cocos2d::Ref * pSender)
{
	//------------------------------------------------------------------
	//ステージ選択に戻る
	auto nextScene = GameMenu::createScene();
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//------------------------------------------------------------------

}
//------------------------------------
//@! 爆発ボタン
//@! Ref
//------------------------------------
void GameSystem::explode(cocos2d::Ref * pSender)
{
	//音を鳴らす---------------------------------------------------------
	int sound = experimental::AudioEngine::play2d("Sounds/button.mp3");
	//-----------------------------------------------------
	m_timeCount = 0;
	m_explode = true;
	//-----------------------------------------------------

}
//-----------------------------------
//@!キーボードの押す
//@!キーコード,イベント
//-----------------------------------
void GameSystem::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	//ESC押された時の処理--------------------------------------------------
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		//ステージ選択に戻る---------------------------------------
		auto nextScene = GameMenu::createScene();
		auto transition = TransitionFade::create(1.0f, nextScene);
		Director::getInstance()->replaceScene(transition);
		//---------------------------------------------------------
	}
	//------------------------------------------------------------------------
}

//------------------------------------
//@! ステージ選択画面に戻る
//@! Ref
//------------------------------------
void GameSystem::reset(cocos2d::Ref * pSender)
{
	//------------------------------------------------------------------
	//リセットする
	m_reset = true;

	//------------------------------------------------------------------

}
//------------------------------------
//@! リセット有効か無効か
//@! リセット
//------------------------------------
void GameSystem::resetOn(bool reset)
{
	//------------------------------------------------------------------
	//リセットの設定
	m_reset = reset;
	//------------------------------------------------------------------
}
//------------------------------------
//@! リセットする
//@! リセットの状態を返す
//------------------------------------
bool GameSystem::resetStart()
{
	//------------------------------------------------------------------
	//リセットを返す
	return m_reset;
	//------------------------------------------------------------------
}
//------------------------------------
//@! 更新
//@! 時間
//------------------------------------
void GameSystem::update(float dt)
{
	//カウント表示
	if (m_timeCount >= 0)
	{
		m_timeCount = m_timeCount - dt;
		String* str = String::createWithFormat("%d", (int)m_timeCount);
		m_countLabel->setString(str->getCString());
	}

	//スライダーリミットを表示
	String* str = String::createWithFormat("線 = %d", m_lineLimit);
	m_sliderLabel->setString(str->getCString());

}
//------------------------------------
//@! 爆発有効か無効か
//@! 爆発状態
//------------------------------------
void GameSystem::explodeOn(bool explode)
{
	m_explode = explode;
}
//------------------------------------
//@! 強制開始
//@! 爆発の状態を返す
//------------------------------------
bool GameSystem::explodeBomb()
{
	//------------------------------------------------------------------
	//リセットを返す
	return m_explode;
	//------------------------------------------------------------------

}
//------------------------------------
//@! 時間を設定
//@! 時間
//------------------------------------
void GameSystem::setTimeCount(float timeCount)
{
	m_timeCount = timeCount;
}
//------------------------------------
//@! 引ける線の数をセットする
//@! 線の数
//------------------------------------
void GameSystem::setLineLimit(int limit)
{
	m_lineLimit = limit;
}
