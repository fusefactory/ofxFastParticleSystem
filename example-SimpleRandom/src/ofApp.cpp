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

const string CIRCLE = "circle";

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0);
    ofSetFrameRate(60);
    
//    ofSetLogLevel(OF_LOG_VERBOSE);
    
    //number of particles
    unsigned w = 1000;
    unsigned h = 1000;
    
    particles.init(w, h, ofPrimitiveMode::OF_PRIMITIVE_POINTS, 2);

    //POSITIONS
    float* particlePosns = new float[w * h * 4];
    for (unsigned y = 0; y < h; ++y)
    {
        for (unsigned x = 0; x < w; ++x)
        {
            unsigned idx = y * w + x;
            particlePosns[idx * 4] =     ofRandom(ofGetWidth());
            particlePosns[idx * 4 + 1] = ofRandom(ofGetHeight());
            particlePosns[idx * 4 + 2] = 0.f;
            particlePosns[idx * 4 + 3] = 0.f;
        }
    }
    particles.loadDataTexture(FastParticleSystem::POSITION, particlePosns);
    delete[] particlePosns;
    
    //VELOCITIES
    float* velocities = new float [w * h * 4];
    for (unsigned y = 0; y < h; y++){
        for(unsigned x = 0; x < w; x++){
            unsigned idx = y * w + x;
            velocities[idx * 4] =    ofRandom(-1.5, 1.5);
            velocities[idx * 4 +1] = ofRandom(-1.5, 1.5);
            velocities[idx * 4 +2] = 0;
            velocities[idx * 4 +3] = 0;
        }
    }
    particles.loadDataTexture(FastParticleSystem::VELOCITY, velocities);
    delete[] velocities;
    
    //update shaders
    particles.addUpdateShader("shaders/updateParticlesRandom");
    particles.addUpdateShader("shaders/updateParticlesCircle", CIRCLE);
    
    //draw shader
    particles.addDrawShader("shaders/drawParticles");
    
    //MATRIX
    projection.makeIdentityMatrix();
    projection.set(ofGetCurrentMatrix(OF_MATRIX_PROJECTION));
    projection.preMult(ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
    
    modelView.makeIdentityMatrix();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    switch (shaderId) {
        case 0:{
            ofShader &shader = particles.getUpdateShader();
            shader.begin();
            shader.setUniform1f("maxSpeed", 1.2);
            shader.setUniform1f("width", ofGetWidth());
            shader.setUniform1f("height", ofGetHeight());
            
            shader.end();
            
            particles.update();
            break;
        }
        case 1:{
            ofShader &shader = particles.getUpdateShader(CIRCLE);
            shader.begin();
            shader.setUniform2f("center", ofGetWidth() / 2.0, ofGetHeight() / 2.0);
            shader.setUniform1f("radius", 300);
            shader.setUniform1f("centerStiffness", 0.01);
            shader.setUniform1f("maxSpeed", 20);
            
            shader.end();
            
            particles.update(CIRCLE);
        }
            
        default:
            break;
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    ofShader &shader = particles.getDrawShader();
    shader.begin();
    shader.setUniformMatrix4f("projection", projection);
    shader.setUniformMatrix4f("modelview", modelView);
    shader.end();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_PROGRAM_POINT_SIZE);
    particles.draw();
    glDisable(GL_PROGRAM_POINT_SIZE);
    glDisable(GL_BLEND);
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 100, 100, ofColor(255, 0, 0), ofColor(0));
    ofDrawBitmapStringHighlight("Press '0' or '1' to switch shader update", 100, 150, ofColor(255, 0, 0), ofColor(0));
    ofDrawBitmapStringHighlight("Current shader update: " + ofToString(shaderId), 100, 200, ofColor(255, 0, 0), ofColor(0));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '0') shaderId = 0;
    else if (key == '1') shaderId = 1;
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
