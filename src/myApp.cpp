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
	ofSetFrameRate(60);
    
    myWavWriter.setFormat(1, sampleRate, 16);
	
    recordState=0;
    
    tempoLine.length = 400;
    tempoLine.onOffRectPos.x = -tempoLine.length/2;
    tempoLine.sizeRectPos.x = tempoLine.length/2;
    tempoLine.bOnOffBeingClick = true;
    
    fileName = "bell_sample_04.wav";
    highVolume = 0.45;
    
    nElementLine = 8;
    for (int i = 0; i<nElementLine; i++)
    {
        spaceLine = tempoLine.length / 10;
        elementLines[i].position = ofVec2f(spaceLine + spaceLine/2 + spaceLine*i, tempoLine.onOffRectPos.y);
        elementLines[i].sizeRect = ofVec2f(elementLines[i].position.x, elementLines[i].position.y+ofRandom(20,ofGetHeight()*2/5));
        elementLines[i].onOffRect = elementLines[i].sizeRect * ofVec2f(1,-1) + ofVec2f(0,ofGetHeight());
		elementLines[i].bSizeOver = false;
        elementLines[i].bOnOffOver = false;
		elementLines[i].bSizeBeingDragged = false;
		elementLines[i].bOnOffBeingClick = false;
		elementLines[i].soundTrigger = true;
		elementLines[i].width = 4;
        elementLines[i].samplePlay.loadSound(fileName);
        elementLines[i].samplePlay.setVolume(highVolume);
        elementLines[i].samplePlay.setMultiPlay(true);
    }
    
    speed = 15;
}

//--------------------------------------------------------------
void myApp::update()
{    
    ofSoundUpdate();
    
    tempoLine.onOffRectPos.x = -tempoLine.length/2;
    tempoLine.sizeRectPos.x = tempoLine.length/2;
    
    speed = int(tempoLine.length/40);
    
    
    for (int i = 0; i<nElementLine; i++)
    {
        spaceLine = tempoLine.length / 10;
        elementLines[i].position = ofVec2f(tempoLine.onOffRectPos.x + spaceLine + spaceLine/2 + spaceLine*i, tempoLine.onOffRectPos.y);
        elementLines[i].sizeRect = ofVec2f(elementLines[i].position.x, elementLines[i].sizeRect.y);
        elementLines[i].onOffRect = elementLines[i].sizeRect * ofVec2f(1,-1);
        
        if (ofGetFrameNum()%(speed*8)==(speed*i))
        {
            elementLines[i].onOffTrigger = true;
            elementLines[i].samplePlay.setSpeed(ofMap(elementLines[i].sizeRect.y, 0, ofGetHeight()/2, 3.0, 0) * ofRandom(0.75,1.25));
            
            if ((elementLines[i].soundTrigger)&&tempoLine.bOnOffBeingClick)
                elementLines[i].samplePlay.play();
        }
        else
        {
            elementLines[i].onOffTrigger = false;
        }
        
    }
    
}

//--------------------------------------------------------------
void myApp::draw()
{
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    ofPushStyle();
    ofSetColor(ofColor::fromHsb(0,0,255,140));
    
    if (tempoLine.bOnOffBeingClick)
    {
        ofNoFill();
        ofSetColor(ofColor::fromHsb(0,0,255,140));
        if (tempoLine.bSizeOver)
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
        if (tempoLine.bSizeOver)
        {
            ofFill();
        }
        else
        {
            ofNoFill();
        }
    }
    ofRect(tempoLine.sizeRectPos, 7, 7);
    
    if (tempoLine.bOnOffBeingClick)
    {
        ofNoFill();
        ofSetColor(ofColor::fromHsb(0,0,255,140));
        if (tempoLine.bOnOffOver)
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
    ofRect(tempoLine.onOffRectPos, 7, 7);
    ofLine(tempoLine.onOffRectPos+ofVec2f(4,0), tempoLine.sizeRectPos-ofVec2f(4,0));
    ofPopStyle();
    
    
    ofPushStyle();
    for (int i = 0; i<nElementLine; i++)
    {
        if (elementLines[i].soundTrigger&&tempoLine.bOnOffBeingClick)
        {
            ofFill();
            ofSetColor(ofColor::fromHsb(0,0,255,140));
        }
        else
        {
            ofNoFill();
            ofSetColor(ofColor::fromHsb(0,0,255,40));
        }
        ofLine(elementLines[i].onOffRect+ofVec2f(0,elementLines[i].width), elementLines[i].sizeRect+ofVec2f(0,-elementLines[i].width));
        
        if (!elementLines[i].bOnOffBeingClick)
        {
            ofNoFill();
            if (elementLines[i].bOnOffOver)
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
            if (elementLines[i].bOnOffOver)
            {
                ofSetColor(ofColor::fromHsb(0,0,255,100));
            }
            else
            {
                ofSetColor(ofColor::fromHsb(0,0,255,40));
            }
        }
        ofRect(elementLines[i].onOffRect, 7, 7);
        

        if (!elementLines[i].bOnOffBeingClick)
        {
            ofNoFill();
            if (elementLines[i].bSizeOver)
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
            if (elementLines[i].bSizeOver)
            {
                ofSetColor(ofColor::fromHsb(0,0,255,120));
            }
            else
            {
                ofSetColor(ofColor::fromHsb(0,0,255,40));
            }
        }
        ofRect(elementLines[i].sizeRect, 7, 7);
        
        if (elementLines[i].onOffTrigger)
        {
            if (!elementLines[i].bOnOffBeingClick)
            {
                ofSetColor(ofColor::fromHsb(0,0,255,255));
            }
            else
            {
                ofSetColor(ofColor::fromHsb(0,0,255,90));
            }
        }
        else
        {
            ofSetColor(ofColor::fromHsb(0,0,255,0));
        }
        ofRect(elementLines[i].position, 7, 7);
        
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
        myWavWriter.open(ofToDataPath("test.wav"), WAVFILE_WRITE);
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
        elementLines[i].samplePlay.loadSound("test.wav");
    }
    
}

//--------------------------------------------------------------
void myApp::mouseMoved(int x, int y)
{
    
    float diffTempoLineOnOffx = x - ofGetWidth()/2 - tempoLine.onOffRectPos.x;
    float diffTempoLineOnOffy = y - ofGetHeight()/2 -tempoLine.onOffRectPos.y;
    float diffTempoLineOnOff = sqrt(diffTempoLineOnOffx*diffTempoLineOnOffx + diffTempoLineOnOffy*diffTempoLineOnOffy);
    if (diffTempoLineOnOff < 7)
    {
        tempoLine.bOnOffOver = true;
    }
    else
    {
        tempoLine.bOnOffOver = false;
    }
    
    float diffTempoLineSizex = x - ofGetWidth()/2 - tempoLine.sizeRectPos.x;
    float diffTempoLineSizey = y - ofGetHeight()/2 - tempoLine.sizeRectPos.y;
    float distTempoLineSizeSize = sqrt(diffTempoLineSizex*diffTempoLineSizex + diffTempoLineSizey*diffTempoLineSizey);
    if (distTempoLineSizeSize < 7)
    {
        tempoLine.bSizeOver = true;
    }
    else
    {
        tempoLine.bSizeOver = false;
    }
	
    
    for (int i = 0; i < nElementLine; i++)
    {
		float diffSizex = x - ofGetWidth()/2 - elementLines[i].sizeRect.x;
		float diffSizey = y - ofGetHeight()/2 - elementLines[i].sizeRect.y;
		float distSize = sqrt(diffSizex*diffSizex + diffSizey*diffSizey);
		if (distSize < elementLines[i].width)
        {
			elementLines[i].bSizeOver = true;
		}
        else
        {
			elementLines[i].bSizeOver = false;
		}
        
		float diffOnOffx = x - ofGetWidth()/2 - elementLines[i].onOffRect.x;
		float diffOnOffy = y - ofGetHeight()/2 - elementLines[i].onOffRect.y;
		float distOnOff = sqrt(diffOnOffx*diffOnOffx + diffOnOffy*diffOnOffy);
		if (distOnOff < elementLines[i].width)
        {
			elementLines[i].bOnOffOver = true;
		}
        else
        {
			elementLines[i].bOnOffOver = false;
		}
	}
}

//--------------------------------------------------------------
void myApp::mouseDragged(int x, int y, int button)
{    
    if (x<ofGetWidth()/2+50)
        x = ofGetWidth()/2+50;
    if (x>ofGetWidth()-10)
        x = ofGetWidth()-10;
    if (y<ofGetHeight()/2+10)
        y = ofGetHeight()/2+10;
    if (y>ofGetHeight()-10)
        y = ofGetHeight()-10;
    
    
    for (int i = 0; i < nElementLine; i++)
    {
		if (elementLines[i].bSizeBeingDragged == true)
        {
			elementLines[i].sizeRect.y = y - ofGetHeight()/2;
		}
	}
    
    if (tempoLine.bSizeBeingDragged == true)
    {
        tempoLine.length = (x - ofGetWidth()/2) * 2;
    }
}

//--------------------------------------------------------------
void myApp::mousePressed(int x, int y, int button)
{
    
    float diffTempoLineSizex = x - ofGetWidth()/2 - tempoLine.sizeRectPos.x;
    float diffTempoLineSizey = y - ofGetHeight()/2 -tempoLine.sizeRectPos.y;
    float distTempoLineSizeSize = sqrt(diffTempoLineSizex*diffTempoLineSizex + diffTempoLineSizey*diffTempoLineSizey);
    if (distTempoLineSizeSize < 7)
    {
        tempoLine.bSizeBeingDragged = true;
    }
    else
    {
        tempoLine.bSizeBeingDragged = false;
    }
    
    float diffTempoLineOnOffx = x - ofGetWidth()/2 - tempoLine.onOffRectPos.x;
    float diffTempoLineOnOffy = y - ofGetHeight()/2 -tempoLine.onOffRectPos.y;
    float diffTempoLineOnOff = sqrt(diffTempoLineOnOffx*diffTempoLineOnOffx + diffTempoLineOnOffy*diffTempoLineOnOffy);
    if (diffTempoLineOnOff < 7)
    {
        tempoLine.bOnOffBeingClick = !tempoLine.bOnOffBeingClick;
    }
    
    
    
    for (int i = 0; i < nElementLine; i++)
    {
		float diffSizex = x - ofGetWidth()/2 - elementLines[i].sizeRect.x;
		float diffSizey = y - ofGetHeight()/2 - elementLines[i].sizeRect.y;
		float distSize = sqrt(diffSizex*diffSizex + diffSizey*diffSizey);
		if (distSize < elementLines[i].width)
        {
			elementLines[i].bSizeBeingDragged = true;
		}
        else
        {
			elementLines[i].bSizeBeingDragged = false;
		}
	}
    
    for (int i = 0; i < nElementLine; i++)
    {
		float diffOnOffx = x - ofGetWidth()/2- elementLines[i].onOffRect.x;
		float diffOnOffy = y - ofGetHeight()/2 - elementLines[i].onOffRect.y;
		float diffOnOff = sqrt(diffOnOffx*diffOnOffx + diffOnOffy*diffOnOffy);
		if (diffOnOff < elementLines[i].width)
        {
            if (tempoLine.bOnOffBeingClick)
            {
                elementLines[i].bOnOffBeingClick = !elementLines[i].bOnOffBeingClick;
                elementLines[i].soundTrigger = !elementLines[i].soundTrigger;
            }
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
		draggedSound.assign( dragInfo.files.size(), ofSoundPlayer() );
	
        for(int k = 0; k < dragInfo.files.size(); k++)
        {
			draggedSound[k].loadSound(dragInfo.files[k]);
            for (int i = 0; i<nElementLine; i++)
            {
                elementLines[i].samplePlay.loadSound(dragInfo.files[k]);
            }
		}
        
	}
}