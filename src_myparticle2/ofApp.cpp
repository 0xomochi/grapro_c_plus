#include "ofApp.h"
#include "Particle.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableSmoothing();
    ofSetCircleResolution(64);
    
  //  p = Particle();
    
    for( int i=0;i<particleNum ; i++){
        Particle* p = new Particle();
        Particles[i] = *p;
        Particles[i].boundnum = 0;

    }
    
    
    //gui
    
    float gravity  =0.6;
    ofVec2f initv = {3,10};
    
    gui.setup();
    gui.add(force.setup("force", 0, 0, 100));
    gui.add(grav.setup("gravity", 0.6, 0, 1));
    gui.add(velocityx.setup("v_x",initv.x,0,30));
    gui.add(velocityy.setup("v_y",initv.y,0,30));
    
    
    showGui = true;
    for (int i =0; i<particleNum;i++){
        Particles[i].initver.x = initv[0];
        Particles[i].initver.y = initv[1];
        Particles[i].gravity.y = grav;
//        Particles[i].initver.x = velocityx;
//        Particles[i].initver.y = velocityy;
        Particles[i].force = force;
    
    }
    
    activateNum=particleNum;
    Particles[0].state=true;
    
    for (int i=0;i<100;i++){
        AParticles[i].init();
    }
    AParticles[0].state = true;

}

//--------------------------------------------------------------
void ofApp::update(){

//    p.update();
    
    ofVec2f tmptoward[1000];
    int bound =0;
    bool newstate[1000]={false}; //particleNum=1000

    
    //AParticle
    for (int i=0;i<100;i++){
        if(AParticles[i].state){
            for (int j=0; j<particleNum;j++){
                if(Particles[j].state){
                    float dist  = pow((AParticles[i].pos.x-Particles[j].pos.x),2)+
                    pow((AParticles[i].pos.y-Particles[j].pos.y),2);
                    float near = pow(AParticles[i].radius+Particles[j].radius,2);
                 //   float near2 = pow(AParticles[i].radius,2);
                    
                    if(dist<1.1*near && dist >0.1*near) {
                        Particles[j].toward *= -1;
                        AParticles[i].radius -= 1;
                       AParticles[i].setCol(ofColor(0,200,100*j));
                    }
                }
            }
        }
    }
    
    for( int i=0;i<100;i++){
        if (AParticles[i].radius <10 ) AParticles[i].state = false;
    }
    
    
    
    //Particles
    
    for (int i=0;i<particleNum;i++){
        if(Particles[i].state) newstate[i]=true;
        tmptoward[i]=Particles[i].toward;
    }
    
    for (int i=0;i<particleNum;i++){
        if(Particles[i].state){

            Particles[i].gravity.y = grav;
            Particles[i].initver.x = velocityx;
            Particles[i].initver.y = velocityy;
            Particles[i].force = force;
            
            
            for(int j=i+1;j<particleNum;j++){

                if(Particles[j].state){
                    float dist  = pow((Particles[i].pos.x-Particles[j].pos.x),2)+
                    pow((Particles[i].pos.y-Particles[j].pos.y),2);
                    float near = pow(Particles[i].radius+Particles[j].radius,2);
                
                    if(dist<1.2*near && dist >0.8*near) {
  //                      newstate[j]=false;
                        tmptoward[j] = Particles[i].toward;
                        tmptoward[i] = Particles[j].toward;
//                        Particles[j].toward = tmptoward;
                    }
                }
            }
        }
    }
    
    for(int i=0;i<particleNum;i++){
        Particles[i].toward = tmptoward[i];
    }
    
    for(int i=0;i<particleNum;i++) Particles[i].state=newstate[i];
    
    
    
    
    for(int i=0;i<activateNum;i++){
        
        if(Particles[i].state) bound += Particles[i].boundnum;
    }

//    activateNum += bound;
    
    if(activateNum > particleNum) activateNum = 1;//particleNum;
    
    int newparticle =0;
    for(int i=0;i<particleNum ;i++){
        
        if(Particles[i].state) Particles[i].update();
  
        bound=0; // stop generation
        if (newparticle<bound && !Particles[i].state) {

            Particles[i].init();
            Particles[i].state=true;
            Particles[i].update();
            newparticle++;
        }
    }
//
//    for(int i=0;i<particleNum;i++) {
//        if(Particles[i].toward.y == 0 && Particles[i].pos.y==ofGetHeight()) Particles[i].state=false;
//        if( Particles[i].pos.y == ofGetHeight()) Particles[i].state=false;
//    }
}

//--------------------------------------------------------------
void ofApp::draw(){


//    p.draw();
    for(int i=0;i<activateNum;i++){

        Particles[i].getMousePos(mouseX,mouseY);

        Particles[i].towardMousePos();
        
        if(Particles[i].state) Particles[i].draw();
    }
    

    for(int i=0;i<100;i++){
        if(AParticles[i].state) AParticles[i].draw();
    }
    
    if(showGui) gui.draw();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

//    if(key == 'e') p.bsoft = !p.bsoft;
    if(key == 'e') {
        for (int i=0;i< particleNum;i++){
            if(Particles[i].state){
            Particles[i].bsoft = true;
            }
        }
    }
    
    if(key == 'r') setup();
    
    if(key == 'p') {
        int i=0;
        while(Particles[i].state) i++;
          Particles[i].init();
        Particles[i].state=true;
    }
    
    
    if(key == 'o'){

        int i=0;
        while(AParticles[i].state) i++;
        AParticles[i].init();
        AParticles[i].state=true;
    }
    
    
    if(key == 's'){
        showGui = !showGui;
    }
        
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
