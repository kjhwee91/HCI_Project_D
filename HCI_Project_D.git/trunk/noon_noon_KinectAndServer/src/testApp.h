#pragma once

#include "ofxOpenNI.h"
#include "ofMain.h"
#include "KinectController.h"
#include "SnowBall.h"
#include "ofxNetwork.h"


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

	bool isMatchSnowBall();


private:
	ofxTCPServer m_Server;
	ofGLRenderer m_OpenGLRenderer;
	ofTrueTypeFont m_textFont;

	int m_CurrentStep;
	int test;
	string m_text;

	myHand m_LeftHand;
	myHand m_RightHand;

	bool m_PowerCharged;
	unsigned long long m_CurrentTime; 

	SnowBall m_SnowBall1;
	SnowBall m_SnowBall2;
	bool stepOneSend;
	bool stepTwoSend;

	ofSoundPlayer m_SummerBGM;

};

