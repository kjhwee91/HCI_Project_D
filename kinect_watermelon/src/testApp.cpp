#include "testApp.h"
#include "KinectController.h"

float HAND_BOX_SIZE = 30.0f;

//--------------------------------------------------------------
void testApp::setup() {

	ofSetLogLevel(OF_LOG_VERBOSE);
	KinectController::getInstance()->InitKinect();
	m_OpenGLRenderer = new ofGLRenderer();

	ofBackground(0,0,0);

	m_LeftHand.m_Width = HAND_BOX_SIZE;
	m_LeftHand.m_Height = HAND_BOX_SIZE;
	m_RightHand.m_Width = HAND_BOX_SIZE;
	m_RightHand.m_Height = HAND_BOX_SIZE;

	m_LeftHand.m_PositionX =KinectController::getInstance()->getLeftHandPoint().x;
	m_LeftHand.m_PositionY =KinectController::getInstance()->getLeftHandPoint().y;

	m_RightHand.m_PositionX =KinectController::getInstance()->getRightHandPoint().x;
	m_RightHand.m_PositionY =KinectController::getInstance()->getRightHandPoint().y;



	m_WaterMelon[0].init(250,150);
	m_WaterMelon[1].init(550.0,150.0f);

	m_CurrentTime = 0;
	m_TitanicPower = 0;
	m_titanicBGM.loadSound("titanic.mp3",false);
	m_isPower = false;
	m_TitanicIMG.loadImage("titanic.png");

}

//--------------------------------------------------------------
void testApp::update(){
	unsigned long long tempTime = ofGetElapsedTimeMillis();

	KinectController::getInstance()->Update();
	m_LeftHand.m_PositionX = KinectController::getInstance()->getLeftHandPoint().x;
	m_LeftHand.m_PositionY = KinectController::getInstance()->getLeftHandPoint().y;
	m_RightHand.m_PositionX = KinectController::getInstance()->getRightHandPoint().x;
	m_RightHand.m_PositionY = KinectController::getInstance()->getRightHandPoint().y;

	for(int i = 0; i< 2; i++)
	{
		if(m_WaterMelon[i].collisionCheck(m_LeftHand.m_PositionX,m_LeftHand.m_PositionY))
		{
			m_WaterMelon[i].smash();
		}
		if(m_WaterMelon[i].collisionCheck(m_RightHand.m_PositionX,m_RightHand.m_PositionY))
		{
			m_WaterMelon[i].smash();
		}
	}


	//타이타닉인가?
	if(abs(m_LeftHand.m_PositionY-m_RightHand.m_PositionY) < 30
		&& abs(m_LeftHand.m_PositionX - m_RightHand.m_PositionX)>200)
	{
		printf("TITANIC!!~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		getTitanicPower(tempTime - m_CurrentTime);
	}
	else
	{
		m_TitanicPower = 0;
	}

	if(m_TitanicPower>3000 && m_isPower == false)
	{
		m_isPower = true;
		m_titanicBGM.play();
	}

	m_CurrentTime = tempTime;
}

//--------------------------------------------------------------
void testApp::draw(){
		KinectController::getInstance()->DrawImage();

		ofPushMatrix();
		KinectController::getInstance()->RenderSkeleton();
		//핸드그리기
		m_OpenGLRenderer.drawRectangle(m_LeftHand.m_PositionX,m_LeftHand.m_PositionY,0,m_LeftHand.m_Width,m_LeftHand.m_Height);
		m_OpenGLRenderer.drawRectangle(m_RightHand.m_PositionX,m_RightHand.m_PositionY,0,m_RightHand.m_Width,m_RightHand.m_Height);
		
		ofPopMatrix();

		if(m_isPower)
		{
			ofPushMatrix();
			m_OpenGLRenderer.translate(0,0);

			m_OpenGLRenderer.draw(m_TitanicIMG, 0, 0, 0.0,
				640,480,
				0.0, 0.0,
				m_TitanicIMG.getWidth(),m_TitanicIMG.getHeight());
			ofPopMatrix();

		}

		m_WaterMelon[0].drawMelons(m_OpenGLRenderer);
		m_WaterMelon[1].drawMelons(m_OpenGLRenderer);
}

//--------------------------------------------------------------
void testApp::exit(){
	KinectController::getInstance()->Stop();
	KinectController::getInstance()->Release();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

void testApp::getTitanicPower( unsigned long long addedTime )
{
	m_TitanicPower +=addedTime;
}
