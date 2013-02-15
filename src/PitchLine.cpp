#include "PitchLine.h"


PitchLine::PitchLine() {

    pitchLineDefaultLength = 200;
    lineOnOff = ofVec2f(0, -pitchLineDefaultLength);
    pitchLineSize = ofVec2f(0, pitchLineDefaultLength);
    
    signalOnOff = false;
}

void PitchLine::drawing() {

    
    ofPushStyle();

    distanceMouseOnOff = (lineOnOff+ofVec2f(_positionPitchLine, ofGetHeight()/2)).distance(mousePosition);

    distanceMouseSize = (pitchLineSize+ofVec2f(_positionPitchLine, ofGetHeight()/2)).distance(mousePosition);
    
    if ((distanceMouseOnOff<10)&&(mouseReleaseButton==true)) {
        signalOnOff = toggle(signalOnOff);
    }

    
    if ((distanceMouseSize<15)&&(mouseButton==true)) {
        if (signalOnOff) {
            ofSetColor(255, 20);
        } else {
            ofSetColor(255, 255);
        }
        pitchLineSize = ofVec2f(0, mousePosition.y-ofGetHeight()/2);
        lineOnOff = pitchLineSize-ofVec2f(0, (-ofGetHeight()/2+mousePosition.y)*2);
    } else {
        if (signalOnOff) {
            ofSetColor(255, 20);
        } else {
            ofSetColor(255, 100);
        }
        pitchLineSize = pitchLineSize;
        lineOnOff = lineOnOff;
    }
    ofRect(lineOnOff, 10, 10);
    ofCircle(pitchLineSize, 6);
    ofLine(pitchLineSize, lineOnOff);

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
