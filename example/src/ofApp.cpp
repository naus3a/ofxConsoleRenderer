#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(20);
    ofSetVerticalSync(true);
    ofBackground(0);
    ofSetWindowPosition(10, 10);
    
    mode = 1;
    
    //cam.setup(640,480);
    
    fbo.allocate(640, 480, GL_RGB);
    console.setup(128, 48);
    
    box.set(150);
    ball.set(100,10);
    
    ofSetSmoothLighting(true);
    for(int i=0;i<4;i++){
        ptLights[i].setPointLight();
    }
    ptLights[0].setDiffuseColor( ofFloatColor(.85, .85, .55) );
    ptLights[0].setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    ptLights[1].setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 135.f/255.f ));
    ptLights[1].setSpecularColor(ofFloatColor(.8f, .8f, .9f));
    ptLights[2].setDiffuseColor( ofFloatColor(.85, .85, .55) );
    ptLights[2].setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    ptLights[3].setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 135.f/255.f ));
    ptLights[3].setSpecularColor(ofFloatColor(.8f, .8f, .9f));
    mat.setShininess( 120 );
    mat.setSpecularColor(ofColor(255, 255, 255, 255));
}

//--------------------------------------------------------------
void ofApp::update(){
    fbo.begin();
    switch (mode) {
        case 0:
            updateCam();
            break;
        case 1:
            update3d();
            break;
            
        default:
            break;
    }
    fbo.end();
    
    
    console.update(fbo);
}

void ofApp::updateCam(){
    
}

void ofApp::update3d(){
    ofClear(0,0,0);
    float t = ofGetElapsedTimef();
    float aY = t;
    float aZ = t*50*0.7;
    ofEnableDepthTest();
    ofEnableLighting();
    for(int i=0;i<4;i++)ptLights[i].enable();
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    float r = 200;
    float s = (sin(t))*r;
    float c = (cos(t))*r;
    float s1 = (sin(t-PI))*r;
    float c1 = (cos(t-PI))*r;
    
    ofVec3f p[4];
    p[0].set(s,0,c);
    p[2].set(0,c,s);
    p[3].set(s1,0,c1);
    p[1].set(0,c1,s1);
    
    for(int i=0;i<3;i++){
        ptLights[i].setPosition(p[i]);
        ofDrawSphere(p[i],20);
    }
    
    
    ofRotateYDeg(aY);
    ofRotateZDeg(aZ);
    
    mat.begin();
    //box.draw();
    ball.draw();
    mat.end();
    
    ofPopMatrix();
    for(int i=0;i<4;i++)ptLights[i].disable();
    ofDisableLighting();
    ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.draw(0,0);
    
    console.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
