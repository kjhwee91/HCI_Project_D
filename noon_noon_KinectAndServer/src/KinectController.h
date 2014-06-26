#pragma once
#include "ofxOpenNI.h"

class KinectController
{
public:
	KinectController(void);
	~KinectController(void);

public:
	static KinectController* getInstance(){
		if(instance == NULL)
		{
			instance = new KinectController();
		}
		return instance;
	}

	void Release(){
		if (NULL != instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void InitKinect();
	void RenderSkeleton();
	void Update();
	void DrawImage();
	void Stop();

	ofPoint getLeftHandPoint() {return m_leftHandPoint;}
	ofPoint getRightHandPoint() {return m_rightHandPoint;}

private:
	static KinectController* instance;
	ofxOpenNI openNIDevice;

	ofPoint m_leftHandPoint;
	ofPoint m_rightHandPoint;
};