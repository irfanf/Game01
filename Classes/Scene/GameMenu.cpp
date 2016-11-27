//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/6/11
//!	
//!	GameMenu.cpp
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//-----------------------------------------------------------------------------
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "StageSelectScene.h"
#include "PlayScene.h"
#include "Stage/StageManager.h"
#include "Tutorial.h"
#include "../EventListenerGesture.h"
#include "audio\include\AudioEngine.h"
#include "GameMenu.h"
#include "RuleScene.h"
//----------------------------------------------------------------------------
USING_NS_CC;

using namespace cocostudio::timeline;
//------------------------------------
//@! �V�[�����쐬
//------------------------------------
Scene* GameMenu::createScene()
{
	//----------------------------------------------------------------------------
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
	//----------------------------------------------------------------------------
}

//------------------------------------
//@! ������
//------------------------------------
bool GameMenu::init()
{
	//----------------------------------------------------------------------------
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//-----------------------------------------
	this->setKeyboardEnabled(true);
	//-----------------------------------------

	experimental::AudioEngine::stopAll();

	//����炷-----------------------------------------------------------
	int bgm = experimental::AudioEngine::play2d("Sounds/menu.mp3");
	experimental::AudioEngine::setVolume(bgm, 0.5);
	experimental::AudioEngine::setLoop(bgm, true);


	//�o�b�N�O���E���h�쐬--------------------------------------------------

	Sprite* bg = Sprite::create("stage_bg.png");
	bg->setPosition(Vec2(480.0f / 2, 800.0f / 2));
	this->addChild(bg);
	//----------------------------------------------------------------------

	//�p�[�e�B�N���̍쐬---------------------------------------------------
	CCParticleSystemQuad* titleStar = CCParticleSystemQuad::create("Title/particlestar.plist");
	titleStar->resetSystem();
	titleStar->setPosition(Vec2(480 / 2, 600));
	titleStar->setScale(0.5f);
	titleStar->setScaleY(1.5f);
	this->addChild(titleStar);

	CCParticleSystemQuad* lightleft = CCParticleSystemQuad::create("Menu/light.plist");
	lightleft->resetSystem();
	lightleft->setPosition(Vec2(0, 50));
	this->addChild(lightleft);

	CCParticleSystemQuad* lightright = CCParticleSystemQuad::create("Menu/light.plist");
	lightright->resetSystem();
	lightright->setPosition(Vec2(480, 50));
	this->addChild(lightright);
	//----------------------------------------------------------------------



	//�`���[�g���A���{�^��---------------------------------------------------
	MenuItemImage* stageSelect = MenuItemImage::create("Menu/play1.png",
		"Menu/play2.png",
		CC_CALLBACK_1(GameMenu::showStageSelectScene, this));
	stageSelect->setPosition(Vec2(240.0f, 480.0f));
	stageSelect->setScale(0.0001);
	//�X�e�[�W�P--------------------------------------------------------------
	MenuItemImage* tutorial = MenuItemImage::create("Menu/tutorial1.png",
		"Menu/tutorial2.png",
		CC_CALLBACK_1(GameMenu::showTutorialScene, this));
	tutorial->setPosition(Vec2(240.0f, 600.0f));
	tutorial->setScale(0.0001);
	//�X�e�[�W�Q--------------------------------------------------------------
	MenuItemImage* rule = MenuItemImage::create("Menu/rule1.png",
		"Menu/rule2.png",
		CC_CALLBACK_1(GameMenu::showRules, this));
	rule->setPosition(Vec2(240.0f,360.0f));
	rule->setScale(0.0001);
	//�X�e�[�W�R---------------------------------------------------------------
	MenuItemImage* close = MenuItemImage::create("Menu/quit1.png",
		"Menu/quit2.png",
		CC_CALLBACK_1(GameMenu::closeGame, this));
	close->setPosition(Vec2(240.0f, 240.0f));
	close->setScale(0.0001);
	//-----------------------------------------------------------------

	//�A�N�V����-------------------------------------------------------

	ScaleTo* playScale1 = ScaleTo::create(0.5, 1.0f, 0.0f);
	ScaleTo* playScale2 = ScaleTo::create(0.5, 1.0f, 1.0f);
	DelayTime* delay1 = DelayTime::create(0.5);
	Sequence* seq1 = Sequence::create(playScale1, delay1, playScale2, nullptr);
	stageSelect->runAction(seq1);

	ScaleTo* tutorialScale1 = ScaleTo::create(0.5, 1.0f, 0.0f);
	ScaleTo* tutorialScale2 = ScaleTo::create(0.5, 1.0f, 1.0f);
	Sequence* seq2 = Sequence::create(tutorialScale1, delay1, tutorialScale2, nullptr);
	tutorial->runAction(seq2);

	ScaleTo* ruleScale1 = ScaleTo::create(0.5, 1.0f, 0.0f);
	ScaleTo* ruleScale2 = ScaleTo::create(0.5, 1.0f, 1.0f);
	Sequence* seq3 = Sequence::create(ruleScale1, delay1, ruleScale2, nullptr);
	rule->runAction(seq3);

	ScaleTo* quitScale1 = ScaleTo::create(0.5, 1.0f, 0.0f);
	ScaleTo* quitScale2 = ScaleTo::create(0.5, 1.0f, 1.0f);
	Sequence* seq4 = Sequence::create(quitScale1, delay1, quitScale2, nullptr);
	close->runAction(seq4);

	//-----------------------------------------------------------------
	Menu* menuStage = Menu::create(stageSelect, tutorial, rule,
		close, NULL);// sprStage7, NULL);
	menuStage->setPosition(Vec2::ZERO);
	this->addChild(menuStage);
	//-----------------------------------------------------------------
	return true;
}

//-----------------------------------------
//@!�X�e�[�W�I�����ړ�����
//@!Ref
//-----------------------------------------
void GameMenu::showStageSelectScene(cocos2d::Ref * pSender)
{
	//����炷
	int sound = experimental::AudioEngine::play2d("Sounds/select.mp3");
	//�`���[�g���A���X�e�[�W�쐬-------------------------------------------------------------------
	this->removeAllChildren();
	//----------------------------------------------------------------------------
	auto nextScene = StageSelectScene::createScene();
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//----------------------------------------------------------------------------

}
//-----------------------------------------
//@!�`���[�g���A�����ړ�����
//@!Ref
//-----------------------------------------
void GameMenu::showTutorialScene(cocos2d::Ref * pSender)
{
	//����炷
	int sound = experimental::AudioEngine::play2d("Sounds/select.mp3");
	//�`���[�g���A���X�e�[�W�쐬-------------------------------------------------------------------
	this->removeAllChildren();
	//----------------------------------------------------------------------------
	auto nextScene = Tutorial::createScene();
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//----------------------------------------------------------------------------

}
//-----------------------------------------
//@!���[����ʂɈړ�����
//@!Ref
//-----------------------------------------
void GameMenu::showRules(cocos2d::Ref * pSender)
{
	//����炷
	int sound = experimental::AudioEngine::play2d("Sounds/select.mp3");
	//���[����ʂɈړ�-----------------------------------------------------
	auto nextScene = RuleScene::createScene();
	auto transition = TransitionFade::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(transition);
	//---------------------------------------------------------------------
}
//-----------------------------------------
//@!�Q�[���𐳏�I��
//@!Ref
//-----------------------------------------
void GameMenu::closeGame(cocos2d::Ref * pSender)
{
	//����I��-----------------------------------------------------
	Director::getInstance()->end();
	//---------------------------------------------------------
}
//-----------------------------------
//@!�L�[�{�[�h�̉���
//@!�L�[�R�[�h,�C�x���g
//-----------------------------------
void GameMenu::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	//����I��---------------------------------------------------
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		Director::getInstance()->end();
	}
	//---------------------------------------------------------
}
