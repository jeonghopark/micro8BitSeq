

#ifndef __emptyExample__PitchLine__
#define __emptyExample__PitchLine__

#include "ofMain.h"


class PitchLine {
  
public:
    
    PitchLine();
    void drawing();
  
    float distMouseSize2;
    
    bool mouseButton;
    
    
    float _positionPitchLine;

    ofVec2f mousePosition;
    float pitchLineDefaultLength;
    ofVec2f lineOnOff;
    ofVec2f lineSize;

    bool trigger;
    
};


#endif /* defined(__emptyExample__PitchLine__) */
