//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/5/10
//!	
//!	Bucket.cpp
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//------------------------------------
#include "Bucket.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
//------------------------------------
USING_NS_CC;
using namespace cocostudio::timeline;
//------------------------------------
const int PTM_RATIO = 32;


//------------------------------------
//@! �N���X�쐬�̎��ɍ���Ă������
//@! ���[���h
//------------------------------------
Bucket* Bucket::create(b2World* world)
{
	Bucket *sprite = new (std::nothrow) Bucket();
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
//@! �X�e�[�W�̍쐬
//@! �X�e�[�W
//------------------------------------
void Bucket::createBucket(float32 x, float32 y, int32 color)
{
	//�J���[��ݒ肷��
	m_color = color;
	m_particleInBucketNum = 0;

	
	//�e�N�X�`���F��\��
	switch (m_color)
	{
	case bRED:
		m_bucketColor = Sprite::create("redBucket.png");
		this->addChild(m_bucketColor);
		this->setName("BucketRED");
		m_bucketColor->setName("BucketREDSprite");
		break;
	case bBLUE:
		m_bucketColor = Sprite::create("blueBucket.png");
		this->addChild(m_bucketColor);
		this->setName("BucketBLUE");
		m_bucketColor->setName("BucketBLUESprite");
		break;
	case bPURPLE:
		m_bucketColor = Sprite::create("purpleBucket.png");
		this->addChild(m_bucketColor);
		this->setName("BucketPURPLE");
		m_bucketColor->setName("BucketPURPLESprite");
		break;
	case bGREEN:
		m_bucketColor = Sprite::create("greenBucket.png");
		this->addChild(m_bucketColor);
		this->setName("BucketGREEN");
		m_bucketColor->setName("BucketGREENSprite");
		break;
	case bORANGE:
		m_bucketColor = Sprite::create("orangeBucket.png");
		this->addChild(m_bucketColor);
		this->setName("BucketORANGE");
		m_bucketColor->setName("BucketORANGESprite");
		break;
	case bYELLOW:
		m_bucketColor = Sprite::create("yellowBucket.png");
		this->addChild(m_bucketColor);
		this->setName("BucketYELLOW");
		m_bucketColor->setName("BucketYELLOWSprite");
		break;
			
	case bBLACK:
		m_bucketColor = Sprite::create("blackBucket.png");
		this->addChild(m_bucketColor);
		this->setName("BucketBLACK");
		m_bucketColor->setName("BucketBLACKSprite");
		break;
	case bPINK:
		m_bucketColor = Sprite::create("pinkBucket.png");
		this->addChild(m_bucketColor);
		this->setName("BucketPINK");
		m_bucketColor->setName("BucketPINKSprite");
		break;
	case bNATTOU:
		m_bucketColor = Sprite::create("nattou.png");
		this->addChild(m_bucketColor);
		this->setName("BucketNATTOU");
		m_bucketColor->setName("BucketNATTOUSprite");
		break;

	}

	//�{�f�B�[�����
	m_BucketBodyDef.position.Set((x + 50) / PTM_RATIO, (y + 50) / PTM_RATIO);
	m_BucketBodyDef.type = b2_staticBody;
	m_BucketBodyDef.userData = m_bucketColor;
	m_bucketBody = m_pWorld->CreateBody(&m_BucketBodyDef);
	
	//�o�P�c�̒��_
	b2Vec2 bucketTopLeft(-1.5, 0.9);
	b2Vec2 bucketTopRight(1.5, 0.9);
	b2Vec2 bucketBottomLeft(-1.2, -1.5);
	b2Vec2 bucketBottomRight(1.2, -1.5);

	//�o�P�c�̌`
	b2EdgeShape bucket;

	//�`
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &bucket;

	//�o�P�c�̕`��
	bucket.Set(bucketTopLeft, bucketBottomLeft);
	m_bucketBody->CreateFixture(&fixtureDef);

	bucket.Set(bucketBottomLeft, bucketBottomRight);
	m_bucketBody->CreateFixture(&fixtureDef);

	bucket.Set(bucketBottomRight, bucketTopRight);
	m_bucketBody->CreateFixture(&fixtureDef);

}
//------------------------------------
//@! �X�V
//@! ����
//------------------------------------
void Bucket::update(float dt)
{
	//�e�N�X�`����ς���
	changeTexture();

}
//------------------------------------
//@! �p�[�e�B�N���̐����擾����
//@! �p�[�e�B�N���̐���Ԃ�
//------------------------------------
int Bucket::getParticleNum()
{
	//------------------------------------
	return m_particleInBucketNum;
	//------------------------------------
}
//------------------------------------
//@! �p�[�e�B�N���̐���ݒ肷��
//@! �p�[�e�B�N���̐����擾
//------------------------------------
void Bucket::setParticleNum(int particleNum)
{
	//------------------------------------
	m_particleInBucketNum = particleNum;
	//------------------------------------
}
//------------------------------------
//@! �e�N�X�`����ς���
//------------------------------------
void Bucket::changeTexture()
{
	//�e�N�X�`���F��\��
	switch (m_color)
	{
		case bRED:
		{

			if (m_particleInBucketNum >= 50 && m_particleInBucketNum <= 100)
			{
				m_bucketColor->setTexture("Ice/red1.png");
			}
			if (m_particleInBucketNum >= 150 && m_particleInBucketNum <= 170)
			{
				m_bucketColor->setTexture("Ice/red2.png");
			}
			if (m_particleInBucketNum >= 200)
			{
				m_bucketColor->setTexture("Ice/red3.png");
			}
			break;

		case bBLUE:
			if (m_particleInBucketNum >= 50 && m_particleInBucketNum <= 100)
			{
				m_bucketColor->setTexture("Ice/blue1.png");
			}
			if (m_particleInBucketNum >= 150 && m_particleInBucketNum <= 170)
			{
				m_bucketColor->setTexture("Ice/blue2.png");
			}
			if (m_particleInBucketNum >= 200)
			{
				m_bucketColor->setTexture("Ice/blue3.png");
			}
			break;

		case bPURPLE:
			if (m_particleInBucketNum >= 50 && m_particleInBucketNum <= 100)
			{
				m_bucketColor->setTexture("Ice/purple1.png");
			}
			if (m_particleInBucketNum >= 150 && m_particleInBucketNum <= 170)
			{
				m_bucketColor->setTexture("Ice/purple2.png");
			}
			if (m_particleInBucketNum >= 200)
			{
				m_bucketColor->setTexture("Ice/purple3.png");
			}
			break;

		case bGREEN:
			if (m_particleInBucketNum >= 50 && m_particleInBucketNum <= 100)
			{
				m_bucketColor->setTexture("Ice/green1.png");
			}
			if (m_particleInBucketNum >= 150 && m_particleInBucketNum <= 170)
			{
				m_bucketColor->setTexture("Ice/green2.png");
			}
			if (m_particleInBucketNum >= 200)
			{
				m_bucketColor->setTexture("Ice/green3.png");
			}
			break;

		case bORANGE:
			if (m_particleInBucketNum >= 50 && m_particleInBucketNum <= 100)
			{
				m_bucketColor->setTexture("Ice/orange1.png");
			}
			if (m_particleInBucketNum >= 150 && m_particleInBucketNum <= 170)
			{
				m_bucketColor->setTexture("Ice/orange2.png");
			}
			if (m_particleInBucketNum >= 200)
			{
				m_bucketColor->setTexture("Ice/orange3.png");
			}
			break;

		case bYELLOW:
			if (m_particleInBucketNum >= 50 && m_particleInBucketNum <= 100)
			{
				m_bucketColor->setTexture("Ice/yellow1.png");
			}
			if (m_particleInBucketNum >= 150 && m_particleInBucketNum <= 170)
			{
				m_bucketColor->setTexture("Ice/yellow2.png");
			}
			if (m_particleInBucketNum >= 200)
			{
				m_bucketColor->setTexture("Ice/yellow3.png");
			}
			break;

		case bNATTOU:
			if (m_particleInBucketNum >= 50 && m_particleInBucketNum <= 100)
			{
				m_bucketColor->setTexture("Ice/nattou1.png");
			}
			if (m_particleInBucketNum >= 150 && m_particleInBucketNum <= 170)
			{
				m_bucketColor->setTexture("Ice/nattou2.png");
			}
			if (m_particleInBucketNum >= 200)
			{
				m_bucketColor->setTexture("Ice/nattou3.png");
			}
			break;
		case bPINK:
			if (m_particleInBucketNum >= 50 && m_particleInBucketNum <= 100)
			{
				m_bucketColor->setTexture("Ice/pink1.png");
			}
			if (m_particleInBucketNum >= 150 && m_particleInBucketNum <= 170)
			{
				m_bucketColor->setTexture("Ice/pink2.png");
			}
			if (m_particleInBucketNum >= 200)
			{
				m_bucketColor->setTexture("Ice/pink3.png");
			}
			break;
		}
	}

	m_BucketBodyDef.userData = m_bucketColor;
	m_bucketBody = m_pWorld->CreateBody(&m_BucketBodyDef);
	
}
//------------------------------------
//@! �o�P�c�{�f�B���擾����
//@! �o�P�c��Ԃ�
//------------------------------------
b2Body* Bucket::getBucket()
{
	//------------------------------------
	//�o�P�c��Ԃ�
	return m_bucketBody;
	//------------------------------------
}

//------------------------------------
//@! �F���擾����
//@! �F��Ԃ�
//------------------------------------
int32 Bucket::getColorNumber()
{
	//------------------------------------
	//�F��Ԃ�
	return m_color;
	//------------------------------------
}

Sprite* Bucket::getBucketSprite()
{
	return m_bucketColor;
}

//------------------------------------
//@! ������
//@! ���[���h
//------------------------------------
bool Bucket::init(b2World* world)
{

	//////////////////////////////
	// 1. super init first
	if (!Node::init())
	{
		return false;
	}

	//------------------------------------------------------------------
	//���[���h������������炤
	m_pWorld = world;

	this->scheduleUpdate();
	return true;
}
