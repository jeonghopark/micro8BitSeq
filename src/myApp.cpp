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
    mouseButton = false;
    
    int tempoLineDefaultLength = 200;
    tempoLineOnOff = ofVec2f(-tempoLineDefaultLength/2+ofGetWidth()/2, ofGetHeight()/2);
    tempoLineSize = ofVec2f(tempoLineDefaultLength/2+ofGetWidth()/2, ofGetHeight()/2);
    
    highVolume = 0.3;
    
    speed = 5;
    preMouseClick = 0;
    
    fileName = "bell_sample_04.wav";
    
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
    ofSetWindowShape(400, 400);
    
    ofSoundUpdate();
    
    mousePosition = ofVec2f(ofGetMouseX(),ofGetMouseY());
    
    distMouseSize = tempoLineSize.distance(mousePosition);
    
    if ((distMouseSize<12)&&(mouseButton==true))
    {
        ofSetColor(255, 255, 255, 255);
        tempoLineSize = ofVec2f(mousePosition.x, ofGetHeight()/2);
        tempoLineOnOff = tempoLineSize-ofVec2f((-ofGetWidth()/2+mousePosition.x)*2, 0);
    }
    else
    {
        ofSetColor(255, 255, 255, 120);
        tempoLineSize = tempoLineSize;
        tempoLineOnOff = tempoLineOnOff;
    }
    
    tempoLineLength = tempoLineOnOff.distance(tempoLineSize);
    
    speed = int(ofMap(tempoLineLength, 0, ofGetWidth(), 2, 10));
    
}

//--------------------------------------------------------------
void myApp::draw()
{
    ofPushStyle();
    ofRect(tempoLineOnOff, 7, 7);
    ofCircle(tempoLineSize, 4);
    ofLine(tempoLineOnOff, tempoLineSize);
    ofPopStyle();
    
    for (int i = 0; i<NUM; i++)
    {
        ofPushMatrix();
        float postionPitchLine = (tempoLineOnOff.x+tempoLineLength*(i+1)/10+tempoLineLength*1/20);
        ofTranslate(postionPitchLine, ofGetHeight()/2);
        pitchLines[i]->_positionPitchLine = postionPitchLine;
        pitchLines[i]->mouseButton = mouseButton;
        pitchLines[i]->mouseReleaseButton = mouseClickRealease;
        pitchLines[i]->mousePosition = mousePosition;
        pitchLines[i]->drawing();
        
        if (pitchLines[i]->signalOnOff)
        {
            samplePiano[i].setVolume(0.0);
        }
        else
        {
            samplePiano[i].setVolume(highVolume);
        }
        
        if (triggerCount%2 == 0)
        {
            //            pitchLines[i]->trigger = false;
        }
        
        if (ofGetFrameNum()%(speed*8)==(speed*i))
        {
            pitchLines[i]->trigger = true;
            samplePiano[i].setSpeed(ofMap(pitchLines[i]->pitchLineSize.y, 0, ofGetHeight()/2, 7.0, 0) * round(ofRandom(0,4))/4.0);
            samplePiano[i].play();
            triggerCount = triggerCount + 1;
        }
        else
        {
            pitchLines[i]->trigger = false;
        }
        
        ofPopMatrix();
    }

    justOneclick();
    
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
void myApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void myApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void myApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void myApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void myApp::mousePressed(int x, int y, int button)
{
    if (button==0)
    {
        mouseButton = true;
        mouseclick = 1;
    }
}

//--------------------------------------------------------------
void myApp::mouseReleased(int x, int y, int button)
{
    if (button==0)
    {
        mouseButton = false;
        mouseclick = 0;
    }
}

//--------------------------------------------------------------
void myApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void myApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void myApp::dragEvent(ofDragInfo dragInfo){
    
}