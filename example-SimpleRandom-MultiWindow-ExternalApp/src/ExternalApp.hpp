//
//  ExternalApp.hpp
//  example-SimpleRandom-Multi-Window-ExternalApp
//
//  Created by Matteo on 20/09/21.
//

#pragma once

#include "ofMain.h"

class ExternalApp : public ofBaseApp {
public:
    shared_ptr<ofAppBaseWindow> window;
    shared_ptr<ofGLRenderer> gl;

    int windowId = -1;
    ofTexture screenTex;

    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
    ofMesh screenMesh;
};
/* ExternalApp_hpp */
