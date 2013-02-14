

#include "PitchLine.h"


PitchLine::PitchLine() {
    pitchLineDefaultLength = 100;
    lineOnOff = ofVec2f(0, -pitchLineDefaultLength);
    lineSize = ofVec2f(0, pitchLineDefaultLength);

}

void PitchLine::drawing() {
    ofPushStyle();
    distMouseSize2 = (lineSize+ofVec2f(_positionPitchLine, ofGetHeight()/2)).distance(mousePosition);
    if ((distMouseSize2<8)&&(mouseButton==true)) {
        ofSetColor(255, 255);
        lineSize = ofVec2f(0, mousePosition.y-ofGetHeight()/2);
        lineOnOff = lineSize-ofVec2f(0, (-ofGetHeight()/2+mousePosition.y)*2);
    } else {
        ofSetColor(255, 100);
        lineSize = lineSize;
        lineOnOff = lineOnOff;
    }
    ofRect(lineOnOff, 10, 10);
    ofCircle(lineSize, 6);
    ofLine(lineSize, lineOnOff);
    ofPopStyle();
    
}