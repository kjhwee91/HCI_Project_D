#include "testApp.h"
#include "math.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);

	m_VisibleHeight=ofGetWindowHeight();
	m_VisibleWidth=ofGetWindowWidth();
	m_snowPoint = 0;
	m_isPerfect = false;
	m_isReady = true;
	m_currentStep = 0;
	m_Origin.v = m_VisibleWidth/2;
	m_Origin.h = m_VisibleHeight/2;
	m_SnowSound.loadSound("snowSound.wav");
	//drawUI();

	m_outerCircle.loadImage("mt_area_outer.png");
	m_innerCircle.loadImage("mt_area_inner.png");



	//Connect to Port
	myTuio.connect(3333);

	//소켓통신
	//isConnected = m_Client.setup("127.0.0.1", 8080);
	isConnected = m_Client.setup("10.73.43.212", 8080);
	//isConnected = false;
	//Assign Global TUIO Callback Functions
	ofAddListener(ofEvents().touchDown,this,&testApp::touchDown);
	ofAddListener(ofEvents().touchUp,this,&testApp::touchUp);
	ofAddListener(ofEvents().touchMoved,this,&testApp::touchMoved);

}

void testApp::drawUI()
{
	//상단 설명 텍스트
	ofImage	mtIntroduction;
	mtIntroduction.loadImage("mt_ui_gatherText.png");
	mtIntroduction.draw(250,50);

	//프로그레스 바 설명 텍스트
	ofImage mtProgressBarText;
	mtProgressBarText.loadImage("mt_ui_snowgage.png");
	mtProgressBarText.draw(50,m_VisibleHeight-300);

	//프로그레스 바
	ofImage mtProgressBar;
	if(m_snowPoint<5)
		mtProgressBar.loadImage("mt_ui_snowBlank.png");
	else if(m_snowPoint>=5 && m_snowPoint<10)
		mtProgressBar.loadImage("mt_ui_snow1.png");
	else if(m_snowPoint>=10 && m_snowPoint<15)
		mtProgressBar.loadImage("mt_ui_snow2.png");
	else if(m_snowPoint>=15 && m_snowPoint<20)
		mtProgressBar.loadImage("mt_ui_snow3.png");
	else if(m_snowPoint>=20 && m_snowPoint<25)
		mtProgressBar.loadImage("mt_ui_snow4.png");
	else if(m_snowPoint>=25)
		mtProgressBar.loadImage("mt_ui_snow5.png");

	mtProgressBar.draw(50,m_VisibleHeight-200);
}

//--------------------------------------------------------------
void testApp::update(){
	if ( m_snowPoint >= SNOW_NUMBER )
	{
		m_isPerfect = true;
	}


	//소켓 관련
	if(isConnected)
	{
		//완성되었을 때 서버로 보내는 메시지
		if(m_isPerfect && m_isReady)
		{
			string msgThrow;
			switch (m_currentStep)
			{
			case 0:
				msgThrow = "FIRSTSNOW";
				m_isReady = false;
				break;
			case 1:
				msgThrow = "SECONDSNOW";
				m_isReady = false;
				break;
			case 3:
				msgThrow = "RESET";
				Reset();
			default:
				break;
			}
			m_Client.send(msgThrow);
			
		}		

		//서버에서 받는 메시지
		string msgRecieve = m_Client.receive();
		cout<<"I received!!!:"<<msgRecieve<<endl;
		if(m_isReady == false)
		{
			if(msgRecieve == "CONTINUE")
			{
				Continue();
				m_isReady = true;
			}
			else if(msgRecieve == "WAIT")
			{
				Wait();
				m_isReady = true;
			}
		}

	}
	else
	{
		cout<<"not connected"<<endl;
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	//render TUIO Cursors and Objects
	if(m_currentStep < 2)
	{
		//바깥 영역
		//ofSetColor(198, 226, 255);
		//ofFill();
		//ofCircle(m_VisibleWidth/2,m_VisibleHeight/2,BOUNDARY_OUTER);

		m_outerCircle.setAnchorPercent(0.5,0.5);
		m_outerCircle.draw(m_Origin.v,m_Origin.h);

		//안쪽 영역
		ofSetColor(185,211,238);
		ofFill();
		ofCircle(m_VisibleWidth/2,m_VisibleHeight/2,BOUNDARY_INNER);

		//m_innerCircle.setAnchorPercent(0.5,0.5);
		//m_innerCircle.draw(m_Origin.v,m_Origin.h);

		drawSnow();
		drawUI();

		myTuio.drawCursors();
		myTuio.drawObjects();
	}//기다리는 스탭
	else if(m_currentStep == 2)
	{
		drawRestart();
	}//다시 시작하냐고 묻는 스텝
	else if(m_currentStep==3)
	{
		drawRestart();
	}

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


void testApp::touchDown(ofTouchEventArgs & touch){
	//터치가 될때마다 손가락 시작좌표에 넣는다.
	int tempIdx = touch.id % FINGER_NUMBER;

	m_StartPoint[tempIdx].x = m_VisibleWidth*touch.x;
	m_StartPoint[tempIdx].y = m_VisibleHeight*touch.y;

	m_StartPoint[tempIdx].location = checkLocation(m_StartPoint[tempIdx]);

	//Wait Step인 경우
	if(m_currentStep == 2)
	{
		m_isPerfect=true;
		m_currentStep = 3;
	}
}

void testApp::touchUp(ofTouchEventArgs & touch){
	int tempIdx = touch.id % FINGER_NUMBER;

	m_EndPoint[tempIdx].x = m_VisibleWidth*touch.x;
	m_EndPoint[tempIdx].y = m_VisibleHeight*touch.y;

	m_EndPoint[tempIdx].location = checkLocation(m_EndPoint[tempIdx]);

	//영역검사를 해볼까?
	if(m_isReady==true 
		&& m_StartPoint[tempIdx].location == OUTER && m_EndPoint[tempIdx].location==INNER)
	{
		m_snowPoint++;
		cout<<"snow Point:" +ofToString(m_snowPoint)<<endl;
	}
	m_SnowSound.play();
}

void testApp::touchMoved(ofTouchEventArgs & touch){

}

PointLocation testApp::checkLocation(TouchPoint myPoint){
	float distance = sqrt( pow(myPoint.x-m_Origin.v,2)+pow(myPoint.y-m_Origin.h,2) );
	if(distance<BOUNDARY_INNER)
	{
		myPoint.location = INNER;
		cout<<"you're in inner boundary!!"<<endl;
	}
	else if(distance>BOUNDARY_INNER && distance<BOUNDARY_OUTER)
	{
		myPoint.location = NOWHERE;
		cout<<"reach farther!"<<endl;
	}
	else
	{
		myPoint.location = OUTER;
		cout<<"you're in outer boundary!!"<<endl;
	}

	return myPoint.location;
}

void testApp::drawSnow(){
	if(m_isPerfect)
	{
		ofImage mtUiThrowBall;

		mtUiThrowBall.loadImage("mt_ui_throw.png");
		mtUiThrowBall.setAnchorPercent(0.5,0.5);
		mtUiThrowBall.draw(m_Origin.v,m_Origin.h);
	}
}

void testApp::Continue()
{
	m_isPerfect = false;
	m_snowPoint = 0;
	m_currentStep=1;
}

void testApp::Wait()
{
	m_isPerfect = true;
	m_snowPoint = 0;
	m_currentStep = 2;
}

void testApp::Reset()
{
	m_isPerfect = false;
	m_isReady = true;
	m_snowPoint = 0;
	m_currentStep = 0;
}

void testApp::drawWait()
{
	ofImage waitMessage;

	waitMessage.loadImage("mt_wait_notice.png");
	waitMessage.setAnchorPercent(0.5,0.5);
	waitMessage.draw(m_Origin.v,m_Origin.h);
}

void testApp::drawRestart()
{
	ofImage waitMessage;

	waitMessage.loadImage("mt_restart_message.png");
	waitMessage.setAnchorPercent(0.5,0.5);
	waitMessage.draw(m_Origin.v,m_Origin.h);
}
