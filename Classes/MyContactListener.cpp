//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/5/10
//!	
//!	MyContactListener.cpp
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

//-----------------------------------
#include "MyContactListener.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
//-----------------------------------

USING_NS_CC;

//----------------------------------
//@! ŠJŽn
//@! 
void MyContactListener::BeginContact(b2ParticleSystem* particleSystem,
	b2ParticleContact* particleContact)
{
	void* bodyUserData;

	//bodyUserData = particleContact->GetIndexA()->GetBody()->GetUserData();
	//if (bodyUserData)
	//{
	//	Sprite* spr = static_cast<Sprite*>(bodyUserData);
	//	ContactFlag = true;
	//	spr->setPosition(0, 0);
	//}
	//bodyUserData = particleContact->GetIndexB()->GetBody()->GetUserData();
	//if (bodyUserData)
	//{
	//	Sprite* spr = static_cast<Sprite*>(bodyUserData);
	//	ContactFlag = true;
	//	spr->setPosition(0, 0);
	//}


}

void MyContactListener::EndContact()
{

}

void MyContactListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
	contact->SetEnabled(false);
}

void MyContactListener::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{
	
}
