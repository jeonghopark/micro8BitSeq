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
    
    tempoLineDown.length = 400;
    tempoLineDown.onOffRectPos.x = -tempoLineDown.length/2;
    tempoLineDown.sizeRectPos.x = tempoLineDown.length/2;
    tempoLineDown.bOnOffBeingClick = true;

    tempoLineUp.length = 400;
    tempoLineUp.onOffRectPos.x = -tempoLineUp.length/2;
    tempoLineUp.sizeRectPos.x = tempoLineUp.length/2;
    tempoLineUp.bOnOffBeingClick = true;

    fileNameDown = "bell_sample_04.wav";
    fileNameUp = "A-HiHat2ClosedB.aif";
    highVolume = 0.45;
    
    nElementLine = 8;
    for (int i = 0; i<nElementLine; i++)
    {
        spaceLineDown = tempoLineDown.length / 10;
        elementLinesDown[i].position = ofVec2f(spaceLineDown + spaceLineDown/2 + spaceLineDown*i, tempoLineDown.onOffRectPos.y);
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
        
        spaceLineUp = tempoLineUp.length / 10;
        elementLinesUp[i].position = ofVec2f(spaceLineUp + spaceLineUp/2 + spaceLineUp*i, tempoLineUp.onOffRectPos.y);
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
    
    speedUp = 15;
    speedDown = 15;
}

//--------------------------------------------------------------
void myApp::update()
{
    ofSoundUpdate();
    
    tempoLineDown.onOffRectPos.x = -tempoLineDown.length/2;
    tempoLineDown.sizeRectPos.x = tempoLineDown.length/2;

    tempoLineUp.onOffRectPos.x = -tempoLineUp.length/2;
    tempoLineUp.sizeRectPos.x = tempoLineUp.length/2;
    
    speedDown = int(tempoLineDown.length/40);
    speedUp = int(tempoLineUp.length/40);
    
    
    for (int i = 0; i<nElementLine; i++)
    {
        spaceLineDown = tempoLineDown.length / 10;
        elementLinesDown[i].position = ofVec2f(tempoLineDown.onOffRectPos.x + spaceLineDown + spaceLineDown/2 + spaceLineDown*i, tempoLineDown.onOffRectPos.y);
        elementLinesDown[i].sizeRect = ofVec2f(elementLinesDown[i].position.x, elementLinesDown[i].sizeRect.y);
        elementLinesDown[i].onOffRect = elementLinesDown[i].sizeRect * ofVec2f(1,0) + ofVec2f(0,5);
        
        if (ofGetFrameNum()%(speedDown*8)==(speedDown*i))
        {
            elementLinesDown[i].onOffTrigger = true;
            elementLinesDown[i].samplePlay.setSpeed(ofMap(elementLinesDown[i].sizeRect.y, 0, ofGetHeight()/2, 3.0, 0) * ofRandom(0.75,1.25));
            
            if ((elementLinesDown[i].soundTrigger)&&tempoLineDown.bOnOffBeingClick)
                elementLinesDown[i].samplePlay.play();
        }
        else
        {
            elementLinesDown[i].onOffTrigger = false;
        }
    }
    
    for (int i = 0; i<nElementLine; i++)
    {
        spaceLineUp = tempoLineUp.length / 10;
        elementLinesUp[i].position = ofVec2f(tempoLineUp.onOffRectPos.x + spaceLineUp + spaceLineUp/2 + spaceLineUp*i, tempoLineUp.onOffRectPos.y);
        elementLinesUp[i].sizeRect = ofVec2f(elementLinesUp[i].position.x, elementLinesUp[i].sizeRect.y);
        elementLinesUp[i].onOffRect = elementLinesUp[i].sizeRect * ofVec2f(1,0) + ofVec2f(0,-5);
        
        if ((ofGetFrameNum()+30)%(speedUp*8)==(speedUp*i))
        {
            elementLinesUp[i].onOffTrigger = true;
            elementLinesUp[i].samplePlay.setSpeed(ofMap(elementLinesUp[i].sizeRect.y+200, ofGetHeight()/2, 0, 3.0, 0) * ofRandom(0.75,1.25));
            
            if ((elementLinesUp[i].soundTrigger)&&tempoLineUp.bOnOffBeingClick)
                elementLinesUp[i].samplePlay.play();
        }
        else
        {
            elementLinesUp[i].onOffTrigger = false;
        }
    }
}

//--------------------------------------------------------------
void myApp::draw()
{
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2+5);
    
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
    ofTranslate(ofGetWidth()/2+tempoLineUp.position.x, ofGetHeight()/2-5);
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
        myWavWriter.open(ofToDataPath("recording.wav"), WAVFILE_WRITE);
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
        elementLinesDown[i].samplePlay.loadSound("recording.wav");
    }
    
}

//--------------------------------------------------------------
void myApp::mouseMoved(int x, int y)
{
    
    float diffTempoLineDownOnOffx = x - ofGetWidth()/2 - tempoLineDown.onOffRectPos.x;
    float diffTempoLineDownOnOffy = y - ofGetHeight()/2-5 -tempoLineDown.onOffRectPos.y;
    float diffTempoLineDownOnOff = sqrt(diffTempoLineDownOnOffx*diffTempoLineDownOnOffx + diffTempoLineDownOnOffy*diffTempoLineDownOnOffy);
    if (diffTempoLineDownOnOff < 7)
    {
        tempoLineDown.bOnOffOver = true;
    }
    else
    {
        tempoLineDown.bOnOffOver = false;
    }
    
    float diffTempoLineDownSizex = x - ofGetWidth()/2 - tempoLineDown.sizeRectPos.x;
    float diffTempoLineDownSizey = y - ofGetHeight()/2-5 - tempoLineDown.sizeRectPos.y;
    float diffTempoLineDownSize = sqrt(diffTempoLineDownSizex*diffTempoLineDownSizex + diffTempoLineDownSizey*diffTempoLineDownSizey);
    if (diffTempoLineDownSize < 7)
    {
        tempoLineDown.bSizeOver = true;
    }
    else
    {
        tempoLineDown.bSizeOver = false;
    }

    float diffTempoLineUpOnOffx = x - ofGetWidth()/2 - tempoLineUp.onOffRectPos.x;
    float diffTempoLineUpOnOffy = y - ofGetHeight()/2+5 -tempoLineUp.onOffRectPos.y;
    float diffTempoLineUpOnOff = sqrt(diffTempoLineUpOnOffx*diffTempoLineUpOnOffx + diffTempoLineUpOnOffy*diffTempoLineUpOnOffy);
    if (diffTempoLineUpOnOff < 7)
    {
        tempoLineUp.bOnOffOver = true;
    }
    else
    {
        tempoLineUp.bOnOffOver = false;
    }
    
    float diffTempoLineUpSizex = x - ofGetWidth()/2 - tempoLineUp.sizeRectPos.x;
    float diffTempoLineUpSizey = y - ofGetHeight()/2+5 - tempoLineUp.sizeRectPos.y;
    float diffTempoLineUpSize = sqrt(diffTempoLineUpSizex*diffTempoLineUpSizex + diffTempoLineUpSizey*diffTempoLineUpSizey);
    if (diffTempoLineUpSize < 7)
    {
        tempoLineUp.bSizeOver = true;
    }
    else
    {
        tempoLineUp.bSizeOver = false;
    }

    
    for (int i = 0; i < nElementLine; i++)
    {
		float diffSizex = x - ofGetWidth()/2 - elementLinesDown[i].sizeRect.x;
		float diffSizey = y - ofGetHeight()/2-5 - elementLinesDown[i].sizeRect.y;
		float distSize = sqrt(diffSizex*diffSizex + diffSizey*diffSizey);
		if (distSize < elementLinesDown[i].width)
        {
			elementLinesDown[i].bSizeOver = true;
		}
        else
        {
			elementLinesDown[i].bSizeOver = false;
		}
        
		float diffOnOffx = x - ofGetWidth()/2 - elementLinesDown[i].onOffRect.x;
		float diffOnOffy = y - ofGetHeight()/2-5 - elementLinesDown[i].onOffRect.y;
		float distOnOff = sqrt(diffOnOffx*diffOnOffx + diffOnOffy*diffOnOffy);
		if (distOnOff < elementLinesDown[i].width)
        {
			elementLinesDown[i].bOnOffOver = true;
		}
        else
        {
			elementLinesDown[i].bOnOffOver = false;
		}
	}
    
    for (int i = 0; i < nElementLine; i++)
    {
		float diffSizex = x - ofGetWidth()/2 - elementLinesUp[i].sizeRect.x;
		float diffSizey = y - ofGetHeight()/2+5 - elementLinesUp[i].sizeRect.y;
		float distSize = sqrt(diffSizex*diffSizex + diffSizey*diffSizey);
		if (distSize < elementLinesUp[i].width)
        {
			elementLinesUp[i].bSizeOver = true;
		}
        else
        {
			elementLinesUp[i].bSizeOver = false;
		}
        
		float diffOnOffx = x - ofGetWidth()/2 - elementLinesUp[i].onOffRect.x;
		float diffOnOffy = y - ofGetHeight()/2+5 - elementLinesUp[i].onOffRect.y;
		float distOnOff = sqrt(diffOnOffx*diffOnOffx + diffOnOffy*diffOnOffy);
		if (distOnOff < elementLinesUp[i].width)
        {
			elementLinesUp[i].bOnOffOver = true;
		}
        else
        {
			elementLinesUp[i].bOnOffOver = false;
		}
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
        if (x>ofGetWidth()-10)
            x = ofGetWidth()-10;
        tempoLineDown.length = (x - ofGetWidth()/2) * 2;
        tempoLineUp.length = (x - ofGetWidth()/2) * 2;
    }

    if (tempoLineUp.bSizeBeingDragged == true)
    {
//        tempoLineUp.length = (x - ofGetWidth()/2) * 2;
        tempoLineUp.position.x = x - ofGetWidth()*3/4;
    }

}

//--------------------------------------------------------------
void myApp::mousePressed(int x, int y, int button)
{
    
    float diffTempoLineDownSizex = x - ofGetWidth()/2 - tempoLineDown.sizeRectPos.x;
    float diffTempoLineDownSizey = y - ofGetHeight()/2-5 -tempoLineDown.sizeRectPos.y;
    float diffTempoLineDownSize = sqrt(diffTempoLineDownSizex*diffTempoLineDownSizex + diffTempoLineDownSizey*diffTempoLineDownSizey);
    if (diffTempoLineDownSize < 7)
    {
        tempoLineDown.bSizeBeingDragged = true;
    }
    else
    {
        tempoLineDown.bSizeBeingDragged = false;
    }
    
    float diffTempoLineDownOnOffx = x - ofGetWidth()/2 - tempoLineDown.onOffRectPos.x;
    float diffTempoLineDownOnOffy = y - ofGetHeight()/2-5 -tempoLineDown.onOffRectPos.y;
    float diffTempoLineDownOnOff = sqrt(diffTempoLineDownOnOffx*diffTempoLineDownOnOffx + diffTempoLineDownOnOffy*diffTempoLineDownOnOffy);
    if (diffTempoLineDownOnOff < 7)
    {
        tempoLineDown.bOnOffBeingClick = !tempoLineDown.bOnOffBeingClick;
    }
    
    float diffTempoLineUpSizex = x - ofGetWidth()/2 - tempoLineUp.sizeRectPos.x;
    float diffTempoLineUpSizey = y - ofGetHeight()/2+5 -tempoLineUp.sizeRectPos.y;
    float diffTempoLineUpSize = sqrt(diffTempoLineUpSizex*diffTempoLineUpSizex + diffTempoLineUpSizey*diffTempoLineUpSizey);
    if (diffTempoLineUpSize < 7)
    {
        tempoLineUp.bSizeBeingDragged = true;
    }
    else
    {
        tempoLineUp.bSizeBeingDragged = false;
    }
    
    float diffTempoLineUpOnOffx = x - ofGetWidth()/2 - tempoLineUp.onOffRectPos.x;
    float diffTempoLineUpOnOffy = y - ofGetHeight()/2+5 -tempoLineUp.onOffRectPos.y;
    float diffTempoLineUpOnOff = sqrt(diffTempoLineUpOnOffx*diffTempoLineUpOnOffx + diffTempoLineUpOnOffy*diffTempoLineUpOnOffy);
    if (diffTempoLineUpOnOff < 7)
    {
        tempoLineUp.bOnOffBeingClick = !tempoLineUp.bOnOffBeingClick;
    }
    
    for (int i = 0; i < nElementLine; i++)
    {
		float diffDownSizex = x - ofGetWidth()/2 - elementLinesDown[i].sizeRect.x;
		float diffDownSizey = y - ofGetHeight()/2-5 - elementLinesDown[i].sizeRect.y;
		float diffDownSize = sqrt(diffDownSizex*diffDownSizex + diffDownSizey*diffDownSizey);
		if (diffDownSize < elementLinesDown[i].width)
        {
			elementLinesDown[i].bSizeBeingDragged = true;
		}
        else
        {
			elementLinesDown[i].bSizeBeingDragged = false;
		}
	}
    
    for (int i = 0; i < nElementLine; i++)
    {
		float diffDownOnOffx = x - ofGetWidth()/2- elementLinesDown[i].onOffRect.x;
		float diffDownOnOffy = y - ofGetHeight()/2-5 - elementLinesDown[i].onOffRect.y;
		float diffDownOnOff = sqrt(diffDownOnOffx*diffDownOnOffx + diffDownOnOffy*diffDownOnOffy);
		if (diffDownOnOff < elementLinesDown[i].width)
        {
            if (tempoLineDown.bOnOffBeingClick)
            {
                elementLinesDown[i].bOnOffBeingClick = !elementLinesDown[i].bOnOffBeingClick;
                elementLinesDown[i].soundTrigger = !elementLinesDown[i].soundTrigger;
            }
		}
	}
    
    for (int i = 0; i < nElementLine; i++)
    {
		float diffUpSizex = x - ofGetWidth()/2 - elementLinesUp[i].sizeRect.x;
		float diffUpSizey = y - ofGetHeight()/2+5 - elementLinesUp[i].sizeRect.y;
		float diffUpSize = sqrt(diffUpSizex*diffUpSizex + diffUpSizey*diffUpSizey);
		if (diffUpSize < elementLinesUp[i].width)
        {
			elementLinesUp[i].bSizeBeingDragged = true;
		}
        else
        {
			elementLinesUp[i].bSizeBeingDragged = false;
		}
	}
    
    for (int i = 0; i < nElementLine; i++)
    {
		float diffUpOnOffx = x - ofGetWidth()/2- elementLinesUp[i].onOffRect.x;
		float diffUpOnOffy = y - ofGetHeight()/2+5 - elementLinesUp[i].onOffRect.y;
		float diffUpOnOff = sqrt(diffUpOnOffx*diffUpOnOffx + diffUpOnOffy*diffUpOnOffy);
		if (diffUpOnOff < elementLinesUp[i].width)
        {
            if (tempoLineUp.bOnOffBeingClick)
            {
                elementLinesUp[i].bOnOffBeingClick = !elementLinesUp[i].bOnOffBeingClick;
                elementLinesUp[i].soundTrigger = !elementLinesUp[i].soundTrigger;
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
		}
    }
}