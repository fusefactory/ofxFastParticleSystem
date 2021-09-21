//
//  ExternalApp.cpp
//  example-SimpleRandom-Multi-Window-ExternalApp
//
//  Created by Matteo on 20/09/21.
//

#include "ExternalApp.hpp"

//--------------------------------------------------------------
void ExternalApp::setup() {

    ofSetFrameRate(60);
    ofSetVerticalSync(true);

    float w = 1920;
    float h = 1080;

    cout << "=====================" << endl;
    cout << "ExternalApp: " << w << ", " << h << endl;
    cout << "=====================" << endl;

    ofBackground(0);

    screenMesh.clear();

    screenMesh.addVertex(ofPoint(0, 0));
    screenMesh.addTexCoord(ofVec2f(0, 0));

    screenMesh.addVertex(ofPoint(w, 0));
    screenMesh.addTexCoord(ofVec2f(w, 0));

    screenMesh.addVertex(ofPoint(w, h));
    screenMesh.addTexCoord(ofVec2f(w, h));

    screenMesh.addVertex(ofPoint(0, h));
    screenMesh.addTexCoord(ofVec2f(0, h));

    screenMesh.addIndex(0);
    screenMesh.addIndex(1);
    screenMesh.addIndex(2);

    screenMesh.addIndex(0);
    screenMesh.addIndex(2);
    screenMesh.addIndex(3);
}

//--------------------------------------------------------------
void ExternalApp::update() {

}

//--------------------------------------------------------------
void ExternalApp::draw() {
    ofBackground(255, 0 ,0);
    ofSetColor(255);

    screenTex.bind();
    screenMesh.draw();
    screenTex.unbind();
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 100, 100, ofColor(255, 0, 0), ofColor(0));
}

//--------------------------------------------------------------
void ExternalApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ExternalApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ExternalApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ExternalApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ExternalApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ExternalApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ExternalApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ExternalApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ExternalApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ExternalApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ExternalApp::dragEvent(ofDragInfo dragInfo) {

}
