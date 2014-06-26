#include "testApp.h"
#include "KinectController.h"

float HAND_RADIUS = 20.0f;

//--------------------------------------------------------------
void testApp::setup() {
	//--SERVER SETUP--//
	m_Server.setup(8080);

	ofSetLogLevel(OF_LOG_VERBOSE);
	KinectController::getInstance()->InitKinect();
	m_OpenGLRenderer = new ofGLRenderer();

	ofBackground(0,0,0);
	//테스트중임
	m_CurrentStep = 0;
	//m_SnowBall1.init(m_OpenGLRenderer,1);
	//m_SnowBall2.init(m_OpenGLRenderer,2);

	m_LeftHand.m_PositionX =KinectController::getInstance()->getLeftHandPoint().x;
	m_LeftHand.m_PositionY =KinectController::getInstance()->getLeftHandPoint().y;

	m_RightHand.m_PositionX =KinectController::getInstance()->getRightHandPoint().x;
	m_RightHand.m_PositionY =KinectController::getInstance()->getRightHandPoint().y;

	m_CurrentTime = 0;
	stepOneSend = true;
	stepTwoSend = true;

	m_SummerBGM.loadSound("summer.mp3");
	m_SummerBGM.setLoop(true);
	m_SummerBGM.play();
}

//--------------------------------------------------------------
void testApp::update(){
	//--SERVERUPDATE--//
	if( m_Server.isClientConnected(0) )
	{
		// maybe the client is sending something
		string str = m_Server.receive(0);
		cout<<str<<endl;
		if (str == "FIRSTSNOW"){
			m_SnowBall1.init(m_OpenGLRenderer,1);
			m_CurrentStep = 1;
		} else if (str == "SECONDSNOW"){
			m_SnowBall2.init(m_OpenGLRenderer,2);
			m_CurrentStep = 2;
		//} else if (str == "LASTSNOW"){
		//	step = 3;
		} else if (str == "RESET"){
			m_CurrentStep = 0;
			stepOneSend = true;
			stepTwoSend = true;
		} else {
			m_CurrentStep = m_CurrentStep;
			cout<<"Received Null String (not FIRSTSNOW or SECONDSNOW or LASTSNOW)"<<endl;
		}
	} else {
		m_CurrentStep = m_CurrentStep;
	}

	unsigned long long tempTime = ofGetElapsedTimeMillis();

	KinectController::getInstance()->Update();
	m_LeftHand.m_PositionX = KinectController::getInstance()->getLeftHandPoint().x;
	m_LeftHand.m_PositionY = KinectController::getInstance()->getLeftHandPoint().y;
	m_RightHand.m_PositionX = KinectController::getInstance()->getRightHandPoint().x;
	m_RightHand.m_PositionY = KinectController::getInstance()->getRightHandPoint().y;
	m_CurrentTime = tempTime;

	switch(m_CurrentStep){
	case 0:
		break;
	case 1:
		//아래쪽에 있는 눈덩이 움직이기
		//매번 눈덩이가 매칭되는지 확인한다.
		if(isMatchSnowBall())
		{
			m_SnowBall1.matchSnowBall();
			if (stepOneSend){
				m_Server.send(0, "CONTINUE");
				stepOneSend = false;
			}
		}
		//눈덩이가 매칭되지 않은 경우에만 이동할 수 있다.
		if(m_SnowBall1.isMatchSnow() == false
			&&m_SnowBall1.handInSnowBall(m_RightHand.m_PositionX,m_RightHand.m_PositionY, m_LeftHand.m_PositionX,m_LeftHand.m_PositionY))
		{
			ofPoint handCenterPos;
			handCenterPos.x = (m_LeftHand.m_PositionX + m_RightHand.m_PositionX)/2;
			handCenterPos.y = (m_LeftHand.m_PositionY + m_RightHand.m_PositionY)/2;
			m_SnowBall1.moveSnowBall(handCenterPos);
			//m_Server.send(0, "WAIT");
		}
		break;
	case 2:
		//매번 눈덩이가 매칭되는지 확인한다.
		if(isMatchSnowBall())
		{
			m_SnowBall2.matchSnowBall();
			if (stepTwoSend){
				m_Server.send(0, "WAIT");
				stepOneSend = false;
			}

		}
		//눈덩이가 매칭되지 않은 경우에만 이동할 수 있다.
		if(m_SnowBall2.isMatchSnow() == false
			&&m_SnowBall2.handInSnowBall(m_RightHand.m_PositionX,m_RightHand.m_PositionY, m_LeftHand.m_PositionX,m_LeftHand.m_PositionY))
		{
			ofPoint handCenterPos;
			handCenterPos.x = (m_LeftHand.m_PositionX + m_RightHand.m_PositionX)/2;
			handCenterPos.y = (m_LeftHand.m_PositionY + m_RightHand.m_PositionY)/2;
			m_SnowBall2.moveSnowBall(handCenterPos);
		}	

		break;
	case 3:
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	KinectController::getInstance()->DrawImage();
	KinectController::getInstance()->RenderSkeleton();
	
	//핸드그리기
	ofPushMatrix();
	ofCircle(m_LeftHand.m_PositionX,m_LeftHand.m_PositionY,HAND_RADIUS);
	ofCircle(m_RightHand.m_PositionX,m_RightHand.m_PositionY,HAND_RADIUS);
	ofPopMatrix();

	ofPushMatrix();
	//바닥 그리기
	ofImage floor;
	floor.loadImage("snow_floor.png");
	floor.draw(0.0f,ofGetWindowHeight()-150);

	//눈사람 만들기
	switch(m_CurrentStep){
	case 0:
		cout<<"set bottom with snow"<<endl;
		break;
	case 1:
		m_SnowBall1.drawSnowBall(m_OpenGLRenderer);
		cout<<"first step"<<endl;
		break;
	case 2:
		m_SnowBall1.drawSnowBall(m_OpenGLRenderer);
		m_SnowBall2.drawSnowBall(m_OpenGLRenderer);
		cout<<"second step"<<endl;
		break;
	case 3:
		cout<<"last step"<<endl;
		break;
	default:
		break;
	}
	ofPopMatrix();
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

bool testApp::isMatchSnowBall()
{
	//스텝에 따른 매칭 조건 확인 (추가 가능)
	if(m_CurrentStep == 1)
	{
		//기준점
		float matchPosX = ofGetWindowWidth()/2 - SNOWBALL1_SIZE/2;
		float matchPosY = ofGetWindowHeight() - SNOW_FLOOR_HEIGHT - SNOWBALL1_SIZE;

		if(abs(m_SnowBall1.getPosition().x-matchPosX)>100)
			return false;
		if(abs(m_SnowBall1.getPosition().y-matchPosY)>100)
			return false;

		return true;
	}

	if(m_CurrentStep == 2)
	{
		//기준점
		float matchPosX = ofGetWindowWidth()/2 - SNOWBALL2_SIZE/2;
		float matchPosY = ofGetWindowHeight() - SNOW_FLOOR_HEIGHT - SNOWBALL1_SIZE - SNOWBALL2_SIZE;

		if(abs(m_SnowBall2.getPosition().x-matchPosX)>100)
			return false;
		if(abs(m_SnowBall2.getPosition().y-matchPosY)>100)
			return false;

		return true;
	}
}

