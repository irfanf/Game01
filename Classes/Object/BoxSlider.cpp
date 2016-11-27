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
//@! �N���X�쐬�̎��ɍ���Ă������
//@! ���[���h
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
//@! �X���C�_�[�̍쐬
//@! ���W
//------------------------------------
void IceBlock::createIceBlock(float32 x, float32 y, int32 boxSliderType)
{

	//���W������������炤
	m_x = x;
	m_y = y;

	//�X���C�_�[�̍쐬-------------------------------------

	//�{�f�B�[�̍쐬
	b2PolygonShape boxShape;
	boxShape.SetAsBox(75.0f / PTM_RATIO, 10.0f / PTM_RATIO);
	m_boxSliderDef.type = b2_kinematicBody;
	m_boxSliderDef.position.Set(x / PTM_RATIO, y / PTM_RATIO);

	m_boxFixtureDef.shape = &boxShape;

	//�^�C�v��I��
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
	//�X���C�_�[���쐬
	m_boxSliderBody = m_pWorld->CreateBody(&m_boxSliderDef);

	m_boxFixtureDef.density = 0.5f;
	m_boxSliderBody->CreateFixture(&m_boxFixtureDef);

}
//------------------------------------
//@! �X���C�_�[�̃{�f�B�[���擾
//@! �X���C�_�[
//------------------------------------
b2Body * IceBlock::getBoxBody()
{
	return m_boxSliderBody;
}
//------------------------------------
//@! ���������Ȃ��X���C�_�[�{�b�N�X�����
//------------------------------------
void IceBlock::createType0()
{
	//�X�s���C�g
	Sprite* box = Sprite::create("Slider/type0.png");
	box->setScale(0.5);
	this->addChild(box);
	m_boxSliderDef.userData = box;
	
}
//------------------------------------
//@! �O���O������Ă�{�b�N�X�X���C�_�[�����
//------------------------------------
void IceBlock::createType1()
{
	//�X�s���C�g
	Sprite* box = Sprite::create("Slider/type1.png");
	box->setScale(0.5);
	this->addChild(box);
	m_boxSliderDef.userData = box;
	m_boxSliderDef.angularVelocity = 3.0f;
}
//------------------------------------
//@! ���������Ȃ��{�b�N�X�����
//------------------------------------
void IceBlock::createType2()
{
	//�X�s���C�g
	Sprite* box = Sprite::create("Slider/type0.png");
	box->setScale(0.5);
	this->addChild(box);
	m_boxSliderDef.userData = box;
	//���Ăɂ���
	m_boxSliderDef.angle = 50.0f / PTM_RATIO;;
}
//------------------------------------
//@! ���ɌX����{�b�N�X�X���C�_�[�����
//------------------------------------
void IceBlock::createType3()
{
	//�X�s���C�g
	Sprite* box = Sprite::create("Slider/type3.png");
	box->setScale(0.5);
	this->addChild(box);
	m_boxSliderDef.userData = box;
	//dynamicBody�ɕϊ����āA���d��
	m_boxSliderDef.type = b2_dynamicBody;
	m_boxSliderDef.gravityScale = 0.0f;
}
//------------------------------------
//@! �O���O������Ă�{�b�N�X�X���C�_�[�����
//------------------------------------
void IceBlock::createType4()
{
	//�X�s���C�g
	Sprite* box = Sprite::create("Slider/type1.png");
	box->setScale(0.5);
	this->addChild(box);
	m_boxSliderDef.userData = box;
	m_boxSliderDef.angularVelocity = -3.0f;
}
//------------------------------------
//@! ������
//@! ���[���h
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

	//�������[���h���擾
	m_pWorld = world;

	return true;
}
