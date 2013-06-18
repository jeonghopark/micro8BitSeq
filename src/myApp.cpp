#include "myApp.h"


//--------------------------------------------------------------
void myApp::setup()
{
    ofSetDataPathRoot("../Resources/");
    backgroundColorHue = ofRandom(0,255);
    ofBackground(ofColor::fromHsb(backgroundColorHue, 150, 180));
    
    ofSetWindowTitle("micro 8Bit sequencer");
    ofEnableAlphaBlending();
    ofSetCircleResolution(24);
    
    initialBufferSize = 512;
	sampleRate = 44100;
	drawCounter = 0;
	bufferCounter = 0;
	buffer = new float[initialBufferSize];
	memset(buffer, 0, initialBufferSize * sizeof(float));
    
	ofSoundStreamSetup(0, 1, this, sampleRate, initialBufferSize, 4);
	ofSetFrameRate(120);
    
    
    dir.listDir("sounds/samples/");
	dir.sort();
	if( dir.size() ){
		soundsList.assign(dir.size(), ofSoundPlayer());
	}
	for(int i = 0; i < (int)dir.size(); i++){
		soundsList[i].loadSound(dir.getPath(i));
	}
	currentSound = 0;
    
    fileNameUp = "sounds/samples/tap_02.wav";
    fileNameDown = "sounds/samples/tap_01.wav";
    highVolume = 0.75;
    
    
    triggerCounterUp = 0;
    triggerCounterDown = 0;
    
    startTime = ofGetElapsedTimeMillis();
    millisDown = ofGetElapsedTimeMillis();
    bangUp = false;
    bangDown = false;
    
    soundRecordingDownOn = true;
    
    
    fullscreen = false;
    
    for (int i=0; i<16; i++) {
        randomY[i] = ofRandom(20,ofGetHeight()*2/5);
    }
    
    tempoLineDown.length = ofGetWidth()*3/8;
    tempoLineDown.bOnOffBeingClick = true;
    tempoLineDown.bTimerReached = true;
    tempoLineDown.bDownSoundRecordClick = true;
    tempoLineDown.bChangeSampleClick = false;
    tempoLineDown.bChangeSampleOver = false;
    tempoLineDown.startTime = ofGetElapsedTimeMillis() - 1000;
    tempoLineDown.rectBlockAlphaFactor = 0;
    tempoLineDown.recordState=0;
    tempoLineDown.soundVolume = 1;
    tempoLineDown.changeSampleIndex = 0;
    tempoLineDown.myWavWriter.setFormat(1, sampleRate, 16);
    tempoLineDown.onOffRectPos.x = -tempoLineDown.length/2 + ofGetWidth()/2;
    tempoLineDown.sizeRectPos.x = tempoLineDown.length/2 + ofGetWidth()/2;
    tempoLineDown.changeSampleSize = 60;
    
    tempoLineUp.length = tempoLineDown.length;
    tempoLineUp.bOnOffBeingClick = true;
    tempoLineUp.bTimerReached = true;
    tempoLineUp.bDownSoundRecordClick = true;
    tempoLineUp.bChangeSampleClick = false;
    tempoLineUp.bChangeSampleOver = false;
    tempoLineUp.startTime = ofGetElapsedTimeMillis() - 1000;
    tempoLineUp.rectBlockAlphaFactor = 0;
    tempoLineUp.recordState=0;
    tempoLineUp.soundVolume = 1;
    tempoLineUp.changeSampleIndex = 0;
    tempoLineUp.myWavWriter.setFormat(1, sampleRate, 16);
    tempoLineUp.onOffRectPos.x = -tempoLineUp.length/2 + ofGetWidth()/2;
    tempoLineUp.sizeRectPos.x = tempoLineUp.length/2 + ofGetWidth()/2;
    tempoLineUp.changeSampleSize = 60;
    
    
    tempoLineUp.position.x = tempoLineUp.sizeRectPos.x-tempoLineDown.sizeRectPos.x;
    tempoLineUp.delayPos.x = tempoLineUp.length/2 + ofGetWidth()/2 - tempoLineUp.length/(10*2);
    
    nElementLine = 8;
    for (int i = 0; i<nElementLine; i++)
    {
		elementLinesDown[i].bSizeOver = false;
        elementLinesDown[i].bOnOffOver = false;
		elementLinesDown[i].bSizeBeingDragged = false;
		elementLinesDown[i].bOnOffBeingClick = false;
		elementLinesDown[i].soundTrigger = true;
        elementLinesDown[i].samplePlay.setMultiPlay(true);
        elementLinesDown[i].samplePlay.loadSound(fileNameDown);
        elementLinesDown[i].samplePlay.setVolume(highVolume);
        spacingLineDown = tempoLineDown.length / 10;
        elementLinesDown[i].position = ofVec2f(spacingLineDown + spacingLineDown/2 + spacingLineDown*i, tempoLineDown.onOffRectPos.y);
        elementLinesDown[i].sizeRect = ofVec2f(elementLinesDown[i].position.x, elementLinesDown[i].position.y+randomY[i]);
        elementLinesDown[i].onOffRect = elementLinesDown[i].sizeRect * ofVec2f(1,-1) + ofVec2f(0,ofGetHeight());
		elementLinesDown[i].width = 4;
        elementLinesDown[i].triggerColor = 120;
        
        elementLinesUp[i].bSizeOver = false;
        elementLinesUp[i].bOnOffOver = false;
		elementLinesUp[i].bSizeBeingDragged = false;
		elementLinesUp[i].bOnOffBeingClick = false;
		elementLinesUp[i].soundTrigger = true;
        elementLinesUp[i].samplePlay.setMultiPlay(true);
        elementLinesUp[i].samplePlay.loadSound(fileNameUp);
        elementLinesUp[i].samplePlay.setVolume(highVolume);
        spacingLineUp = tempoLineUp.length / 10;
        elementLinesUp[i].position = ofVec2f(spacingLineUp + spacingLineUp/2 + spacingLineUp*i, tempoLineUp.onOffRectPos.y);
        elementLinesUp[i].sizeRect = ofVec2f(elementLinesUp[i].position.x, elementLinesUp[i].position.y-randomY[i+8]);
        elementLinesUp[i].onOffRect = elementLinesUp[i].sizeRect * ofVec2f(1,-1) + ofVec2f(0,ofGetHeight());
		elementLinesUp[i].width = 4;
        elementLinesUp[i].triggerColor = 120;
    }
}

//--------------------------------------------------------------
void myApp::update()
{
    if (!fullscreen)
    {
        ofSetWindowShape(1280, 720);
    }
    
//    tempoLineDown.recBlockPos = ofVec2f(ofGetWidth()*0.05, ofGetHeight()*3/4);
    tempoLineDown.recBlockPos = ofVec2f(tempoLineDown.onOffRectPos.x-30, ofGetHeight()/2+ofGetHeight()*0.1);
    tempoLineDown.changeSamplePos = ofVec2f(tempoLineDown.sizeRectPos.x,ofGetHeight()/2+ofGetHeight()*0.09);
    
//    tempoLineUp.recBlockPos = ofVec2f(ofGetWidth()*0.05, ofGetHeight()*1/4);
    tempoLineUp.recBlockPos = ofVec2f(tempoLineUp.onOffRectPos.x-30, ofGetHeight()/2-ofGetHeight()*0.1);
    tempoLineUp.changeSamplePos = ofVec2f(tempoLineUp.sizeRectPos.x,ofGetHeight()/2-ofGetHeight()*0.09);
    
    
    
    ofSoundUpdate();
    
    //    tempoLineDown.sizeRectPos.x = tempoLineDown.sizeRectPos.x;
    //    tempoLineDown.onOffRectPos.x = ofGetWidth() - tempoLineDown.sizeRectPos.x;
    
    tempoLineDown.length = tempoLineDown.sizeRectPos.x - tempoLineDown.onOffRectPos.x;
    
    tempoLineDown.onOffRectPos.x = -tempoLineDown.length/2 + ofGetWidth()/2;
    tempoLineDown.sizeRectPos.x = tempoLineDown.length/2 + ofGetWidth()/2;
    
    
    //    float speed = ofMap(tempoLineDown.length, 40, ofGetWidth(), 10, 88);
    float speed = tempoLineDown.length/12;
    float timer = (ofGetElapsedTimeMillis()-millisDown)*1.0;
    
    int delayTempoLineUp = (int)(tempoLineUp.position.x)/12;
    
    
    int speedFactor = 32;
    int speedFactor8th = speedFactor/8;
    
    if (timer>=speed)
    {
        millisDown = ofGetElapsedTimeMillis();
        
        cout << timer << endl;
        cout << speed << endl;
        
        triggerCounterDown++;
        int _index = triggerCounterDown%speedFactor;
        for (int i = 0; i<nElementLine; i++)
        {
            
            if (_index==((i*speedFactor8th)))
            {
                if ((elementLinesDown[i].soundTrigger)&&tempoLineDown.bOnOffBeingClick)
                {
                    elementLinesDown[i].onOffTrigger = true;
                    elementLinesDown[i].samplePlay.play();
                    elementLinesDown[i].samplePlay.setVolume( ofRandom(0.325,0.95) * tempoLineDown.soundVolume);
                    elementLinesDown[i].samplePlay.setSpeed( ofMap(elementLinesDown[i].sizeRect.y, 0, ofGetHeight()/2, 3.0, 0) * ofRandom(0.75,1.25) );
                }
            }
            else
            {
                elementLinesDown[i].onOffTrigger = false;
            }
            
            if (_index==((i*speedFactor8th)+delayTempoLineUp%8))
            {
                if ((elementLinesUp[i].soundTrigger)&&tempoLineUp.bOnOffBeingClick)
                {
                    elementLinesUp[i].onOffTrigger = true;
                    elementLinesUp[i].samplePlay.play();
                    elementLinesUp[i].samplePlay.setVolume( ofRandom(0.325,0.95) * tempoLineUp.soundVolume);
                    elementLinesUp[i].samplePlay.setSpeed( ofMap(elementLinesUp[i].sizeRect.y+ofGetHeight()/2, ofGetHeight()/2, 0, 3.0, 0) * ofRandom(0.75,1.25) );
                }
            }
            else
            {
                elementLinesUp[i].onOffTrigger = false;
            }
        }
        
        
    }
    
    
    spacingLineDown = tempoLineDown.length / 10;
    spacingLineUp = tempoLineDown.length / 10;
    
    tempoLineUp.sizeRectPos.x = tempoLineDown.sizeRectPos.x + spacingLineUp * delayTempoLineUp * 0.25;
    tempoLineUp.onOffRectPos.x = tempoLineDown.onOffRectPos.x + spacingLineUp * delayTempoLineUp * 0.25;
    tempoLineUp.length = tempoLineUp.sizeRectPos.x - tempoLineUp.onOffRectPos.x;
    
    
    
    for (int i = 0; i<nElementLine; i++)
    {
        elementLinesDown[i].position = ofVec2f( tempoLineDown.onOffRectPos.x + spacingLineDown + spacingLineDown/2 + spacingLineDown*i, tempoLineDown.onOffRectPos.y );
        elementLinesDown[i].sizeRect = ofVec2f( elementLinesDown[i].position.x, elementLinesDown[i].sizeRect.y );
        elementLinesDown[i].onOffRect = elementLinesDown[i].sizeRect * ofVec2f(1,0) + ofVec2f(0,5);
        elementLinesUp[i].position.x = elementLinesDown[i].position.x + spacingLineUp * delayTempoLineUp * 0.25;
        elementLinesUp[i].sizeRect = ofVec2f( elementLinesUp[i].position.x, elementLinesUp[i].sizeRect.y );
        elementLinesUp[i].onOffRect = elementLinesUp[i].sizeRect * ofVec2f(1,0) + ofVec2f(0,-5);
    }
    
}

void myApp::drawingTempoLine(bool _bTOnOff, bool _bTSizeOver, bool _bTOnOffOver, ofVec2f _vTSizePos, ofVec2f _vTOnOffPos)
{
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor(ofColor::fromHsb(0,0,255,140));
    
    if (_bTOnOff)
    {
        ofNoFill();
        ofSetColor(ofColor::fromHsb(0,0,255,140));
        if (_bTSizeOver)
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
        if (_bTSizeOver)
        {
            ofFill();
        }
        else
        {
            ofNoFill();
        }
    }
    ofRect(_vTSizePos, 7, 7);
    
    if (_bTOnOff)
    {
        ofNoFill();
        ofSetColor(ofColor::fromHsb(0,0,255,140));
        if (_bTOnOffOver)
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
    ofRect(_vTOnOffPos, 7, 7);
    ofLine(_vTOnOffPos+ofVec2f(4,0), _vTSizePos-ofVec2f(4,0));
    ofPopStyle();
}

//void myApp::drawingElementLine(bool _bOnOffT, bool _bOnOffBeingClick, bool _bSoundT, bool _bTColor, ofVec2f _vOnOffRect, ofVec2f _vSizeRect)
//{
//
//}

//--------------------------------------------------------------
void myApp::draw()
{
    
    ofPushMatrix();
    ofTranslate(0, ofGetHeight()/2+5);
    
    
    drawingTempoLine(tempoLineDown.bOnOffBeingClick, tempoLineDown.bSizeOver, tempoLineDown.bOnOffOver, tempoLineDown.sizeRectPos, tempoLineDown.onOffRectPos);
    
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    
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
        
    }
    ofPopStyle();
    
    ofPopMatrix();
    
    
    ofPushMatrix();
    ofTranslate(0, ofGetHeight()/2-5);
    
    drawingTempoLine(tempoLineUp.bOnOffBeingClick, tempoLineUp.bSizeOver, tempoLineUp.bOnOffOver, tempoLineUp.sizeRectPos, tempoLineUp.onOffRectPos);
    
    
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
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
    
    if (!tempoLineUp.bOnOffBeingClick&&tempoLineDown.bOnOffBeingClick)
    {
        recordingLineDraw(tempoLineDown.recBlockPos);
    }
    if (!tempoLineDown.bOnOffBeingClick&&tempoLineUp.bOnOffBeingClick)
    {
        recordingLineDraw(tempoLineUp.recBlockPos);
    }
    
    if ((!tempoLineUp.bOnOffBeingClick&&!tempoLineUp.bDownSoundRecordClick)||tempoLineDown.bOnOffBeingClick)
    {
        tempoLineUp.bDownSoundRecordClick = true;
    }
    if ((!tempoLineDown.bOnOffBeingClick&&!tempoLineDown.bDownSoundRecordClick)||tempoLineUp.bOnOffBeingClick)
    {
        tempoLineDown.bDownSoundRecordClick = true;
    }
    

    tempoLineDown.bDownSoundRecordPos = ofVec2f(tempoLineDown.recBlockPos.x,tempoLineDown.recBlockPos.y-(initialBufferSize/8-1)/2);
    tempoLineUp.bDownSoundRecordPos = ofVec2f(tempoLineUp.recBlockPos.x,tempoLineUp.recBlockPos.y-(initialBufferSize/8-1)/2);
    
    ofPushStyle();
    ofSetColor( ofColor::fromHsb(backgroundColorHue, 0, 220, 100) );
    if (tempoLineUp.bChangeSampleOver)
    {
        ofPushStyle();
        if (tempoLineUp.bChangeSampleClick)
        {
            ofSetColor( ofColor::fromHsb(backgroundColorHue, 0, 220, 160) );
            tempoLineUp.changeSampleIndex++;
            tempoLineUp.changeSampleIndex = tempoLineUp.changeSampleIndex%dir.size();
            for (int i = 0; i<nElementLine; i++)
            {
                string fileNameUp = "sounds/samples/" + dir.getName(tempoLineUp.changeSampleIndex);
                elementLinesUp[i].samplePlay.loadSound(fileNameUp);
            }
            tempoLineUp.bChangeSampleClick = !tempoLineUp.bChangeSampleClick;
        }
        else
        {
            ofSetColor( ofColor::fromHsb(backgroundColorHue, 0, 220, 50) );
        }
        ofRect(tempoLineUp.changeSamplePos.x-tempoLineUp.changeSampleSize/2, tempoLineUp.changeSamplePos.y-tempoLineUp.changeSampleSize/2, tempoLineUp.changeSampleSize, tempoLineUp.changeSampleSize);
        ofNoFill();
        ofSetColor(ofColor::fromHsb(backgroundColorHue, 0, 230, 80) );
//        ofRect(tempoLineUp.changeSamplePos.x-tempoLineUp.changeSampleSize/2, tempoLineUp.changeSamplePos.y-tempoLineUp.changeSampleSize/2, tempoLineUp.changeSampleSize, tempoLineUp.changeSampleSize);
        ofLine(tempoLineUp.changeSamplePos.x+tempoLineUp.changeSampleSize/2,tempoLineUp.changeSamplePos.y+tempoLineUp.changeSampleSize/2,tempoLineUp.sizeRectPos.x+3,tempoLineUp.sizeRectPos.y+ofGetHeight()/2-7);
        ofPopStyle();
        
    }
    if (tempoLineDown.bChangeSampleOver)
    {
        ofPushStyle();
        if (tempoLineDown.bChangeSampleClick)
        {
            ofSetColor( ofColor::fromHsb(backgroundColorHue, 0, 220, 160) );
            tempoLineDown.changeSampleIndex++;
            tempoLineDown.changeSampleIndex = tempoLineDown.changeSampleIndex%dir.size();
            for (int i = 0; i<nElementLine; i++)
            {
                string fileNameDown = "sounds/samples/" + dir.getName(tempoLineDown.changeSampleIndex);
                elementLinesDown[i].samplePlay.loadSound(fileNameDown);
            }
            tempoLineDown.bChangeSampleClick = !tempoLineDown.bChangeSampleClick;        }
        else
        {
            ofSetColor( ofColor::fromHsb(backgroundColorHue, 0, 220, 50) );
        }
        ofRect(tempoLineDown.changeSamplePos.x-30, tempoLineDown.changeSamplePos.y-30, 60, 60);
        ofNoFill();
        ofSetColor(ofColor::fromHsb(backgroundColorHue, 0, 230, 80) );
//        ofRect(tempoLineDown.changeSamplePos.x-30, tempoLineDown.changeSamplePos.y-30, 60, 60);
        ofLine(tempoLineDown.changeSamplePos.x+30,tempoLineDown.changeSamplePos.y-30,tempoLineDown.sizeRectPos.x+3,tempoLineDown.sizeRectPos.y+ofGetHeight()/2+7);
        ofPopStyle();
    }
    ofPopStyle();
    
    infomationWindow();
    ofSetFullscreen(fullscreen);
    
}


void myApp::infomationWindow()
{
    ofPushStyle();
    startTime = startTime + 1;
    if (startTime>300) startTime = 301;
    ofSetColor( ofColor::fromHsb(backgroundColorHue, 0, ofMap(startTime,0,300,0,230), ofMap(startTime,0,300,255,0) ) );
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofPopStyle();
    
}

void myApp::recordingLineDraw(ofVec2f _vP)
{
    
    ofPushMatrix();
    ofTranslate(_vP);
    ofPushStyle();
    
    float colorAlpha = 120;
    
    if (_vP.y == tempoLineDown.recBlockPos.y)
    {
        ofPushStyle();
        if (tempoLineDown.bDownSoundRecordClick)
        {
            tempoLineDown.rectBlockAlphaFactor = tempoLineDown.rectBlockAlphaFactor + 2.5;
            tempoLineDown.soundVolume = 1;
            ofFill();
            ofSetColor(ofColor::fromHsb(backgroundColorHue, 0, 230, abs(sin(ofDegToRad(tempoLineDown.rectBlockAlphaFactor))*colorAlpha*0.5) ));
            ofRect(0,-(initialBufferSize/8-1)/2,initialBufferSize/8-1,initialBufferSize/8-1);
            ofNoFill();
        }
        else
        {
            tempoLineDown.rectBlockAlphaFactor = colorAlpha;
            tempoLineDown.soundVolume = 0;
            ofSetColor(ofColor::fromHsb(backgroundColorHue, 0, 230, abs(sin(ofDegToRad(tempoLineDown.rectBlockAlphaFactor))*colorAlpha*0.2) ));
            ofRect(0,-(initialBufferSize/8-1)/2,initialBufferSize/8-1,initialBufferSize/8-1);
        }
        ofPushStyle();
        ofSetColor(ofColor::fromHsb(backgroundColorHue, 0, 230, abs(sin(ofDegToRad(tempoLineDown.rectBlockAlphaFactor))*colorAlpha*0.3) ));
        ofLine( 0,-(initialBufferSize/8-1)/2,tempoLineDown.onOffRectPos.x-_vP.x-5,ofGetHeight()/2-_vP.y+5+3 );
        ofPopStyle();
        
        ofPopStyle();
    }
    else
    {
        ofPushStyle();
        if (tempoLineUp.bDownSoundRecordClick)
        {
            tempoLineUp.rectBlockAlphaFactor = tempoLineUp.rectBlockAlphaFactor + 2.5;
            tempoLineUp.soundVolume = 1;
            ofFill();
            ofSetColor(ofColor::fromHsb(backgroundColorHue, 0, 230, abs(sin(ofDegToRad(tempoLineUp.rectBlockAlphaFactor))*colorAlpha*0.5) ));
            ofRect(0,-(initialBufferSize/8-1)/2,initialBufferSize/8-1,initialBufferSize/8-1);
            ofNoFill();
        }
        else
        {
            tempoLineUp.rectBlockAlphaFactor = colorAlpha;
            tempoLineUp.soundVolume = 0;
            ofSetColor(ofColor::fromHsb(backgroundColorHue, 0, 230, abs(sin(ofDegToRad(tempoLineUp.rectBlockAlphaFactor))*colorAlpha*0.2) ));
            ofRect(0,-(initialBufferSize/8-1)/2,initialBufferSize/8-1,initialBufferSize/8-1);
        }
        ofPushStyle();
        ofSetColor(ofColor::fromHsb(backgroundColorHue, 0, 230, abs(sin(ofDegToRad(tempoLineUp.rectBlockAlphaFactor))*colorAlpha*0.3) ));
        ofLine( 0,(initialBufferSize/8-1)/2,tempoLineUp.onOffRectPos.x-_vP.x-5,ofGetHeight()/2-_vP.y-5-3 );
        ofPopStyle();
        ofPopStyle();
    }
    ofPopStyle();
    
    float oldValue;
    
    for(int i = 0; i < initialBufferSize/8-1; i++)
    {
        ofPushStyle();
        ofSetColor(ofColor::fromHsb(backgroundColorHue, 0, 220, 150));
        
        ofLine(i, buffer[i] * (initialBufferSize/8-1)/3, i+1, buffer[i+1] * -(initialBufferSize/8-1)/3);
        //        ofEllipse(i, 0, buffer[i] * (initialBufferSize/8-1)/3, buffer[i] * (initialBufferSize/8-1)/2);
        
        ofPopStyle();
        
        if ((abs(buffer[i+1]*50.0f)>5)&&!tempoLineDown.bDownSoundRecordClick)
        {
            tempoLineDown.startTime = ofGetElapsedTimeMillis();
        }
        if ((abs(buffer[i+1]*50.0f)>5)&&!tempoLineUp.bDownSoundRecordClick)
        {
            tempoLineUp.startTime = ofGetElapsedTimeMillis();
        }
    }
    
    ofPopMatrix();
    
    if (_vP.y == tempoLineDown.recBlockPos.y)
    {
        tempoLineDown.recordingTime = 1000;
        tempoLineDown.timeStamp = ofGetElapsedTimeMillis() - tempoLineDown.startTime;
        
        if ((tempoLineDown.timeStamp<tempoLineDown.recordingTime))
        {
            if (tempoLineDown.recordState==0)
            {
                tempoLineDown.recordState=1;
            }
            tempoLineDown.bTimerReached = false;
        }
        
        if ((tempoLineDown.timeStamp>=tempoLineDown.recordingTime)&&!tempoLineDown.bTimerReached)
        {
            if (tempoLineDown.recordState==3)
            {
                tempoLineDown.recordState=2;
            }
            tempoLineDown.bTimerReached = true;
            tempoLineDown.bDownSoundRecordClick = true;
        }
    }
    else
    {
        tempoLineUp.recordingTime = 1000;
        tempoLineUp.timeStamp = ofGetElapsedTimeMillis() - tempoLineUp.startTime;
        
        if ((tempoLineUp.timeStamp<tempoLineUp.recordingTime))
        {
            if (tempoLineUp.recordState==0)
            {
                tempoLineUp.recordState=1;
            }
            tempoLineUp.bTimerReached = false;
        }
        
        if ((tempoLineUp.timeStamp>=tempoLineUp.recordingTime)&&!tempoLineUp.bTimerReached)
        {
            if (tempoLineUp.recordState==3)
            {
                tempoLineUp.recordState=2;
            }
            tempoLineUp.bTimerReached = true;
            tempoLineUp.bDownSoundRecordClick = true;
        }
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
    
    if ((tempoLineDown.recordState==1)&&(soundRecordingDownOn))
    {
        tempoLineDown.recordState=3;
        tempoLineDown.myWavWriter.open(ofToDataPath("sounds/recordingDown.wav"), WAVFILE_WRITE);
    }
    
	if (tempoLineDown.recordState==3)
    {
		tempoLineDown.myWavWriter.write(input, bufferSize*nChannels);
	}
    
    if (tempoLineDown.recordState==2)
    {
        tempoLineDown.myWavWriter.close();
        tempoLineDown.recordState=0;
        for (int i = 0; i<nElementLine; i++)
        {
            elementLinesDown[i].samplePlay.loadSound("sounds/recordingDown.wav");
        }
    }
    
    if ((tempoLineUp.recordState==1)&&(soundRecordingDownOn))
    {
        tempoLineUp.recordState=3;
        tempoLineUp.myWavWriter.open(ofToDataPath("sounds/recordingUp.wav"), WAVFILE_WRITE);
    }
    
	if (tempoLineUp.recordState==3)
    {
		tempoLineUp.myWavWriter.write(input, bufferSize*nChannels);
	}
    
    if (tempoLineUp.recordState==2)
    {
        tempoLineUp.myWavWriter.close();
        tempoLineUp.recordState=0;
        for (int i = 0; i<nElementLine; i++)
        {
            elementLinesUp[i].samplePlay.loadSound("sounds/recordingUp.wav");
        }
    }
    
}


//--------------------------------------------------------------
void myApp::keyPressed(int key)
{
    //    if (recordState==0)
    //    {
    //        recordState=1;
    //    }
}

//--------------------------------------------------------------
void myApp::keyReleased(int key)
{
    //    if (recordState==3)
    //    {
    //        recordState=2;
    //    }
    
    if (key=='f') fullscreen = !fullscreen;
    
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
    
    tempoLineDown.bChangeSampleOver = inOutCal(x, y, tempoLineDown.changeSamplePos, 30);
    tempoLineUp.bChangeSampleOver = inOutCal(x, y, tempoLineUp.changeSamplePos, 30);
    
    //    bDownSoundRecordOver = inOutCal(x, y, ofVec2f(((initialBufferSize/8-1)+40)/2,ofGetHeight()*3/4), 50);
    //    if (bDownSoundRecordOver)
    //    {
    //        cout << "bang" << endl;
    //    } else
    //    {
    //        cout << "out" << endl;
    //    }
    
    
    
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
        if (x<ofGetWidth()/2+ofGetWidth()*0.07)
            x = ofGetWidth()/2+ofGetWidth()*0.07;
        if (x>ofGetWidth()-ofGetWidth()*0.11)
            x = ofGetWidth()-ofGetWidth()*0.11;
        tempoLineDown.sizeRectPos.x = x;
    }
    
    if (tempoLineUp.bSizeBeingDragged == true)
    {
        tempoLineUp.position.x = x - (tempoLineUp.length/2+ofGetWidth()/2);
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
    
    tempoLineDown.bDownSoundRecordClick = onOffOut(x, y, tempoLineDown.bDownSoundRecordPos+ofVec2f(initialBufferSize/8/2,initialBufferSize/8/2+1), initialBufferSize/8/2, tempoLineDown.bDownSoundRecordClick);
    tempoLineUp.bDownSoundRecordClick = onOffOut(x, y, tempoLineUp.bDownSoundRecordPos+ofVec2f(initialBufferSize/8/2,initialBufferSize/8/2+1), initialBufferSize/8/2, tempoLineUp.bDownSoundRecordClick);
    
    
    
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
    tempoLineDown.bChangeSampleClick = onOffOut(x, y, tempoLineDown.changeSamplePos, 30, tempoLineDown.bChangeSampleClick);
    tempoLineUp.bChangeSampleClick = onOffOut(x, y, tempoLineUp.changeSamplePos, 30, tempoLineUp.bChangeSampleClick);
    //    if(inOutCal(x, y, tempoLineDown.changeSamplePos, 30)) tempoLineDown.bChangeSampleClick = false;
    //    if(inOutCal(x, y, tempoLineUp.changeSamplePos, 30)) tempoLineUp.bChangeSampleClick = false;
    
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