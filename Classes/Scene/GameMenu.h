//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/6/11
//!	
//!	GameMenu.h
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//----------------------------------------------------------------------------
#ifndef __GAMEMENU_H__
#define __GAMEMENU_H__
//----------------------------------------------------------------------------
#include "cocos2d.h"
//----------------------------------------------------------------------------
class GameMenu : public cocos2d::Layer
{
	//----------------------------------------------------------------------------
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameMenu);

	//---------------------------------------------------------------------------------------

	void showStageSelectScene(cocos2d::Ref* pSender);				//�`���[�g���A���Ɉړ�
	void showTutorialScene(cocos2d::Ref* pSender);					//�X�e�[�W�P�Ɉړ�
	void showRules(cocos2d::Ref* pSender);					//�X�e�[�W�Q�Ɉړ�
	void closeGame(cocos2d::Ref* pSender);					//�X�e�[�W�R�Ɉړ�

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	//---------------------------------------------------------------------------------------

};
//----------------------------------------------------------------------------
#endif 
