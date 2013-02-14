#include "PitchLine.h"


PitchLine::PitchLine() {

    pitchLineDefaultLength = 200;
    lineOnOff = ofVec2f(0, -pitchLineDefaultLength);
    lineSize = ofVec2f(0, pitchLineDefaultLength);
    
    signalOnOff = false;

}

void PitchLine::drawing() {

    ofPushStyle();

    distanceMouseOnOff = (lineOnOff+ofVec2f(_positionPitchLine, ofGetHeight()/2)).distance(mousePosition);

    distanceMouseSize = (lineSize+ofVec2f(_positionPitchLine, ofGetHeight()/2)).distance(mousePosition);
    
    if ((distanceMouseOnOff<10)&&(mouseButton==true)) {
        signalOnOff = toggle(signalOnOff);
    }

    
    if ((distanceMouseSize<15)&&(mouseButton==true)) {
        if (signalOnOff) {
            ofSetColor(255, 20);
        } else {
            ofSetColor(255, 255);
        }
        lineSize = ofVec2f(0, mousePosition.y-ofGetHeight()/2);
        lineOnOff = lineSize-ofVec2f(0, (-ofGetHeight()/2+mousePosition.y)*2);
    } else {
        if (signalOnOff) {
            ofSetColor(255, 20);
        } else {
            ofSetColor(255, 100);
        }
        lineSize = lineSize;
        lineOnOff = lineOnOff;
    }
    ofRect(lineOnOff, 10, 10);
    ofCircle(lineSize, 6);
    ofLine(lineSize, lineOnOff);

    ofPushStyle();
    if (trigger) {
        ofSetColor(255, 220);
    } else {
        ofSetColor(255, 40);
    }
    ofCircle(0, 0, 4);
    ofPopStyle();
    
    

    ofPopStyle();
    
}


//--------------------------------------------------------------
bool PitchLine::toggle(bool b) {
    if (b) {
        return false;
    } else {
        return true;
    }
}
