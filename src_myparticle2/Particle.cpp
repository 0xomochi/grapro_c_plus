//
//  Particle.cpp
//  myGoodSketch0
//
//  Created by k on 2016/06/17.
//
//

#include "Particle.h"

#include "ofApp.h"

Particle::Particle(){


 
    pos.x = ofRandom(0, ofGetWidth());
    pos.y = ofRandom(0, ofGetHeight());


    toward.x = ofRandom(-initver.x, initver.x);
    toward.y = ofRandom(-initver.y, initver.y);
    
    
    
    gravity.x=0;
//    gravity.y=0.6;
//    gravity.y=0.0;

radius = ofRandom(10,20);

}

void Particle::init(){
    pos.x = ofRandom(0, ofGetWidth());
    pos.y = ofRandom(0, ofGetHeight());
    
    
    toward.x = ofRandom(-initver.x, initver.x);
    toward.y = ofRandom(-initver.y, initver.y);
    
    
    
//    gravity.x=0;
//    gravity.y=0.6;
//    gravity.y=0.0;
    
    radius = ofRandom(10,20);
    
    bsoft=false;
}


void Particle::update(){
    
    pos.x += toward.x;
 
    toward.y += gravity.y;
    pos.y += toward.y;
    

    boundnum=0;
    
    if (bsoft) {
        reflex=0.9;
    }else reflex=1;

/*
    if( pos.x <0 || pos.x > ofGetWidth() ){
        toward.x= -toward.x;
    }
  
*/
    
    if(pos.x <0) pos.x=ofGetWidth();
    if(pos.x> ofGetWidth()) pos.x=0;
  
    
  // reflex
//    if(pos.y<0 || pos.y > ofGetHeight() ){
    
  
    if(pos.y<0 )
    {
        toward.y = -toward.y;
    
  }

    
    boundnum = 0;
    
    
    if(pos.y > ofGetHeight()){

        float j= -abs(toward.y);
  //      toward.y= -abs(reflex*toward.y);
        
        if (j*toward.y<0) {
//            if(j<-25.3)boundnum=1;
//            if(j<-20)boundnum=1;
            if(j<-5)boundnum=1;
            j=reflex*j;
        }
        
        toward.y=j;
        
        if (gravity.y+0.98*toward.y>=0) {
            toward.y=0;pos.y=ofGetHeight();
            state = false;  //???
        }else toward.y -=gravity.y;
        
    }
    
 
}

void Particle::draw(){
    
    ofSetColor( (pos.x+pos.y)/8, ofRandom(0,10), 200);
    ofDrawCircle(pos.x,pos.y,radius);
    
}

void Particle::getMousePos(int _x, int _y){
    
    mousePosX = _x;
    mousePosY = _y;

}

void Particle::towardMousePos(){
    
    if(towardMouseCount == 0){
        towardMouse.x = mousePosX - pos.x;
        towardMouse.y = mousePosY - pos.y;
    }
    
    if(towardMouseCount <1){
        towardMouseCount++;
        
    }else{
        towardMouseCount = 0;
    }

    float dist = pow(towardMouse.x,2)+pow(towardMouse.y,2.0);
    
    if (dist>50){
//        pos.x += 1000000*towardMouse.x/pow(dist,1.5);
        pos.x += 1000*force*towardMouse.x/pow(dist,1.5);
        pos.y += 1000*force*towardMouse.y/pow(dist,1.5);
//        pos.x += 10*towardMouse.x/pow(dist,0.5);
//        pos.y += 10*towardMouse.y/pow(dist,0.5);
    }else{
        state = false;
    }

    

}


//Aparticle

AParticle::AParticle(){
    
    
    
    pos.x = ofRandom(0, ofGetWidth());
    pos.y = ofRandom(0, ofGetHeight());
    
    
//    toward.x = ofRandom(-initver.x, initver.x);
//    toward.y = ofRandom(-initver.y, initver.y);
    
    
    
//    gravity.x=0;
    //    gravity.y=0.6;
    //    gravity.y=0.0;
    
 //   setRad(ofRandom(40,60));
 //   setCol(ofColor(0,0,1));
    radius =ofRandom(40,60);
    color = ofColor(1,0,0);
    
}

void AParticle::setRad(float rad) {
    radius = rad;
}

void AParticle::setCol(ofColor col){
    color = col;
}


void AParticle::init(){
    pos.x = ofRandom(0, ofGetWidth());
    pos.y = ofRandom(0, ofGetHeight());
    
    
  //  toward.x = ofRandom(-initver.x, initver.x);
  //  toward.y = ofRandom(-initver.y, initver.y);
    
    
    radius = ofRandom(40,60);
    setCol(ofColor(0,200,100));
    state = false;
    
 
   
}


void AParticle::update(){
    
//    pos.x += toward.x;
    
//    toward.y += gravity.y;
//    pos.y += toward.y;
    
    

    /*
     if( pos.x <0 || pos.x > ofGetWidth() ){
     toward.x= -toward.x;
     }
     

    
    if(pos.x <0) pos.x=ofGetWidth();
    if(pos.x> ofGetWidth()) pos.x=0;
     */
    
    // reflex
    //    if(pos.y<0 || pos.y > ofGetHeight() ){
    
    
/*    if(pos.y<0 )
    {
        toward.y
        
        if(pos.y<0 )
        {
            toward.y = -toward.y;
            
        }
        
        
        boundnum = 0;
        
        
        if(pos.y > ofGetHeight()){
            
            float j= -abs(toward.y);
            //      toward.y= -abs(reflex*toward.y);
            
            if (j*toward.y<0) {
                //            if(j<-25.3)boundnum=1;
                //            if(j<-20)boundnum=1;
                if(j<-5)boundnum=1;
                j=reflex*j;
            }
            
            toward.y=j;
            
            if (gravity.y+0.98*toward.y>=0) {
                toward.y=0;pos.y=ofGetHeight();
                state = false;  //???
            }else toward.y -=gravity.y;
            
        }
 }
*/
        
 }


void AParticle::draw(){
        
        ofSetColor(color);
        ofDrawCircle(pos.x,pos.y,radius);
        
    }
