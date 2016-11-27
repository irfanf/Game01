//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/5/24
//!	
//!	LogoScene.cpp
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//---------------------------------------------------------------------
#include "LogoScene.h"
#include "ui/CocosGUI.h"
#include "TitleScene.h"
//---------------------------------------------------------------------
USING_NS_CC;
//---------------------------------------------------------------------
//------------------------------------
//@! �N���X�쐬
//------------------------------------
Scene* LogoScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LogoScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

//------------------------------------
//@! �N���X�̏�����
//------------------------------------
bool LogoScene::init()
{

	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}


	//�^�b�`������ړ�
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(LogoScene::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	//-----------------------------------------------------------------
	//���S���o��
	auto logo_bg = Sprite::create("Logo/Logo_bg.png");
	logo_bg->setPosition(Vec2(480 / 2, 800 / 2));
	logo_bg->setScale(0.0001);
	this->addChild(logo_bg);

	//���S�����o��
	auto logo_tag = Sprite::create("Logo/Logo_name.png");
	logo_tag->setPosition(Vec2(-1000.0f, 800 / 2));
	this->addChild(logo_tag);

	//���S�̃p�[�e�B�N��
	CCParticleSystemQuad* logo_particle = CCParticleSystemQuad::create("Logo/particleLogo2.plist");
	logo_particle->resetSystem();
	logo_particle->setPosition(Vec2(480 / 2, 800 / 2));
	logo_particle->setScale(1.5);
	this->addChild(logo_particle);

	//���S�̃A�N�V����
	DelayTime* delay = DelayTime::create(1.5f);
	RotateBy* rot = RotateBy::create(1.5f, 360);
	ScaleTo* scale = ScaleTo::create(1.0f,1);
	Spawn* spawn = Spawn::create(rot, scale, nullptr);
	Sequence* seq = Sequence::create(delay, spawn, nullptr);
	logo_bg->runAction(seq);

	//���S���̃A�N�V����
	MoveTo* move = MoveTo::create(2.0f, Vec2(480 / 2, 800 / 2));
	Sequence* seq2 = Sequence::create(delay, move, nullptr);
	logo_tag->runAction(seq2);

	//-----------------------------------------------------------------

	//�V�[����������Ă���4�b���"ChangeScene"���Ă΂��
	this->scheduleOnce(schedule_selector(LogoScene::changeScene), 5.0f);

	//-----------------------------------------------------------------

	return true;
}


//------------------------------------
//@! ���Ԃ�������,�V�[���ړ�����
//@! ����
//------------------------------------
void LogoScene::changeScene(float dt)
{
	//�ړ���V�[���̍쐬
	auto scene = TitleScene::createScene();
	scene = TitleScene::createScene();
	auto transition = TransitionFade::create(3.0f, scene);
	Director::getInstance()->replaceScene(transition);
}
//------------------------------------
//@! ���Ԃ�������,�V�[���ړ�����
//@! ����
//------------------------------------
bool LogoScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	//�ړ���V�[���̍쐬
	auto scene = TitleScene::createScene();
	auto transition = TransitionFade::create(1.0f, scene);
	Director::getInstance()->replaceScene(transition);

	this->unscheduleAllSelectors();

	return false;
}


