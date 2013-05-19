#pragma once

#include "ofMain.h"
#include "PitchLine.h"
#include "WavFile.h"

#define NUM 8


typedef struct
{
	ofVec2f position;
	bool 	bSizeBeingDragged;
	bool 	bOnOffBeingClick;
	bool 	bSizeOver;
	bool 	bOnOffOver;
	float 	width;
    ofVec2f onOffRect;
    ofVec2f sizeRect;
    ofVec2f sizeRectStart;
    bool onOffTrigger;
    bool soundTrigger;
    int counter;
    ofSoundPlayer samplePlay;
}
controlElementLine;

typedef struct
{
	ofVec2f position;
	bool 	bSizeBeingDragged;
	bool 	bOnOffBeingClick;
	bool 	bSizeOver;
	bool 	bOnOffOver;
	float 	width;
    ofVec2f onOffRectPos;
    ofVec2f sizeRectPos;
    ofVec2f sizeRectStart;
    float length;
}
controlTempoLine;


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
    
    ofSoundPlayer samplePiano[NUM];
    PitchLine *pitchLines[NUM];
    
    string fileName;
    
    bool mouseClickRealease;
    
    ofVec2f tempoLineOnOffPos, tempoLinesizeRect;
    
    ofVec2f mousePos, mouseDraggedPos, mouseClickPos, mouseReleasePos;
    ofVec2f preMousePosition;
    ofVec2f mousePosition;
    
    float distMouseSize, distMouseOnOff;
    
    bool mouseButton;
    bool mouseRelease;
    
    ofVec2f setsizeRectition, setOnOffPosition;
    
    int firstLineDefaultLength;
    float tempoLineLength;
    float postionPitchLine;
    
    
    float highVolume;
    
    void justOneclick();
    int preMouseClick, mouseclick;
    
    int triggerCount;
    
    void audioIn(float * input, int bufferSize, int nChannels);
    
    int	initialBufferSize;
	int	sampleRate;
	int	drawCounter;
    int bufferCounter;
	float * buffer;
    
    WavFile myWavWriter;
    ofSoundStream soundStream;
	bool bIsRecording;
    //	int   sampleRate;
    //	float           * buffer;
	int channels;
    int recordState=0;
    
    
    int tempoLineDefaultLength;
    int nElementLine;
    controlElementLine elementLines[8];
    
    float spaceLine;
    int timeCount;
    
    controlTempoLine tempoLine;
    

    vector <ofSoundPlayer> draggedSound;
    ofPoint dragPt;

    
};
