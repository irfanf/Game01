//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/5/10
//!	
//!	Slider.cpp
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#include "BoxSlider.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

const int PTM_RATIO = 32;

using namespace cocostudio::timeline;

//------------------------------------
//@! クラス作成の時に作られているもの
//@! ワールド
//------------------------------------
IceBlock* IceBlock::create(b2World* world)
{
	IceBlock *sprite = new (std::nothrow) IceBlock();
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
}
//------------------------------------
//@! スライダーの作成
//@! 座標
//------------------------------------
void IceBlock::createIceBlock(float32 x, float32 y, int32 boxSliderType)
{

	//座標を引数からもらう
	m_x = x;
	m_y = y;

	//スライダーの作成-------------------------------------

	//ボディーの作成
	b2PolygonShape boxShape;
	boxShape.SetAsBox(75.0f / PTM_RATIO, 10.0f / PTM_RATIO);
	m_boxSliderDef.type = b2_kinematicBody;
	m_boxSliderDef.position.Set(x / PTM_RATIO, y / PTM_RATIO);

	m_boxFixtureDef.shape = &boxShape;

	//タイプを選択
	switch (boxSliderType)
	{
	case TYPE0:
		createType0();
		break;
	case TYPE1:
		createType1();
		break;
	case TYPE2:
		createType2();
		break;
	case TYPE3:
		createType3();
		break;
	case TYPE4:
		createType4();
		break;
	}
	//スライダーを作成
	m_boxSliderBody = m_pWorld->CreateBody(&m_boxSliderDef);

	m_boxFixtureDef.density = 0.5f;
	m_boxSliderBody->CreateFixture(&m_boxFixtureDef);

}
//------------------------------------
//@! スライダーのボディーを取得
//@! スライダー
//------------------------------------
b2Body * IceBlock::getBoxBody()
{
	return m_boxSliderBody;
}
//------------------------------------
//@! 何も動かないスライダーボックスを作る
//------------------------------------
void IceBlock::createType0()
{
	//スピライト
	Sprite* box = Sprite::create("Slider/type0.png");
	box->setScale(0.5);
	this->addChild(box);
	m_boxSliderDef.userData = box;
	
}
//------------------------------------
//@! グルグル回ってるボックススライダーを作る
//------------------------------------
void IceBlock::createType1()
{
	//スピライト
	Sprite* box = Sprite::create("Slider/type1.png");
	box->setScale(0.5);
	this->addChild(box);
	m_boxSliderDef.userData = box;
	m_boxSliderDef.angularVelocity = 3.0f;
}
//------------------------------------
//@! 何も動かないボックスを作る
//------------------------------------
void IceBlock::createType2()
{
	//スピライト
	Sprite* box = Sprite::create("Slider/type0.png");
	box->setScale(0.5);
	this->addChild(box);
	m_boxSliderDef.userData = box;
	//たてにする
	m_boxSliderDef.angle = 50.0f / PTM_RATIO;;
}
//------------------------------------
//@! 左に傾けるボックススライダーを作る
//------------------------------------
void IceBlock::createType3()
{
	//スピライト
	Sprite* box = Sprite::create("Slider/type3.png");
	box->setScale(0.5);
	this->addChild(box);
	m_boxSliderDef.userData = box;
	//dynamicBodyに変換して、無重力
	m_boxSliderDef.type = b2_dynamicBody;
	m_boxSliderDef.gravityScale = 0.0f;
}
//------------------------------------
//@! グルグル回ってるボックススライダーを作る
//------------------------------------
void IceBlock::createType4()
{
	//スピライト
	Sprite* box = Sprite::create("Slider/type1.png");
	box->setScale(0.5);
	this->addChild(box);
	m_boxSliderDef.userData = box;
	m_boxSliderDef.angularVelocity = -3.0f;
}
//------------------------------------
//@! 初期化
//@! ワールド
//------------------------------------
bool IceBlock::init(b2World* world)
{

	//////////////////////////////
	// 1. super init first
	if (!Node::init())
	{
		return false;
	}

	//------------------------------------------------------------------

	//物理ワールドを取得
	m_pWorld = world;

	return true;
}
