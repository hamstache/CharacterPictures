#include "Picture.h"
#include <iostream>
#include <cstring>
using namespace std;

static int max(int m, int n) { return (m>n ? m : n);}

Picture::Picture()
: _height(0), _width(0), _data(0) {    }

Picture::Picture (const char* data[], int height) {
    int maxline = 0;
    for (int i = 0; i < height; i++){
            maxline = max(maxline, static_cast<int>(strlen(data[i])));
    }
    dataset (height, maxline);
    memset(_data, ' ', _height * _width);
    char* p = _data;
    for (int i = 0; i < _height; i++){
        memcpy(p, data[i], static_cast<int> (strlen(data[i])));
        p+= _width;
    }
}

void Picture::dataset(int height, int width){
    _height = height;
    _width = width;
    _data= new char [_height * _width];
    memset(_data, ' ' , _height * _width);
}

Picture::Picture (const Picture& pOther )
: _height (pOther._height), _width (pOther._width){
    _data = new char[pOther._height * pOther._width];
    blockcopy(0, 0, pOther);
}

Picture::~Picture() {
    delete[] _data;
}

char Picture::position(int r, int c) const  {return _data[r * _width + c]; }
char& Picture::position(int r, int c) {return _data[r *_width +c];}

Picture  frame( Picture const& p ){
    Picture frame;
    frame.dataset(p._height+2, p._width + 2);
    frame.position(0,0) = '+';
    frame.position(frame._height -1, 0) = '+';
    frame.position(0, frame._width - 1) = '+';
    frame.position(frame._height - 1, frame._width - 1) = '+';
    for (int x = 1; x < frame._width - 1 ; x++){
        frame.position(0, x) = '-';
        frame.position( frame._height - 1, x) = '-';
    }
    for (int y = 1; y < frame._height -1; y++){
        frame.position(y,0) = '|';
        frame.position(y, frame._width - 1) = '|';
    }
    frame.blockcopy(1,1,p);
    return frame;
    
    
}
Picture  operator|( Picture const& p1, Picture const& p2 ){
    Picture hcat;
    hcat.dataset (max(p1._height , p2._height), p1._width + p2._width);
    hcat.blockcopy(0,0,p1);
    hcat.blockcopy(0 ,p1._width , p2);
    return hcat;
}
Picture  operator&( Picture const& p1, Picture const& p2 ){
    Picture hcat;
    hcat.dataset(p1._height + p2._height , max(p1._width, p2._width));
    hcat.blockcopy(0,0,p1);
    hcat.blockcopy(p1._height, 0, p2);
    return hcat;
    
}
void Picture::blockcopy( int r, int c, Picture const& other ){
    for (int x = 0; x<other._height; x++){
        for (int y = 0; y<other._width; y++){
            position(x+r, y+c) = other.position(x, y);
        }
    }
}


std::ostream& operator<<(std::ostream& os, const Picture& p){
    for (int x = 0; x<p._height; x++){
        for (int y = 0; y<p._width; y++){
            os << p.position(x, y);
        }
        os << endl;
    }
    return os;
}

    
    
Picture& Picture::operator=(const Picture& p){
	if (this != &p){
		delete[] _data;
        dataset(p._height, p._width);
		blockcopy(0, 0, p);
	}
	return *this;
}
