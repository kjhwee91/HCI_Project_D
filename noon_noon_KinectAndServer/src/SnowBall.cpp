#include "SnowBall.h"

SnowBall::SnowBall(void)
{
	m_Position.x = 0.0f;
	m_Position.y = 0.0f;
}

SnowBall::~SnowBall(void)
{
}

void SnowBall::init(ofGLRenderer openGLRender, int currentStep)
{
	//스텝에 따른 눈덩이 형성
	switch (currentStep)
	{
	case 1:
		m_SnowBallImg.loadImage("snowball1.png");
		m_SnowBallType = 1;
		m_SnowBallPosition.x = SNOWBALL1_INITPOS_X;
		m_SnowBallPosition.y = ofGetWindowHeight() - SNOW_FLOOR_HEIGHT- SNOWBALL1_SIZE;

		//m_SnowBallType = 1;
		//m_SnowBallPosition.x = ofGetWindowWidth()/2 - SNOWBALL1_SIZE/2;
		//m_SnowBallPosition.y = ofGetWindowHeight() - SNOW_FLOOR_HEIGHT- SNOWBALL1_SIZE;
		break;
	case 2:
		m_SnowBallImg.loadImage("snowball2_nonose.png");
		m_SnowBallType = 2;
		m_SnowBallPosition.x = SNOWBALL2_INITPOS_X;
		m_SnowBallPosition.y = ofGetWindowHeight() - SNOW_FLOOR_HEIGHT- SNOWBALL2_SIZE;
		break;
	default:
		break;
	}
	m_isMatchSnow = false;
	m_isMovable = false;
	m_Height = m_SnowBallImg.getHeight();
	m_Width = m_SnowBallImg.getWidth();
}

void SnowBall::drawSnowBall(ofGLRenderer openGLRender)
{
	openGLRender.pushMatrix();	
	m_SnowBallImg.draw(m_SnowBallPosition);
	openGLRender.popMatrix();
}

bool SnowBall::handInSnowBall(ofPoint rightHandPosition, ofPoint leftHandPosition)
{
	return handInSnowBall(rightHandPosition.x,rightHandPosition.y,leftHandPosition.x,leftHandPosition.y);
}

bool SnowBall::handInSnowBall(float rightX, float rightY, float leftX, float leftY)
{
	float minX = m_SnowBallPosition.x;
	float minY = m_SnowBallPosition.y;
	float maxX = minX + m_Width;
	float maxY = minY + m_Height;

	if ((minX > rightX)||(maxX < rightX)){
		return false;
	}
	if ((minY > rightY)||(maxY < rightY)){
		return false;
	}
	if ((minX > leftX)||(maxX < leftX)){
		return false;
	}
	if ((minY > leftY)||(maxY < leftY)){
		return false;
	}
	return true;
}

void SnowBall::moveSnowBall(ofPoint centerPosition)
{
	m_SnowBallPosition.x = centerPosition.x - m_Width/2;
	m_SnowBallPosition.y = centerPosition.y - m_Height/2;
}

void SnowBall::matchSnowBall()
{
	//스텝에 따른 특정 위치에 고정시켜 버린다.(스텝3 추가 가능)
	if (m_SnowBallType == 1)
	{
		m_isMatchSnow = true;
		m_SnowBallPosition.x = ofGetWindowWidth()/2 - SNOWBALL1_SIZE/2;
		m_SnowBallPosition.y = ofGetWindowHeight() - SNOW_FLOOR_HEIGHT- SNOWBALL1_SIZE;
	}

	if( m_SnowBallType == 2)
	{
		m_SnowBallImg.loadImage("snowball2.png");
		m_isMatchSnow = true;
		m_SnowBallPosition.x = ofGetWindowWidth()/2 - m_Width/2;
		m_SnowBallPosition.y = ofGetWindowHeight() - SNOW_FLOOR_HEIGHT- SNOWBALL1_SIZE - SNOWBALL2_SIZE;
	}
}


