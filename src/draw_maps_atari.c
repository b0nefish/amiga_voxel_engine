#include "engine.h"


void DrawBitmap8b(unsigned char *bLogo, BITMAPINFOHEADER *bhLogo)
{
	UWORD position;
	unsigned char b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15,b16;
	unsigned char byte;
	ULONG xx,yy;
	UBYTE offsety;
	UWORD startOffset;

	offsety = 0;
	startOffset = 0;

	position = startOffset;

	for (ULONG y = bhLogo->biHeight; y > 0; y--)
	{
		yy = (y - 1 - offsety) * bhLogo->biWidth;
		position = (bhLogo->biHeight - (y - offsety)) * PLANEWIDTH/2 * 4;

		for (ULONG x = 0; x < bhLogo->biWidth/16; x++)
		{
			xx = x*16;
			//if(yy%3 == 1) xx += debugValue8;
			//if(yy%3 == 0) xx += debugValue9;

			b1 = bLogo[xx+yy];
			b2 = bLogo[xx+1+yy];
			b3 = bLogo[xx+2+yy];
			b4 = bLogo[xx+3+yy];
			b5 = bLogo[xx+4+yy];
			b6 = bLogo[xx+5+yy];
			b7 = bLogo[xx+6+yy];
			b8 = bLogo[xx+7+yy];
			b9 = bLogo[xx+8+yy];
			b10 = bLogo[xx+9+yy];
			b11 = bLogo[xx+10+yy];
			b12 = bLogo[xx+11+yy];
			b13 = bLogo[xx+12+yy];   
			b14 = bLogo[xx+13+yy];
			b15 = bLogo[xx+14+yy];
			b16 = bLogo[xx+15+yy];
			


			planes[position+0] = ((b1>>0) & 1) *0b1000000000000000+
			((b2>>0) & 1) *0b0100000000000000+
			((b3>>0) & 1) *0b0010000000000000+
			((b4>>0) & 1) *0b0001000000000000+
			((b5>>0) & 1) *0b0000100000000000+
			((b6>>0) & 1) *0b0000010000000000+
			((b7>>0) & 1) *0b0000001000000000+
			((b8>>0) & 1) *0b0000000100000000+
			((b9>>0) & 1) *0b0000000010000000+
			((b10>>0) & 1) *0b0000000001000000+
			((b11>>0) & 1) *0b0000000000100000+
			((b12>>0) & 1) *0b0000000000010000+
			((b13>>0) & 1) *0b0000000000001000+
			((b14>>0) & 1) *0b0000000000000100+
			((b15>>0) & 1) *0b0000000000000010+
			((b16>>0) & 1) *0b0000000000000001;
			planes[position+1] = ((b1>>1) & 1) *0b1000000000000000+
			((b2>>1) & 1) *0b0100000000000000+
			((b3>>1) & 1) *0b0010000000000000+
			((b4>>1) & 1) *0b0001000000000000+
			((b5>>1) & 1) *0b0000100000000000+
			((b6>>1) & 1) *0b0000010000000000+
			((b7>>1) & 1) *0b0000001000000000+
			((b8>>1) & 1) *0b0000000100000000+
			((b9>>1) & 1) *0b0000000010000000+
			((b10>>1) & 1) *0b0000000001000000+
			((b11>>1) & 1) *0b0000000000100000+
			((b12>>1) & 1) *0b0000000000010000+
			((b13>>1) & 1) *0b0000000000001000+
			((b14>>1) & 1) *0b0000000000000100+
			((b15>>1) & 1) *0b0000000000000010+
			((b16>>1) & 1) *0b0000000000000001;
			planes[position+2] = ((b1>>2) & 1) *0b1000000000000000+
			((b2>>2) & 1) *0b0100000000000000+
			((b3>>2) & 1) *0b0010000000000000+
			((b4>>2) & 1) *0b0001000000000000+
			((b5>>2) & 1) *0b0000100000000000+
			((b6>>2) & 1) *0b0000010000000000+
			((b7>>2) & 1) *0b0000001000000000+
			((b8>>2) & 1) *0b0000000100000000+
			((b9>>2) & 1) *0b0000000010000000+
			((b10>>2) & 1) *0b0000000001000000+
			((b11>>2) & 1) *0b0000000000100000+
			((b12>>2) & 1) *0b0000000000010000+
			((b13>>2) & 1) *0b0000000000001000+
			((b14>>2) & 1) *0b0000000000000100+
			((b15>>2) & 1) *0b0000000000000010+
			((b16>>2) & 1) *0b0000000000000001;
			planes[position+3] = ((b1>>3) & 1) *0b1000000000000000+
			((b2>>3) & 1) *0b0100000000000000+
			((b3>>3) & 1) *0b0010000000000000+
			((b4>>3) & 1) *0b0001000000000000+
			((b5>>3) & 1) *0b0000100000000000+
			((b6>>3) & 1) *0b0000010000000000+
			((b7>>3) & 1) *0b0000001000000000+
			((b8>>3) & 1) *0b0000000100000000+
			((b9>>3) & 1) *0b0000000010000000+
			((b10>>3) & 1) *0b0000000001000000+
			((b11>>3) & 1) *0b0000000000100000+
			((b12>>3) & 1) *0b0000000000010000+
			((b13>>3) & 1) *0b0000000000001000+
			((b14>>3) & 1) *0b0000000000000100+
			((b15>>3) & 1) *0b0000000000000010+
			((b16>>3) & 1) *0b0000000000000001;
			position+=4;
		}
		//position+=PLANEWIDTH/2;
	}
}

void DrawColorMap(UBYTE (*map)[256])
{
	UWORD position;
	unsigned char b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15,b16;
	unsigned char byte;
	ULONG xx,yy;
	UBYTE offsety;
	UWORD startOffset;

	offsety = 0;
	startOffset = 0;

	position = startOffset;

	for (ULONG y=0; y < 200; y++)
	{
		//yy = (y - 1) * 256*4;
		position = y * PLANEWIDTH/2 * 4;

		for (ULONG x = 0; x < 256/16; x++)
		{
			xx = x*16;

			b1 = map[xx+0][y];
			b2 = map[xx+1][y];
			b3 = map[xx+2][y];
			b4 = map[xx+3][y];
			b5 = map[xx+4][y];
			b6 = map[xx+5][y];
			b7 = map[xx+6][y];
			b8 = map[xx+7][y];
			b9 = map[xx+8][y];
			b10 = map[xx+9][y];
			b11 = map[xx+10][y];
			b12 = map[xx+11][y];
			b13 = map[xx+12][y];  
			b14 = map[xx+13][y];
			b15 = map[xx+14][y];
			b16 = map[xx+15][y];
			


			planes[position+0] = ((b1>>0) & 1) *0b1000000000000000+
			((b2>>0) & 1) *0b0100000000000000+
			((b3>>0) & 1) *0b0010000000000000+
			((b4>>0) & 1) *0b0001000000000000+
			((b5>>0) & 1) *0b0000100000000000+
			((b6>>0) & 1) *0b0000010000000000+
			((b7>>0) & 1) *0b0000001000000000+
			((b8>>0) & 1) *0b0000000100000000+
			((b9>>0) & 1) *0b0000000010000000+
			((b10>>0) & 1) *0b0000000001000000+
			((b11>>0) & 1) *0b0000000000100000+
			((b12>>0) & 1) *0b0000000000010000+
			((b13>>0) & 1) *0b0000000000001000+
			((b14>>0) & 1) *0b0000000000000100+
			((b15>>0) & 1) *0b0000000000000010+
			((b16>>0) & 1) *0b0000000000000001;
			planes[position+1] = ((b1>>1) & 1) *0b1000000000000000+
			((b2>>1) & 1) *0b0100000000000000+
			((b3>>1) & 1) *0b0010000000000000+
			((b4>>1) & 1) *0b0001000000000000+
			((b5>>1) & 1) *0b0000100000000000+
			((b6>>1) & 1) *0b0000010000000000+
			((b7>>1) & 1) *0b0000001000000000+
			((b8>>1) & 1) *0b0000000100000000+
			((b9>>1) & 1) *0b0000000010000000+
			((b10>>1) & 1) *0b0000000001000000+
			((b11>>1) & 1) *0b0000000000100000+
			((b12>>1) & 1) *0b0000000000010000+
			((b13>>1) & 1) *0b0000000000001000+
			((b14>>1) & 1) *0b0000000000000100+
			((b15>>1) & 1) *0b0000000000000010+
			((b16>>1) & 1) *0b0000000000000001;
			planes[position+2] = ((b1>>2) & 1) *0b1000000000000000+
			((b2>>2) & 1) *0b0100000000000000+
			((b3>>2) & 1) *0b0010000000000000+
			((b4>>2) & 1) *0b0001000000000000+
			((b5>>2) & 1) *0b0000100000000000+
			((b6>>2) & 1) *0b0000010000000000+
			((b7>>2) & 1) *0b0000001000000000+
			((b8>>2) & 1) *0b0000000100000000+
			((b9>>2) & 1) *0b0000000010000000+
			((b10>>2) & 1) *0b0000000001000000+
			((b11>>2) & 1) *0b0000000000100000+
			((b12>>2) & 1) *0b0000000000010000+
			((b13>>2) & 1) *0b0000000000001000+
			((b14>>2) & 1) *0b0000000000000100+
			((b15>>2) & 1) *0b0000000000000010+
			((b16>>2) & 1) *0b0000000000000001;
			planes[position+3] = ((b1>>3) & 1) *0b1000000000000000+
			((b2>>3) & 1) *0b0100000000000000+
			((b3>>3) & 1) *0b0010000000000000+
			((b4>>3) & 1) *0b0001000000000000+
			((b5>>3) & 1) *0b0000100000000000+
			((b6>>3) & 1) *0b0000010000000000+
			((b7>>3) & 1) *0b0000001000000000+
			((b8>>3) & 1) *0b0000000100000000+
			((b9>>3) & 1) *0b0000000010000000+
			((b10>>3) & 1) *0b0000000001000000+
			((b11>>3) & 1) *0b0000000000100000+
			((b12>>3) & 1) *0b0000000000010000+
			((b13>>3) & 1) *0b0000000000001000+
			((b14>>3) & 1) *0b0000000000000100+
			((b15>>3) & 1) *0b0000000000000010+
			((b16>>3) & 1) *0b0000000000000001;
			position+=4;
		}
		//position+=PLANEWIDTH/2;
	}
}