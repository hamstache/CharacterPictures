#ifndef __Picture__h__
#define __Picture__h__

#include <string>

class Picture{
public:
    Picture ();
    Picture(const char* data[], int height);
    Picture(const Picture& pOther);   //copy constructor
    ~Picture();
    
    char position(int r, int c) const;
    char& position(int r, int c);
    void dataset(int height, int width);
    friend Picture  frame( Picture const& p );
    friend Picture  operator|( Picture const& p1, Picture const& p2 );
    friend Picture  operator&( Picture const& p1, Picture const& p2 );
    friend std::ostream& operator<<(std::ostream& os, const Picture& p);
    Picture& operator=(const Picture& other);
private:
    void blockcopy( int r, int c, Picture const& other );
private:
    int _height;
    int _width;
    char* _data;
};

#endif
