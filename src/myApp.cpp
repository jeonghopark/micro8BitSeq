#include "myApp.h"


//--------------------------------------------------------------
void myApp::setup()
{
    //    ofSetDataPathRoot("../Resources/");
    backgroundColorHue = ofRandom(0,255);
    ofBackground(ofColor::fromHsb(backgroundColorHue, 100, 200));
    ofSetWindowTitle("Micro 8Bit Sequencer");
    ofSetFrameRate(60);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofEnableAlphaBlending();
    ofSetCircleResolution(24);
    
    initialBufferSize = 512;
	sampleRate = 44100;
	drawCounter = 0;
	bufferCounter = 0;
	buffer = new float[initialBufferSize];
	memset(buffer, 0, initialBufferSize * sizeof(float));
    
	ofSoundStreamSetup(0, 1, this, sampleRate, initialBufferSize, 4);
	ofSetFrameRate(64);
    
    myWavWriter.setFormat(1, sampleRate, 16);
	
    recordState=0;
    
    tempoLineDown.length = 512;
    tempoLineDown.onOffRectPos.x = -tempoLineDown.length/2 + ofGetWidth()/2;
    tempoLineDown.sizeRectPos.x = tempoLineDown.length/2 + ofGetWidth()/2;
    tempoLineDown.bOnOffBeingClick = true;
    
    tempoLineUp.length = 512;
    tempoLineUp.onOffRectPos.x = -tempoLineUp.length/2 + ofGetWidth()/2;
    tempoLineUp.sizeRectPos.x = tempoLineUp.length/2 + ofGetWidth()/2;
    tempoLineUp.bOnOffBeingClick = true;
    
    tempoLineUp.position.x = tempoLineUp.sizeRectPos.x-tempoLineDown.sizeRectPos.x;
    tempoLineUp.delayPos.x = tempoLineUp.length/2 + ofGetWidth()/2 - tempoLineUp.length/(10*2);
    
    
    dir.listDir("sounds/samples/");
	dir.sort();
	if( dir.size() ){
		soundsList.assign(dir.size(), ofSoundPlayer());
	}
	for(int i = 0; i < (int)dir.size(); i++){
		soundsList[i].loadSound(dir.getPath(i));
	}
	currentSound = 0;
    
    
    string fileNameDown = "sounds/samples/" + dir.getName(round(ofRandom(0,dir.size())));
    string fileNameUp = "sounds/samples/" + dir.getName(round(ofRandom(0,dir.size())));
    fileNameDown = "sounds/samples/tap_01.wav";
    fileNameUp = "sounds/samples/tap_02.wav";
    highVolume = 0.45;
    
    nElementLine = 8;
    for (int i = 0; i<nElementLine; i++)
    {
        spacingLineDown = tempoLineDown.length / 10;
        elementLinesDown[i].position = ofVec2f(spacingLineDown + spacingLineDown/2 + spacingLineDown*i, tempoLineDown.onOffRectPos.y);
        elementLinesDown[i].sizeRect = ofVec2f(elementLinesDown[i].position.x, elementLinesDown[i].position.y+ofRandom(20,ofGetHeight()*2/5));
        elementLinesDown[i].onOffRect = elementLinesDown[i].sizeRect * ofVec2f(1,-1) + ofVec2f(0,ofGetHeight());
		elementLinesDown[i].bSizeOver = false;
        elementLinesDown[i].bOnOffOver = false;
		elementLinesDown[i].bSizeBeingDragged = false;
		elementLinesDown[i].bOnOffBeingClick = false;
		elementLinesDown[i].soundTrigger = true;
		elementLinesDown[i].width = 4;
        elementLinesDown[i].samplePlay.loadSound(fileNameDown);
        elementLinesDown[i].samplePlay.setVolume(highVolume);
        elementLinesDown[i].samplePlay.setMultiPlay(true);
        elementLinesDown[i].triggerColor = 120;
        
        spacingLineUp = tempoLineUp.length / 10;
        elementLinesUp[i].position = ofVec2f(spacingLineUp + spacingLineUp/2 + spacingLineUp*i, tempoLineUp.onOffRectPos.y);
        elementLinesUp[i].sizeRect = ofVec2f(elementLinesUp[i].position.x, elementLinesUp[i].position.y-ofRandom(20,ofGetHeight()*2/5));
        elementLinesUp[i].onOffRect = elementLinesUp[i].sizeRect * ofVec2f(1,-1) + ofVec2f(0,ofGetHeight());
		elementLinesUp[i].bSizeOver = false;
        elementLinesUp[i].bOnOffOver = false;
		elementLinesUp[i].bSizeBeingDragged = false;
		elementLinesUp[i].bOnOffBeingClick = false;
		elementLinesUp[i].soundTrigger = true;
		elementLinesUp[i].width = 4;
        elementLinesUp[i].samplePlay.loadSound(fileNameUp);
        elementLinesUp[i].samplePlay.setVolume(highVolume);
        elementLinesUp[i].samplePlay.setMultiPlay(true);
        elementLinesUp[i].triggerColor = 120;
    }
    
    
    triggerCounterUp = 0;
    triggerCounterDown = 0;
    
    millisUp = ofGetElapsedTimeMillis();
    millisDown = ofGetElapsedTimeMillis();
    bangUp = false;
    bangDown = false;
    
}

//--------------------------------------------------------------
void myApp::update()
{
    ofSoundUpdate();
    
    tempoLineDown.sizeRectPos.x = tempoLineDown.sizeRectPos.x;
    tempoLineDown.onOffRectPos.x = ofGetWidth() - tempoLineDown.sizeRectPos.x;
    tempoLineDown.length = tempoLineDown.sizeRectPos.x - tempoLineDown.onOffRectPos.x;
    
    float speed = ofMap(tempoLineDown.length, 40, ofGetWidth(), 14, 70);
    float timer = (ofGetElapsedTimeMillis()-millisDown)*1.9;
    
    int delayTempoLineUp = (int)(tempoLineUp.position.x)/12;
    
    
    if (timer>=speed)
    {
        triggerCounterDown++;
        int _index = triggerCounterDown%32;
        for (int i = 0; i<nElementLine; i++)
        {
            
            if (_index==((i*4)))
            {
                if ((elementLinesDown[i].soundTrigger)&&tempoLineDown.bOnOffBeingClick)
                {
                    elementLinesDown[i].onOffTrigger = true;
                    elementLinesDown[i].samplePlay.play();
                    elementLinesDown[i].samplePlay.setVolume(ofRandom(0.125,0.75));
                    elementLinesDown[i].samplePlay.setSpeed(ofMap(elementLinesDown[i].sizeRect.y, 0, ofGetHeight()/2, 3.0, 0) * ofRandom(0.75,1.25));
                }
            }
            else
            {
                elementLinesDown[i].onOffTrigger = false;
            }
        
            if (_index==((i*4)+delayTempoLineUp))
            {
                if ((elementLinesUp[i].soundTrigger)&&tempoLineUp.bOnOffBeingClick)
                {
                    elementLinesUp[i].onOffTrigger = true;
                    elementLinesUp[i].samplePlay.play();
                    elementLinesUp[i].samplePlay.setVolume(ofRandom(0.125,0.75));
                    elementLinesUp[i].samplePlay.setSpeed(ofMap(elementLinesUp[i].sizeRect.y+200, ofGetHeight()/2, 0, 3.0, 0) * ofRandom(0.75,1.25));                }
            }
            else
            {
                elementLinesUp[i].onOffTrigger = false;
            }
        }

        millisDown = ofGetElapsedTimeMillis();
        
    }
    
    
    spacingLineDown = tempoLineDown.length / 10;
    spacingLineUp = tempoLineDown.length / 10;
    
    tempoLineUp.sizeRectPos.x = tempoLineDown.sizeRectPos.x + spacingLineUp * delayTempoLineUp * 0.25;
    tempoLineUp.onOffRectPos.x = tempoLineDown.onOffRectPos.x + spacingLineUp * delayTempoLineUp * 0.25;
    tempoLineUp.length = tempoLineUp.sizeRectPos.x - tempoLineUp.onOffRectPos.x;
    
    
    for (int i = 0; i<nElementLine; i++)
    {
        elementLinesDown[i].position = ofVec2f(tempoLineDown.onOffRectPos.x + spacingLineDown + spacingLineDown/2 + spacingLineDown*i, tempoLineDown.onOffRectPos.y);
        elementLinesDown[i].sizeRect = ofVec2f(elementLinesDown[i].position.x, elementLinesDown[i].sizeRect.y);
        elementLinesDown[i].onOffRect = elementLinesDown[i].sizeRect * ofVec2f(1,0) + ofVec2f(0,5);
        elementLinesUp[i].position.x = elementLinesDown[i].position.x + spacingLineUp * delayTempoLineUp * 0.25;
        elementLinesUp[i].sizeRect = ofVec2f(elementLinesUp[i].position.x, elementLinesUp[i].sizeRect.y);
        elementLinesUp[i].onOffRect = elementLinesUp[i].sizeRect * ofVec2f(1,0) + ofVec2f(0,-5);
    }
    
}



//--------------------------------------------------------------
void myApp::draw()
{
    
    ofPushMatrix();
    ofTranslate(0, ofGetHeight()/2+5);
    
    ofPushStyle();
    ofSetColor(ofColor::fromHsb(0,0,255,140));
    
    if (tempoLineDown.bOnOffBeingClick)
    {
        ofNoFill();
        ofSetColor(ofColor::fromHsb(0,0,255,140));
        if (tempoLineDown.bSizeOver)
        {
            ofFill();
        }
        else
        {
            ofNoFill();
        }
    }
    else
    {
        ofSetColor(ofColor::fromHsb(0,0,255,40));
        if (tempoLineDown.bSizeOver)
        {
            ofFill();
        }
        else
        {
            ofNoFill();
        }
    }
    ofRect(tempoLineDown.sizeRectPos, 7, 7);
    
    if (tempoLineDown.bOnOffBeingClick)
    {
        ofNoFill();
        ofSetColor(ofColor::fromHsb(0,0,255,140));
        if (tempoLineDown.bOnOffOver)
        {
            ofFill();
        }
        else
        {
            ofNoFill();
        }
    }
    else
    {
        ofFill();
        ofSetColor(ofColor::fromHsb(0,0,255,40));
    }
    ofRect(tempoLineDown.onOffRectPos, 7, 7);
    ofLine(tempoLineDown.onOffRectPos+ofVec2f(4,0), tempoLineDown.sizeRectPos-ofVec2f(4,0));
    ofPopStyle();
    
    ofPushStyle();
    for (int i = 0; i<nElementLine; i++)
    {
        
        if (elementLinesDown[i].onOffTrigger)
        {
            if (!elementLinesDown[i].bOnOffBeingClick)
            {
                elementLinesDown[i].triggerColor = 100;
            }
            else
            {
                elementLinesDown[i].triggerColor = 0;
            }
        }
        else
        {
            elementLinesDown[i].triggerColor = 0;
        }
        
        
        if (elementLinesDown[i].soundTrigger&&tempoLineDown.bOnOffBeingClick)
        {
            ofFill();
            ofSetColor(ofColor::fromHsb(0,0,230+elementLinesDown[i].triggerColor,155+elementLinesDown[i].triggerColor));
        }
        else
        {
            ofNoFill();
            ofSetColor(ofColor::fromHsb(0,0,230+elementLinesDown[i].triggerColor,50+elementLinesDown[i].triggerColor));
        }
        ofLine(elementLinesDown[i].onOffRect+ofVec2f(0,elementLinesDown[i].width), elementLinesDown[i].sizeRect+ofVec2f(0,-elementLinesDown[i].width));
        
        if (!elementLinesDown[i].bOnOffBeingClick)
        {
            ofNoFill();
            if (elementLinesDown[i].bOnOffOver)
            {
                ofFill();
            }
            else
            {
                ofNoFill();
            }
        }
        else
        {
            ofFill();
            if (elementLinesDown[i].bOnOffOver)
            {
                ofSetColor(ofColor::fromHsb(0,0,255,100));
            }
            else
            {
                ofSetColor(ofColor::fromHsb(0,0,255,40));
            }
        }
        ofRect(elementLinesDown[i].onOffRect, 7, 7);
        
        
        if (!elementLinesDown[i].bOnOffBeingClick)
        {
            ofNoFill();
            if (elementLinesDown[i].bSizeOver)
            {
                ofFill();
            }
            else
            {
                ofNoFill();
            }
        }
        else
        {
            ofNoFill();
            if (elementLinesDown[i].bSizeOver)
            {
                ofSetColor(ofColor::fromHsb(0,0,255,120));
            }
            else
            {
                ofSetColor(ofColor::fromHsb(0,0,255,40));
            }
        }
        ofRect(elementLinesDown[i].sizeRect, 7, 7);
        
        //        ofRect(elementLinesDown[i].position, 7, 7);
        
    }
    ofPopStyle();
    
    ofPopMatrix();
    
    
    ofPushMatrix();
    ofTranslate(0, ofGetHeight()/2-5);
    ofPushStyle();
    ofSetColor(ofColor::fromHsb(0,0,255,140));
    
    if (tempoLineUp.bOnOffBeingClick)
    {
        ofNoFill();
        ofSetColor(ofColor::fromHsb(0,0,255,140));
        if (tempoLineUp.bSizeOver)
        {
            ofFill();
        }
        else
        {
            ofNoFill();
        }
    }
    else
    {
        ofSetColor(ofColor::fromHsb(0,0,255,40));
        if (tempoLineUp.bSizeOver)
        {
            ofFill();
        }
        else
        {
            ofNoFill();
        }
    }
    ofRect(tempoLineUp.sizeRectPos, 7, 7);
    
    if (tempoLineUp.bOnOffBeingClick)
    {
        ofNoFill();
        ofSetColor(ofColor::fromHsb(0,0,255,140));
        if (tempoLineUp.bOnOffOver)
        {
            ofFill();
        }
        else
        {
            ofNoFill();
        }
    }
    else
    {
        ofFill();
        ofSetColor(ofColor::fromHsb(0,0,255,40));
    }
    ofRect(tempoLineUp.onOffRectPos, 7, 7);
    ofLine(tempoLineUp.onOffRectPos+ofVec2f(4,0), tempoLineUp.sizeRectPos-ofVec2f(4,0));
    ofPopStyle();
    
    ofPushStyle();
    for (int i = 0; i<nElementLine; i++)
    {
        
        if (elementLinesUp[i].onOffTrigger)
        {
            if (!elementLinesUp[i].bOnOffBeingClick)
            {
                elementLinesUp[i].triggerColor = 100;
            }
            else
            {
                elementLinesUp[i].triggerColor = 0;
            }
        }
        else
        {
            elementLinesUp[i].triggerColor = 0;
        }
        
        
        if (elementLinesUp[i].soundTrigger&&tempoLineUp.bOnOffBeingClick)
        {
            ofFill();
            ofSetColor(ofColor::fromHsb(0,0,230+elementLinesUp[i].triggerColor,155+elementLinesUp[i].triggerColor));
        }
        else
        {
            ofNoFill();
            ofSetColor(ofColor::fromHsb(0,0,230+elementLinesUp[i].triggerColor,50+elementLinesUp[i].triggerColor));
        }
        ofLine(elementLinesUp[i].onOffRect+ofVec2f(0,-elementLinesUp[i].width), elementLinesUp[i].sizeRect+ofVec2f(0,elementLinesUp[i].width));
        
        if (!elementLinesUp[i].bOnOffBeingClick)
        {
            ofNoFill();
            if (elementLinesUp[i].bOnOffOver)
            {
                ofFill();
            }
            else
            {
                ofNoFill();
            }
        }
        else
        {
            ofFill();
            if (elementLinesUp[i].bOnOffOver)
            {
                ofSetColor(ofColor::fromHsb(0,0,255,100));
            }
            else
            {
                ofSetColor(ofColor::fromHsb(0,0,255,40));
            }
        }
        ofRect(elementLinesUp[i].onOffRect, 7, 7);
        
        
        if (!elementLinesUp[i].bOnOffBeingClick)
        {
            ofNoFill();
            if (elementLinesUp[i].bSizeOver)
            {
                ofFill();
            }
            else
            {
                ofNoFill();
            }
        }
        else
        {
            ofNoFill();
            if (elementLinesUp[i].bSizeOver)
            {
                ofSetColor(ofColor::fromHsb(0,0,255,120));
            }
            else
            {
                ofSetColor(ofColor::fromHsb(0,0,255,40));
            }
        }
        ofRect(elementLinesUp[i].sizeRect, 7, 7);
        
        //        ofRect(elementLinesUp[i].position, 7, 7);
        
    }
    ofPopStyle();
    
    
    ofPopMatrix();
    
    
    ofSetColor(ofColor::fromHsb(backgroundColorHue, 100, 220));
	for(int i = 0; i < initialBufferSize-1; i++)
    {
        ofLine(i+(ofGetWidth()/2-initialBufferSize/2), ofGetHeight(), i+1+(ofGetWidth()/2-initialBufferSize/2), ofGetHeight() + buffer[i+1] * 100.0f);
	}
    
    
}


//--------------------------------------------------------------
void myApp::audioIn(float * input, int bufferSize, int nChannels){
    
	if (initialBufferSize != bufferSize)
    {
		ofLog(OF_LOG_ERROR, "your buffer size was set to %i - but the stream needs a buffer size of %i", initialBufferSize, bufferSize);
		return;
	}
	
	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++)
    {
		buffer[i] = input[i];
	}
	bufferCounter++;
    
    if (recordState==1)
    {
        recordState=3;
        myWavWriter.open(ofToDataPath("sounds/recording.wav"), WAVFILE_WRITE);
    }
    
	if (recordState==3)
    {
		myWavWriter.write(input, bufferSize*nChannels);
	}
    
    if (recordState==2)
    {
        myWavWriter.close();
        recordState=0;
    }
    
}


//--------------------------------------------------------------
void myApp::keyPressed(int key)
{
    if (recordState==0)
    {
        recordState=1;
    }
}

//--------------------------------------------------------------
void myApp::keyReleased(int key)
{
    if (recordState==3)
    {
        recordState=2;
    }
    
    for (int i = 0; i<nElementLine; i++)
    {
        elementLinesDown[i].samplePlay.loadSound("sounds/recording.wav");
    }
    
}


bool myApp::inOutCal(float x, float y, ofVec2f xyN, int distSize)
{
    float diffx = x - xyN.x;
    float diffy = y - xyN.y;
    float diff = sqrt(diffx*diffx + diffy*diffy);
    if (diff < distSize)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool myApp::onOffOut(float x, float y, ofVec2f xyN, int distSize, bool _b)
{
    float diffx = x - xyN.x;
    float diffy = y - xyN.y;
    float diff = sqrt(diffx*diffx + diffy*diffy);
    if (diff < distSize)
    {
        return _b = !_b;
    }
    else
    {
        return _b = _b;
    }
}



//--------------------------------------------------------------
void myApp::mouseMoved(int x, int y)
{
    
    tempoLineDown.bOnOffOver = inOutCal(x, y - ofGetHeight()/2-5, tempoLineDown.onOffRectPos, 7);
    tempoLineDown.bSizeOver = inOutCal(x, y - ofGetHeight()/2-5, tempoLineDown.sizeRectPos, 7);
    tempoLineUp.bOnOffOver = inOutCal(x, y - ofGetHeight()/2+5, tempoLineUp.onOffRectPos, 7);
    tempoLineUp.bSizeOver = inOutCal(x, y - ofGetHeight()/2+5, tempoLineUp.sizeRectPos, 7);
    
    for (int i = 0; i < nElementLine; i++)
    {
        elementLinesDown[i].bSizeOver = inOutCal(x, y - ofGetHeight()/2-5, elementLinesDown[i].sizeRect, elementLinesDown[i].width);
        elementLinesDown[i].bOnOffOver = inOutCal(x, y - ofGetHeight()/2-5, elementLinesDown[i].onOffRect, elementLinesDown[i].width);
        elementLinesUp[i].bSizeOver = inOutCal(x, y - ofGetHeight()/2+5, elementLinesUp[i].sizeRect, elementLinesUp[i].width);
        elementLinesUp[i].bOnOffOver = inOutCal(x, y - ofGetHeight()/2+5, elementLinesUp[i].onOffRect, elementLinesUp[i].width);
	}
    
}

//--------------------------------------------------------------
void myApp::mouseDragged(int x, int y, int button)
{
    for (int i = 0; i < nElementLine; i++)
    {
		if (elementLinesDown[i].bSizeBeingDragged == true)
        {
            if (y<ofGetHeight()/2+20)
                y = ofGetHeight()/2+20;
            if (y>ofGetHeight()-10)
                y = ofGetHeight()-10;
			elementLinesDown[i].sizeRect.y = y - ofGetHeight()/2-5;
		}
	}
    
    for (int i = 0; i < nElementLine; i++)
    {
		if (elementLinesUp[i].bSizeBeingDragged == true)
        {
            if (y>ofGetHeight()/2-20)
                y = ofGetHeight()/2-20;
            if (y<10)
                y = 10;
			elementLinesUp[i].sizeRect.y = y - ofGetHeight()/2+5;
		}
	}
    
    if (tempoLineDown.bSizeBeingDragged == true)
    {
        if (x<ofGetWidth()/2+50)
            x = ofGetWidth()/2+50;
        if (x>ofGetWidth()-80)
            x = ofGetWidth()-80;
        tempoLineDown.sizeRectPos.x = x;
    }
    
    if (tempoLineUp.bSizeBeingDragged == true)
    {
        tempoLineUp.position.x = x - (tempoLineDown.length+ofGetWidth())/2;
        if (tempoLineUp.position.x>49) tempoLineUp.position.x = 49;
        if (tempoLineUp.position.x<-49) tempoLineUp.position.x = -49;
        
    }
    
}


//--------------------------------------------------------------
void myApp::mousePressed(int x, int y, int button)
{
    tempoLineDown.bOnOffBeingClick = onOffOut(x, y - ofGetHeight()/2-5, tempoLineDown.onOffRectPos, 7, tempoLineDown.bOnOffBeingClick);
    tempoLineDown.bSizeBeingDragged = inOutCal(x, y - ofGetHeight()/2-5, tempoLineDown.sizeRectPos, 7);
    tempoLineUp.bOnOffBeingClick = onOffOut(x, y - ofGetHeight()/2+5, tempoLineUp.onOffRectPos, 7, tempoLineUp.bOnOffBeingClick);
    tempoLineUp.bSizeBeingDragged = inOutCal(x, y - ofGetHeight()/2+5, tempoLineUp.sizeRectPos, 7);
    
    for (int i = 0; i < nElementLine; i++)
    {
        elementLinesDown[i].bSizeBeingDragged = inOutCal(x, y - ofGetHeight()/2-5, elementLinesDown[i].sizeRect, elementLinesDown[i].width);
        elementLinesUp[i].bSizeBeingDragged = inOutCal(x, y - ofGetHeight()/2+5, elementLinesUp[i].sizeRect, elementLinesUp[i].width);
        
        if (tempoLineDown.bOnOffBeingClick)
        {
            elementLinesDown[i].bOnOffBeingClick = onOffOut(x, y - ofGetHeight()/2-5, elementLinesDown[i].onOffRect, 7, elementLinesDown[i].bOnOffBeingClick);
            elementLinesDown[i].soundTrigger = onOffOut(x, y - ofGetHeight()/2-5, elementLinesDown[i].onOffRect, 7, elementLinesDown[i].soundTrigger);
        }
        if (tempoLineUp.bOnOffBeingClick)
        {
            elementLinesUp[i].bOnOffBeingClick = onOffOut(x, y - ofGetHeight()/2+5, elementLinesUp[i].onOffRect, 7, elementLinesUp[i].bOnOffBeingClick);
            elementLinesUp[i].soundTrigger = onOffOut(x, y - ofGetHeight()/2+5, elementLinesUp[i].onOffRect, 7, elementLinesUp[i].soundTrigger);
        }
	}
    
}

//--------------------------------------------------------------
void myApp::mouseReleased(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void myApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void myApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void myApp::dragEvent(ofDragInfo dragInfo)
{
    
	if( dragInfo.files.size() > 0 )
    {
        dragPt = dragInfo.position;
        
		draggedSound.assign( dragInfo.files.size(), ofSoundPlayer() );
        
        for(int k = 0; k < dragInfo.files.size(); k++)
        {
            if (dragPt.y>ofGetHeight()/2)
            {
                draggedSound[k].loadSound(dragInfo.files[k]);
                for (int i = 0; i<nElementLine; i++)
                {
                    elementLinesDown[i].samplePlay.loadSound(dragInfo.files[k]);
                }
            }
            if (dragPt.y<ofGetHeight()/2)
            {
                draggedSound[k].loadSound(dragInfo.files[k]);
                for (int i = 0; i<nElementLine; i++)
                {
                    elementLinesUp[i].samplePlay.loadSound(dragInfo.files[k]);
                }
            }
		}
    }
}