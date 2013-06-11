#include "myApp.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
int main(){
	ofAppGlutWindow window; // create a window
	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
    window.setGlutDisplayString("rgba double samples>=4");
	ofSetupOpenGL(&window, 850, 400, OF_WINDOW);
	ofRunApp(new myApp()); // start the app
}
