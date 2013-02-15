#pragma once

#include "ofMain.h"
#include "PitchLine.h"

#define NUM 8

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
    
    int speed;
    
    PitchLine *pitchLines[NUM];
    
    ofSoundPlayer samplePiano[NUM];
    string fileName;

    bool mouseClickRealease;

    ofVec2f tempoLineOnOff, tempoLineSize;

    ofVec2f mousePos, mouseDraggedPos, mouseClickPos, mouseReleasePos;
    ofVec2f preMousePosition;
    ofVec2f mousePosition;
    
    float distMouseSize, distMouseOnOff;
    
    bool mouseButton;
    bool mouseRelease;
    
    ofVec2f setSizePosition, setOnOffPosition;
    
    int firstLineDefaultLength;
    float tempoLineLength;
    float postionPitchLine;
    
    
    float highVolume;
    
    void justOneclick();
    int preMouseClick, mouseclick;    
    
};
