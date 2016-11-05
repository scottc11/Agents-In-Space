#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(77);
    
    ofEnableDepthTest();
    
    std::cout << "Window Width: " << ofGetWindowWidth() << "   Window Height: " << ofGetWindowHeight() << endl;
    newAgent.build(boxWidth, boxHeight, boxDepth);
    
    
    // Creating the container/box
    
    box.set(boxWidth, boxHeight, boxDepth, resolution, resolution, resolution);
    box.setPosition(ofGetWindowWidth()/2, ofGetWindowHeight()/2, 0);
    box.pan(30); // roating the box 30 degrees to the right (on an angle)
    
    std::cout << "---------------" << endl;
    std::cout << "Box Centre Axis: " << box.getPosition() << endl;
    std::cout << "Box Size: " << box.getSize() << endl;
    std::cout << "Box Global Transform Matrix: " << &box.getMesh() << endl;

    
    
}


//--------------------------------------------------------------
void ofApp::update(){
    newAgent.update();
    
    
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    newAgent.draw();
    
    
    
    // box.drawWireframe();
    // box.drawAxes(10);
    
    
    
    
}




//--------------------------------------------------------------
//          AGENT CLASS
//--------------------------------------------------------------

void Agent::build(int x, int y, int z) {
    
    containerSizeX = x;
    containerSizeY = y;
    containerSizeZ = z;
    
    position.set(ofGetWindowWidth()/2, ofGetWindowHeight()/2, 0);
    // setRandomPosition(containerSizeX, containerSizeY, containerSizeZ);
    
    offset = 10; // use to be set at 10000
    // stepSize = ofRandom(1, 8);
    
    ribbon.build(position, int(ofRandom(50, 150)) ); // may have to change this random deleration from int to float. is expecting int
    
    
    
    std::cout << "Position: " << position << endl;
    std::cout << "StepSize: " << stepSize << endl;
}


void Agent::update() {
    
    angleY = ofNoise(position.x / noiseScale, position.y / noiseScale, position.z / noiseScale) * noiseStrength;
    //
    // a second, random angle is needed for an agent to move in all three dimensions.
    // To produce this agnle, the point at which the random number is selected is simply
    // shifted by the value of 'offset'
    //
    angleZ = ofNoise( (position.x / noiseScale) + offset, position.y / noiseScale, position.z / noiseScale) * noiseStrength;
    
    
    // the new point of the agent is defined by the two angles 'angleY' and 'angleZ'
    position.x += cos(angleZ) * cos(angleY) * stepSize;
    position.y += sin(angleZ) * stepSize;
    position.z += cos(angleZ) * sin(angleY) * stepSize;
    
    
    // checking to see if agent is outside of the given container dimensions (not window)
    /*
    if (position.x<0 || position.x>containerSizeX ||
        position.y<0 || position.y>containerSizeY ||
        position.z<0 || position.z>containerSizeZ ) {
        
        setRandomPosition(containerSizeX, containerSizeY, containerSizeZ);
        isOutside = true;
    }
    */
    
    ribbon.update(position, isOutside);
    isOutside = false;
    
}


void Agent::draw() {
    ribbon.drawLineRibbon(ofColor(255), 2.0);
}


void Agent::setRandomPosition(int x, int y, int z) {
    position.set(ofRandom(0, x), ofRandom(0, y), ofRandom(0, z));
    
}





//--------------------------------------------------------------
//          RIBBON CLASS
//--------------------------------------------------------------



void Ribbon3d::build(ofVec3f _position, int _count) {
    
    count = _count;
    positionArray.resize(count); // init array with predifined size (count is size)
    isGapArray.resize(count); // init array with predifined size (count is size)
    
    // declare the location for every ofVec3f point in the ribbon
    for (int i = 0; i < count; i++) {
        positionArray[i] = ofVec3f(_position.x, _position.y, _position.z);
        isGapArray[i] = false;
    }
    
}



// In each step, the values are shifted on step to the right (in the array) to make
// room for the new value.  In doing this, the oldest value is overwritten / erased

void Ribbon3d::update(ofVec3f _position, bool _isGap) {
    
    /*
    for (int i = count-1; i > 0; i--) {
        
        positionArray[i].set(positionArray[i-1]);// setting the ofVec3f object to previous one
        
        isGapArray[i] = isGapArray[i-1];
    }
    */
    
    if (line.size() > count){
        line.getVertices().erase(
                                 line.getVertices().begin()
                                 );
    }
    
    // setting new value to beggining of array
    positionArray[0].set(_position);
    isGapArray[0] = _isGap;
}



// DRAWING THE RIBBON

void Ribbon3d::drawLineRibbon(ofColor _strokeColor, float _width) {
    
    for (int i = 0; i < count; i++) {
        line.addVertex(positionArray[i]);  // add a point to the end of the line from positionsArray
        if (isGapArray[i] == true) {
            line.clear();  // if a point is outside the container, delete all points in line and start again
        }
    }
    ofSetColor(_strokeColor);
    ofFill();
    line.draw();  // draw the line
}










