// nap
// (my)NeatAsciiPainter
// written by enrico<naus3a>viola in march 2019
// naus3a@gmail.com
// http://naus3a.ml
// naus3a on github, twitter and basically everywhere else
// license: MIT
//

#include <iostream>

namespace Nap{
    enum Color{
        black,
        red,
        green,
        yellow,
        blue,
        magenta,
        cyan,
        white
    };

    enum ClearMode{
        FROM_CURSOR,
        TILL_CURSOR,
        ALL
    };

    static const unsigned char esc[2] = "\033";
    static const unsigned char colTxtPrefix[3] = "[3";
    static const unsigned char colBgPrefix[3] = "[4";

    void clear(ClearMode _cm=ALL){
        std::cout<<Nap::esc<<"["<<(int)(_cm)<<"J";
    }
    void clearLine(ClearMode _cm=ALL){
        std::cout<<Nap::esc<<"["<<(int)(_cm)<<"K";
    }
 
    void resetTextColor(){std::cout<<Nap::esc<<"[0m";}
    
    std::string makeColor(const unsigned char * _prefix, Color _c, bool _bright=false){
        std::string s;
        for(int i=0;i<3;i++){
            s.push_back(_prefix[i]);
        }
        s += (char)_c+'0';
        if(_bright)s+=";1";
        s+="m";
        return s;
    }


    std::string makeTextColor(Color _c, bool _bright=false){
        return makeColor(Nap::colTxtPrefix, _c, _bright);
    }

    std::string makeBgColor(Color _c, bool _bright=false){
        return makeColor(Nap::colBgPrefix, _c, _bright);
    }

    void setTextColor(Color _c, bool _bright=false){
        std::cout<<Nap::esc<<makeTextColor(_c, _bright);
    }

    void setBgColor(Color _c, bool _bright=false){
        std::cout<<Nap::esc<<makeBgColor(_c, _bright);
    }

    void setTextColor256(int _cId){
        std::cout<<Nap::esc<<"[38;5;"<<_cId<<"m";
    }

    void setBgColor256(int _cId){
        std::cout<<Nap::esc<<"[48;5;"<<_cId<<"m";
    }

    void setBold(){std::cout<<Nap::esc<<"[1m";}
    void setUnderline(){std::cout<<Nap::esc<<"4m";}
    void setReversed(){std::cout<<Nap::esc<<"7m";}

    void moveBy(int _amt, char _movCode){
        std::cout<<Nap::esc<<"["<<_amt<<_movCode;
    }

    void up(int _n=1){moveBy(_n, 'A');}
    void down(int _n=1){moveBy(_n, 'B');}
    void right(int _n=1){moveBy(_n, 'C');}
    void left(int _n=1){moveBy(_n, 'D');}
    void nextLine(int _n=1){moveBy(_n, 'E');}
    void prevLine(int _n=1){moveBy(_n, 'F');}
    void setCol(int _col){moveBy(_col, 'G');} 

    void setPos(int _row, int _col){
        std::cout<<Nap::esc<<"["<<_row<<";"<<_col<<"H";
    }
}
