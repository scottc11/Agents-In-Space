#pragma once

#include "ofMain.h"


//--------------------------------------------------------------
//          RIBBON CLASS
//--------------------------------------------------------------

// each 'ribbon' has a certain size/length to it, which is determined by
// the 'count' variable.  Each time a new ribbon is intantiated, the 'count'
// variable is randomized.
// the 'count' variable effects the length/size of the two arrays within the
// ribbon class (ie. 'isGapArray', 'positionArray')


class Ribbon3d {
public:
    void build(ofVec3f _position, int _count);
    void update(ofVec3f _position, bool _isGap);
    void drawLineRibbon(ofColor _strokeColor, float _width);
    
    
    int count; // how many previous positions are saved to arrays
    vector <ofVec3f> positionArray;
    vector <bool> isGapArray;
    
    ofPolyline line;
    
};


//--------------------------------------------------------------
//          AGENT CLASS
//--------------------------------------------------------------

// the agent class represents the 'starting point' for each 'ribon class'
// there is one ribbon for every agent (i think.)

class Agent {
public:
    void update();
    void build(int x, int y, int z);
    void draw();
    void setRandomPosition(int x, int y, int z);
    
    // PRESET VARIABLES which alter the sketch based on their values
    float noiseStrength = 20;
    float noiseScale = 150;
    
    // the same as spazeSize variable in ofApp variable decloration
    int containerSizeX;
    int containerSizeY;
    int containerSizeZ;
    
    bool isOutside = false;
    ofVec3f position;
    
    float offset;
    float stepSize = 2; // how fast things happen
    float angleY;
    float angleZ; // random angle needed for agent to move in 3 dimensions
    
    
    // declare the ribbon class
    Ribbon3d ribbon;
    
};


//--------------------------------------------------------------
//          OPENFRAMEWORKS APPLICATION
//--------------------------------------------------------------

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

    
    // ofBoxPrimitive to contain the agents being drawn.
    
    ofBoxPrimitive box;
    
    float boxWidth = 300;
    float boxHeight = 400;
    float boxDepth = 300;
    
    int resolution = 1;  // how many points are used to create shape

    
    Agent newAgent;
		
};

