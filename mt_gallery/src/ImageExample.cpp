#include "ImageExample.h"

//array<string,MAX_NUM> ALBUM00 = {"sun.png","mercury.png","venus.png","earth.png","mars.png","jupiter.png","saturn.png"};
array<string,MAX_NUM> ALBUM00 = {"album00.png","ca.jpg","darkknight.jpg","gaogal.jpg","ironman.png","maleficent.png","startrek.png"};

const int ALBUM00_NUM = 6;


//--------------------------------------------------------------
void ImageExample::setup(){
	ofSetFrameRate(60);
	// Connect
	MyClient.connect(3333);

	ofAddListener(ofEvents().touchDown, this, &ImageExample::touchDown);
	ofAddListener(ofEvents().touchMoved, this, &ImageExample::touchMoved);
	ofAddListener(ofEvents().touchUp, this, &ImageExample::touchUp);

	// 해제는 어디서 하죠?
	m_OpenGLRenderer = new ofGLRenderer();

	//초기 앨범 위치 지정
	m_Mode = M_OUT;
	m_currentElement = nullptr;
	m_backOriginX = 0;
	m_backOriginY = 0;
	m_backImage.loadImage("galaxy04.jpg");
	

	for(int albumNum = 0;albumNum<1;albumNum++)
	{
		m_Album[albumNum] = new myImage;
		m_Album[albumNum]->m_Image.loadImage(ALBUM00[0].c_str());
		m_Album[albumNum]->m_ImgPositionX = WINDOW_WIDTH/2;
		m_Album[albumNum]->m_ImgPositionY = WINDOW_HEIGHT/2;
		m_Album[albumNum]->m_ImgRotateAngle = 0;
		m_Album[albumNum]->m_ImgWidth = m_Album[albumNum]->m_Image.getWidth()*0.5;
		m_Album[albumNum]->m_ImgHeight = m_Album[albumNum]->m_Image.getHeight()*0.5;
		m_Album[albumNum]->m_Distance = 400.0f;
		m_Album[albumNum]->m_isCover = true;
		m_Album[albumNum]->m_Mode = M_OUT;
		myImage* currentImage = m_Album[albumNum];

		float rad = -90.0;

		for(int i = 0; i<ALBUM00_NUM;i++)
		{
			myImage* newImage = new myImage;
			newImage->m_Image.loadImage(ALBUM00[i+1].c_str());
			newImage->m_ImgWidth = newImage->m_Image.getWidth()*0.5;
			newImage->m_ImgHeight = newImage->m_Image.getHeight()*0.5;
			newImage->m_ImgPositionX = m_Album[albumNum]->m_ImgPositionX + m_Album[albumNum]->m_Distance*cos(rad*PI/180);
			newImage->m_ImgPositionY = m_Album[albumNum]->m_ImgPositionY + m_Album[albumNum]->m_Distance*sin(rad*PI/180);
			newImage->m_ImgRotateAngle = 0.0;
			newImage->m_Mode = M_OUT;
			newImage->m_isCover = false;
			newImage->m_isVisible = false;
			currentImage->nextImage = newImage;
			newImage->nextImage = nullptr;
			currentImage = newImage;
			rad += 30.0f;
			
		}
	}
	//시작시간 넣는다
	m_elapsedTime = ofGetElapsedTimeMillis();

}

//--------------------------------------------------------------
void ImageExample::update(){

}

//--------------------------------------------------------------
void ImageExample::draw(){
	m_backImage.draw(0,0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
	//모든 엘리멘트 다 그린다
	for(int albumNum = 0; albumNum<1; albumNum++)
	{
		m_OpenGLRenderer.pushMatrix();

		m_OpenGLRenderer.translate(m_Album[albumNum]->m_ImgPositionX, m_Album[albumNum]->m_ImgPositionY);
		m_OpenGLRenderer.rotateZ(m_Album[albumNum]->m_ImgRotateAngle);

		m_OpenGLRenderer.draw(m_Album[albumNum]->m_Image, -m_Album[albumNum]->m_ImgWidth / 2, -m_Album[albumNum]->m_ImgHeight / 2, 0.0,
			m_Album[albumNum]->m_ImgWidth, m_Album[albumNum]->m_ImgHeight,
			0.0, 0.0,
			m_Album[albumNum]->m_Image.getWidth(),m_Album[albumNum]->m_Image.getHeight());

		m_OpenGLRenderer.popMatrix();

		myImage* currentImage = new myImage;
		currentImage = m_Album[albumNum]->nextImage;
		while(currentImage != nullptr && currentImage->m_isVisible)
		{
			m_OpenGLRenderer.pushMatrix();	
			m_OpenGLRenderer.translate(currentImage->m_ImgPositionX,currentImage->m_ImgPositionY);
			m_OpenGLRenderer.rotateZ(currentImage->m_ImgRotateAngle);

			m_OpenGLRenderer.draw(currentImage->m_Image, -currentImage->m_ImgWidth / 2, -currentImage->m_ImgHeight / 2, 0.0,
				currentImage->m_ImgWidth, currentImage->m_ImgHeight,
				0.0, 0.0,
				currentImage->m_Image.getWidth(),currentImage->m_Image.getHeight());
			m_OpenGLRenderer.popMatrix();
			currentImage = currentImage->nextImage;
		}

	}

}

//--------------------------------------------------------------
void ImageExample::keyPressed(int key){

}

//--------------------------------------------------------------
void ImageExample::keyReleased(int key){

}

//--------------------------------------------------------------
void ImageExample::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ImageExample::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ImageExample::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ImageExample::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ImageExample::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ImageExample::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ImageExample::dragEvent(ofDragInfo dragInfo){ 
	
}

void ImageExample::touchDown( ofTouchEventArgs & touch )
{
	TUIO::TuioCursor* cursor1 = nullptr;
	TUIO::TuioCursor* cursor2 = nullptr;
	TUIO::TuioCursor* cursor3 = nullptr;
	TUIO::TuioCursor* cursor4 = nullptr;


	unsigned long long currentTime = ofGetElapsedTimeMillis();
	if(currentTime - m_elapsedTime <= 500)
	{
		m_Mode = M_DOUBLETAP;
	}
	else
	{
		m_Mode = M_TAP;
	}

	int cursorNum = MyClient.client->getTuioCursors().size();
	switch (cursorNum)
	{
	case 1:
		//앨범이고 더블클릭일 경우 사진들 숨기기
		for ( auto *iter : MyClient.client->getTuioCursors() )
		{
			switch ( iter->getCursorID() )
			{
			case 0:
				cursor1 = iter;
				break;
			default:
				break;
			}
		}
		if(cursor1 == nullptr)
			return;
		m_currentElement = getCurrentImage(cursor1);
		if(m_currentElement == nullptr)
		{
			break;
		}
		if(m_currentElement->m_isCover && m_Mode == M_DOUBLETAP)
		{
			hideImages(m_currentElement);
		}
		//앨범이고 탭일 경우 사진들 보이기
		else if(m_currentElement->m_isCover && m_Mode == M_TAP)
		{
			showImages(m_currentElement);
		}
		//사진일 경우 단순 선택
		else if(m_currentElement->m_isCover == false && m_Mode == M_TAP)
		{
			m_currentElement->m_Mode = M_TAP;
		}
		break;
	case 2:
		for ( auto *iter : MyClient.client->getTuioCursors() )
		{
			switch ( iter->getCursorID() )
			{
			case 0:
				cursor1 = iter;
				break;
			case 1:
				cursor2 = iter;
				break;
				break;
			default:
				break;
			}
		}
		if (cursor1 == nullptr || cursor2 == nullptr)
		{
			return;
		}
		if(getCurrentImage(cursor1) ==nullptr && getCurrentImage(cursor2)==nullptr)
			break;
		if(getCurrentImage(cursor1)==getCurrentImage(cursor2))
			m_currentElement = getCurrentImage(cursor1);
		else if(getCurrentImage(cursor1)!= nullptr && getCurrentImage(cursor2)==nullptr)
			m_currentElement = getCurrentImage(cursor1);
		else if(getCurrentImage(cursor1)== nullptr && getCurrentImage(cursor2)!=nullptr)
			m_currentElement = getCurrentImage(cursor2);
		else
			break;

		if(m_currentElement->m_isCover == true)
			return;
		m_currentElement->m_Distance =sqrt(pow(cursor1->getX()-cursor2->getX(),2)+pow(cursor1->getY()-cursor2->getY(),2));
		m_backOriginX = (cursor1->getX()-cursor2->getX())/2;
		m_backOriginY =  (cursor1->getY()-cursor2->getY())/2;
		m_currentAngle = 180.0 * atan( ( cursor1->getY() - cursor2->getY() ) / ( cursor1->getX() - cursor2->getX() )) * PI;
		m_Mode = M_SCALE;
		break;
	case 3:
		for ( auto *iter : MyClient.client->getTuioCursors() )
		{
			switch ( iter->getCursorID() )
			{
			case 0:
				cursor1 = iter;
				break;
			case 1:
				cursor2 = iter;
				break;
			case 2:
				cursor3 = iter;
				break;
			default:
				break;
			}
		}
		if (cursor1 == nullptr || cursor2 == nullptr|| cursor3 == nullptr)
		{
			return;
		}
		m_Mode = M_ZOOM;
		m_currentElement = getZoomingImage(cursor1,cursor2,cursor3);
		break;
	case 4:
			for ( auto *iter : MyClient.client->getTuioCursors() )
			{
				switch ( iter->getCursorID() )
				{
				case 0:
					cursor1 = iter;
					break;
				case 1:
					cursor2 = iter;
					break;
				case 2:
					cursor3 = iter;
					break;
				case 3:
					cursor4 = iter;
					break;
				default:
					break;
				}
			}
			if (cursor1 == nullptr || cursor2 == nullptr|| cursor3 == nullptr|| cursor4 == nullptr)
			{
				return;
			}
			m_Mode = M_NAVIGATION;
			m_backOriginX = WINDOW_WIDTH*(cursor1->getX()+cursor2->getX() + cursor3->getX()+cursor4->getX())/4;
			m_backOriginY = WINDOW_HEIGHT*(cursor1->getY()+cursor2->getY() + cursor3->getY()+cursor4->getY())/4;
		break;
	default:
		break;
	}



	

	m_elapsedTime = currentTime;
}

void ImageExample::touchMoved( ofTouchEventArgs & touch )
{
	TUIO::TuioCursor* cursor1 = nullptr;
	TUIO::TuioCursor* cursor2 = nullptr;
	TUIO::TuioCursor* cursor3 = nullptr;
	TUIO::TuioCursor* cursor4 = nullptr;

	if(m_Mode == M_TAP)
	{
		for ( auto *iter : MyClient.client->getTuioCursors() )
		{
			if (iter->getCursorID() == 0)
			{
				cursor1 = iter;
			}
		}

		if (cursor1 == nullptr)
		{
			return;
		}
	}
	if(m_Mode == M_SCALE)
	{
		for ( auto *iter : MyClient.client->getTuioCursors() )
		{
			switch ( iter->getCursorID() )
			{
			case 0:
				cursor1 = iter;
				break;
			case 1:
				cursor2 = iter;
				break;
			}
		}
		if(cursor1 == nullptr || cursor2 == nullptr)
			return;
	}
	if(m_Mode == M_NAVIGATION)
	{
		for ( auto *iter : MyClient.client->getTuioCursors() )
		{
			switch ( iter->getCursorID() )
			{
			case 0:
				cursor1 = iter;
				break;
			case 1:
				cursor2 = iter;
				break;
			case 2:
				cursor3 = iter;
				break;
			case 3:
				cursor4 = iter;
				break;
			default:
				break;
			}
		}
	}
	if(m_Mode == M_ZOOM)
	{
		for ( auto *iter : MyClient.client->getTuioCursors() )
		{
			switch ( iter->getCursorID() )
			{
			case 0:
				cursor1 = iter;
				break;
			case 1:
				cursor2 = iter;
				break;
			case 2:
				cursor3 = iter;
				break;
			default:
				break;
			}
		}
	}

	//탭한 상태의 이미지라면
	if(m_Mode == M_TAP && m_currentElement != nullptr && m_currentElement->m_isCover ==false)
	{
		m_currentElement->m_ImgPositionX = cursor1->getX() * WINDOW_WIDTH;
		m_currentElement->m_ImgPositionY =cursor1->getY() * WINDOW_HEIGHT;
	}//탭한 상태의 앨범이라면 전체를 이동한다.
	else if(m_Mode == M_TAP && m_currentElement != nullptr && m_currentElement->m_isCover==true)
	{
		float movedX = cursor1->getX() * WINDOW_WIDTH - m_currentElement->m_ImgPositionX;
		float movedY = cursor1->getY() * WINDOW_HEIGHT - m_currentElement->m_ImgPositionY;

		m_currentElement->m_ImgPositionX = cursor1->getX() * WINDOW_WIDTH;
		m_currentElement->m_ImgPositionY =cursor1->getY() * WINDOW_HEIGHT;
		myImage* currentImage = m_currentElement->nextImage;
		//전체 이미지도 이동
		while(currentImage != nullptr)
		{
			currentImage->m_ImgPositionX +=movedX;
			currentImage->m_ImgPositionY +=movedY;
			currentImage = currentImage->nextImage;
		}
	}
	else if(m_Mode == M_NAVIGATION)
	{
		if (cursor1 == nullptr || cursor2 == nullptr|| cursor3 == nullptr|| cursor4 == nullptr)
			return;

		float positionX = (cursor1->getX()+cursor2->getX() + cursor3->getX()+cursor4->getX())/4;
		float positionY = (cursor1->getY()+cursor2->getY() + cursor3->getY()+cursor4->getY())/4;

		navigate(positionX*WINDOW_WIDTH,positionY*WINDOW_HEIGHT);
	}
	else if(m_Mode == M_SCALE)
	{
		scale(cursor1,cursor2);
		rotate(cursor1,cursor2);
	}
	else if(m_Mode == M_ZOOM)
	{
		if (cursor1 == nullptr || cursor2 == nullptr|| cursor3 == nullptr)
			return;
		if(m_currentElement ==nullptr)
			return;
		zoomAlbum(m_currentElement,cursor1);
	}
	else
	{
		return;
	}
}

void ImageExample::touchUp( ofTouchEventArgs & touch )
{
	m_Mode = M_OUT;
	if(m_currentElement != nullptr)
	{
		m_currentElement->m_Mode = M_OUT;
		m_currentElement = nullptr;
	}

}

myImage* ImageExample::getCurrentImage( TUIO::TuioCursor* cursor )
{
	myImage* currentImage = m_Album[0];
	
	while(currentImage!=nullptr)
	{
		if(abs(cursor->getX()*WINDOW_WIDTH-currentImage->m_ImgPositionX) < currentImage->m_ImgWidth
			&&abs(cursor->getY()*WINDOW_HEIGHT-currentImage->m_ImgPositionY) < currentImage->m_ImgWidth)
		{
			return currentImage;
		}
		else
		{
			currentImage = currentImage->nextImage;
		}
	}

	return nullptr;
}

void ImageExample::showImages( myImage* album )
{
	myImage* currentImage = album->nextImage;
	while(currentImage != nullptr)
	{
		currentImage->m_isVisible = true;
		currentImage = currentImage->nextImage;
	}
}

void ImageExample::hideImages( myImage* album )
{
	myImage* currentImage = album->nextImage;
	while(currentImage != nullptr)
	{
		currentImage->m_isVisible = false;
		currentImage = currentImage->nextImage;

	}
}

void ImageExample::moveAlbum( ofTouchEventArgs & touch,myImage* album )
{

}

void ImageExample::moveImage( ofTouchEventArgs & touch, myImage* image )
{

}

void ImageExample::navigate(float positionX, float positionY)
{
	float movedX = positionX - m_backOriginX;
	float movedY = positionY - m_backOriginY;

	m_Album[0]->m_ImgPositionX +=movedX;
	m_Album[0]->m_ImgPositionY +=movedY;
	myImage* currentImage = m_Album[0]->nextImage;
	//전체 이미지도 이동
	while(currentImage != nullptr)
	{
		currentImage->m_ImgPositionX +=movedX;
		currentImage->m_ImgPositionY +=movedY;
		currentImage = currentImage->nextImage;
	}
	m_backOriginX = positionX;
	m_backOriginY = positionY;
	
}

void ImageExample::scale( TUIO::TuioCursor* cursor1 ,TUIO::TuioCursor* cursor2 )
{
	float movedDistance = sqrt(pow(abs(cursor1->getX()-cursor2->getX()),2)+pow(abs(cursor1->getY()-cursor2->getY()),2));
	m_currentElement->m_ImgWidth *= movedDistance/m_currentElement->m_Distance;
	m_currentElement->m_ImgHeight *= movedDistance/m_currentElement->m_Distance;
	m_currentElement->m_Distance = movedDistance;
}

void ImageExample::rotate(TUIO::TuioCursor* cursor1 ,TUIO::TuioCursor* cursor2 )
{
	float movedRotate = PI*180.0*atan(( cursor1->getY() - cursor2->getY() ) / ( cursor1->getX() - cursor2->getX() ));
	printf("%f ROTATE",movedRotate);
	m_currentElement->m_ImgRotateAngle +=(movedRotate-m_currentAngle);
	m_currentAngle +=(movedRotate-m_currentAngle);
	printf("======%f ROTATE",m_currentElement->m_ImgRotateAngle);

}

void ImageExample::zoomAlbum( myImage* album, TUIO::TuioCursor* cursor1 )
{
	float movedDistance = sqrt(pow((cursor1->getX()-m_backOriginX)*WINDOW_WIDTH,2)+pow((cursor1->getY()-m_backOriginY)*WINDOW_HEIGHT,2));
	m_currentElement->m_Distance *= movedDistance/m_distance;

	//위치 다 고쳐야 됨..소름..
	myImage* curretImage = album->nextImage;
	while(curretImage != nullptr)
	{
		curretImage->m_ImgPositionX += (curretImage->m_ImgPositionX - album->m_ImgPositionX)*(movedDistance-m_distance)/m_distance;
		curretImage->m_ImgPositionY += (curretImage->m_ImgPositionY - album->m_ImgPositionY)*(movedDistance-m_distance)/m_distance;
		curretImage = curretImage->nextImage;
	}
	m_distance = movedDistance;

}

myImage* ImageExample::getZoomingImage( TUIO::TuioCursor* cursor1,TUIO::TuioCursor* cursor2,TUIO::TuioCursor* cursor3 )
{
	float midX = (cursor1->getX()+cursor2->getX()+cursor3->getX())/3;
	float midY =(cursor1->getY()+cursor2->getY()+cursor3->getY())/3;

	myImage* currentImage = m_Album[0];
	//앨범일 경우만 본다
	if(abs(midX*WINDOW_WIDTH-currentImage->m_ImgPositionX) < currentImage->m_ImgWidth
		&&abs(midY*WINDOW_HEIGHT-currentImage->m_ImgPositionY) < currentImage->m_ImgWidth)
	{
		m_backOriginX = midX;
		m_backOriginY = midY;
		m_distance = sqrt(pow((cursor1->getX()-midX)*WINDOW_WIDTH,2)+pow((cursor1->getY()-midY)*WINDOW_HEIGHT,2));
		return currentImage;
	}
	else
	{
		return nullptr;
	}
}
