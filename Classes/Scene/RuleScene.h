//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/6/15
//!	
//!	RuleScene.h
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//----------------------------------------------------------------------------
#ifndef __RULE_SCENE_H__
#define __RULE_SCENE_H__
//----------------------------------------------------------------------------
#include "cocos2d.h"
//----------------------------------------------------------------------------

enum Rules
{
	RULE1,
	RULE2,
	RULE3,
	RULE4,
	RULE5,
	RULE6,
	RULE7,
	RULE8,

	RULE_NUM
};

//----------------------------------------------------------------------------
class RuleScene : public cocos2d::Layer
{
//----------------------------------------------------------------------------
private:
	//--------------------------------------------------------
	cocos2d::Sprite* m_pointer;	
	cocos2d::Label* m_hint;
	int m_ruleNum;
	bool m_ruleFlag;
	cocos2d::RepeatForever* m_rep;
	//--------------------------------------------------------
	//void runRuleActionLine();
	//void runRuleActionMove();

public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(RuleScene);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	void update(float dt)override;
	//---------------------------------------------------------------------------------------

};
//----------------------------------------------------------------------------
#endif // __RULE_SCENE_H__
