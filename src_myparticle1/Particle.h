//
//  Particle.hpp
//  myGoodSketch0
//
//  Created by k on 2016/06/17.
//
//

#ifndef Particle_h
#define Particle_h

#include <stdio.h>

#endif /* Particle_h*/

#pragma once
#include "ofMain.h"

class Particle{
    
public:
    void update();
    void draw();
    void init();

    
    void getMousePos(int _x, int  _y);
    int mousePosX, mousePosY;
    void towardMousePos();
    
    
    Particle();
    
    ofVec2f pos;
    ofVec2f toward;
    ofVec2f towardMouse;
    
    ofVec2f initial;
    
    
    ofVec2f gravity;
 
    ofVec2f initver;
    
    float force =10000;
    
    
    float reflex =1;
    
    float radius =0;
    
    bool bsoft = false;
    
    int boundnum=0;
    
    bool state = false;

    int towardMouseCount = 0;
    

};
