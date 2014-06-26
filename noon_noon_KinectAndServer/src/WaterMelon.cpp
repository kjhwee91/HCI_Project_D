#include "WaterMelon.h"

std::string WaterMelon_IMAGE[4] ={"watermelon0.png","watermelon1.png","watermelon2.png","watermelon3.png"};
std::string WaterMelon_SMASHED[4]={"watermelo_smashed0.png","watermelo_smashed0.png","watermelo_smashed0.png","watermelo_smashed0.png"};
ofPoint WaterMelon_POS[4] = {ofPoint(-50,-50),ofPoint(0,-50),ofPoint(-50,0),ofPoint(0,0)};
float WaterMelon_SPEED[4] = {50,50,60,70};
float WaterMelon_FlyingAngle[4] = {45,135,225,315};

unsigned long long CHARGE_RATE = 2*1000;
float WaterMelon_SCALE_RATE = 0.2f;

WaterMelon::WaterMelon(void)
{
	m_Position.x = 0.0f;
	m_Position.y = 0.0f;
}

WaterMelon::~WaterMelon(void)
{
}

void WaterMelon::init(float positionX, float positionY)
{
	m_IsSmashed = false;
	m_Position.x = positionX;
	m_Position.y = positionY;

	for(int i = 0 ; i <4 ; i++)
	{
		m_WaterMelon[i].m_Melon.loadImage(WaterMelon_IMAGE[i].c_str());
		m_WaterMelon[i].m_MelonPosition.x = m_Position.x + WaterMelon_POS[i].x;
		m_WaterMelon[i].m_MelonPosition.y = m_Position.y + WaterMelon_POS[i].y;
		m_WaterMelon[i].m_FlyingAngle = WaterMelon_FlyingAngle[i];
		m_WaterMelon[i].m_InitialSpeed = WaterMelon_SPEED[i];
		m_WaterMelon[i].m_Width = m_WaterMelon[i].m_Melon.getWidth();
		m_WaterMelon[i].m_Height = m_WaterMelon[i].m_Melon.getHeight();
	}
	m_Width = m_WaterMelon[0].m_Width*2;
	m_Height = m_WaterMelon[0].m_Height*2;
}

bool WaterMelon::collisionCheck( ofPoint point )
{
	return collisionCheck(point.x,point.y);
}

bool WaterMelon::collisionCheck( float pointX, float pointY )
{
	if(abs(pointX-(m_Position.x-50))<50 && abs(pointY-(m_Position.y-50))<50)
		return true;
	else
		return false;
}

void WaterMelon::drawMelons(ofGLRenderer openGLRender)
{
	for(int i = 0 ; i<4;i++)
	{
		openGLRender.pushMatrix();	
		openGLRender.translate(m_WaterMelon[i].m_MelonPosition);

		openGLRender.draw(m_WaterMelon[i].m_Melon, -m_Width / 2, -m_Height / 2, 0.0,
			m_WaterMelon[i].m_Width,m_WaterMelon[i].m_Height,
			0.0, 0.0,
			m_WaterMelon[i].m_Melon.getWidth(),m_WaterMelon[i].m_Melon.getHeight());
		openGLRender.popMatrix();
	}
}

void WaterMelon::smash()
{
	m_IsSmashed = true;
	for(int i = 0 ; i < 4; i++)
	{
		m_WaterMelon[i].m_Melon.loadImage(WaterMelon_SMASHED[i].c_str());
	}
}