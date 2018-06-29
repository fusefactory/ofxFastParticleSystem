/*
 *  FastParticleSystem.h
 *
 *  Copyright (c) 2018, fuse*, http://fuseworks.it/
 *  All rights reserved. 
 *  
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions are met: 
 *  
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer. 
 *  * Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 *  * Neither the name of Neil Mendoza nor the names of its contributors may be used 
 *    to endorse or promote products derived from this software without 
 *    specific prior written permission. 
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 *  POSSIBILITY OF SUCH DAMAGE. 
 *
 */

#ifndef FastParticleSystem_h
#define FastParticleSystem_h

#include "ofMain.h"

class FastParticleSystem {
    
public:
    static const string UNIFORM_PREFIX;
    static const string UPDATE_SHADER;
    static const string DRAW_SHADER;
    static const unsigned FLOATS_PER_TEXEL = 4;
    
    enum DataTextureIndex
    {
        POSITION,   // 0
        VELOCITY,   // 1
    };
    
    struct FastShader {
        string key;
        ofShader shader;
    };
    
    FastParticleSystem();
    void init(unsigned width, unsigned height, ofPrimitiveMode primitive = OF_PRIMITIVE_POINTS, unsigned numDataTextures = 2);
    void update(string shaderKey = UPDATE_SHADER);
    void draw(string shaderKey = DRAW_SHADER, bool line = false);
    ofVboMesh &getMesh() { return mesh; }
    int getWidth();
    int getHeight();
    
    void addUpdateShader(string shaderName, string key = UPDATE_SHADER);
    void addUpdateShader(string vertName, string geomName, string fragName, string key = UPDATE_SHADER);
    void addDrawShader(string shaderName, string key = DRAW_SHADER);
    void addDrawShader(string vertName, string geomName, string fragName, string key = DRAW_SHADER);

    void addDrawShader(ofShader &shader, string key);
    void replaceDrawShader(ofShader &shader, string key);
    
    void addUpdateShader(ofShader &shader, string key);
    void replaceUpdateShader(ofShader &shader, string key);
    
    void loadDataTexture(unsigned index, float *data, unsigned x = 0, unsigned y = 0, unsigned width = 0, unsigned height = 0);
    void zeroDataTexture(unsigned index, unsigned x = 0, unsigned y = 0, unsigned width = 0, unsigned height = 0);
    
    ofFbo &getCurrentReadFbo();
    ofFbo &getCurrentWriteFbo();
    
    ofShader &getUpdateShader(string shaderKey = UPDATE_SHADER);
    ofShader &getDrawShader(string shaderKey = DRAW_SHADER);
    
private:
    unsigned width, height;
    
    ofFbo fbos[2];
    unsigned currentReadFbo;
    
    ofVboMesh mesh;
    ofVboMesh mesh_line;
    ofVboMesh quadMesh;
    
    map<string, ofShader> updateShaders;
    map<string, ofShader> drawShaders;
    
    void setUniforms(ofShader &shader);
};

#endif /* FastParticleSystem_h */
