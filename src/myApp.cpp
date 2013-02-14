#include "myApp.h"

ofVec2f tempoLineOnOff, tempoLineSize;
int tempoLineDefaultLength;
ofVec2f mousePos, mouseDraggedPos, mouseClickPos, mouseReleasePos;
ofVec2f preMousePosition;
ofVec2f mousePosition;

float distMouseSize, distMouseOnOff;

Boolean mouseButton;


ofVec2f setSizePosition, setOnOffPosition;
float distMouseSize2;

int firstLineDefaultLength;

float tempoLength;

float postionPitchLine;

int pitchIndex;

//--------------------------------------------------------------
void myApp::setup(){
//    ofSetDataPathRoot("../Resources/");
    
    ofBackground(40);
    ofSetFrameRate(30);
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofNoFill();
    
    ofEnableAlphaBlending();
    ofSetCircleResolution(24);
    
    mouseButton = false;

    tempoLineDefaultLength = 400;
    tempoLineOnOff = ofVec2f(-tempoLineDefaultLength/2+ofGetWidth()/2, ofGetHeight()/2);
    tempoLineSize = ofVec2f(tempoLineDefaultLength/2+ofGetWidth()/2, ofGetHeight()/2);
    
    firstLine = new PitchLine;
    secondLine = new PitchLine;
    thirdLine = new PitchLine;
    forthLine = new PitchLine;
    fifthLine = new PitchLine;
    sixthLine = new PitchLine;
    seventhLine = new PitchLine;
    eighthLine = new PitchLine;


    
    // !!!: new Sound player - sample player
    piano.loadSound("pf_sample_01.wav");
    piano.setVolume(0.5f);
    piano.setMultiPlay(true);
    
    pitchIndex = -1;
}

//--------------------------------------------------------------
void myApp::update(){
    ofSoundUpdate();

    mousePosition = ofVec2f(ofGetMouseX(),ofGetMouseY());
    int speed = 10;
    if (ofGetFrameNum()%speed==0) {
        pitchIndex = pitchIndex + 1;
    }
    
    if (pitchIndex>7) {
        pitchIndex = 0;
    }
    
    cout << pitchIndex << endl;
 
}

//--------------------------------------------------------------
void myApp::draw(){
    
    ofPushStyle();
    distMouseSize = tempoLineSize.distance(mousePosition);
    if ((distMouseSize<8)&&(mouseButton==true)) {
        ofSetColor(255, 255);
        tempoLineSize = ofVec2f(mousePosition.x, ofGetHeight()/2);
        tempoLineOnOff = tempoLineSize-ofVec2f((-ofGetWidth()/2+mousePosition.x)*2, 0);
    } else {
        ofSetColor(255, 100);
        tempoLineSize = tempoLineSize;
        tempoLineOnOff = tempoLineOnOff;
    }
    ofRect(tempoLineOnOff, 10, 10);
    ofCircle(tempoLineSize, 6);
    ofLine(tempoLineOnOff, tempoLineSize);
    ofPopStyle();

    tempoLength = tempoLineOnOff.distance(tempoLineSize);

    ofPushMatrix();
    float postionPitchLine1 = (tempoLineOnOff.x+tempoLength*1/10+tempoLength*1/20);
    ofTranslate(postionPitchLine1, ofGetHeight()/2);
    firstLine->_positionPitchLine = postionPitchLine1;
    firstLine->mouseButton = mouseButton;
    firstLine->mousePosition = mousePosition;
    firstLine->drawing();

    if (pitchIndex==0) {
        firstLine->trigger = true;
    } else {
        firstLine->trigger = false;
    }
    if (ofGetFrameNum()%80==0) {
        piano.play();
        piano.setSpeed(ofMap(firstLine->lineSize.y, 0, 300, 5.0, 0));
    }
    ofPopMatrix();

    ofPushMatrix();
    float postionPitchLine2 = (tempoLineOnOff.x+tempoLength*2/10+tempoLength*1/20);
    ofTranslate(postionPitchLine2, ofGetHeight()/2);
    secondLine->_positionPitchLine = postionPitchLine2;
    secondLine->mouseButton = mouseButton;
    secondLine->mousePosition = mousePosition;
    secondLine->drawing();
    if (pitchIndex==1) {
        secondLine->trigger = true;
    } else {
        secondLine->trigger = false;
    }
    if (ofGetFrameNum()%80==10) {
        piano.play();
        piano.setSpeed(ofMap(secondLine->lineSize.y, 0, 300, 5.0, 0));
    }
    ofPopMatrix();

    ofPushMatrix();
    float postionPitchLine3 = (tempoLineOnOff.x+tempoLength*3/10+tempoLength*1/20);
    ofTranslate(postionPitchLine3, ofGetHeight()/2);
    thirdLine->_positionPitchLine = postionPitchLine3;
    thirdLine->mouseButton = mouseButton;
    thirdLine->mousePosition = mousePosition;
    thirdLine->drawing();
    if (pitchIndex==2) {
        thirdLine->trigger = true;
    } else {
        thirdLine->trigger = false;
    }
    if (ofGetFrameNum()%80==20) {
        piano.play();
        piano.setSpeed(ofMap(thirdLine->lineSize.y, 0, 300, 5.0, 0));
    }
    ofPopMatrix();

    ofPushMatrix();
    float postionPitchLine4 = (tempoLineOnOff.x+tempoLength*4/10+tempoLength*1/20);
    ofTranslate(postionPitchLine4, ofGetHeight()/2);
    forthLine->_positionPitchLine = postionPitchLine4;
    forthLine->mouseButton = mouseButton;
    forthLine->mousePosition = mousePosition;
    forthLine->drawing();
    if (pitchIndex==3) {
        forthLine->trigger = true;
    } else {
        forthLine->trigger = false;
    }
    if (ofGetFrameNum()%80==30) {
        piano.play();
        piano.setSpeed(ofMap(forthLine->lineSize.y, 0, 300, 5.0, 0));
    }
    ofPopMatrix();

    ofPushMatrix();
    float postionPitchLine5 = (tempoLineOnOff.x+tempoLength*5/10+tempoLength*1/20);
    ofTranslate(postionPitchLine5, ofGetHeight()/2);
    fifthLine->_positionPitchLine = postionPitchLine5;
    fifthLine->mouseButton = mouseButton;
    fifthLine->mousePosition = mousePosition;
    fifthLine->drawing();
    if (pitchIndex==4) {
        fifthLine->trigger = true;
    } else {
        fifthLine->trigger = false;
    }
    if (ofGetFrameNum()%80==40) {
        piano.play();
        piano.setSpeed(ofMap(fifthLine->lineSize.y, 0, 300, 5.0, 0));
    }
    ofPopMatrix();

    ofPushMatrix();
    float postionPitchLine6 = (tempoLineOnOff.x+tempoLength*6/10+tempoLength*1/20);
    ofTranslate(postionPitchLine6, ofGetHeight()/2);
    sixthLine->_positionPitchLine = postionPitchLine6;
    sixthLine->mouseButton = mouseButton;
    sixthLine->mousePosition = mousePosition;
    sixthLine->drawing();
    if (pitchIndex==5) {
        sixthLine->trigger = true;
    } else {
        sixthLine->trigger = false;
    }
    if (ofGetFrameNum()%80==50) {
        piano.play();
        piano.setSpeed(ofMap(sixthLine->lineSize.y, 0, 300, 5.0, 0));
    }
    ofPopMatrix();

    ofPushMatrix();
    float postionPitchLine7 = (tempoLineOnOff.x+tempoLength*7/10+tempoLength*1/20);
    ofTranslate(postionPitchLine7, ofGetHeight()/2);
    seventhLine->_positionPitchLine = postionPitchLine7;
    seventhLine->mouseButton = mouseButton;
    seventhLine->mousePosition = mousePosition;
    seventhLine->drawing();
    if (pitchIndex==6) {
        seventhLine->trigger = true;
    } else {
        seventhLine->trigger = false;
    }
    if (ofGetFrameNum()%80==60) {
        piano.play();
        piano.setSpeed(ofMap(seventhLine->lineSize.y, 0, 300, 5.0, 0));
    }
    ofPopMatrix();

    ofPushMatrix();
    float postionPitchLine8 = (tempoLineOnOff.x+tempoLength*8/10+tempoLength*1/20);
    ofTranslate(postionPitchLine8, ofGetHeight()/2);
    eighthLine->_positionPitchLine = postionPitchLine8;
    eighthLine->mouseButton = mouseButton;
    eighthLine->mousePosition = mousePosition;
    eighthLine->drawing();
    if (pitchIndex==7) {
        eighthLine->trigger = true;
    } else {
        eighthLine->trigger = false;
    }
    if (ofGetFrameNum()%80==70) {
        piano.play();
        piano.setSpeed(ofMap(eighthLine->lineSize.y, 0, 300, 5.0, 0));
    }
    ofPopMatrix();

}




//--------------------------------------------------------------
bool myApp::toggle(bool b) {
    if (b) {
        return false;
    } else {
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
void myApp::mousePressed(int x, int y, int button){
    if (button==0) {
        mouseButton = true;
    }
}

//--------------------------------------------------------------
void myApp::mouseReleased(int x, int y, int button){
    if (button==0) {
        mouseButton = false;
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