#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
//    ofGLFWWindowSettings settings;
//    settings.glVersionMajor = 3;
//    settings.glVersionMinor = 3;
//    settings.windowMode = OF_WINDOW;
//    settings.width = 1700;
//    settings.height = 960;
//    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
//    mainWindow->setWindowTitle("FAST PARTICLE SYSTEM - EXAMPLE");
//    shared_ptr<ofApp> mainApp(new ofApp);
//    
//    ofRunApp(mainWindow, mainApp);
//    ofRunMainLoop();
    
    
    ofSetupOpenGL(1700,960, OF_WINDOW);            // <-------- setup the GL context
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp( new ofApp());
}
