#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "config.h"
#include "ofxTuioClient.h"
#include <array>
#include "ofxNetwork.h"

enum PointLocation
{
	NOWHERE = -1,
	INNER = 0,
	OUTER =1
};

struct TouchPoint
{
	float x;
	float y;
	PointLocation location;
};


class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void drawUI();
	void drawWait();
	void drawRestart();
	PointLocation checkLocation(TouchPoint myPoint);
	void drawSnow();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

	ofxTuioClient myTuio;

	void touchDown(ofTouchEventArgs & touch);
	void touchUp(ofTouchEventArgs & touch);
	void touchMoved(ofTouchEventArgs & touch);

	void Continue();
	void Wait();
	void Reset();


private:
	//통신관련
	ofxTCPClient m_Client;
	bool isConnected;
	bool flag;

	float m_VisibleWidth;
	float m_VisibleHeight;
	Point m_Origin;

	//손가락 시작점과 끝점을 계산하기 위한 배열
	std::array <TouchPoint,FINGER_NUMBER> m_StartPoint;
	std::array <TouchPoint,FINGER_NUMBER> m_EndPoint;
	unsigned int m_fingerIdx;

	int m_snowPoint;
	bool m_isPerfect;
	bool m_isReady;
	int m_currentStep;

	ofSoundPlayer m_SnowSound;

	ofImage m_outerCircle;
	ofImage m_innerCircle;


};

#endif
