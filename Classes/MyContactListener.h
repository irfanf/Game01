//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/5/10
//!	
//!	MyContactListener.h
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#ifndef __MYCONTACTLISTENER_H__
#define __MYCONTACTLISTENER_H__

//--------------------------
#include "cocos2d.h"
#include "Box2D/Box2D.h"
//--------------------------

class MyContactListener : public b2ContactListener
{
//-----------------------------------------------------------------
public:
	void BeginContact(b2ParticleSystem* particleSystem,
		b2ParticleContact* particleContact);
	void EndContact();
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	bool ContactFlag;
//-----------------------------------------------------------------
};

#endif
