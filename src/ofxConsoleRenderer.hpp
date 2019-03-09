//
//  ofxConsoleRenderer.hpp
// written by enrico<naus3a>viola in march 2019
// naus3a@gmail.com
// http://naus3a.ml
// naus3a on github, twitter and basically everywhere else
// license: MIT
//

#pragma once
#include "ofMain.h"
#include "Nap.hpp"

class ofxConsoleRenderer{
public:
    static const string srcShdLuminanceES2;
    static const string srcShdLuminanceGL2;
    static const string srcShdLuminanceGL3;
    
    class Tbo{
    public:
        Tbo(){tixels=NULL;setupDefaultShades();}
        ~Tbo();
        void allocate(int _w, int _h);
        void setFromPixels(ofPixels & _pix);
        void drawGL();
        void drawCLI();
        
        int getWidth(){return width;}
        int getHeight(){return height;}
    protected:
        void destroyTixels();
        void setupDefaultShades();
        
        string shades;
        unsigned char * tixels;
        int tixCnt;
        int width;
        int height;
    };
    
    void setup(int _w, int _h);
    void update(ofFbo & _fbo);
    void draw();
protected:
    Tbo tbo;
    ofFbo fbo;
    ofFbo fboLum;
    ofPixels pix;
    ofShader shdLum;
};
