//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/4/27
//!	
//!	Paint.h
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#ifndef __PAINT_H__
#define __PAINT_H__

//--------------------------
#include "cocos2d.h"
#include "Box2D/Box2D.h"
//--------------------------
//�p�[�e�B�N���̐F
enum ParticleColor
{
	RED,
	BLUE,
	PURPLE,
	GREEN,
	ORANGE,
	YELLOW,
	BLACK,
	PINK,
	NATTOU
};

//---------------------------------------------------------------------
class Paint : public cocos2d::Node
{
//-----------------------------------------------------------------------
private:

	b2ParticleGroupDef m_pParticleDef;
	b2ParticleSystem* m_particleSystem;
	b2World* m_pWorld;								//���[���h
	cocos2d::Sprite* m_Bomb;
	float m_x, m_y;									//���W
//�W------------------------------------------------------------------
	
	b2Body* m_capBody;
	int m_count;									//�J�E���g�p
	bool m_Closed;									//�W���J���Ă邩�ǂ���

//---------------------------------------------------------------------
public:

	virtual bool init(b2World* world);				//������
	static Paint* create(b2World* world);			//�쐬����Ƃ��Ƀ��[���h����^����
	void createParticle(float x, float y,			//�p�[�e�B�N������� 
		int color);							

	void update(float dt)override;					//�X�V

	b2ParticleSystem* getParticleSystem();		
	
	void setBombStatus(bool status) { m_Closed = status; };
//-----------------------------------------------------------------------
private:

	void setColor(int color);						//�J���[�ݒ�
		
//-----------------------------------------------------------------------
};
//-----------------------------------------------------------------------
#endif 
