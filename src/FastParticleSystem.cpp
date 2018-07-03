/*
 *  ofxFastParticleSytem.h
 *
 *  This file is part of the ofxFastParticleSystem [https://github.com/fusefactory/ofxFastParticleSystem]
 *  Copyright (C) 2018 Fuse srl
 * 
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *      http://www.apache.org/licenses/LICENSE-2.0
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

#include "FastParticleSystem.h"

const string FastParticleSystem::UNIFORM_PREFIX = "particles";
const string FastParticleSystem::UPDATE_SHADER = "update";
const string FastParticleSystem::DRAW_SHADER = "draw";

FastParticleSystem::FastParticleSystem() {
    currentReadFbo = 0;
}

void FastParticleSystem::init(unsigned width, unsigned height, ofPrimitiveMode primitive, unsigned numDataTextures) {
    FastParticleSystem::width = width;
    FastParticleSystem::height = height;
    
    // fbos
    ofFbo::Settings settings;
    settings.width = width;
    settings.height = height;
    settings.numColorbuffers = numDataTextures;
    settings.internalformat = GL_RGBA32F;
    settings.textureTarget = GL_TEXTURE_RECTANGLE;
    settings.minFilter = GL_NEAREST;
    settings.maxFilter = GL_NEAREST;
    settings.wrapModeHorizontal = GL_CLAMP;
    settings.wrapModeVertical = GL_CLAMP;
    for (unsigned i = 0; i < 2; ++i) {
        fbos[i].allocate(settings);
    }
    
    // mesh
    mesh.clear();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            mesh.addVertex(ofVec3f(0, 0, 0));
            mesh.addTexCoord(ofVec2f(x, y));
        }
    }
    mesh.setMode(primitive);
    
    //line mesh with reduced particles
    mesh_line.clear();
    for (int y = 0; y < height/4.0; y++) {
        for (int x = 0; x < width/4.0; x++) {
            mesh_line.addVertex(ofVec3f(0, 0, 0));
            mesh_line.addTexCoord(ofVec2f(x, y));
        }
    }
    mesh_line.setMode(primitive);

    // quad mesh
    quadMesh.addVertex(ofVec3f(-1.f, -1.f, 0.f));
    quadMesh.addVertex(ofVec3f(1.f, -1.f, 0.f));
    quadMesh.addVertex(ofVec3f(1.f, 1.f, 0.f));
    quadMesh.addVertex(ofVec3f(-1.f, 1.f, 0.f));
    
    quadMesh.addTexCoord(ofVec2f(0.f, 0.f));
    quadMesh.addTexCoord(ofVec2f(width, 0.f));
    quadMesh.addTexCoord(ofVec2f(width, height));
    quadMesh.addTexCoord(ofVec2f(0.f, height));
    
    quadMesh.addIndex(0);
    quadMesh.addIndex(1);
    quadMesh.addIndex(2);
    quadMesh.addIndex(0);
    quadMesh.addIndex(2);
    quadMesh.addIndex(3);
    
    quadMesh.setMode(OF_PRIMITIVE_TRIANGLES);
}

int FastParticleSystem::getWidth() {
    return width;
}

int FastParticleSystem::getHeight() {
    return height;
}

ofFbo &FastParticleSystem::getCurrentReadFbo() {
    return fbos[currentReadFbo];
}

ofFbo &FastParticleSystem::getCurrentWriteFbo() {
    return fbos[1 - currentReadFbo];
}

void FastParticleSystem::addUpdateShader(string shaderName, string key) {
    ofShader shader;
    shader.load(shaderName);
    updateShaders.insert({ key, shader });
}

void FastParticleSystem::addUpdateShader(string vertName, string geomName, string fragName, string key) {
    ofShader shader;
    shader.load(vertName, fragName, geomName);
    updateShaders.insert({ key, shader });
}

void FastParticleSystem::addDrawShader(string shaderName, string key) {
    ofShader shader;
    shader.load(shaderName);
    drawShaders.insert({ key, shader });
}

void FastParticleSystem::addDrawShader(ofShader &shader, string key) {
    drawShaders.insert({ key, shader });
}

void FastParticleSystem::replaceDrawShader(ofShader &shader, string key) {
    drawShaders.at(key) = shader;
}

void FastParticleSystem::addUpdateShader(ofShader &shader, string key) {
    updateShaders.insert({ key, shader });
}

void FastParticleSystem::replaceUpdateShader(ofShader &shader, string key) {
    updateShaders.at(key) = shader;
}


void FastParticleSystem::addDrawShader(string vertName, string geomName, string fragName, string key) {
    ofShader shader;
    shader.load(vertName, fragName, geomName);
    drawShaders.insert({ key, shader });
}

ofShader& FastParticleSystem::getUpdateShader(string shaderKey) {
    return updateShaders.at(shaderKey);
}

ofShader& FastParticleSystem::getDrawShader(string shaderKey) {
    return drawShaders.at(shaderKey);
}

void FastParticleSystem::loadDataTexture(unsigned index, float *data, unsigned x, unsigned y, unsigned width, unsigned height) {
    if (index < fbos[currentReadFbo].getNumTextures()) {
        if (!width) width = FastParticleSystem::width;
        if (!height) height = FastParticleSystem::height;
        fbos[currentReadFbo].getTexture(index).bind();
        glTexSubImage2D(GL_TEXTURE_RECTANGLE, 0, x, y, width, height, GL_RGBA, GL_FLOAT, data);
        fbos[currentReadFbo].getTexture(index).unbind();
    }
    else ofLogError() << "Trying to load data from array into non-existent buffer.";
}

void FastParticleSystem::zeroDataTexture(unsigned index, unsigned x, unsigned y, unsigned width, unsigned height) {
    if (!width) width = FastParticleSystem::width;
    if (!height) height = FastParticleSystem::height;
    float *zeroes = new float[width * height * FLOATS_PER_TEXEL];
    memset(zeroes, 0, sizeof(float) * width * height * FLOATS_PER_TEXEL);
    loadDataTexture(index, zeroes, x, y, width, height);
    delete[] zeroes;
}

void FastParticleSystem::setUniforms(ofShader &shader) {
    for (unsigned i = 0; i < fbos[currentReadFbo].getNumTextures(); ++i) {
        ostringstream oss;
        oss << UNIFORM_PREFIX << ofToString(i);
        shader.setUniformTexture(oss.str().c_str(), fbos[currentReadFbo].getTexture(i), i);
    }
}

void FastParticleSystem::update(string shaderKey) {
#if (OF_VERSION_MINOR == 9)
    fbos[1 - currentReadFbo].begin(false);
#else
    fbos[1 - currentReadFbo].begin(OF_FBOMODE_NODEFAULTS);
#endif
    
    glPushAttrib(GL_ENABLE_BIT);
    // we set up no camera model and ignore the modelview and projection matrices
    // in the vertex shader, we make a viewport large enough to ensure the shader
    // is executed for each pixel
    glViewport(0, 0, width, height);
    glDisable(GL_BLEND);
    ofSetColor(255);
    fbos[1 - currentReadFbo].activateAllDrawBuffers();
    
    ofShader &updateShader = updateShaders.at(shaderKey);
    updateShader.begin();
    
    setUniforms(updateShader);
    quadMesh.draw();
    updateShader.end();
    glPopAttrib();
    
    fbos[1 - currentReadFbo].end();
    
    currentReadFbo = 1 - currentReadFbo;
}

void FastParticleSystem::draw(string shaderKey, bool line) {
    ofShader &drawShader = drawShaders.at(shaderKey);
    drawShader.begin();
    
    setUniforms(drawShader);
    if(line)
        mesh_line.draw();
    else
        mesh.draw();
    drawShader.end();
}



