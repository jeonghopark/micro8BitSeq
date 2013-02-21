#include "PitchLine.h"


PitchLine::PitchLine() {

    pitchLineDefaultLength = 100;
    lineOnOff = ofVec2f(0, -pitchLineDefaultLength);
    pitchLineSize = ofVec2f(0, pitchLineDefaultLength);
    randomOnOff = ofVec2f(0, -pitchLineDefaultLength/2);
    randomLineSize = ofVec2f(0, pitchLineDefaultLength/2);
    
    signalOnOff = false;
    triggerCount = -1;
}

void PitchLine::drawing() {

    
    ofPushStyle();

    distanceMouseOnOff = (lineOnOff+ofVec2f(_positionPitchLine, ofGetHeight()/2)).distance(mousePosition);
    distanceMouseSize = (pitchLineSize+ofVec2f(_positionPitchLine, ofGetHeight()/2)).distance(mousePosition);
    distanceMouseRandomOnOff = (randomOnOff+ofVec2f(_positionPitchLine, ofGetHeight()/2)).distance(mousePosition);

    if ((distanceMouseRandomOnOff<10)&&(mouseButton==true)) {
        randomOnOff = ofVec2f(0, mousePosition.y-ofGetHeight()/2);
    } else {
        randomOnOff = randomOnOff;
    }

    if ((distanceMouseOnOff<10)&&(mouseReleaseButton==true)) {
        signalOnOff = toggle(signalOnOff);
    }


    if (((distanceMouseRandomOnOff<10)||(distanceMouseSize<10))&&(mouseButton==true)) {
        if (signalOnOff) {
            ofSetColor(255, 255, 255, 20);
        } else {
            ofSetColor(255, 255, 255, 255);
        }
    } else {
        if (signalOnOff) {
            ofSetColor(255, 255, 255, 20);
        } else {
            ofSetColor(255, 255, 255, 100);
        }
    }
    
    if ((distanceMouseSize<10)&&(mouseButton==true)) {
        pitchLineSize = ofVec2f(0, mousePosition.y-ofGetHeight()/2);
        lineOnOff = pitchLineSize-ofVec2f(0, (-ofGetHeight()/2+mousePosition.y)*2);
    } else {
        pitchLineSize = pitchLineSize;
        lineOnOff = lineOnOff;
    }


    
    
    ofRect(lineOnOff, 5, 5);
//    ofTriangle(randomOnOff+ofVec2f(0,-3), randomOnOff+ofVec2f(-3,2), randomOnOff+ofVec2f(3,2));
//    ofTriangle(randomLineSize+ofVec2f(0,3), randomLineSize+ofVec2f(-3,-2), randomLineSize+ofVec2f(3,-2));
    ofCircle(pitchLineSize, 3);
    ofLine(pitchLineSize, lineOnOff);

    ofPushStyle();
    if (trigger) {
        ofSetColor(255, 255, 255, 220);
    } else {
        ofSetColor(255, 255, 255, 40);
    }
    ofCircle(0, 0, 3);
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
