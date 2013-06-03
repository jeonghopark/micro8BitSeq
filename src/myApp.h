#pragma once

#include "ofMain.h"
#include "WavFile.h"

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
    int triggerColor;
}
controlElementLine;

typedef struct
{
	ofVec2f position;
	ofVec2f oldPosition;
	bool 	bSizeBeingDragged;
	bool 	bOnOffBeingClick;
	bool 	bSizeOver;
	bool 	bOnOffOver;
	float 	width;
    ofVec2f onOffRectPos;
    ofVec2f sizeRectPos;
    ofVec2f sizeRectStart;
    float length;
    ofVec2f delayPos;
	bool 	bDelayPosOver;
    bool    bDelayPosDragged;
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
    
    void threadedFunction();
    
    bool inOutCal(float x, float y, ofVec2f xyN, int distSize);
    bool onOffOut(float x, float y, ofVec2f xyN, int distSize, bool _b);
    
    int speedUp;
    int speedDown;
    
    string fileNameUp;
    string fileNameDown;
    
    float highVolume;
    
    void audioIn(float * input, int bufferSize, int nChannels);
    
    int	initialBufferSize;
	int	sampleRate;
	int	drawCounter;
    int bufferCounter;
	float * buffer;
    
    WavFile myWavWriter;
    ofSoundStream soundStream;
	bool bIsRecording;
	int channels;
    int recordState=0;
    
    int nElementLine;
    controlElementLine elementLinesDown[8];
    controlElementLine elementLinesUp[8];
    
    float spacingLineDown;
    float spacingLineUp;
    
    controlTempoLine tempoLineDown;
    controlTempoLine tempoLineUp;

    vector <ofSoundPlayer> draggedSound;
    ofPoint dragPt;
    
    int backgroundColorHue;
    
    int tempoLineRelativePos;
    
    int tempoDistanceFactor;
    
    int triggerCounterUp;
    int triggerCounterDown;
    
    int millisUp;
    int millisDown;
    bool bangUp;
    bool bangDown;
    
    

    ofDirectory dir;
    vector<ofSoundPlayer> soundsList;
    
    int currentSound;
    
    void drawingTempoLine(bool _bTOnOff, bool _bTSizeOver, bool _bTOnOffOver, ofVec2f _vTSizePos, ofVec2f _vTOnOffPos);

};
