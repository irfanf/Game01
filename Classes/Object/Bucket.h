//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/5/10
//!	
//!	Bucket.h
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#ifndef __BUCKET_H__
#define __BUCKET_H__

//--------------------------
#include "cocos2d.h"
#include "Box2D/Box2D.h"
//--------------------------

enum BucketColor
{
	bRED,
	bBLUE,
	bPURPLE,
	bGREEN,
	bORANGE,
	bYELLOW,
	bBLACK,
	bPINK,
	bNATTOU,

	BucketColorNum
};


//---------------------------------------------------------------------
class Bucket : public cocos2d::Node
{
	//-----------------------------------------------------------------------
private:
	b2BodyDef m_BucketBodyDef;						//�o�P�c�{�f�B�[�f�t
	b2World* m_pWorld;								//���[���h
	b2Body* m_bucketBody;							//�o�P�c�{�f�B�[
	int32 m_color;									//�F
	cocos2d::Sprite* m_bucketColor;					//�o�P�c�̐F
	int m_particleInBucketNum;						//�o�P�c�̒��ɂ���p�[�e�B�N���̐�
	
	//---------------------------------------------------------------------
public:
	virtual bool init(b2World* world);						//������
	static Bucket* create(b2World* world);

	void createBucket(float32 x, float32 y,int32 color);
	b2Body* getBucket();
	int32 getColorNumber();
	cocos2d::Sprite* getBucketSprite();
	void update(float dt)override;
	int getParticleNum();
	void setParticleNum(int particleNum);
	void changeTexture();
	//--------------------------------------

	//-----------------------------------------------------------------------
};
#endif