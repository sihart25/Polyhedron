//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Writer.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Writer_h
#define Writer_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Writer {
    public:
        static void Writer::write(const string &filename, int width, int height);
    };

    //------------------------------------------------------------------------------
    // class definition

    class TRGBQuad {
    public:
        unsigned char _Blue;
        unsigned char _Green;
        unsigned char _Red;
        unsigned char _Reserved;
        TRGBQuad() {}
        TRGBQuad(unsigned char Red, unsigned char Green, unsigned char Blue) :
        _Blue(Blue), _Green(Green), _Red(Red), _Reserved(0xff) {}
        void invert() { unsigned char t=_Red; _Red = _Blue; _Blue = t; }
    };

    //------------------------------------------------------------------------------
    // class definition

    class TRGBTriple {
    public:
        unsigned char _Blue;
        unsigned char _Green;
        unsigned char _Red;
        TRGBTriple() {}
        TRGBTriple(unsigned char Red, unsigned char Green, unsigned char Blue) :
        _Blue(Blue), _Green(Green), _Red(Red) {}
        void invert() { unsigned char t=_Red; _Red = _Blue; _Blue = t; }
    };

    //------------------------------------------------------------------------------
    // class definition

    class TBitmap {
    private:

        //------------------------------------------------------------------------------
        // nested class definition

        class TBitmapInfoHeader {
            public:
            unsigned long _Size;
            long _Width;
            long _Height;
            unsigned short _Planes;
            unsigned short _BitCount;
            unsigned long _Compression;
            unsigned long _SizeImage;
            long _XPelsPerMeter;
            long _YPelsPerMeter;
            unsigned long _ClrUsed;
            unsigned long _ClrImportant;

            TBitmapInfoHeader() {}
            TBitmapInfoHeader(int Width, int Height, int BitCount);
            ostream &Write(ostream &out) const;
        };

        //------------------------------------------------------------------------------
        // nested class definition

        class TBitmapFileHeader {
        public:
            unsigned short _Type;
            unsigned long _Size;
            unsigned short _Reserved1;
            unsigned short _Reserved2;
            unsigned long _OffBits;

            TBitmapFileHeader() {}
            TBitmapFileHeader(const TBitmapInfoHeader& Info);
            ostream &Write(ostream &out) const;
        };

        TBitmapFileHeader _FileHeader;
        TBitmapInfoHeader _InfoHeader;
        TRGBQuad *_pPalette;
        void *_pPixels;
        long _pSize;
        void WriteLong(ostream &out, const char * Buffer, unsigned long Size) const;

    public:
        TBitmap(int Width, int Height, int BitCount, void *pPixels, long pSize, TRGBQuad *pPalette=0);
        ostream &Write(ostream &out) const;
    };

} // ComputerGraphics

#endif // Writer_h

//------------------------------------------------------------------------------
