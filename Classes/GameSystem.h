//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/5/26
//!	
//!	GameSystem.h
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//--------------------------------------------
#ifndef __GAMESYSTEM_H__
#define __GAMESYSTEM_H__
//--------------------------------------------
#include "cocos2d.h"
//--------------------------------------------

class GameSystem : public cocos2d::Layer
{
	//--------------------------------------------
private:
	bool m_reset;										//���Z�b�g
	float m_timeCount;
	int m_lineLimit;
	bool m_explode;


	cocos2d::Sprite* m_bg;
	cocos2d::Sprite* m_msgsBox;
	cocos2d::Menu* m_menu;


	void reset(cocos2d::Ref* pSender);					//���Z�b�g�{�^�������ꂽ���̏���
	void cancelMenu(cocos2d::Ref* pSender);
	void backToStageSelect(cocos2d::Ref* pSender);		//�X�e�[�W�Z���N�g�ɕԂ�
	void backToGameMenu(cocos2d::Ref* pSender);
	void explode(cocos2d::Ref* pSender);				//
	cocos2d::Label* m_countLabel;
	cocos2d::Label* m_sliderLabel;

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	

	//--------------------------------------------
public:
	//--------------------------------------------
	static cocos2d::Scene* createScene();		//�V�[���쐬
	virtual bool init();						//������
	CREATE_FUNC(GameSystem);
	//--------------------------------------------
	void resetOn(bool reset);
	bool resetStart();	
	void update(float dt)override;
	
	void explodeOn(bool explode);
	bool explodeBomb();
	void setTimeCount(float timeCount);
	void setLineLimit(int limit);


};
//--------------------------------------------

#endif // __TITLE_SCENE_H__
