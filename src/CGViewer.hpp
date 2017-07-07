//
//  CGViewer.hpp
//  orphe3DViewer
//
//  Created by kyosuke on 2017/07/05.
//
//

#pragma once

#include "ofMain.h"

#include "ofxAssimpModelLoader.h"

enum OrpheSide{
    OrpheSide_left = 0,
    OrpheSide_right = 1
};

class CGViewer{
public:
    OrpheSide side;
    CGViewer(int x, int y, int w, int h, OrpheSide _side);
    void setSize(int x, int y, int w, int h);
    
    void draw();
    void drawShoe();
    ofVec4f quat;
    
    int x0, y0, x1, y1, width, height;
    
    
    ofxAssimpModelLoader orpheModel;
    ofLight light;
    
    //camera
    ofEasyCam* easyCam;
    ofRectangle viewGrid;
    
private:
    void setCGSettings();
    void drawGrid();
};
