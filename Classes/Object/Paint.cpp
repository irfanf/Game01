//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/4/27
//!	
//!	Paint.cpp
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

//------------------------------------
#include "Paint.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "../GLESDebugDraw.h"
#include "audio\include\AudioEngine.h"
//------------------------------------

USING_NS_CC;
using namespace cocostudio::timeline;

//--------------------------------------------------------------------------
const int PTM_RATIO = 32;
//--------------------------------------------------------------------------

//------------------------------------
//@! クラス作成の時に作られているもの
//@! ワールド
//------------------------------------
Paint* Paint::create(b2World* world)
{
	//--------------------------------------------------------------------------
	Paint *sprite = new (std::nothrow) Paint();
	if (sprite && sprite->init(world))
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
	//--------------------------------------------------------------------------
}

//------------------------------------
//@! 初期化
//------------------------------------
bool Paint::init(b2World* world)
{
	//--------------------------------------------------------------------------
	//////////////////////////////
	// 1. super init first
	if (!Node::init())
	{
		return false;
	}

	m_pWorld = world;

	//更新
	this->scheduleUpdate();
	
	return true;
	//--------------------------------------------------------------------------
}
//------------------------------------
//@! パーティクルの作成
//@! x,y座標とカラー
//------------------------------------
void Paint::createParticle(float x, float y, int color)
{
	//--------------------------------------------------------------------------
	//座標を引数からもらう
	m_x = x;
	m_y = y;

	Sprite* sprPaintColor;
	//スプライト------------------------------------------
	switch (color)
	{
	case RED:
		sprPaintColor = Sprite::create("redPaint.png");
		this->addChild(sprPaintColor);
		break;
	case BLUE:
		sprPaintColor = Sprite::create("bluePaint.png");
		this->addChild(sprPaintColor);
		break;
	case PURPLE:
		sprPaintColor = Sprite::create("purplePaint.png");
		this->addChild(sprPaintColor);
		break;
	case GREEN:
		sprPaintColor = Sprite::create("greenPaint.png");
		this->addChild(sprPaintColor);
		break;
	case ORANGE:
		sprPaintColor = Sprite::create("orangePaint.png");
		this->addChild(sprPaintColor);
		break;
	case PINK:
		sprPaintColor = Sprite::create("pinkPaint.png");
		this->addChild(sprPaintColor);
		break;
	case YELLOW:
		sprPaintColor = Sprite::create("yellowPaint.png");
		this->addChild(sprPaintColor);
		break;
	case NATTOU:
		sprPaintColor = Sprite::create("nattouPaint.png");
		this->addChild(sprPaintColor);
		break;

	}

	//パーティクルを囲む壁の作成--------------------------
	b2BodyDef paintgroundDef;
	//paintgroundDef.position.Set(0, 0);
	paintgroundDef.position.Set((x + 50) / PTM_RATIO, (y + 50) / PTM_RATIO);
	paintgroundDef.type = b2_staticBody;
	paintgroundDef.userData = sprPaintColor;

	b2Body* paintGroundBody;
	paintGroundBody = m_pWorld->CreateBody(&paintgroundDef);


	//頂点---------------------------------------
	b2Vec2 topLeft(-1.5, 1.5);
	b2Vec2 topRight(1.5, 1.5);
	b2Vec2 bottomLeft(-1.5,0.96-1.5);
	b2Vec2 bottomRight(1.5, 0.96-1.5);
	b2Vec2 gateTopLeft(1.5/2 - 0.96, 0.32-1.5);
	b2Vec2 gateTopRight(1.5/2 - 0.63, 0.32-1.5);
	b2Vec2 gateBottomLeft(1.5/2 - 0.96, -1.5);
	b2Vec2 gateBottomRight(1.5/2 - 0.63, -1.5);

	b2EdgeShape paintGroundBox;

	b2FixtureDef fd;
	fd.density = 1.0f;
	fd.shape = &paintGroundBox;


	//描画--------------------------------------
	paintGroundBox.Set(topLeft, topRight);
	paintGroundBody->CreateFixture(&fd);
	
	paintGroundBox.Set(topLeft, bottomLeft);
	paintGroundBody->CreateFixture(&fd);

	paintGroundBox.Set(topRight, bottomRight);
	paintGroundBody->CreateFixture(&fd);

	paintGroundBox.Set(bottomLeft, gateTopLeft);
	paintGroundBody->CreateFixture(&fd);

	paintGroundBox.Set(bottomRight, gateTopRight);
	paintGroundBody->CreateFixture(&fd);

	paintGroundBox.Set(gateTopLeft, gateBottomLeft);
	paintGroundBody->CreateFixture(&fd);

	paintGroundBox.Set(gateTopRight, gateBottomRight);
	paintGroundBody->CreateFixture(&fd);


	//パーティクルデフの作成---------------------------------------------------
	b2ParticleSystemDef particleSystemDef;
	particleSystemDef.density = 1.0f;
	particleSystemDef.radius = 2.0f / PTM_RATIO;
	m_particleSystem = m_pWorld->CreateParticleSystem(&particleSystemDef);

	//パーティクルの形
	b2CircleShape shape;
	shape.m_radius = 1.0f;

	//パーティクルの作成
	m_pParticleDef.flags = b2_waterParticle;
	m_pParticleDef.shape = &shape;

	//座標設定
	m_pParticleDef.position.Set((x+50) / PTM_RATIO, (y+50) / PTM_RATIO);
	//カラー設定
	setColor(color);

	//描画
	m_particleSystem->CreateParticleGroup(m_pParticleDef);

	//ふたを作る-----------------------------------------------------
	
	//ふたの形
	b2PolygonShape capShape;
	capShape.SetAsBox(0.5f,0.25f);

	//爆弾の作成
	m_Bomb = Sprite::create("bom.png");
	m_Bomb->setScale(0.1);
	this->addChild(m_Bomb);

	//爆弾のボディの作成
	b2BodyDef capBodyDef;
	capBodyDef.position.Set((x + 50) / PTM_RATIO, (y - 5)/PTM_RATIO);
	capBodyDef.type = b2_staticBody;
	capBodyDef.userData = m_Bomb;
	
	m_capBody = m_pWorld->CreateBody(&capBodyDef);

	b2FixtureDef capFixtureDef;
	capFixtureDef.shape = &capShape;
	capFixtureDef.density = 1.0f;

	m_capBody->CreateFixture(&capFixtureDef);
	
	//爆弾のアクション--------------------------------------------
	auto scale = ScaleBy::create(4, 3);
	auto delay = DelayTime::create(6);
	auto seq1 = Sequence::create(delay, scale, nullptr);
	m_Bomb->runAction(seq1);
	//------------------------------------------------------------


	//蓋の初期化状態
	m_Closed = true;


//-------------------------------------------------------------
}
//------------------------------------
//@! 更新
//@! 時間
//------------------------------------
void Paint::update(float dt)
{
	//--------------------------------------------------------------------------
	//蓋閉まっているときの処理
	if (m_Closed)
	{
		//カウントする
		m_count++;
	
		//時間がきたら蓋が消える
		if (m_count >= (10 * 60))
		{
			
			m_count = 0;
			m_Closed = false;
		}
	}

	//蓋が破壊されたら
	if (!m_Closed)
	{
		//ボディーを破壊する
		if (m_capBody)
		{
			m_pWorld->DestroyBody(m_capBody);
			m_capBody = nullptr;
		}
		if (m_Bomb)
		{
			m_Bomb->removeFromParent();
			//爆発を作る
			CCParticleSystemQuad* explosion = CCParticleSystemQuad::create("ice_particle.plist");
			explosion->resetSystem();
			explosion->setPosition(Vec2(m_x + 50, m_y));
			explosion->setScale(0.5f);
			this->addChild(explosion);
			m_Bomb = nullptr;
		}

		
		m_Closed = true;


	}
	//--------------------------------------------------------------------------
}
//------------------------------------
//@! パーティクルシステムを取得
//@! パーティクルシステム
//------------------------------------
b2ParticleSystem * Paint::getParticleSystem()
{
	//--------------------------------------------------------------------------
	//パーティクルシステムを返す
	return m_particleSystem;
	//--------------------------------------------------------------------------
}
//------------------------------------
//@! カラーを設定する
//@! カラー
//------------------------------------
void Paint::setColor(int color)
{
	//カラーを変える--------------------------------------------------------------------------
	switch (color)
	{
	case RED:
		m_pParticleDef.color.Set(255, 0, 0, 255);
		break;
	case BLUE:
		m_pParticleDef.color.Set(0, 0, 255, 255);
		break;
	case PURPLE:
		m_pParticleDef.color.Set(255, 0, 255, 255);
		break;
	case GREEN:
		m_pParticleDef.color.Set(0, 255, 0, 255);
		break;
	case ORANGE:
		m_pParticleDef.color.Set(255, 125, 0, 255);
		break;
	case YELLOW:
		m_pParticleDef.color.Set(255, 235, 0, 255);
		break;
	case BLACK:
		m_pParticleDef.color.Set(0, 0, 0, 255);
		break;
	case PINK:
		m_pParticleDef.color.Set(220, 130, 220, 255);
		break;
	case NATTOU:
		m_pParticleDef.color.Set(150, 117, 2, 255);
		break;
	}
	//--------------------------------------------------------------------------
}
//--------------------------------------------------------------------------


