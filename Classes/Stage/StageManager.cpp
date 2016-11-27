//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/5/7
//!	
//!	StageManager.cpp
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//------------------------------------------------------------
#pragma execution_character_set("utf-8")

#include "StageManager.h"
#include "Object/Paint.h"
#include "Object/Bucket.h"
#include "Object/BoxSlider.h"
#include "Scene/StageSelectScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Scene/GameClearScene.h"
#include "../GameSystem.h"
#include "audio\include\AudioEngine.h"
#include "../DebugDrawNode.h"


//------------------------------------------------------------
USING_NS_CC;
using namespace cocostudio::timeline;
//------------------------------------------------------------

//------------------------------------
//@! クラス作成の時に作られているもの
//@! ワールド
//------------------------------------
Stage* Stage::create(b2World* world)
{
	//--------------------------------------
	Stage *sprite = new (std::nothrow) Stage();
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
	//--------------------------------------
}
//------------------------------------
//@! ステージの作成
//@! ステージ
//------------------------------------
void Stage::createStage(int stage)
{
	//--------------------------------------------------------
	//タッチ可能
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	
	//勝利判定
	m_clear = false;
	m_selectedStage = stage;

	//バックグラウンド
	Sprite* bg = Sprite::create("wall.png");
	bg->setPosition(Vec2(480.0f / 2, 800.0f / 2));
	this->addChild(bg);

	//テクスチャー
	Sprite* wall = Sprite::create("wallheight.png");
	wall->setAnchorPoint(Vec2::ZERO);
	this->addChild(wall);

	//壁の設定
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0,0);
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.userData = wall;

	b2Body* groundBody;
	groundBody = m_pWorld->CreateBody(&groundBodyDef);

	//壁の座標設定
	b2Vec2 leftbottom(0,0);
	b2Vec2 rightbottom(480,0);
	b2Vec2 lefttop(0,640);
	b2Vec2 righttop(480, 640);
	
	leftbottom.x /= PTM_RATIO;
	leftbottom.y /= PTM_RATIO;
	rightbottom.x /= PTM_RATIO;
	rightbottom.y /= PTM_RATIO;
	lefttop.x /= PTM_RATIO;
	lefttop.y /= PTM_RATIO;
	righttop.x /= PTM_RATIO;
	righttop.y /= PTM_RATIO;

	//線の形
	b2EdgeShape groundBox;

	b2FixtureDef fd;
	fd.density = 1.0f;
	fd.shape = &groundBox;

	//描画--------------------------------------------------------
	
	groundBox.Set(lefttop, leftbottom);
	groundBody->CreateFixture(&fd);

	groundBox.Set(rightbottom, righttop);
	groundBody->CreateFixture(&fd);

	groundBox.Set(lefttop, righttop);
	groundBody->CreateFixture(&fd);


	
	//スライダーを描く-----------------------------------------

	//数の初期化
	m_bucketNum = 0;
	m_paintNum = 0;

	m_particleLabelNum = 0;
	m_ParticleCount = 0;
	m_pSliderBody = m_pWorld->CreateBody(&groundBodyDef);

	//移動するときのパーティクルの作成
	m_parClickMoved = CCParticleSystemQuad::create("line_click.plist");
	m_parClickMoved->resetSystem();
	m_parClickMoved->setScale(0.5);
	m_parClickMoved->setPosition(Vec2(1000, 1000));
	m_parClickMoved->setVisible(false);
	this->addChild(m_parClickMoved);

	//それぞれのステージに行く---------------------------------
	switch (m_selectedStage)
	{
	case Tutorial1:
		toTutorial1();
		break;
	case Tutorial2:
		toTutorial2();
		break;
	case Tutorial3:
		toTutorial3();
		break;
	case Stage1:
		toStage1();
		break;
	case Stage2:
		toStage2();
		break;
	case Stage3:
		toStage3();
		break;
	case Stage4:
		toStage4();
		break;
	case Stage5:
		toStage5();
		break;
	case Stage6:
		toStage6();
		break;
	case Stage7:
		toStage7();
		break;
	case Stage8:
		toStage8();
		break;
	case Stage9:
		toStage9();
		break;
	case Stage10:
		toStage10();
		break;
	}

	//パーティクル%---------------------------------------------------------------------
	for (int i = 0; i < m_bucketNum; i++)
	{
		m_particleLabel[i] = Label::create("","fonts/KodomoRounded.otf",23);
		m_particleLabel[i]->setPosition(Vec2(120, 750 - (i * 23)));
		this->addChild(m_particleLabel[i]);
	}
	//--------------------------------------------------------
}
//------------------------------------
//@! チュートリアルステージに移動
//------------------------------------
void Stage::toTutorial1()
{

	//スライダーのリミット
	m_SliderLimit = 1;
	//------------------------------------------
	//バックグラウンドの作成
	Sprite* tutor_bg = Sprite::create("Stage/Tutorial/tutorial1.png");
	tutor_bg->setAnchorPoint(Vec2::ZERO);
	this->addChild(tutor_bg);

	//-------------------------------------------

	//赤ペンキの作成
	m_pPaint[0] = Paint::create(m_pWorld);
	m_pPaint[0]->createParticle(400.0f/2, 540.0f, GREEN);
	m_paintNum++;
	this->addChild(m_pPaint[0]);

	//ドロー用
	auto debugDraw = DebugDrawNode::create(m_pWorld);
	this->addChild(debugDraw);

	//バケツの作成
	m_pBucket[0] = Bucket::create(m_pWorld);
	m_pBucket[0]->createBucket(520.0f/2, 20, bGREEN);
	m_bucketNum++;
	this->addChild(m_pBucket[0]);

	//-------------------------------------------
	
}
//------------------------------------
//@! チュートリアルステージに移動
//------------------------------------
void Stage::toTutorial2()
{
	//スライダーのリミット
	m_SliderLimit = 2;
	//------------------------------------------
	//バックグラウンドの作成
	Sprite* tutor_bg = Sprite::create("Stage/Tutorial/tutorial2.png");
	tutor_bg->setAnchorPoint(Vec2::ZERO);
	this->addChild(tutor_bg);
	//-------------------------------------------

	//赤ペンキの作成
	m_pPaint[0] = Paint::create(m_pWorld);
	m_pPaint[0]->createParticle(400.0f / 2, 540.0f, GREEN);
	m_paintNum++;
	this->addChild(m_pPaint[0]);

	//ドロー用
	auto debugDraw = DebugDrawNode::create(m_pWorld);
	this->addChild(debugDraw);

	//バケツの作成
	m_pBucket[0] = Bucket::create(m_pWorld);
	m_pBucket[0]->createBucket(400.0f / 2, 20, bGREEN);
	m_bucketNum++;
	this->addChild(m_pBucket[0]);


	IceBlock* box = IceBlock::create(m_pWorld);
	box->createIceBlock(500.0f / 2, 300.0f, TYPE0);
	this->addChild(box);
	

	//-------------------------------------------

}
//------------------------------------
//@! チュートリアルステージに移動
//------------------------------------
void Stage::toTutorial3()
{

	//スライダーのリミット
	m_SliderLimit = 2;
	//------------------------------------------
	//バックグラウンドの作成
	Sprite* tutor_bg = Sprite::create("Stage/Tutorial/tutorial3.png");
	tutor_bg->setAnchorPoint(Vec2::ZERO);
	this->addChild(tutor_bg);
	//-------------------------------------------

	//ペンキを作成する
	m_pPaint[0] = Paint::create(m_pWorld);
	m_pPaint[0]->createParticle(150.0f, 540.0f, GREEN);
	m_paintNum++;
	this->addChild(m_pPaint[0]);

	m_pPaint[1] = Paint::create(m_pWorld);
	m_pPaint[1]->createParticle(250.0f , 540.0f, BLUE);
	m_paintNum++;
	this->addChild(m_pPaint[1]);

	//ドロー用
	auto debugDraw = DebugDrawNode::create(m_pWorld);
	this->addChild(debugDraw);

	//ペンキバケツ
	m_pBucket[0] = Bucket::create(m_pWorld);
	m_pBucket[0]->createBucket(0.0f, 20.0f, bGREEN);
	m_bucketNum++;
	this->addChild(m_pBucket[0]);

	m_pBucket[1] = Bucket::create(m_pWorld);
	m_pBucket[1]->createBucket(380.0f, 20.0f, bBLUE);
	m_bucketNum++;
	this->addChild(m_pBucket[1]);

	//-------------------------------------------

}
//------------------------------------
//@! ステージ１に移動
//------------------------------------
void Stage::toStage1()
{

	//スライダーのリミット
	m_SliderLimit = 2;

	//--------------------------------------------

	m_pPaint[0] = Paint::create(m_pWorld);
	m_pPaint[0]->createParticle(450.0f/2, 540.0f, BLUE);
	m_paintNum++;
	this->addChild(m_pPaint[0]);

	//ドロー用
	auto debugDraw = DebugDrawNode::create(m_pWorld);
	this->addChild(debugDraw);

	m_pBucket[0] = Bucket::create(m_pWorld);
	m_pBucket[0]->createBucket(450.0f/2, 20.0f, bBLUE);
	m_bucketNum++;
	this->addChild(m_pBucket[0]);

	IceBlock* box = IceBlock::create(m_pWorld);
	box->createIceBlock(500.0f/2, 300.0f,TYPE1);
	this->addChild(box);

	//--------------------------------------------

}
//------------------------------------
//@! ステージ2に移動
//------------------------------------
void Stage::toStage2()
{

	//スライダーのリミット
	m_SliderLimit = 2;

	//--------------------------------------------

	m_pPaint[0] = Paint::create(m_pWorld);
	m_pPaint[0]->createParticle(450.0f / 2, 540.0f, YELLOW);
	m_paintNum++;
	this->addChild(m_pPaint[0]);

	//ドロー用
	auto debugDraw = DebugDrawNode::create(m_pWorld);
	this->addChild(debugDraw);

	m_pBucket[0] = Bucket::create(m_pWorld);
	m_pBucket[0]->createBucket(450.0f / 2, 20.0f, bYELLOW);
	m_bucketNum++;
	this->addChild(m_pBucket[0]);

	//ボックススライダーの表示
	IceBlock* box1 = IceBlock::create(m_pWorld);
	box1->createIceBlock(280.0f, 180.0f, TYPE0);
	this->addChild(box1);

	IceBlock* box2 = IceBlock::create(m_pWorld);
	box2->createIceBlock(280.0f, 480.0f, TYPE0);
	this->addChild(box2);


	

}
//------------------------------------
//@! ステージ3に移動
//------------------------------------
void Stage::toStage3()
{

	//スライダーのリミット
	m_SliderLimit = 2;

	//--------------------------------------------

	m_pPaint[0] = Paint::create(m_pWorld);
	m_pPaint[0]->createParticle(0.0f, 540.0f, ORANGE);
	m_paintNum++;
	this->addChild(m_pPaint[0]);

	//ドロー用
	auto debugDraw = DebugDrawNode::create(m_pWorld);
	this->addChild(debugDraw);

	m_pBucket[0] = Bucket::create(m_pWorld);
	m_pBucket[0]->createBucket(380.0f, 20.0f, bORANGE);
	m_bucketNum++;
	this->addChild(m_pBucket[0]);

	//ボックススライダーの表示
	IceBlock* box[5];

	for (int i = 0; i < 5; i++)
	{
		box[i] = IceBlock::create(m_pWorld);
		box[i]->createIceBlock(240.0f, 0.0f + (i * 110), TYPE2);
		this->addChild(box[i]);
	}

}
//------------------------------------
//@! ステージ4に移動
//------------------------------------
void Stage::toStage4()
{
	//スライダーのリミット
	m_SliderLimit = 2;

	//-------------------------------------------
	//ペンキを作成する
	m_pPaint[0] = Paint::create(m_pWorld);
	m_pPaint[0]->createParticle(200.0f / 2, 540.0f, YELLOW);
	m_paintNum++;
	this->addChild(m_pPaint[0]);

	m_pPaint[1] = Paint::create(m_pWorld);
	m_pPaint[1]->createParticle(600.0f / 2, 540.0f, GREEN);
	m_paintNum++;
	this->addChild(m_pPaint[1]);

	//ドロー用
	auto debugDraw = DebugDrawNode::create(m_pWorld);
	this->addChild(debugDraw);

	//ペンキバケツ
	m_pBucket[0] = Bucket::create(m_pWorld);
	m_pBucket[0]->createBucket(600.0f / 2, 20.0f, bYELLOW);
	m_bucketNum++;
	this->addChild(m_pBucket[0]);

	m_pBucket[1] = Bucket::create(m_pWorld);
	m_pBucket[1]->createBucket(200.0f / 2, 20.0f, bGREEN);
	m_bucketNum++;
	this->addChild(m_pBucket[1]);

	//-------------------------------------------

}
//------------------------------------
//@! ステージ5に移動
//------------------------------------
void Stage::toStage5()
{
	//スライダーリミット
	m_SliderLimit = 3;

	//-----------------------------------------------------------
	//ペンキを作成する
	m_pPaint[0] = Paint::create(m_pWorld);
	m_pPaint[0]->createParticle(300, 540.0f, ORANGE);
	m_paintNum++;
	this->addChild(m_pPaint[0]);

	//ペンキを作成する
	m_pPaint[1] = Paint::create(m_pWorld);
	m_pPaint[1]->createParticle(50, 540.0f, GREEN);
	m_paintNum++;
	this->addChild(m_pPaint[1]);

	//ドロー用
	auto debugDraw = DebugDrawNode::create(m_pWorld);
	this->addChild(debugDraw);

	//ペンキバケツ
	m_pBucket[0] = Bucket::create(m_pWorld);
	m_pBucket[0]->createBucket(250.0f, 20.0f, bORANGE);
	m_bucketNum++;
	this->addChild(m_pBucket[0]);

	//ペンキバケツ
	m_pBucket[1] = Bucket::create(m_pWorld);
	m_pBucket[1]->createBucket(300.0f, 300.0f, bGREEN);
	m_bucketNum++;
	this->addChild(m_pBucket[1]);

}
//------------------------------------
//@! ステージ6に移動
//------------------------------------
void Stage::toStage6()
{
	//スライダーリミット
	m_SliderLimit = 3;

	//-----------------------------------------------------------
	//ペンキを作成する
	m_pPaint[0] = Paint::create(m_pWorld);
	m_pPaint[0]->createParticle(0, 540.0f, PINK);
	m_paintNum++;
	this->addChild(m_pPaint[0]);

	m_pPaint[1] = Paint::create(m_pWorld);
	m_pPaint[1]->createParticle(380, 540.0f, YELLOW);
	m_paintNum++;
	this->addChild(m_pPaint[1]);

	//ドロー用
	auto debugDraw = DebugDrawNode::create(m_pWorld);
	this->addChild(debugDraw);

	//ペンキバケツ
	m_pBucket[0] = Bucket::create(m_pWorld);
	m_pBucket[0]->createBucket(0.0f, 20.0f, bPINK);
	m_bucketNum++;
	this->addChild(m_pBucket[0]);

	//ペンキバケツ
	m_pBucket[1] = Bucket::create(m_pWorld);
	m_pBucket[1]->createBucket(0.0f, 220.0f, bYELLOW);
	m_bucketNum++;
	this->addChild(m_pBucket[1]);

	//お邪魔もの
	IceBlock* box = IceBlock::create(m_pWorld);
	box->createIceBlock(260.0f, 400.0f, TYPE1);
	this->addChild(box);
}
//------------------------------------
//@! ステージ7に移動
//------------------------------------
void Stage::toStage7()
{	
	//スライダーリミット
	m_SliderLimit = 3;

	//-----------------------------------------------------------
	//ペンキを作成する
	m_pPaint[0] = Paint::create(m_pWorld);
	m_pPaint[0]->createParticle(70.0f, 540.0f, RED);
	m_paintNum++;
	this->addChild(m_pPaint[0]);

	m_pPaint[1] = Paint::create(m_pWorld);
	m_pPaint[1]->createParticle(330.0f, 540.0f, ORANGE);
	m_paintNum++;
	this->addChild(m_pPaint[1]);

	//ドロー用
	auto debugDraw = DebugDrawNode::create(m_pWorld);
	this->addChild(debugDraw);

	//ペンキバケツ
	m_pBucket[0] = Bucket::create(m_pWorld);
	m_pBucket[0]->createBucket(330.0f, 20.0f, bRED);
	m_bucketNum++;
	this->addChild(m_pBucket[0]);

	//ペンキバケツ
	m_pBucket[1] = Bucket::create(m_pWorld);
	m_pBucket[1]->createBucket(70.0f, 20.0f, bORANGE);
	m_bucketNum++;
	this->addChild(m_pBucket[1]);

	IceBlock* box = IceBlock::create(m_pWorld);
	box->createIceBlock(50.0f, 500.0f, TYPE3);
	this->addChild(box);

	IceBlock* box1 = IceBlock::create(m_pWorld);
	box1->createIceBlock(430.0f, 500.0f, TYPE3);
	this->addChild(box1);


	IceBlock* box2 = IceBlock::create(m_pWorld);
	box2->createIceBlock(240.0f, 350.0f, TYPE1);
	this->addChild(box2);


	IceBlock* box3 = IceBlock::create(m_pWorld);
	box3->createIceBlock(50.0f, 350.0f, TYPE0);
	this->addChild(box3);

	IceBlock* box4 = IceBlock::create(m_pWorld);
	box4->createIceBlock(430.0f, 350.0f, TYPE0);
	this->addChild(box4);
}
//------------------------------------
//@! ステージ8に移動
//------------------------------------
void Stage::toStage8()
{
	//スライダーリミット
	m_SliderLimit = 4;

	//-----------------------------------------------------------
	//ペンキを作成する
	m_pPaint[0] = Paint::create(m_pWorld);
	m_pPaint[0]->createParticle(0, 540.0f, BLUE);
	m_paintNum++;
	this->addChild(m_pPaint[0]);

	//ペンキを作成する
	m_pPaint[1] = Paint::create(m_pWorld);
	m_pPaint[1]->createParticle(200, 540.0f, PURPLE);
	m_paintNum++;
	this->addChild(m_pPaint[1]);

	//ペンキを作成する
	m_pPaint[2] = Paint::create(m_pWorld);
	m_pPaint[2]->createParticle(380, 540.0f, RED);
	m_paintNum++;
	this->addChild(m_pPaint[2]);

	//ドロー用
	auto debugDraw = DebugDrawNode::create(m_pWorld);
	this->addChild(debugDraw);

	//ペンキバケツ
	m_pBucket[0] = Bucket::create(m_pWorld);
	m_pBucket[0]->createBucket(0.0f, 20.0f, bPURPLE);
	m_bucketNum++;
	this->addChild(m_pBucket[0]);

	//ペンキバケツ
	m_pBucket[1] = Bucket::create(m_pWorld);
	m_pBucket[1]->createBucket(200.0f, 20.0f, bRED);
	m_bucketNum++;
	this->addChild(m_pBucket[1]);

	//ペンキバケツ
	m_pBucket[2] = Bucket::create(m_pWorld);
	m_pBucket[2]->createBucket(380.0f, 20.0f, bBLUE);
	m_bucketNum++;
	this->addChild(m_pBucket[2]);

}
//------------------------------------
//@! ステージ9に移動
//------------------------------------
void Stage::toStage9()
{
	//スライダーリミット
	m_SliderLimit = 4;

	//-------------------------------------------
	//ペンキを作成する
	m_pPaint[0] = Paint::create(m_pWorld);
	m_pPaint[0]->createParticle(0.0f, 540.0f, PINK);
	m_paintNum++;
	this->addChild(m_pPaint[0]);

	m_pPaint[1] = Paint::create(m_pWorld);
	m_pPaint[1]->createParticle(380.0f, 540.0f, PURPLE);
	m_paintNum++;
	this->addChild(m_pPaint[1]);

	//ドロー用
	auto debugDraw = DebugDrawNode::create(m_pWorld);
	this->addChild(debugDraw);


	//ペンキバケツ
	m_pBucket[0] = Bucket::create(m_pWorld);
	m_pBucket[0]->createBucket(0.0f,20.0f, bPINK);
	m_bucketNum++;
	this->addChild(m_pBucket[0]);

	//ペンキバケツ
	m_pBucket[1] = Bucket::create(m_pWorld);
	m_pBucket[1]->createBucket(380.0f, 20.0f, bPURPLE);
	m_bucketNum++;
	this->addChild(m_pBucket[1]);

	//ボックススライダーの表示
	IceBlock* box1 = IceBlock::create(m_pWorld);
	box1->createIceBlock(405.0f, 470.0f, TYPE0);
	this->addChild(box1);

	IceBlock* box2 = IceBlock::create(m_pWorld);
	box2->createIceBlock(75.0f, 470.0f, TYPE0);
	this->addChild(box2);

	IceBlock* box3 = IceBlock::create(m_pWorld);
	box3->createIceBlock(75.0f + 50.0f, 470.0f, TYPE0);
	this->addChild(box3);

	IceBlock* box4 = IceBlock::create(m_pWorld);
	box4->createIceBlock(405.0f - 50.0f, 470.0f, TYPE0);
	this->addChild(box4);

	IceBlock* box5 = IceBlock::create(m_pWorld);
	box5->createIceBlock(240 , 320, TYPE3);
	this->addChild(box5);

	IceBlock* box6 = IceBlock::create(m_pWorld);
	box6->createIceBlock(405.0f, 200.0f, TYPE0);
	this->addChild(box6);

	IceBlock* box7 = IceBlock::create(m_pWorld);
	box7->createIceBlock(75.0f, 200.0f, TYPE0);
	this->addChild(box7);

}
//------------------------------------
//@! ステージ10に移動
//------------------------------------
void Stage::toStage10()
{
	//スライダーリミット
	m_SliderLimit = 3;

	//-------------------------------------------
	//ペンキを作成する
	m_pPaint[0] = Paint::create(m_pWorld);
	m_pPaint[0]->createParticle(0.0f, 540.0f, NATTOU);
	m_paintNum++;
	this->addChild(m_pPaint[0]);

	//ドロー用
	auto debugDraw = DebugDrawNode::create(m_pWorld);
	this->addChild(debugDraw);


	//ペンキバケツ
	m_pBucket[0] = Bucket::create(m_pWorld);
	m_pBucket[0]->createBucket(380.0f, 20.0f, bNATTOU);
	m_bucketNum++;
	this->addChild(m_pBucket[0]);

	//ボックススライダーの表示--------------------------------------------
	IceBlock* box1[3];
	IceBlock* box2[2];
	IceBlock* box3[3];

	//1行-----------------------------------------------------
	for (int i = 0; i < 3; i++)
	{
		box1[i] = IceBlock::create(m_pWorld);
		box1[i]->createIceBlock(150.0f + (i*150), 540.0f, TYPE0);
		this->addChild(box1[i]);
	}
	

	//2行-------------------------------------------------------
	for (int i = 0; i < 2; i++)
	{
		box2[i] = IceBlock::create(m_pWorld);
		box2[i]->createIceBlock(50.0f + (i * 150), 420.0f, TYPE0);
		this->addChild(box2[i]);
	}

	IceBlock* box2_1 = IceBlock::create(m_pWorld);
	box2_1->createIceBlock(350.0f, 420, TYPE3);
	this->addChild(box2_1);

	//3行-------------------------------------------------------
	for (int i = 0; i < 3; i++)
	{
		box3[i] = IceBlock::create(m_pWorld);
		box3[i]->createIceBlock(150.0f + (i * 150), 300.0f, TYPE0);
		this->addChild(box3[i]);
	}
	//4行-------------------------------------------------------
	IceBlock* box4_1 = IceBlock::create(m_pWorld);
	box4_1->createIceBlock(75.0f, 180.0f, TYPE0);
	this->addChild(box4_1);

	IceBlock* box4_2 = IceBlock::create(m_pWorld);
	box4_2->createIceBlock(60.0f + 160.0f, 180.0f, TYPE4);
	this->addChild(box4_2);

	IceBlock* box4_3 = IceBlock::create(m_pWorld);
	box4_3->createIceBlock(75.0f + 270.0f, 180.0f, TYPE0);
	this->addChild(box4_3);

	//IceBlock* box4_4 = IceBlock::create(m_pWorld);
	//box4_4->createIceBlock(150.0f + 270.0f, 180.0f, TYPE2);
	//this->addChild(box4_4);

	//たて-------------------------------------------------------
	IceBlock* boxVer1 = IceBlock::create(m_pWorld);
	boxVer1->createIceBlock(125, 540 - 125, TYPE2);
	this->addChild(boxVer1);

	/*IceBlock* boxVer2 = IceBlock::create(m_pWorld);
	boxVer2->createIceBlock(125 + 95, 420 - 125, TYPE2);
	this->addChild(boxVer2);*/

	IceBlock* boxVer3 = IceBlock::create(m_pWorld);
	boxVer3->createIceBlock(200 + 175, 420 - 125, TYPE2);
	this->addChild(boxVer3);

	//IceBlock* box4 = IceBlock::create(m_pWorld);
	//box4->createIceBlock(50.0f, 450.0f, TYPE0);
	//this->addChild(box4);
	//IceBlock* box5 = IceBlock::create(m_pWorld);
	//box4->createIceBlock(50.0f, 450.0f, TYPE0);
	//this->addChild(box4);
	//IceBlock* box6 = IceBlock::create(m_pWorld);
	//box4->createIceBlock(50.0f, 450.0f, TYPE0);
	//this->addChild(box4);
}
//------------------------------------
//@! 更新
//@! 時間
//------------------------------------
void Stage::update(float dt)
{

	if (m_SliderLimit > 0)
	{
		//タッチ可能
		this->setTouchEnabled(true);
	}
	else
	{
		this->setTouchEnabled(false);
	}

	//------------------------------------------------------------------------

	//ボックスの判定をAABBで決める
	b2AABB aabb;

	//カラーの設定
	b2ParticleColor color_table[BucketColorNum] =
	{
		b2ParticleColor(255, 0, 0, 255),		//赤
		b2ParticleColor(0, 0, 255, 255),		//青
		b2ParticleColor(255, 0, 255, 255),		//紫
		b2ParticleColor(0, 255, 0, 255),		//緑
		b2ParticleColor(255, 125, 0, 255),		//オレンジ
		b2ParticleColor(255, 235, 0, 255),		//黄色
		b2ParticleColor(0, 0, 0, 255),			//黒
		b2ParticleColor(220, 130, 220, 255),	//ピンク
		b2ParticleColor(150, 117, 2, 255),		//納豆

	};

	
	bool color_flag = true;

	//バケツごとの当たり判定の設定
	for (int i = 0; i < m_bucketNum; i++)
	{
		b2Vec2 body_pos = m_pBucket[i]->getBucket()->GetPosition();
		int32 _bcolorNum = m_pBucket[i]->getColorNumber();
		
		//int particleInBucket = m_pBucket[i]->getParticleNum();

		aabb.lowerBound = b2Vec2(body_pos.x - 100 / PTM_RATIO, body_pos.y - 100 / PTM_RATIO);
		aabb.upperBound = b2Vec2(body_pos.x + 100 / PTM_RATIO, body_pos.y + 100 / PTM_RATIO);
		
		m_BucketColor = color_table[_bcolorNum];
		m_ParticleCount = 0;
		m_particleLabelNum = 0;
		m_pWorld->QueryAABB(this, aabb);

		String* par_str;


		//表示用
		switch (_bcolorNum)
		{
		case RED:
			par_str = String::createWithFormat("いちご = %d %%", (int)m_particleLabelNum);
			m_particleLabel[i]->setColor(Color3B::RED);
			break;
		case BLUE:
			par_str = String::createWithFormat("ブルーハワイ = %d %%", (int)m_particleLabelNum);
			m_particleLabel[i]->setColor(Color3B(55,150,250));
			break;
		case PURPLE:
			par_str = String::createWithFormat("グレープ = %d %%", (int)m_particleLabelNum);
			m_particleLabel[i]->setColor(Color3B::MAGENTA);
			break;
		case GREEN:
			par_str = String::createWithFormat("メロン = %d %%", (int)m_particleLabelNum);
			m_particleLabel[i]->setColor(Color3B::GREEN);
			break;
		case ORANGE:
			par_str = String::createWithFormat("オレンジ = %d %%", (int)m_particleLabelNum);
			m_particleLabel[i]->setColor(Color3B::ORANGE);
			break;
		case YELLOW:
			par_str = String::createWithFormat("レモン = %d %%", (int)m_particleLabelNum);
			m_particleLabel[i]->setColor(Color3B::YELLOW);
			break;
		case BLACK:
			par_str = String::createWithFormat("Black = %d %%", (int)m_particleLabelNum);
			m_particleLabel[i]->setColor(Color3B::BLACK);
			break;
		case PINK:
			par_str = String::createWithFormat("イチゴミルク = %d %%", (int)m_particleLabelNum);
			m_particleLabel[i]->setColor(Color3B(255, 150, 235));
			break;
		case NATTOU:
			par_str = String::createWithFormat("ナットウ = %d %%", (int)m_particleLabelNum);
			m_particleLabel[i]->setColor(Color3B(150, 117, 2));

			break;
		}
		
		m_particleLabel[i]->setString(par_str->getCString());
		
		m_pBucket[i]->setParticleNum(m_ParticleCount);

		log("particle : %d", m_ParticleCount);
		

		
		//200以上貯まればクリア
		if (m_ParticleCount < 200)
		{
			color_flag = false;
		}
	}

	//ステージクリア条件
	if (color_flag)
	{
		//勝利
		m_clear = true;
	}
	
	//パーティクルの数
	b2ParticleSystem* ps = m_pWorld->GetParticleSystemList();
	int count = ps->GetParticleCount();
	log("%d", count);

}
//------------------------------------------------------------------
//------------------------------------
//@! 初期化
//@! ワールド
//------------------------------------
bool Stage::init(b2World* world)
{

	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//------------------------------------------------------------------

	//物理世界
	m_pWorld = world;

	//------------------------------------------------------------------
	this->scheduleUpdate();
	//------------------------------------------------------------------
	return true;
}
//------------------------------------
//@! タッチ
//@! タッチ、イベント
//------------------------------------
bool Stage::onTouchBegan(Touch *touch, Event *unused_event)
{
	m_touchpos = touch->getLocation();

	//--------------------------------------------------------------------------
	//頂点を取得
	m_topPoint = getPoint();
	Vec2 topDot = Vec2(m_topPoint.x * PTM_RATIO, m_topPoint.y * PTM_RATIO);
	//エフェクトを出す
	m_parClickBegan = CCParticleSystemQuad::create("line_click.plist");
	m_parClickBegan->resetSystem();
	m_parClickBegan->setPosition(topDot);
	m_parClickBegan->setScale(0.5);
	this->addChild(m_parClickBegan);
	//--------------------------------------------------------------------------
	return true;
}
//------------------------------------
//@! タッチ移動するとき
//@! タッチ、イベント
//------------------------------------
void Stage::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	//---------------------------------------------------------------------
	m_touchpos = touch->getLocation();
	
	//移動するときのパーティクルの作成
	m_parClickMoved->setVisible(true);
	m_parClickMoved->setPosition(m_touchpos);

	//---------------------------------------------------------------------
}
//------------------------------------
//@! タッチ離したとき
//@! タッチ、イベント
//------------------------------------
void Stage::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	//---------------------------------------------------------------------
	m_touchpos = touch->getLocation();

	//点を取得
	m_bottomPoint = getPoint();


	b2PolygonShape m_SliderShape;
	b2Vec2 b2points[] =
	{
		{ m_topPoint.x, m_topPoint.y + 0.23f },
		{ m_bottomPoint.x, m_bottomPoint.y + 0.23f },
		{ m_bottomPoint.x,m_bottomPoint.y - 0.23f },
		{ m_topPoint.x,m_topPoint.y - 0.23f },
	};
	int b2npoints = sizeof(b2points) / sizeof(b2Vec2);
	m_SliderShape.Set(b2points, b2npoints);


	//線の設定
	b2FixtureDef sliderFd;
	sliderFd.density = 1.0f;
	sliderFd.shape = &m_SliderShape;

	//線の描画
	m_pSliderBody->CreateFixture(&sliderFd);

	//---------------------------------------------------------------------
	//引ける線を減らす
	m_SliderLimit--;

	//最初のパーティクルを消す
	m_parClickBegan->removeFromParent();
	m_parClickMoved->setVisible(false);

	//ラインの頂点
	Vec2 topDot = Vec2(m_topPoint.x * PTM_RATIO, m_topPoint.y * PTM_RATIO);
	Vec2 bottomDot = Vec2(m_bottomPoint.x * PTM_RATIO,m_bottomPoint.y * PTM_RATIO);


	int sound = experimental::AudioEngine::play2d("Sounds/click.mp3");

	//パーティクル発生
	CCParticleSystemQuad* particle = CCParticleSystemQuad::create("click.plist");
	particle->resetSystem();
	particle->setPosition(bottomDot);
	particle->setScale(0.25);
	this->addChild(particle);


	//ポリゴンの作成-------------------------------------
	Vec2 points[] =
	{
		{ topDot.x, topDot.y + 5 },
		{ bottomDot.x, bottomDot.y + 5 },
		{ bottomDot.x,bottomDot.y - 5 },
		{ topDot.x,topDot.y - 5 },
	};
	int npoints = sizeof(points) / sizeof(Vec2);
	//---------------------------------------------------

	//ラインを作る
	DrawNode* drawnode = DrawNode::create();
	drawnode->drawPolygon(points, npoints, Color4F::BLACK, 1.0f, Color4F::BLACK);
	//drawnode->drawLine(topDot, bottomDot, Color4F::BLACK);
	this->addChild(drawnode);
	//---------------------------------------------------------------------
}

//------------------------------------	
//@! ペンキのボディーを取得する
//@! ペンキの番号
//@! ペンキのボディー
//------------------------------------
Paint* Stage::getPaintBody(int num)
{
	//------------------------------------
	//ペンキのボディーを返す
	return m_pPaint[num];
	//------------------------------------
}
//------------------------------------	
//@! ペンキバケツのボディーを取得する
//@! ペンキバケツの番号
//@! ペンキバケツのボディー
//------------------------------------
Bucket * Stage::getBucketBody(int num)
{
	//------------------------------------
	//ペンキバケツのボディーを返す
	return m_pBucket[num];
	//------------------------------------
}
//------------------------------------	
//@! ペンキの数を取得する
//@! ペンキの数
//------------------------------------
int Stage::getPaintNum()
{
	//------------------------------------
	//ペンキの数を返す
	return m_paintNum;
	//------------------------------------
}
//------------------------------------	
//@! ペンキバケツの数を取得する
//@! ペンキバケツの数
//------------------------------------
int Stage::getBucketNum()
{
	//------------------------------------
	//ペンキバケツの数を返す
	return m_paintNum;
	//------------------------------------
}
//------------------------------------	
//@! 線の数を取得する
//@! 線の数
//------------------------------------
int Stage::getLineLimit()
{
	//------------------------------------
	//ペンキの数を返す
	return m_SliderLimit;
	//------------------------------------

}
//------------------------------------	
//@! 選択されたステージを取得する
//@! 選択されたステージ
//------------------------------------
int Stage::getSelectedStage()
{
	return m_selectedStage;
}
//------------------------------------
//@! タッチ座標を取得
//------------------------------------
b2Vec2 Stage::getPoint()
{
	//---------------------------------------------------------------------
	//頂点を返す
	return b2Vec2(m_touchpos.x / PTM_RATIO, m_touchpos.y / PTM_RATIO);
	//---------------------------------------------------------------------
}
//------------------------------------
//@! パーティクル
//@! パーティクル,インデックス
//------------------------------------
bool Stage::ReportParticle(const b2ParticleSystem * particleSystem, int32 index)
{
	//---------------------------------------------------------------------
	//カラーの判定
	b2ParticleColor particleColor = particleSystem->GetColorBuffer()[index];
	
	//勝利条件
	if (m_BucketColor == particleColor)
	{
		//入った水の数をカウントする
		m_ParticleCount++;

		//％の表示するため
		m_particleLabelNum = m_ParticleCount /2;
		if (m_particleLabelNum >= 100)
		{
			m_particleLabelNum = 100;
			
		}
		
	}
	return true;
	//---------------------------------------------------------------------
}
//------------------------------------
//@! クリアかどうかの判定
//@! 勝利判定を返す
//------------------------------------
bool Stage::isCleared()
{
	return m_clear;
}
//------------------------------------------------------------------


