//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/5/7
//!	
//!	StageManager.h
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#ifndef __STAGE_H__
#define __STAGE_H__

//--------------------------
#include "cocos2d.h"
#include "Box2D/Box2D.h"
//--------------------------
//定数----------------------
const int MAX_BUCKET = 5;
const int MAX_PAINT = 5;
//--------------------------
//ステージ------------------
enum Level
{
	Tutorial1,
	Tutorial2,
	Tutorial3,
	Stage1,
	Stage2,
	Stage3,
	Stage4,
	Stage5,
	Stage6,
	Stage7,
	Stage8,
	Stage9,
	Stage10,

	MAX_STAGE
};
//---------------------------
class Paint;
class Bucket;
class GameSystem;
class IceBlock;

//---------------------------------------------------------------------
class Stage : public cocos2d::Layer, public b2QueryCallback
{
//-----------------------------------------------------------------------
private:
	
	b2Body* m_pGroundBody;
	b2World* m_pWorld;								//ワールド
	
	
	b2ParticleColor m_BucketColor;
	int m_ParticleCount;

	int m_selectedStage;
	int m_bucketNum;
	int m_paintNum;
	Bucket* m_pBucket[MAX_BUCKET];
	Paint* m_pPaint[MAX_PAINT];

	//ラベル
	//cocos2d::LabelTTF m_label;

	//スライダー-------------------
	b2Body* m_pSliderBody;
	//b2EdgeShape m_pSlider;
	cocos2d::Vec2 m_touchpos;
	b2Vec2 m_topPoint;
	b2Vec2 m_bottomPoint;
	int m_SliderLimit;
	float m_timeCount;
	float m_particleLabelNum;
	bool m_clear;

	//出力用
	cocos2d::Label* m_sliderLabel;
	cocos2d::Label* m_countLabel;
	cocos2d::Label* m_particleLabel[MAX_BUCKET];

	//初期化フラグ
	bool m_initFlag;
	GameSystem* m_gameSystem;


	
	//タップ時にエフェクトを出す
	cocos2d::CCParticleSystemQuad* m_parClickBegan;
	cocos2d::CCParticleSystemQuad* m_parClickMoved;
//---------------------------------------------------------------------
	cocos2d::MenuItemImage* m_resetButton;
//---------------------------------------------------------------------
public:
	virtual bool init(b2World* world);				//初期化
	static Stage* create(b2World* world);

	void createStage(int stage);
	
	void toTutorial1();
	void toTutorial2();
	void toTutorial3();
	void toStage1();
	void toStage2();
	void toStage3();
	void toStage4();
	void toStage5();
	void toStage6();
	void toStage7();
	void toStage8();
	void toStage9();
	void toStage10();

	void update(float dt)override;
	//タッチ--------------------------------
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
//--------------------------------------

	Paint* getPaintBody(int num);
	Bucket* getBucketBody(int num);
	int getPaintNum();
	int getBucketNum();
	int getLineLimit();
	int getSelectedStage();

	bool isCleared();
//---------------------------------------------------------------------
private:
	//--------------------------------------
	//ラインの頂点を取得
	b2Vec2 getPoint();
	//--------------------------------------
	//あたり判定
	bool ReportFixture(b2Fixture* fixture)override { return true; }
	bool ReportParticle(const b2ParticleSystem* particleSystem, int32 index)override;
	//--------------------------------------
	
//-----------------------------------------------------------------------
};
#endif