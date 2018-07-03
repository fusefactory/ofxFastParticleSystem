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
    ofGLFWWindowSettings settings;
    settings.setGLVersion(4, 1);
#if (OF_VERSION_MINOR == 9)
    settings.width = 1920;
    settings.height = 1080;
#else
    settings.setSize(1920, 1080);
#endif
    settings.numSamples = 4;

    ofCreateWindow(settings);
    
    ofRunApp(new ofApp());
}
