#include "ofApp.h"

#define PORT 1234

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetDataPathRoot("../Resources/data/");
    ofSetFrameRate(30);
    cgViewWidth = ofGetWidth()/2;
    leftOrpheModel = new CGViewer(0,0,cgViewWidth,ofGetHeight(),OrpheSide_left);
    rightOrpheModel = new CGViewer(cgViewWidth,0,cgViewWidth,ofGetHeight(),OrpheSide_right);
    receiver.setup(PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    while(receiver.hasWaitingMessages()){
        
        ofxOscMessage m;
        receiver.getNextMessage(m);
        vector<string> address;
        address = ofSplitString(m.getAddress(), "/");
        OrpheSide side;
        if(address[1] == "LEFT"){
            side = OrpheSide_left;
        }else if (address[1] == "RIGHT"){
            side = OrpheSide_right;
        }
        
        //sensorValues
        if(address[2] == "sensorValues"){
            //ofvec4f x,y,z,w -> 0,1,2,3
            ofVec4f quat;
            for(int i =0 ; i < 4;i++){
                if(i == 3){
                    quat.w = m.getArgAsFloat(0);
                }
                else{
                    quat[i] = m.getArgAsFloat(i+1);
                }
            }
            
            if (side == OrpheSide_left) {
                leftOrpheModel->quat = quat;
            }
            else{
                rightOrpheModel->quat = quat;
            }
            
            //other values
//            for(int i =0 ; i < 3;i++){
//                angle[i] = m.getArgAsFloat(4 + i);
//            }
//            for(int i =0 ; i < 3;i++){
//                acc[i] = m.getArgAsFloat(7 + i);
//            }
//            for(int i =0 ; i < 3;i++){
//                gyto[i] = m.getArgAsFloat(10 + i);
//            }
//            compass = (int)(m.getArgAsFloat(13));
            
            
        }
        
        //gesture
        if(address[2] == "gesture"){
            cout << "gesture name:" << m.getArgAsString(0) << endl;
            cout << "angle:" << m.getArgAsString(1) << endl;
            cout << "power:" << m.getArgAsFloat(2) << endl;
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    leftOrpheModel->draw();
    rightOrpheModel->draw();
    
    ofSetColor(255);
    ofDrawBitmapString("OSC receive port: "+ofToString(PORT), 10, 20);
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
    cgViewWidth = w/2;
    leftOrpheModel->setSize(0,0,cgViewWidth,ofGetHeight());
    rightOrpheModel->setSize(cgViewWidth,0,cgViewWidth,ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
