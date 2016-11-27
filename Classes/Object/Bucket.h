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
	b2BodyDef m_BucketBodyDef;						//バケツボディーデフ
	b2World* m_pWorld;								//ワールド
	b2Body* m_bucketBody;							//バケツボディー
	int32 m_color;									//色
	cocos2d::Sprite* m_bucketColor;					//バケツの色
	int m_particleInBucketNum;						//バケツの中にあるパーティクルの数
	
	//---------------------------------------------------------------------
public:
	virtual bool init(b2World* world);						//初期化
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