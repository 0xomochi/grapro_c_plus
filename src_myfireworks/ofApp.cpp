#include "ofApp.h"
#include <GLUT/GLUT.h>

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
 
    ofEnableDepthTest();
    ofEnableLighting();
    ofSetSmoothLighting(true);
    ofSetWindowTitle("Fireworks Festival");
    
   
    
   //gui
   
    newball.addListener(this, &ofApp::newfirework);
 
    
    
    gui.setup();
 
    gui.add(newball.setup("create new fireworks"));
    
    gui.add(light1pt.setup("light1",ofVec3f(10,200,300),ofVec3f(500,500,500),ofVec3f(-500,-500,-500),10,10));
    gui.add(light2pt.setup("light2",ofVec3f(10,200,-300),ofVec3f(500,500,500),ofVec3f(-500,-500,-500),10,10));
    
    gui.add(particleColor.setup("Colors",ofColor(150,100,100),ofColor(0,0),ofColor(255,255)));
    
 
    showGui = false;
    
    camera.setDistance(300);
    camera.setTarget(ofVec3f(0, 0, 0));

    
    light_amb.set(0.3, 0.3, 0.3);
    light_diff.set(0.7, 0.7, 0.7);
    light_spe.set(1.0, 1.0, 1.0);
    
    light.setAmbientColor(light_amb);
    light.setDiffuseColor(light_diff);
    light.setSpecularColor(light_spe);
    light.setPosition(300, 200, 0);
    light.enable();
    
    
      //add light same color
    light2_amb.set(0.3, 0.3, 0.3);
    
    light2.setAmbientColor(light2_amb);
    light2.setDiffuseColor(light_diff);
    light2.setSpecularColor(light_spe);
    light2.setPosition(-300, 200, 0);
    light2.enable();
    
    slen[0] = ofRandom(2,8);//(5,12);
    slen[1] = ofRandom(3,10);//8;
    slen[2] = ofRandom(2,8);//(5,12);
    
    shape = 0;
    
    
    // buildingData
    
    building.clear();
    buildingColor.clear();
    buildhw.clear();
    
 
    int xint = 0;
    int yint = 0;
    
    float px=-400;
    float py=-300;
    
    while( px < 400){
    
        while( py < 300){
            
            if (px >400 || py > 300) break;
            
            buildingColor.push_back(ofColor(100+ofRandom(0,10)*xint, ofRandom(5,10)*yint, 255));
            building.push_back(ofVec3f(px,py, -ofRandom(10,20)));
            buildhw.push_back(ofVec2f(ofRandom(8,15),ofRandom(8,15)));
            
            py += ofRandom(10,20);
            yint ++;
        }
        py = -300;
        yint = 0;
    
        px += ofRandom(10,20);
        xint++;
    }

    // nfall
    
    npos.clear();
    nvel.clear();
    nCol.clear();
    nindices.clear();
    bNfall = true;
 
    bdemo = false;
    fwstart = 0;
    
    // bBall
    
    bpos.clear();
    bvel.clear();
    tempbpos.clear();
    tempbvel.clear();
    bCol.clear();
    tempbCol.clear();
    bindices.clear();
    
    pBall = 0;
    
}

void ofApp::newPressed(){
    
    float px,py,pz,len;
    
    ofVec3f ppp;

             ppp.x=ofRandom(-200,200);
             ppp.y=ofRandom(-60,60);
             ppp.z=ofRandom(-60,30);
    
    int count = position.size();
    
    ofColor pColordata[10];
    
    ofColor partColord;
    
    for (int i =0 ; i<10;i++){

        
        partColord = ofColor(particleColor);
        
        pColordata[i] =
          ofColor(ofRandom(partColord.r,200),ofRandom(partColord.g,235), ofRandom(partColord.b,235));

    }
    
    shape ++;
    if (shape >2) shape =0;
    
    shapeColor = (int) ofRandom(0,9.999);
    
    int dir[3];
    float dlen;
    
    if (shape ==2){
        dir[0] = (int) ofRandom(0,10);
        dir[1] = (int) ofRandom(0,10);
        dir[2]=  (int) ofRandom(5,10);
        dlen = dir[0]*dir[0]+dir[1]*dir[1]+dir[2]*dir[2];
    }

    
    for (int i=0; i<2000; i++){
        position.push_back(ppp);
        indices.push_back(count+i);

     ofVec3f randomVel;
        
        px = ofRandom(-.01, .01);
        py=ofRandom(-.01, .01);
        pz=ofRandom(-.04, .01);
        len = slen[shape]*pow((px*px)+(py*py)+(pz*pz),0.5);
        px /= len;
        py /= len;
        pz /= len;

        if (shape == 2 ){
            
              px =px-ofRandom(0.95,1.05)*(px*dir[0]+py*dir[1]+pz*dir[2])*dir[0]/dlen;
            py =py-ofRandom(0.95,1.05)*(px*dir[0]+py*dir[1]+pz*dir[2])*dir[1]/dlen;
            pz =pz-ofRandom(0.95,1.05)*(px*dir[0]+py*dir[1]+pz*dir[2])*dir[2]/dlen;
            
        }
        

        
        randomVel.set(px,py,pz);
        
        velocity.push_back(randomVel);
        
        
         partColord =ofColor(pColordata[shapeColor].r+ofRandom(-40,100),
                            pColordata[shapeColor].g+ofRandom(-10,10),
                            pColordata[shapeColor].b+ofRandom(-20,40));

        pColor.push_back(partColord);
    
  
    }
  
    vbo.setVertexData(&position[0], (int) position.size(), GL_DYNAMIC_DRAW);
    vbo.setIndexData(&indices[0], (int) indices.size(), GL_DYNAMIC_DRAW);
    vbo.setColorData(&pColor[0], (int) pColor.size(), GL_DYNAMIC_DRAW);
    
}


void ofApp::newfirework(){
    for (int i=0; i<10;i++)  newPressed();
}




//--------------------------------------------------------------
void ofApp::update(){
    

    
    for(int i=0; i<position.size(); i++){
        position[i] += velocity[i];
        
        if( position[i].z >150){
       
            
            
            position.pop_back();
            velocity.pop_back();
            indices.pop_back();
            pColor.pop_back();
            pColor[i]= ofColor(pColor[i].r+0.1*position[i].z,pColor[i].g,pColor[i].b);
          
        }else {velocity[i].z +=0.001;}  //gravity
    }
    
    
    
    if (position.size()<10) {
        position.clear();
        velocity.clear();
        indices.clear();
        pColor.clear();
    }
    
 
    light.setPosition(light1pt);
    light2.setPosition(light2pt);

    vbo.updateVertexData(&position[0], (int) position.size());
    vbo.updateIndexData(&indices[0], (int) indices.size());
    vbo.updateColorData(&pColor[0], (int) pColor.size());
    
    if (bNfall){
        
        
        
        for(int i=0; i<npos.size(); i++){
            npos[i] += nvel[i];
            
            if( npos[i].z >280){
                
                npos.pop_back();
                nvel.pop_back();
                nindices.pop_back();
                nCol.pop_back();
                nCol[i]= ofColor( nCol[i].r+0.1*npos[i].z,nCol[i].g, nCol[i].b);

            }else {nvel[i].z +=0.001;}  //gravity
        }
        
        
        
        if (npos.size()<10) {
            npos.clear();
            nvel.clear();
            nindices.clear();
            nCol.clear();

        }
        
        
        
        
    }
    
    nvbo.updateVertexData(&npos[0], (int) npos.size());
    nvbo.updateIndexData(&nindices[0], (int) nindices.size());
    nvbo.updateColorData(&nCol[0], (int) nCol.size());
    
    
    
    
    
    //bBall
    
    for(int i=0; i<bpos.size(); i++){
  
  //      cout << i << "," << bpos[i] << "\n";
        
        bpos[i] += bvel[i];
        
        if( bpos[i].z >150){
            
            
            bpos.pop_back();
            bvel.pop_back();
            bindices.pop_back();
            bCol.pop_back();
            bCol[i]= ofColor(bCol[i].r+0.1*bpos[i].z,bCol[i].g,bCol[i].b);
            
            tempbpos.clear();
            tempbvel.clear();
            tempbCol.clear();
            
            pBall =0;
            
        }else {bvel[i].z +=0.002;}  //gravity
    }
    
 

    // push 100 times
 
    int pcountNum ;
    
    pcountNum = bpos.size();
    
    int tempcount;
    
    tempcount = tempbpos.size();
    
//    cout << pcountNum <<", " << tempcount << "\n";
    
    
    
    if (!bpos.empty()){
   
    
        if (pBall <50){
        
            for ( int i =0; i<tempbpos.size();i++){

                bpos.push_back(tempbpos[i]);
                bvel.push_back(tempbvel[i]);
                bindices.push_back(pcountNum+i);
                bCol.push_back(tempbCol[i]);
            }
            

  //          cout << tempbpos.size() << "," << pBall << "," << bpos.size() <<"\n";

            pBall++;
        }
    
       else {

        //    pBall =0;
         /*     if (tempcount >100){

                tempbpos.clear();
                tempbvel.clear();
                tempbCol.clear();
            }
            if (!tempbpos.empty()){
                tempbpos.pop_back();
                tempbvel.pop_back();
                tempbCol.pop_back();
            } */
        }
    }


 

    
    
    if (bpos.size()<5) {
            bpos.clear();
            bvel.clear();
            bindices.clear();
            bCol.clear();
        
    }
    
     
    bvbo.setVertexData(&bpos[0], (int) bpos.size(), GL_DYNAMIC_DRAW);
    bvbo.setIndexData(&bindices[0], (int) bindices.size(), GL_DYNAMIC_DRAW);
    bvbo.setColorData(&bCol[0], (int) bCol.size(),GL_DYNAMIC_DRAW);
    
}


//----------------------------------
void ofApp::demo(){
    
    if (ofGetElapsedTimef()-fwstart > 4){
        bball();
        newfirework();
//        for (int i= 0;i<3;i++) bball();
        
        fwstart = ofGetElapsedTimef();
        bBall = true;
    }
  
    if (bBall && ofGetElapsedTimef()-fwstart > 2){
        for (int i= 0;i<3;i++) bball();
        bBall = false;
    }
}


//----------------------------------
void ofApp::town(){

    
    int townHor = 200;
    
    glPushMatrix();
    glTranslatef(0,0, townHor);
    ofSetColor(0, 255, 0);
    ofNoFill();
    ofDrawPlane(0,0, 800, 600);
    
    
    glPopMatrix();
    
    for (int i = 0; i<building.size();i++){

            glPushMatrix();
    
            glTranslatef(0, 0, townHor);
            ofSetColor(buildingColor[i]);
            
            ofFill();
        ofDrawBox(building[i] , buildhw[i].x, buildhw[i].y,-building[i].z);
        
        glPopMatrix();
    }
    
    
}



//-----------------------------------------------------
void ofApp::nfall(){
    
    float px = -200;
    float py = -200;
    float pz = 90;
    
    ofVec3f pvel=ofVec3f(0,0.0,.001);
    
    int ind = npos.size();

    ofColor npcolor;
    
  
    
    while ( px < 200){
       
        for (int i =0 ; i<100;i++){
            npos.push_back(ofVec3f(px,py,pz));
            nvel.push_back(ofVec3f(pvel.x+ofRandom(-.7,.7), pvel.y+ofRandom(-0.001,0.001),pvel.z+ofRandom(.6)));

            npcolor = ofColor(100+ofRandom(155),180+ofRandom(100),80+ofRandom(155));
            nCol.push_back(npcolor);
            nindices.push_back(ind);
            ind++;
        }
        
        px += 2;
        //ind ++;
    }
    
    nvbo.setVertexData(&npos[0], npos.size(), GL_DYNAMIC_DRAW);
    nvbo.setIndexData(&nindices[0], nindices.size(), GL_DYNAMIC_DRAW);
    nvbo.setColorData(&nCol[0], nCol.size(), GL_DYNAMIC_DRAW);
}


// bBall

void ofApp::bball(){
    
    float px,py,pz,len;
    
    int bNum =30;
    
    ofVec3f ppp;
    
    pBall =0;
    
    ppp.x=ofRandom(-200,200);
    ppp.y=ofRandom(-60,60);
    ppp.z=ofRandom(-60,30);
    
    int count = bpos.size();
    
    ofColor pColordata[10];
    
    ofColor partColord;
    
    for (int i =0 ; i<10;i++){
        
        
        partColord = ofColor(particleColor);
        
        pColordata[i] =
        ofColor(ofRandom(partColord.r,200),ofRandom(partColord.g,235), ofRandom(partColord.b,235));
        
    }
    

    int tmpColor = (int) ofRandom(0,9.999);
    /*
    if (shape >2) shape =0;
    

    
    int dir[3];
    float dlen;
    
    if (shape ==2){
        dir[0] = (int) ofRandom(0,10);
        dir[1] = (int) ofRandom(0,10);
        dir[2]=  (int) ofRandom(5,10);
        dlen = dir[0]*dir[0]+dir[1]*dir[1]+dir[2]*dir[2];
    }
    */
    
    
    for (int i=0; i<bNum; i++){
     
        bpos.push_back(ppp);
        tempbpos.push_back(ppp);
        bindices.push_back(count+i);
        
        ofVec3f randomVel;
        
        px = ofRandom(-.01, .01);
        py=ofRandom(-.01, .01);
        pz=ofRandom(-.04, .01);
        len = ofRandom(5,8)*pow((px*px)+(py*py)+(pz*pz),0.5);
        px /= len;
        py /= len;
        pz /= len;
        
        randomVel.set(px,py,pz);
        
        bvel.push_back(randomVel);
        tempbvel.push_back(randomVel);
        
        
        partColord =ofColor(pColordata[tmpColor].r+ofRandom(-40,100),
                            pColordata[tmpColor].g+ofRandom(-10,10),
                            pColordata[tmpColor].b+ofRandom(-20,40));
        
        bCol.push_back(partColord);
        tempbCol.push_back(partColord);

    

    }
    bvbo.setVertexData(&bpos[0], bpos.size(), GL_DYNAMIC_DRAW);
    bvbo.setIndexData(&bindices[0], bindices.size(), GL_DYNAMIC_DRAW);
    bvbo.setColorData(&bCol[0], bCol.size(), GL_DYNAMIC_DRAW);
    
}





//--------------------------------------------------------------
void ofApp::draw(){
  
    
    camera.begin();
    
    light.draw();
    light2.draw();
    
    town();
 
    glTranslatef(0,0,0);
    glPointSize(ofRandom(1,3));
    vbo.drawElements(GL_POINTS, (int)position.size());

    if (bNfall){
        glTranslatef(0,0,0);
        glPointSize(ofRandom(1,3));
        nvbo.drawElements(GL_POINTS, (int)npos.size());
    }
    
    glTranslatef(0,0,0);
    glPointSize(ofRandom(.01,.05));
    bvbo.drawElements(GL_POINTS, (int)bpos.size());
    

    camera.end();
 
    ofDisableDepthTest();
    ofDisableLighting();
    if(showGui) gui.draw();
    ofEnableLighting();
    ofEnableDepthTest();
    
    
    if(bdemo) demo();
}


    


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == OF_KEY_UP){
        newfirework();
    }
    
    if (key == 'g'){
        showGui = !showGui;
    }
    
    if(key == 'f'){
        ofToggleFullscreen();
    }
    
    if(key == 'n'){
        nfall();
    }
    
    if(key == 'b'){
        bball();
    }
    
    if(key == 'd'){
        bdemo = !bdemo;
    }
    
    if(key == 's'){
        ofSaveFrame();
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
