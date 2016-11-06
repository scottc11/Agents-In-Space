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
    void clear();
    
    
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
    void build(int _width, int _height, int _depth, ofVec3f _origin);
    void draw();
    void setRandomPosition();
    
    // PRESET VARIABLES which alter the agent  based on their values
    float noiseStrength;  // sketch default 20
    float noiseScale;  // sketch default: 150
    
    // the same as box size variables in ofApp variable decloration
    int containerWidth;
    int containerHeight;
    int containerDepth;
    ofVec3f containerOrigin;
    
    bool isOutside = false;
    ofVec3f position;
    
    float offset;
    float stepSize = 1; // how fast things happen
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
    
    // AGENTS
    int maxAgents = 30;
    vector <Agent> agents;
    Agent newAgent;
		
};

