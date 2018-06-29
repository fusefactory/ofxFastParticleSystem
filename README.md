# ofxFastParticleSystem

OpenFrameworks addon with _heavily opiniated_ tools for working with remote Depth Sensor streams.

## What?

This is a suit of tools to work with multiple (different) depth sensors like the Kinect, the Orbbecs (Persee, Astra and Astra-mini) and -soon- the Intel RealSense.


##### What about OpenNI??

OpenNI provides a uniform API for working with various depth sensors and is used in some of the applications in this repository. The aim of this package is to provide high-level tools and instructions to work with remote depth sensors streaming over a network (currently using TCP).



## Instructions

#### Build and run a remote Server
See the ```./tools``` folder for various server (transmitter) applications for various platforms/sensors.
Each tool has its own README;
 * [KinectForWindows2](tools/KinectForWindows2/README.md)
 * [OrbbecAstraTransmitter](tools/OrbbecAstraTransmitter/README.md)
 * [OrbbecPerseeTransmitter](tools/OrbbecPerseeTransmitter/README.md)

#### Build and run a local Client
This OpenFrameworks addon tailors only to streaming _clients_ (receivers), try
any of the example applications:

```cd``` into one of the example application's folders and run:
```bash
make Debug # to build the applications
make RunDebug # to run the last development-build
```

## SDK Usage
See also the [API (doxygen) documentation](https://fusefactory.github.io/ofxDepthStream/docs/html/hierarchy.html)

#### Basic Usage
See also the example applications

```c++
#include "ofxDepthStream/ofxDepthStream.h"

std::shared_ptr<depth::Receiver> receiverRef;
ofTexture depthTexture;
ofMesh mesh1;

void ofApp::setup() {
   // Create depth stream network receiver (takes a hostname/ip string and port number)
   // this receiver instance will start a separate thread in which it listens for new frame data
   receiverRef = depth::Receiver::createAndStart("persee.local", 4445);
}

void ofApp::update() {
  // this addons provides some convenience methods for;
  // ...processing raw frame byte data (which is compressed for network streaming)
  depth::emptyAndInflateBuffer(*receiverRef, [this](const void* data, size_t size){

    // ...loading texture data
    ofxDepthStream::loadDepthTexture(this->depthTexture, data, size);

    // ...loading mesh data
    ofxDepthStream::loadMesh(this->mesh1, data, size);
  }
}

void ofApp::draw() {
  if(depthTexture.isAllocated()) {
    depthTexture.draw(0,0);
  }

  mesh1.draw();
}

```
#### Run unit tests
From this addon's root folder;
```shell
cd tests
make Debug
make RunDebug
```

## Screenshots
![Clients](screenshots/DualStreamOrbbecKinect2.png "Dual Stream with Orbbec [left] and Kinect [right] and")
_streaming two sensors over a network; orbbec left, kinect right_
