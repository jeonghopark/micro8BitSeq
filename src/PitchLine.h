#ifndef __emptyExample__PitchLine__
#define __emptyExample__PitchLine__

#include "ofMain.h"

class PitchLine {

private:

    float distanceMouseSize;
    float distanceMouseOnOff;

    bool toggle(bool b);

    float pitchLineDefaultLength;

public:
    
    PitchLine();
    void drawing();
  
    bool mouseButton;
    bool mouseReleaseButton;
    
    float _positionPitchLine;

    bool trigger;
    bool signalOnOff;

    ofVec2f mousePosition;
    ofVec2f lineOnOff;
    ofVec2f pitchLineSize;
    
};


#endif /* defined(__emptyExample__PitchLine__) */
