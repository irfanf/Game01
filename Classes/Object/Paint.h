//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/4/27
//!	
//!	Paint.h
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#ifndef __PAINT_H__
#define __PAINT_H__

//--------------------------
#include "cocos2d.h"
#include "Box2D/Box2D.h"
//--------------------------
//パーティクルの色
enum ParticleColor
{
	RED,
	BLUE,
	PURPLE,
	GREEN,
	ORANGE,
	YELLOW,
	BLACK,
	PINK,
	NATTOU
};

//---------------------------------------------------------------------
class Paint : public cocos2d::Node
{
//-----------------------------------------------------------------------
private:

	b2ParticleGroupDef m_pParticleDef;
	b2ParticleSystem* m_particleSystem;
	b2World* m_pWorld;								//ワールド
	cocos2d::Sprite* m_Bomb;
	float m_x, m_y;									//座標
//蓋------------------------------------------------------------------
	
	b2Body* m_capBody;
	int m_count;									//カウント用
	bool m_Closed;									//蓋が開いてるかどうか

//---------------------------------------------------------------------
public:

	virtual bool init(b2World* world);				//初期化
	static Paint* create(b2World* world);			//作成するときにワールド環境を与える
	void createParticle(float x, float y,			//パーティクルを作る 
		int color);							

	void update(float dt)override;					//更新

	b2ParticleSystem* getParticleSystem();		
	
	void setBombStatus(bool status) { m_Closed = status; };
//-----------------------------------------------------------------------
private:

	void setColor(int color);						//カラー設定
		
//-----------------------------------------------------------------------
};
//-----------------------------------------------------------------------
#endif 
