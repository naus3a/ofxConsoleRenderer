//
//  ofxConsoleRenderer.cpp
// written by enrico<naus3a>viola in march 2019
// naus3a@gmail.com
// http://naus3a.ml
// naus3a on github, twitter and basically everywhere else
// license: MIT
//

#include "ofxConsoleRenderer.hpp"

const string ofxConsoleRenderer::srcShdLuminanceES2=R"(
precision highp float;
uniform sampler2D tex;
const vec3 k = vec3(0.2125,0.7154,0.0721);
void main(){
    vec4 c = texture2D(tex, gl_TexCoord[0].st);
    float l = dot(c.rgb,k);
    gl_FragColor = vec4(l,l,l,c.a);
}
)";
const string ofxConsoleRenderer::srcShdLuminanceGL2=R"(
#version 120
uniform sampler2DRect tex;
const vec3 k = vec3(0.2125,0.7154,0.0721);
void main(){
    vec4 c = texture2DRect(tex, gl_TexCoord[0].st);
    float l = dot(c.rgb,k);
    gl_FragColor = vec4(l,l,l,c.a);
}
)";
const string ofxConsoleRenderer::srcShdLuminanceGL3=R"(
#version 150
uniform sampler2DRect tex;
out vec4 outputColor;
const vec3 k = vec3(0.2125,0.7154,0.0721);
void main(){
    vec4 c = texture2DRect(tex, gl_TexCoord[0].st);
    float l = dot(c.rgb,k);
    outputColor = vec4(l,l,l,c.a);
}
)";

void ofxConsoleRenderer::Tbo::setupDefaultShades(){
    shades = " .,-~:;=!*#$@";
}

void ofxConsoleRenderer::Tbo::destroyTixels(){
    if(tixels==NULL)return;
    delete [] tixels;
    tixels = NULL;
}

ofxConsoleRenderer::Tbo::~Tbo(){
    destroyTixels();
}

void ofxConsoleRenderer::Tbo::allocate(int _w, int _h){
    width=_w;
    height=_h;
    destroyTixels();
    tixCnt = _w*_h;
    tixels = new unsigned char[tixCnt];
}

void ofxConsoleRenderer::Tbo::setFromPixels(ofPixels &_pix){
    for(int i=0;i<tixCnt;i++){
        unsigned char p = _pix.getData()[i*_pix.getNumChannels()];
        int sId = ofMap(p, 0, 255, 0, shades.size(), true);
        tixels[i] = shades[sId];
    }
}

void ofxConsoleRenderer::Tbo::drawGL(){
    string s;
    for(int i=0;i<tixCnt;i++){
        s+=tixels[i];
        //s+=tixels[i];
        if(i%width==0){
            s+="\n";
        }
    }
    ofDrawBitmapString(s, 10, 10);
}

void ofxConsoleRenderer::Tbo::drawCLI(){
    cout<<Nap::esc<<"["<<(int)(Nap::ClearMode::ALL)<<"J";
    
    for(int i=0;i<tixCnt;i++){
        cout<<tixels[i];
        //cout<<tixels[i];
        if(i>0 && i%width==0){
            cout<<endl;
        }
    }
    fflush(stdout);
}

void ofxConsoleRenderer::setup(int _w, int _h){
    tbo.allocate(_w, _h);
    fbo.allocate(_w, _h, GL_RGB);
    fboLum.allocate(_w, _h, GL_RGB);
#ifdef TARGET_OPENGLES
    shdLum.setupShaderFromSource(GL_FRAGMENT_SHADER, srcShdLuminanceES2);
#else
    if(ofIsGLProgrammableRenderer()){
        shdLum.setupShaderFromSource(GL_FRAGMENT_SHADER, srcShdLuminanceGL3);
    }else{
        shdLum.setupShaderFromSource(GL_FRAGMENT_SHADER, srcShdLuminanceGL2);
    }
#endif
    shdLum.linkProgram();
}

void ofxConsoleRenderer::update(ofFbo & _fbo){
    fbo.begin();
    ofClear(0, 0, 0);
    _fbo.draw(0,0,fbo.getWidth(),fbo.getHeight());
    fbo.end();
    
    fboLum.begin();
    ofClear(0, 0, 0);
    shdLum.begin();
    fbo.draw(0,0);
    shdLum.end();
    fboLum.end();
    
    fboLum.readToPixels(pix);
    tbo.setFromPixels(pix);
}

void ofxConsoleRenderer::draw(){
    tbo.drawCLI();
    fboLum.draw(10,10);
}
