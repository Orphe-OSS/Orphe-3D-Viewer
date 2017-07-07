//
//  CGViewer.cpp
//  orphe3DViewer
//
//  Created by kyosuke on 2017/07/05.
//
//

#include "CGViewer.hpp"

CGViewer::CGViewer(int x, int y, int w, int h, OrpheSide _side){
    side = _side;
    setSize(x, y, w, h);
    setCGSettings();
}

void CGViewer::setSize(int x, int y, int w, int h){
    x0 = x;
    y0 = y;
    width = w;
    height = h;
    x1 = x0+width;
    y1 = y0+height;
    
    ///camera
    float offsetX = width/2;
    float offsetY = height/2;
    
    viewGrid.set(x0, y0, width, height);
}

void CGViewer::setCGSettings(){
    //3D model
    if (side == OrpheSide_left) {
        orpheModel.loadModel("Orphe3D_L.3ds", false);
    }
    else{
        orpheModel.loadModel("Orphe3D_R.3ds", false);
    }
    
    //camera
    easyCam = new ofEasyCam();
    easyCam->tilt(-20);
    easyCam->setPosition(0, 200, 500);
    easyCam->disableMouseInput();
    
    //light
    light.enable();
    light.setSpotlight();
    light.setPosition(0, 0, 1000);
    float ambient = 0.3;
    light.setAmbientColor(ofFloatColor(ambient, ambient, ambient, 1.0));
    float diffuse = 0.4;
    light.setDiffuseColor(ofFloatColor(diffuse, diffuse, diffuse));
    float specular = 0.1;
    light.setSpecularColor(ofFloatColor(specular, specular, specular));
    
    ofEnableSmoothing();
}

void CGViewer::draw(){
    
    ofSetColor(30);
    ofFill();
    ofDrawRectangle(x0, y0, width, height);
    
    easyCam->begin(viewGrid);
    drawGrid();
    drawShoe();
    easyCam->end();
    
}

void CGViewer::drawGrid(){
    ofPushMatrix();
    int num = 20;
    ofRotate(90, 0, 0, 1);
    ofGetCurrentRenderer()->setColor(100);
    ofDrawGridPlane(100, num);
    ofPopMatrix();
}

void CGViewer::drawShoe(){
    
    
    ofEnableLighting();
    ofEnableDepthTest();
    
    ofPushMatrix();
    
    //convert axis
    ofQuaternion new_q;
    new_q.w() = quat.w;
    new_q.x() = quat.y;
    new_q.y() = quat.z;
    new_q.z() = quat.x;
    
    ofVec3f qaxis;
    float qangle;
    new_q.getRotate(qangle, qaxis);
    
    //rotate
    ofRotateY(180); //rotate 3d model
    ofRotate(qangle, qaxis.x, qaxis.y, qaxis.z);
    ofRotateZ(180); //upside down
    
    orpheModel.drawFaces();
    
    ofPopMatrix();
    ofDisableLighting();
    ofDisableDepthTest();
    
}
