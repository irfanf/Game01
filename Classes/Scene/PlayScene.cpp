//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/4/27
//!	
//!	PlayScene.cpp
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

//------------------------------------
#include "PlayScene.h"
#include "Object/Bucket.h"
#include "Object/Paint.h"
#include "Stage/StageManager.h"
#include "../GameSystem.h"
#include "../DebugDrawNode.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "../GLESDebugDraw.h"
#include "GameClearScene.h"
#include "audio\include\AudioEngine.h"
#include <Box2D/Particle/b2ParticleSystem.h>
//------------------------------------

USING_NS_CC;
using namespace cocostudio::timeline;

Scene* PlayScene::createScene(int level)
{
	//----------------------------------------------------------------------------
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PlayScene::create(level);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
	//----------------------------------------------------------------------------
}

//------------------------------------
//@! クラス作成の時に作られているもの
//@! ワールド
//------------------------------------
PlayScene* PlayScene::create(int stageLevel)
{
	//----------------------------------------------------------------------
	PlayScene* sprite = new (std::nothrow) PlayScene();
	if (sprite && sprite->init(stageLevel))
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
	//----------------------------------------------------------------------
}

//------------------------------------
//@! 初期化
//------------------------------------	
bool PlayScene::init(int stageLevel)
{
	//---------------------------------------------------------------------
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	experimental::AudioEngine::stopAll();

	int bgm = experimental::AudioEngine::play2d("Sounds/clear.mp3");
	experimental::AudioEngine::setVolume(bgm, 0.5);
	experimental::AudioEngine::setLoop(bgm, true);



	initPhysics();
	m_stageLevel = stageLevel;

	//ステージ----------------------------------------------------------
	
	m_Stage = Stage::create(m_pWorld);
	m_Stage->createStage(m_stageLevel);
	this->addChild(m_Stage);
	
	//ゲームシステム-----------------------------------------------------
	m_gameSystem = GameSystem::create();
	m_gameSystem->resetOn(false);
	m_gameSystem->setLineLimit(m_Stage->getLineLimit());
	m_gameSystem->setTimeCount(10);
	this->addChild(m_gameSystem);

	//更新
	this->scheduleUpdate();
	//---------------------------------------------------------------------
	
	return true;
}

//------------------------------------
//@! 更新
//------------------------------------
void PlayScene::update(float dt)
{
	//線のリミットを取得する
	m_gameSystem->setLineLimit(m_Stage->getLineLimit());
	
	//爆発ボタンを押されたら、爆弾が爆発する
	if (m_gameSystem->explodeBomb())
	{
		for (int i = 0; i < m_Stage->getPaintNum(); i++)
		{
			//ゲーム開始
			m_Stage->getPaintBody(i)->setBombStatus(false);
			m_gameSystem->explodeOn(false);
		}	
	}

	//リセットボタンを押された処理
	if (m_gameSystem->resetStart())
	{
		//物理世界とデバックドローを消す
		delete m_pWorld;
		//m_debugDraw->removeFromParent();
		m_gameSystem->resetOn(false);

		//物理世界とデバックドローを作り直す
		createWorld();
		
		//ステージをリセットする
		m_Stage->removeFromParent();
		m_Stage = Stage::create(m_pWorld);
		m_Stage->createStage(m_stageLevel);
		this->addChild(m_Stage);

		m_gameSystem = GameSystem::create();
		this->addChild(m_gameSystem);
	}

	//勝利判定
	if (m_Stage->isCleared())
	{
		GameClearScene* stageClear = GameClearScene::create();
		stageClear->setSelectedStage(m_Stage->getSelectedStage());
		this->addChild(stageClear);
		this->unscheduleUpdate();
	}
	
	//---------------------------------------------------------------------
	//ステップ
	m_pWorld->Step(1.0f / 60.0f, 8, 3);

	//物理ワールド内のすべてのボディについて処理
	for (b2Body* body = m_pWorld->GetBodyList();
	body != nullptr;
		body = body->GetNext())
	{
		Sprite* spr = (Sprite*)body->GetUserData();

		if (spr != nullptr)
		{
			b2Vec2 pos = body->GetPosition();
			spr->setPosition(pos.x * PTM_RATIO, pos.y * PTM_RATIO);

			float rot = body->GetAngle();
			spr->setRotation(-CC_RADIANS_TO_DEGREES(rot));

		}
	}
	//---------------------------------------------------------------------
}
//------------------------------------
//@! Box2Dの初期化
//------------------------------------
void PlayScene::initPhysics()
{
	//物理世界の作成----------------------------------------------------------
	createWorld();
	//---------------------------------------------------------------------

}	
//------------------------------------
//@! デストラクター
//------------------------------------
PlayScene::~PlayScene()
{
	//解放---------------------------------------------------------------------
	delete m_pWorld;
	//---------------------------------------------------------------------
}
//------------------------------------
//@! ステージを取得する
//------------------------------------
Stage * PlayScene::getStage()
{
	return m_Stage;
}
//------------------------------------
//@! 物理世界を作る
//------------------------------------
void PlayScene::createWorld()
{
	//重力を作成---------------------------------------------------------------------
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);
	m_pWorld = new b2World(gravity);
	//---------------------------------------------------------------------

}


