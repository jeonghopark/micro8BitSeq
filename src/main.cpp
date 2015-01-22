#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
int main(){
    ofAppGlutWindow window; // create a window
                            // set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
                            //    window.setGlutDisplayString("rgba double samples>=4");
    ofSetupOpenGL(&window, 1280, 720, OF_WINDOW);
    ofRunApp( new ofApp());  // start the app
}

