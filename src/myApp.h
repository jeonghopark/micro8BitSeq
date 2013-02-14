#pragma once

#include "ofMain.h"

#include "PitchLine.h"

class myApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        bool toggle (bool b);
    
    void lineStructure(float _positionPitchLine);
    
    PitchLine *firstLine;
    PitchLine *secondLine;
    PitchLine *thirdLine;
    PitchLine *forthLine;
    PitchLine *fifthLine;
    PitchLine *sixthLine;
    PitchLine *seventhLine;
    PitchLine *eighthLine;
    
    
    // new Sound Player
    ofSoundPlayer piano1;
    ofSoundPlayer piano2;
    ofSoundPlayer piano3;
    ofSoundPlayer piano4;
    ofSoundPlayer piano5;
    ofSoundPlayer piano6;
    ofSoundPlayer piano7;
    ofSoundPlayer piano8;


};
