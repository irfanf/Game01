//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/5/20
//!	
//!	GameClearScene.h
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//---------------------------------------------------------
#ifndef __GAMECLEAR_SCENE_H__
#define __GAMECLEAR_SCENE_H__

#include "cocos2d.h"

//---------------------------------------------------------
class GameClearScene : public cocos2d::Layer
{
	//---------------------------------------------------------
private:
	cocos2d::MenuItemImage* m_nextButton;
	cocos2d::Sprite* m_sprIce;
	int m_stageNow;
	//---------------------------------------------------------
public:

	virtual bool init();
	static GameClearScene* create();
	void setSelectedStage(int stage);
	void update(float dt)override;
	//---------------------------------------------------------------------------------------
private:
	void showButton();
	void backToStageSelectScene();
	void moveNextStage();
	//---------------------------------------------------------------------------------------
};
//---------------------------------------------------------------------------------------
#endif // __GAMECLEAR_SCENE_H__
