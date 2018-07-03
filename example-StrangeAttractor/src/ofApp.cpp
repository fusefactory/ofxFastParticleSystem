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

#include "ofApp.h"

float timestep = 0.0005;

float cameraDist        = 20.0;
float cameraRotation    = 0.0;
float rotAmount         = 0.005;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);

    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    width = ofGetWidth();
    height = ofGetHeight();
    
    cam.rotateDeg(-90, ofVec3f(1.0,0.0, 0.0));
    cam.setDistance(cameraDist);
    
    cam.setNearClip(0.1);
    cam.setFarClip(200000);
    
    fboScreen.allocate(width, height, GL_RGB);
    fboScreen.begin();
    ofClear(0.0);
    fboScreen.end();
    
    unsigned w = 2000;
    unsigned h = 1000;
    unsigned d = 5;
    
    float* particlesPosns = new float [w * h  * 4];
    particles.init(w, h, ofPrimitiveMode::OF_PRIMITIVE_POINTS, 2);
    
    // random offset for particle's initial position
    // different attractors works better with different starting offset positions
    float startOffset = 10.0;//1.5;
    
    for (unsigned y = 0; y < h; y++){
        for(unsigned x = 0; x < w; x++){
            unsigned idx = y * w + x;
            
            particlesPosns[idx * 4] =    ofRandom(-startOffset, startOffset);
            particlesPosns[idx * 4 +1] = ofRandom(-startOffset, startOffset);
            particlesPosns[idx * 4 +2] = ofRandom(-startOffset, startOffset);
            particlesPosns[idx * 4 +3] = 0;
        }
    }
    
    particles.loadDataTexture(FastParticleSystem::POSITION, particlesPosns);
    delete[] particlesPosns;
   
    particles.zeroDataTexture(FastParticleSystem::VELOCITY);

    particles.addUpdateShader("shaders/updateParticle");
    particles.addDrawShader("shaders/drawParticle");
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
    
    cam.lookAt(ofVec3f(0.0, 0.0, 0.0));
    cam.setPosition(cameraDist*sin(cameraRotation),
                    0.0,
                    cameraDist*cos(cameraRotation));
    
    cameraRotation += rotAmount;
    
    timestep = ofMap(ofGetMouseX(), 0.0, ofGetWidth(), 0.0001, 0.055);
    ofShader &shader = particles.getUpdateShader();
    shader.begin();
    
    shader.setUniform1f("timestep", timestep);
    
    shader.end();
    
    particles.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0,0,0,255);
    
    fboScreen.begin();
    ofClear(0, 0, 0);
    ofBackground(0, 0, 0);
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    glEnable(GL_PROGRAM_POINT_SIZE);
    
    cam.begin();
    
    ofShader &shader = particles.getDrawShader();
    shader.begin();
    shader.setUniformMatrix4f("modelViewProjectionMatrix", cam.getModelViewProjectionMatrix());
    shader.end();
    particles.draw();
    ofDisableBlendMode();
    
    cam.end();
    fboScreen.end();
    
    fboScreen.draw(0, 0, width, height);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
