#pragma once

#include "ofxOpenNI.h"
#include "ofMain.h"
#include "KinectController.h"
#include "WaterMelon.h"



struct myHand
{
	float m_Width;
	float m_Height;
	float m_PositionX;
	float m_PositionY;
};

class testApp : public ofBaseApp{

public:

	void setup(); 
	void update();
	void draw();
	void exit();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void getTitanicPower(unsigned long long addedTime);

private:
	ofGLRenderer m_OpenGLRenderer;
	ofTrueTypeFont m_textFont;

	string m_text;

	myHand m_LeftHand;
	myHand m_RightHand;

	bool m_PowerCharged;
	unsigned long long m_CurrentTime; 

	unsigned long long m_TitanicPower;
	bool m_isPower;

	WaterMelon m_WaterMelon[2];

	ofSoundPlayer m_titanicBGM;
	ofImage m_TitanicIMG;
};

