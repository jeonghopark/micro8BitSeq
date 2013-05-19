#include "myApp.h"


//--------------------------------------------------------------
void myApp::setup()
{
    //    ofSetDataPathRoot("../Resources/");
    ofBackground(ofRandom(255), ofRandom(255), ofRandom(255), 255);
    ofSetWindowTitle("Micro 8Bit Sequencer");
    ofSetFrameRate(30);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofNoFill();
    ofEnableAlphaBlending();
    ofSetCircleResolution(24);
    
    
    initialBufferSize = 512;
	sampleRate = 44100;
	drawCounter = 0;
	bufferCounter = 0;
	
	buffer = new float[initialBufferSize];
	memset(buffer, 0, initialBufferSize * sizeof(float));
    
	// 0 output channels,
	// 1 input channels
	// 44100 samples per second
	// 512 samples per buffer
	// 4 num buffers (latency)
	ofSoundStreamSetup(0, 1, this, sampleRate, initialBufferSize, 4);
	ofSetFrameRate(60);
    
    myWavWriter.setFormat(1, sampleRate, 16);
	
    recordState=0;
    
    mouseButton = false;

    tempoLine.length = 400;
    tempoLine.onOffRectPos.x = -tempoLine.length/2;
    tempoLine.sizeRectPos.x = tempoLine.length/2;
    tempoLine.bOnOffBeingClick = true;
    
    fileName = "bell_sample_04.wav";
    highVolume = 0.3;
    
    nElementLine = 8;
    for (int i = 0; i<nElementLine; i++)
    {
        spaceLine = tempoLine.length / 10;
        elementLines[i].position = ofVec2f(spaceLine + spaceLine/2 + spaceLine*i, tempoLineOnOffPos.y);
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
    preMouseClick = 0;
    
    
    for (int i = 0; i<NUM; i++)
    {
        pitchLines[i] = new PitchLine();
        samplePiano[i].loadSound(fileName);
        samplePiano[i].setVolume(highVolume);
        samplePiano[i].setMultiPlay(true);
    }
    
    triggerCount = -1;
    
    
}

//--------------------------------------------------------------
void myApp::update()
{
//    ofSetWindowShape(850, 400);


    tempoLine.onOffRectPos.x = -tempoLine.length/2;
    tempoLine.sizeRectPos.x = tempoLine.length/2;
    
    speed = int(tempoLine.length/40);
    
    
    ofSoundUpdate();

    
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
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    ofPushStyle();
    
    if (tempoLine.bSizeOver)
    {
        ofFill();
    }
    else
    {
        ofNoFill();
    }
    ofRect(tempoLine.sizeRectPos, 7, 7);
    
    if (tempoLine.bOnOffOver)
    {
        ofFill();
    }
    else
    {
        ofNoFill();
    }
    ofRect(tempoLine.onOffRectPos, 7, 7);
    
    if (tempoLine.bOnOffBeingClick)
    {
        ofSetColor(ofColor::fromHsb(0,0,255,140));
    }
    else
    {
        ofSetColor(ofColor::fromHsb(0,0,255,40));
    }
    ofLine(tempoLine.onOffRectPos+ofVec2f(4,0), tempoLine.sizeRectPos-ofVec2f(4,0));
    ofPopStyle();
    
    
    ofPushStyle();
    for (int i = 0; i<nElementLine; i++)
    {
        if ((elementLines[i].soundTrigger)&&tempoLine.bOnOffBeingClick)
        {
                ofSetColor(ofColor::fromHsb(0,0,255,140));
            }
            else
            {
                ofSetColor(ofColor::fromHsb(0,0,255,40));
            }            
        ofLine(elementLines[i].onOffRect+ofVec2f(0,elementLines[i].width), elementLines[i].sizeRect+ofVec2f(0,-elementLines[i].width));
        
        if (elementLines[i].bOnOffOver)
        {
            ofFill();
        }
        else{
            ofNoFill();
        }
        ofRect(elementLines[i].onOffRect, 7, 7);
        
        if (elementLines[i].bSizeOver)
        {
            ofFill();
        }
        else
        {
            ofNoFill();
        }
        ofRect(elementLines[i].sizeRect, 7, 7);
        
        if (elementLines[i].onOffTrigger)
        {
            ofSetColor(ofColor::fromHsb(0,0,255,240));
        }
        else
        {
            ofSetColor(ofColor::fromHsb(0,0,255,0));
        }
        ofRect(elementLines[i].position, 7, 7);
        
    }
    ofPopStyle();
    
    
    
    justOneclick();
    
    
	ofSetHexColor(0xFFFFFF);
	for(int i = 0; i < initialBufferSize; i++)
    {
		ofLine(70 + i, 200, 70 + i, 200 + buffer[i] * 100.0f);
	}
    
    //	ofSetHexColor(0x333333);
    //	drawCounter++;
    //	char reportString[255];
    //	sprintf(reportString, "buffers received: %i\ndraw routines called: %i\n", bufferCounter, drawCounter);
    //	ofDrawBitmapString(reportString, 70, 308);
    
    
    
}

//--------------------------------------------------------------
void myApp::justOneclick()
{
    if ((preMouseClick-mouseclick)==-1)
    {
        mouseClickRealease = true;
    }
    else
    {
        mouseClickRealease = false;
    }
    preMouseClick = mouseclick;
}

//--------------------------------------------------------------
bool myApp::toggle(bool b)
{
    if (b)
    {
        return false;
    }
    else
    {
        return true;
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
        //        pitchLines[i] = new PitchLine();
        //        samplePiano[i].loadSound("test.wav");
        //        samplePiano[i].setVolume(highVolume);
        //        samplePiano[i].setMultiPlay(true);
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
void myApp::mouseDragged(int x, int y, int button){

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
            //			elementLines[i].sizeRect.x = x - ofGetWidth()/2;
			elementLines[i].sizeRect.y = y - ofGetHeight()/2;
		}
	}
    
    mouseDraggedPos.x = x;
    
    if (tempoLine.bSizeBeingDragged == true)
    {
        //			elementLines[i].sizeRect.x = x - ofGetWidth()/2;
//        tempoLine.sizeRectPos.x = x;
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
	if( dragInfo.files.size() > 0 ){
		draggedSound.assign( dragInfo.files.size(), ofSoundPlayer() );
		for(int k = 0; k < dragInfo.files.size(); k++){
			draggedSound[k].loadSound(dragInfo.files[k]);
            for (int i = 0; i<nElementLine; i++)
            {
                elementLines[i].samplePlay.loadSound(dragInfo.files[k]);
            }
		}
        
	}
}