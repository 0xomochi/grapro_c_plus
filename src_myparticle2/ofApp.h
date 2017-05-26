#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Particle.h"

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
    
    
    bool showGui;
    ofxPanel gui;
    
    ofxFloatSlider force;
    ofxFloatSlider grav;
    ofxFloatSlider velocityx;
    ofxFloatSlider velocityy;
    
    Particle p;
    
    Particle Particles[1000];
    
    int particleNum = 1000;
    
    int activateNum = 1;
    
    AParticle AParticles[100];
    
		
};

