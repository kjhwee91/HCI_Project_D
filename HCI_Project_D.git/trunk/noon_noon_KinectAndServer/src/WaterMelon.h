#pragma once
#include "ofGLRenderer.h"
#include "ofMain.h"
#include <array>

struct myWaterMelon
{
	ofImage m_Melon;
	float m_InitialSpeed;
	ofPoint m_MelonPosition;
	float m_FlyingAngle;
	float m_Width;
	float m_Height;
};

class WaterMelon
{
public:
	WaterMelon(void);
	~WaterMelon(void);

	void init(float positionX, float positionY);
	ofPoint getPosition() {return m_Position;};
	void drawMelons(ofGLRenderer openGLRender);
	bool collisionCheck(ofPoint point);
	bool collisionCheck(float pointX, float pointY);
	void smash();
	bool isSmashed() {return m_IsSmashed;};



private:
	//수박의 중점
	ofPoint m_Position;
	bool m_IsSmashed;
	//수박 전체의 크기
	float m_Width;
	float m_Height;
	std::array<myWaterMelon,4> m_WaterMelon;


};

