//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/5/12
//!	
//!	IceBlock.h
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#ifndef __ICEBLOCK_H__
#define __ICEBLOCK_H__

//--------------------------
#include "cocos2d.h"
#include "Box2D/Box2D.h"
//--------------------------

enum BoxType
{
	TYPE0,
	TYPE1,
	TYPE2,
	TYPE3,
	TYPE4
};


//---------------------------------------------------------------------
class IceBlock : public cocos2d::Node
{
	//-----------------------------------------------------------------------
private:
	b2World* m_pWorld;								//ÉèÅ[ÉãÉh
	b2BodyDef m_boxSliderDef;
	b2Body* m_boxSliderBody;
	b2FixtureDef m_boxFixtureDef;
	int32 m_boxSliderType;
	float32 m_x, m_y;

	//---------------------------------------------------------------------
public:
	virtual bool init(b2World* world);				//èâä˙âª
	static IceBlock* create(b2World* world);
	void createIceBlock(float32 x, float32 y, int32 boxSliderType);
	b2Body* getBoxBody();
	//----------------------------------------------------------------------
private:
	void createType0();
	void createType1();
	void createType2();
	void createType3();
	void createType4();
	//-----------------------------------------------------------------------
};
#endif