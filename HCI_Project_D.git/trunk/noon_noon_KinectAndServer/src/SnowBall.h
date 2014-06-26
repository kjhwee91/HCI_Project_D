#pragma once
#include "ofGLRenderer.h"
#include "config.h"
#include "ofMain.h"
#include <array>

class SnowBall
{
public:
	SnowBall(void);
	~SnowBall(void);

	void init(ofGLRenderer openGLRender, int currentStep);
	ofPoint getPosition() {return m_SnowBallPosition;};
	void drawSnowBall(ofGLRenderer openGLRender);
	bool handInSnowBall(ofPoint rightHandPosition, ofPoint leftHandPosition);
	bool handInSnowBall(float rightX, float rightY, float leftX, float leftY);
	void moveSnowBall(ofPoint centerPosition);
	void matchSnowBall();
	bool isMatchSnow() {return m_isMatchSnow;}

private:
	ofImage m_SnowBallImg;
	ofPoint m_SnowBallPosition;
	int m_SnowBallType;
	float m_Width;
	float m_Height;
	bool m_isMovable;
	bool m_isMatchSnow;


	ofPoint m_Position;
	ofPoint m_initPosition;
};
