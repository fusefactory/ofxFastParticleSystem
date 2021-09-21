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
#include "ExternalApp.hpp"

//========================================================================
int main( ){
    //hardcoded
    ofVec2f windowSize(1920, 1080);

    ofGLFWWindowSettings settings;
    settings.glVersionMajor = 3;
    settings.glVersionMinor = 3;
    settings.windowMode = OF_WINDOW;
    #if (OF_VERSION_MINOR == 9)
    settings.width = windowSize.x  / 2.0f;
    settings.height = windowSize.y  / 2.0f;
    #else
    settings.setSize(windowSize.x / 2.0f, windowSize.y  / 2.0f);
    #endif
    
    //MAIN WINDOW
    shared_ptr<ofAppBaseWindow> mainWindow = ofGetMainLoop()->createWindow(settings);
    mainWindow->setWindowTitle("example-SimpleRandom-MultiWindow-ExternalApp | MAIN SCREEN");
    
    //external settings settings
    settings.shareContextWith = mainWindow;
    settings.resizable = false;

    #if (OF_VERSION_MINOR == 9)
    settings.width = EXTERNAL_WINDOW_WIDTH;
    settings.height = windowSize.y;
    #else
    settings.setSize(EXTERNAL_WINDOW_WIDTH, windowSize.y);
    #endif
    
    //EXTERNAL WINDOW
    shared_ptr<ofAppBaseWindow> windowExt = ofCreateWindow(settings);
    windowExt->setWindowTitle("example-SimpleRandom-MultiWindow-ExternalApp | EXTERNAL SCREEN");
    windowExt->setWindowPosition(windowSize.x, 0);
    
    shared_ptr<ofApp> mainApp(new ofApp);
    shared_ptr<ExternalApp> externalApp(new ExternalApp);
    mainApp->windowSize = windowSize;

    ofRunApp(mainWindow, mainApp);          //execute setup
    ofRunApp(windowExt, externalApp);
    
    externalApp->gl = static_pointer_cast<ofGLRenderer>(windowExt->renderer());
    externalApp->screenTex = mainApp->mainFbo.getTexture();
    externalApp->windowId = 1;
    
    ofRunMainLoop();
}
