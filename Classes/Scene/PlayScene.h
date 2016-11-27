//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/4/27
//!	
//!	PlayScene.h
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//--------------------------------------------
#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__
//--------------------------------------------
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLESDebugDraw.h"
#include "MyContactListener.h"
#include "Box2D\Dynamics\b2WorldCallbacks.h"
#include <stdint.h>
//--------------------------------------------
class Paint;
class Stage;
class GameSystem;
class DebugDrawNode;
//----------------------------------------------------------------------------------------
class PlayScene : public cocos2d::Layer//, public b2ContactListener
{
//----------------------------------------------------------------------------------------
private:
	b2World* m_pWorld;						//世界
	DebugDrawNode* m_debugDraw;					//レンダー
	cocos2d::Vec2 m_touchpos;				//タッチ座標					
	Stage* m_Stage;							//ステージ
	GameSystem* m_gameSystem;				//ゲームシステム
	int m_stageLevel;					//選んだステージ

//----------------------------------------------------------------------------------------
public:

	static cocos2d::Scene* createScene(int level);		//シーン作成

	virtual bool init(int stageLevel);				//初期化
	static PlayScene* create(int stageLevel);

	void update(float dt)override;										//更新
	void initPhysics();													//初期化
	~PlayScene();														//デストラクター
	Stage* getStage();
	void createWorld();
																		
																		
//----------------------------------------------------------------------------------------

	//当たり判定-------------------------------------------------
	//void BeginContact(b2Contact* contact)override;
	//void EndContact(b2Contact* contact)override;
	//void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)override;
	//void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)override;
	//---------------------------------------------------------------



};
//----------------------------------------------------------------------------------------
#endif 
