//
//  This file is part of the ofxFastParticleSystem [https://github.com/fusefactory/ofxFastParticleSystem]
//  Copyright (C) 2018 Fuse srl
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    //hardcodec
    ofVec2f windowSize(1920, 1080);

    
    ofGLFWWindowSettings settings;
    settings.glVersionMajor = 3;
    settings.glVersionMinor = 3;
    settings.windowMode = OF_WINDOW;
    #if (OF_VERSION_MINOR == 9)
    settings.width = windowSize.x;
    settings.height = windowSize.y;
    #else
    settings.setSize(windowSize.x, windowSize.y);
    #endif
    
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    mainWindow->setWindowTitle("MAIN SCREEN");
    shared_ptr<ofApp> mainApp(new ofApp);
    mainApp->windowSize.x = windowSize.x;
    mainApp->windowSize.y = windowSize.y;

    //external screen
    #if (OF_VERSION_MINOR == 9)
    settings.width = EXTERNAL_WINDOW_WIDTH;
    settings.height = windowSize.y;
    #else
    settings.setSize(EXTERNAL_WINDOW_WIDTH, windowSize.y);
    #endif
    settings.shareContextWith = mainWindow;
    settings.resizable = false;
    settings.decorated = true;
    
    shared_ptr<ofAppBaseWindow> externalWindow = ofCreateWindow(settings);
    externalWindow->setWindowTitle("EXTERNAL SCREEN");
    externalWindow->setWindowPosition(windowSize.x, 0);
    ofAddListener(externalWindow->events().draw, mainApp.get(), &ofApp::drawExternalScreen);

    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
}
