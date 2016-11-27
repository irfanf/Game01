#include "DebugDrawNode.h"

USING_NS_CC;

DebugDrawNode::~DebugDrawNode()
{
	delete m_pDraw;
}

DebugDrawNode* DebugDrawNode::create(b2World* world)
{
	DebugDrawNode* pRet = new(std::nothrow) DebugDrawNode();
	if (pRet&&pRet->init(world))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

void DebugDrawNode::onDraw()
{
	m_pWorld->DrawDebugData();
}

bool DebugDrawNode::init(b2World* world)
{
	if (!Node::init())
	{
		return false;
	}

	m_pWorld = world;

	m_pDraw = new GLESDebugDraw(PTM_RATIO);

	//uint32 flags = 0xffffffff;
	uint32 flags = b2Draw::e_particleBit;
	m_pDraw->SetFlags(flags);
	m_pWorld->SetDebugDraw(m_pDraw);

	return true;
}

void DebugDrawNode::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, uint32_t flags)
{
	
	m_Command.init(this->getGlobalZOrder());
	m_Command.func = CC_CALLBACK_0(DebugDrawNode::onDraw, this);

	renderer->addCommand(&m_Command);
}



