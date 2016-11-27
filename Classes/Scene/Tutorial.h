//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/5/31
//!	
//!	Tutorial.h
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//----------------------------------------------------------------------------
#ifndef __TUTORIAL_H__
#define __TUTORIAL_H__
//----------------------------------------------------------------------------

#include "cocos2d.h"


//�N���X�쐬----------------------------------------------------------------------------
class Tutorial : public cocos2d::Layer
{
	//----------------------------------------------------------------------------
private:
	cocos2d::Menu* m_menu;					//���j���[�X�e�[�W
	cocos2d::Sprite* m_bg;
	//----------------------------------------------------------------------------
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(Tutorial);

	//---------------------------------------------------------------------------------------
private:
	//---------------------------------------------------------------------------------------
	void goToTutorial1(cocos2d::Ref* pSender);
	void goToTutorial2(cocos2d::Ref* pSender);
	void goToTutorial3(cocos2d::Ref* pSender);
	void backToMenu(cocos2d::Ref* pSender);
	//----------------------------------------------------------------------------
};
//----------------------------------------------------------------------------
#endif