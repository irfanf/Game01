//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/6/15
//!	
//!	RuleScene.cpp
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#pragma execution_character_set("utf-8")
//---------------------------------------------------------------------
#include "GameMenu.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Stage/StageManager.h"
#include "RuleScene.h"
#include "audio\include\AudioEngine.h"
//---------------------------------------------------------------------
USING_NS_CC;

using namespace cocostudio::timeline;


//---------------------------------------------------------------------
//------------------------------------
//@! クラス作成
//------------------------------------
Scene* RuleScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = RuleScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

//------------------------------------
//@! クラスの初期化
//------------------------------------
bool RuleScene::init()
{

	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//タッチしたら移動
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(RuleScene::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	m_ruleNum = 0;
	m_ruleFlag = false;

	Sprite* bg = Sprite::create("Rule/rule_bg.png");
	bg->setAnchorPoint(Vec2::ZERO);
	this->addChild(bg);

	m_hint = Label::create("", "fonts/KodomoRounded.otf", 20);
	m_hint->setPosition(Vec2(480/2, 50));
	m_hint->setColor(Color3B::BLACK);
	this->addChild(m_hint);
	
	m_pointer = Sprite::create("Rule/arrow.png");
	//m_pointer->setAnchorPoint(Vec2(30, 90));
	m_pointer->setPosition(Vec2(480/2,800/2));
	this->addChild(m_pointer);
	


	//MoveBy* move1 = MoveBy::create(0.3, Vec2(0, 20));
	//MoveBy* move2 = MoveBy::create(0.3, Vec2(0, -20));
	//Sequence* seq = Sequence::create(move1, move2, nullptr);
	//m_rep = RepeatForever::create(seq);
	//


	this->scheduleUpdate();

	//-----------------------------------------------------------------
	return true;
}
bool RuleScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	int sound = experimental::AudioEngine::play2d("Sounds/select1.mp3");

	m_ruleNum++;
	
	if (m_ruleNum >= RULE_NUM)
	{
		//移動先シーンの作成
		auto scene = GameMenu::createScene();
		auto transition = TransitionFade::create(1.0f, scene);
		Director::getInstance()->replaceScene(transition);
	}
	return false;
}
//-----------------------------------
//@! 更新
//@! 時間
//-----------------------------------
void RuleScene::update(float dt)
{
	switch (m_ruleNum)
	{
		case RULE1:
			m_hint->setString("このゲームはシロップをかき氷にかけるゲーム");
			m_pointer->setVisible(false);
			break;

		case RULE2:
			m_hint->setString("ビンからかき氷まで線を引いてシロップを流す");
			m_pointer->setRotation(45);
			m_pointer->setPosition(Vec2(65,800-330));
			m_pointer->setVisible(true);
			break;

		case RULE3:
			m_hint->setString("これは線の数。この数まで線が引けます");
			m_pointer->setRotation(0);
			m_pointer->setPosition(Vec2(80, 800 - 180));
			m_pointer->setVisible(true);

			break;
		case RULE4:
			m_hint->setString("これは出来上がりまでの%");
			m_pointer->setRotation(0);
			m_pointer->setPosition(Vec2(80, 800 - 100));
			m_pointer->setVisible(true);
			break;
		case RULE5:
			m_hint->setString("このボタンは開始ボタン");
			m_pointer->setRotation(0);
			m_pointer->setPosition(Vec2(250, 800 - 160));
			m_pointer->setVisible(true);
			break;
		case RULE6:
			m_hint->setString("このボタンリセットボタン,何回もやり直せるよ");
			m_pointer->setRotation(0);
			m_pointer->setPosition(Vec2(335, 800 - 160));
			m_pointer->setVisible(true);
			break;
		case RULE7:
			m_hint->setString("このれはステージメニューにもどるボタン");
			m_pointer->setRotation(0);
			m_pointer->setPosition(Vec2(410, 800 - 160));
			m_pointer->setVisible(true);
			break;
		case RULE8:
			m_hint->setString("くわしくはチュートリアルをやってみましょう！");
			m_pointer->setVisible(false);
			break;
		
	}

}
//void RuleScene::runRuleActionLine()
//{
//	MoveTo* move = MoveTo::create(1.0f, Vec2(270, 800 - 580));
//	m_pointer->runAction(move);
//}
//
//void RuleScene::runRuleActionMove()
//{
//	/*if (m_ruleFlag)
//	{*/
//		MoveBy* move1 = MoveBy::create(0.3, Vec2(0, 10));
//		MoveBy* move2 = MoveBy::create(0.3, Vec2(0, -10));
//		Sequence* seq = Sequence::create(move1, move2, nullptr);
//		RepeatForever* rep = RepeatForever::create(seq);
//		m_pointer->runAction(rep);
//		//m_ruleFlag = false;
//	//}
//}
