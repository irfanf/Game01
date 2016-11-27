//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/5/19
//!	
//!	StageSelectScene.h
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//----------------------------------------------------------------------------
#ifndef __STAGESELECT_SCENE_H__
#define __STAGESELECT_SCENE_H__
//----------------------------------------------------------------------------
#include "cocos2d.h"
//----------------------------------------------------------------------------
class StageSelectScene : public cocos2d::Layer
{
	//----------------------------------------------------------------------------
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(StageSelectScene);

	//---------------------------------------------------------------------------------------

			
	void goToStage1(cocos2d::Ref* pSender);					//ステージ１に移動
	void goToStage2(cocos2d::Ref* pSender);					//ステージ２に移動
	void goToStage3(cocos2d::Ref* pSender);					//ステージ３に移動
	void goToStage4(cocos2d::Ref* pSender);
	void goToStage5(cocos2d::Ref* pSender);
	void goToStage6(cocos2d::Ref* pSender);
	void goToStage7(cocos2d::Ref* pSender);
	void goToStage8(cocos2d::Ref* pSender);
	void goToStage9(cocos2d::Ref* pSender);
	void goToStage10(cocos2d::Ref* pSender);
	void backToMenu(cocos2d::Ref* pSender);
	
//---------------------------------------------------------------------------------------

};
//----------------------------------------------------------------------------
#endif // __STAGESELECT_SCENE_H__
