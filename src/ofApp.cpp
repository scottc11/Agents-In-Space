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

    
    // buiding a collection of Agent classes
    
    for (int i = 0; i < maxAgents; i++) {
        Agent agent;
        agent.build(boxWidth, boxHeight, boxDepth);
        agents.push_back(agent);
    }
    
    
}


//--------------------------------------------------------------
void ofApp::update(){
    
    for (int i = 0; i < agents.size(); i++) {
        agents[i].update();
    }
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    for (int i = 0; i < agents.size(); i++) {
        agents[i].draw();
    }
    
    
    ofSetColor(0);
    box.drawWireframe();
    box.drawAxes(10);
    
    
    
    
}




//--------------------------------------------------------------
//          AGENT CLASS
//--------------------------------------------------------------

void Agent::build(int x, int y, int z) {
    
    containerSizeX = x;
    containerSizeY = y;
    containerSizeZ = z;
    
    noiseStrength = ofRandom(20, 60);
    noiseScale = ofRandom(100, 150);
    
    position.set(ofGetWindowWidth()/2, ofGetWindowHeight()/2, 0);
    // setRandomPosition(containerSizeX, containerSizeY, containerSizeZ);
    
    offset = 10; // use to be set at 10000
    // stepSize = ofRandom(1, 8);
    
    ribbon.build(position, int(ofRandom(50, 150)) ); // may have to change this random deleration from int to float. is expecting int
    
    
    std::cout << "-----------------" << endl;
    std::cout << "Position: " << position << endl;
    std::cout << "StepSize: " << stepSize << endl;
    std::cout << "NoiseStrength: " << noiseStrength << endl;
    std::cout << "NoiseScale: " << noiseScale << endl;
    std::cout << "-----------------" << endl;
}


void Agent::update() {
    
    
    angleY = ofNoise(position.x / noiseScale, position.y / noiseScale, position.z / noiseScale) * noiseStrength;
    
    
    // a second, random angle is needed for an agent to move in all three dimensions.
    // To produce this angle, the point at which the random number is selected is simply
    // shifted by the value of 'offset'
    
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
    
    
}



// In each step, the values are shifted on step to the right (in the array) to make
// room for the new value.  In doing this, the oldest value is overwritten / erased

void Ribbon3d::update(ofVec3f _position, bool _isGap) {
    
    line.addVertex(_position);
    
    
    // when line gets bigger than count, delete the first/end point of the line
    
    if (line.size() > count){
        line.getVertices().erase(
                                 line.getVertices().begin()
                                 );
    }
    
    
    isGapArray[0] = _isGap;
}



// DRAWING THE RIBBON

void Ribbon3d::drawLineRibbon(ofColor _strokeColor, float _width) {
    
    ofSetColor(_strokeColor);
    ofFill();
    line.draw();  // draw the line
}










