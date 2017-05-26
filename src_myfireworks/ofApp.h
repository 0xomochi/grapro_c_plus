#pragma once

#include "ofMain.h"
#include <GLUT/GLUT.h>
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofEasyCam camera;
    ofLight light, light2;
    
    ofFloatColor light_amb, light_diff, light_spe, light2_amb;
    
    vector<ofVec3f> position;
    vector<ofVec3f> velocity;
    vector<ofFloatColor> pColor;
    
    vector<ofIndexType> indices;
    
    
    bool showGui;
    ofxPanel gui;
 

    
    ofxColorSlider particleColor;
    
     
    ofxVec3Slider light1pt;
    ofxVec3Slider light2pt;
    
    ofxButton newball;
    ofxColorSlider color;
    
    void newPressed();
    void newfirework();
  
    float slen[3];
    
    int shape;
    
    int shapeColor;
    
    ofVbo vbo;
    
    void town();
    
    vector<ofVec3f> building;
    
    vector<ofVec2f> buildhw;
    
    vector<ofColor> buildingColor;
    
    
    //niagara fall
    
    ofVbo nvbo;
    void nfall();
    vector<ofVec3f> npos;
    vector<ofVec3f> nvel;
    vector<ofFloatColor> nCol;
    vector<ofIndexType> nindices;
    bool bNfall;
    
    bool bdemo;
    void demo();
    float fwstart =0;
    
    //new ball
    
    ofVbo bvbo;
    void bball();
    vector<ofVec3f> bpos;
    vector<ofVec3f> bvel;
    vector<ofVec3f> tempbpos;
    vector<ofVec3f> tempbvel;
    
    
    vector<ofFloatColor> bCol;
    vector<ofFloatColor> tempbCol;
    vector<ofIndexType> bindices;
    
    int pBall;
    //int bNum = 100;
    bool bBall = true;
    
};

