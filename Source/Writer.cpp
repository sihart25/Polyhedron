//------------------------------------------------------------------------------
//
// Module 08933 : Graphics Algorithms and Techniques
// Polyhedron Assessment
// Writer.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <fstream>
#include <string>
#include <gl/glut.h>
#pragma hdrstop
#include "Writer.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// write
void Writer::write(const string &filename, int width, int height) {
    GLubyte *image = 0;
    try {
        const int pack = 4;
        long size = (long)height * (((long)width * 3 + (pack - 1)) & ~(pack - 1));
        image = new GLubyte[size];
        glPixelStorei(GL_PACK_ALIGNMENT, pack);
        glReadPixels(0, 0, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, image);
        TBitmap bmp(width, height, 24, image, size, 0);
        ofstream out(filename.c_str(), ios::out | ios::binary);
        if (!out.good()) {
            throw string("Error : Invalid file name = " + filename);
        }
        bmp.Write(out);
    }
    catch (string s) {
        cout << s << endl;
    }
    catch (...) {
        cout << "Error : Unknown exception caught in writer" << endl;
    }
    delete[] image;
}

//------------------------------------------------------------------------------
// TBitmapFileHeader::TBitmapFileHeader
TBitmap::TBitmapFileHeader::TBitmapFileHeader(const TBitmapInfoHeader& Info) {
    _Type = 0x4d42;
    _Reserved1 = 0;
    _Reserved2 = 0;
    _OffBits = 14 + Info._Size + Info._ClrUsed * sizeof(TRGBQuad);
    _Size = _OffBits + Info._SizeImage;
}

//------------------------------------------------------------------------------
// TBitmapFileHeader::Write
ostream &TBitmap::TBitmapFileHeader::Write(ostream &out) const {
    out.write((const char*)&_Type, sizeof(_Type));
    out.write((const char*)&_Size, sizeof(_Size));
    out.write((const char*)&_Reserved1, sizeof(_Reserved1));
    out.write((const char*)&_Reserved2, sizeof(_Reserved2));
    out.write((const char*)&_OffBits, sizeof(_OffBits));
    return out;
}

//------------------------------------------------------------------------------
// TBitmapInfoHeader::TBitmapInfoHeader
TBitmap::TBitmapInfoHeader::TBitmapInfoHeader(int Width, int Height, int BitCount) {
    _Size=40;
    _Width=Width;
    _Height=Height;
    _Planes=1;
    _BitCount=BitCount;
    _Compression=0L; // No compression
    _SizeImage=(long)Width*(long)Height*(BitCount>8 ? 3L : 1L);
    _XPelsPerMeter=0;
    _YPelsPerMeter=0;
    _ClrUsed=(BitCount>8 ? 0L : 1L<<BitCount);
    _ClrImportant=_ClrUsed;
}

//------------------------------------------------------------------------------
// TBitmapInfoHeader::Write
ostream &TBitmap::TBitmapInfoHeader::Write(ostream &out) const {
    out.write((const char*)&_Size, sizeof(_Size));
    out.write((const char*)&_Width, sizeof(_Width));
    out.write((const char*)&_Height, sizeof(_Height));
    out.write((const char*)&_Planes, sizeof(_Planes));
    out.write((const char*)&_BitCount, sizeof(_BitCount));
    out.write((const char*)&_Compression, sizeof(_Compression));
    out.write((const char*)&_SizeImage, sizeof(_SizeImage));
    out.write((const char*)&_XPelsPerMeter, sizeof(_XPelsPerMeter));
    out.write((const char*)&_YPelsPerMeter, sizeof(_YPelsPerMeter));
    out.write((const char*)&_ClrUsed, sizeof(_ClrUsed));
    out.write((const char*)&_ClrImportant, sizeof(_ClrImportant));
    return out;
}

//------------------------------------------------------------------------------
// TBitmap
TBitmap::TBitmap(int Width, int Height, int BitCount, void *pPixels, long pSize, TRGBQuad *pPalette)
: _InfoHeader(Width, Height, BitCount),	_pPixels(pPixels), _pSize(pSize), _pPalette(pPalette) {
    _FileHeader = TBitmapFileHeader(_InfoHeader);
}

//------------------------------------------------------------------------------
// WriteLong
// Some older streaming classes use a short to specify the size of the data (BC++Builder5 uses a long)
void TBitmap::WriteLong(ostream &out, const char * Buffer, unsigned long Size) const {
    if (Size>0) {
        #if WRITE16BIT
            const long Partition = 0x4000L;
            long iLimit = Size / Partition;
            int Remainder = int(Size % Partition);
            for (int i=0; i<iLimit; i++) {
                out.write((const char*)Buffer, Partition);
                Buffer += Partition;
            }
            out.write((const char*)Buffer, Remainder);
        #else
            out.write((const char*)Buffer, Size);
        #endif
    }
}

//------------------------------------------------------------------------------
// Write
ostream &TBitmap::Write(ostream &out) const {
    _FileHeader.Write(out);
    _InfoHeader.Write(out);
    WriteLong(out, (const char*)_pPalette, sizeof(TRGBQuad)*_InfoHeader._ClrUsed);
    WriteLong(out, (const char*)_pPixels, _pSize);
    return out;
}

//------------------------------------------------------------------------------
