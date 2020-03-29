
#ifdef AMIGA
void ClearBuffor()
{
	memset(engine.renderer.plane1W, 0, PLANEWIDTH*PLANEHEIGHT);
	memset(engine.renderer.plane2W, 0, PLANEWIDTH*PLANEHEIGHT);
	memset(engine.renderer.plane3W, 0, PLANEWIDTH*PLANEHEIGHT);
	memset(engine.renderer.plane4W, 0, PLANEWIDTH*PLANEHEIGHT);
	
}
#else
void ClearBuffor()
{
	memset(engine.renderer.planes, 0, PLANEWIDTH*PLANEHEIGHT);
}
#endif

void DrawSprite4b(unsigned char *bLogo, BITMAPINFOHEADER *bhLogo, 
					UWORD posX, UWORD posY, WORD spriteIndexX, WORD spriteIndexY,
					UWORD spriteSizeX, UWORD spriteSizeY)
{
	UWORD position;
	UWORD word1, word2, word3, word4, mask;

	WORD planePosX = posX>>4;
	BYTE leftGap = posX - (planePosX<<4);
	BYTE rightGap = 16 - leftGap;

	UBYTE xSteps = (spriteSizeX>>4);


	//position = startOffset;

	UWORD baseX = spriteIndexX*(spriteSizeX>>4);
	UWORD baseY = spriteIndexY*spriteSizeY;


#ifdef AMIGA
	position = (posY - (spriteSizeY>>1)) * PLANEWIDTHWORD + planePosX - (spriteSizeX>>5);
    UWORD *firstCol = engine.renderer.plane1W + position;
    UWORD *secondCol = engine.renderer.plane2W + position;
    UWORD *thirdCol = engine.renderer.plane3W + position;
    UWORD *fourthCol = engine.renderer.plane4W + position;
    #else 
	position = (posY - (spriteSizeY/2)) * PLANEWIDTHWORD + planePosX*4 - spriteSizeX/32*4;
    UWORD *firstCol = engine.renderer.planes + position;
    UWORD *secondCol = engine.renderer.planes + position + 1;
    UWORD *thirdCol = engine.renderer.planes + position + 2;
    UWORD *fourthCol = engine.renderer.planes + position + 3;
	#endif

	UWORD wordWidth = bhLogo->biWidth>>4;

	UWORD size = bhLogo->biHeight*wordWidth;
	UWORD offset = baseY*wordWidth + baseX;

	UWORD *bmpRowPtr1 = (UWORD *)bLogo + offset;
	UWORD *bmpRowPtr2 = bmpRowPtr1 + size;
	UWORD *bmpRowPtr3 = bmpRowPtr2 + size;
	UWORD *bmpRowPtr4 = bmpRowPtr3 + size;

	UWORD *maskPtr = (UWORD *)bLogo  + offset + (bhLogo->biSizeImage>>1);
	

	for (UWORD y =0; y < spriteSizeY; y++)
	{
		
        UWORD *firstPos = firstCol;
        UWORD *secondPos = secondCol;
        UWORD *thirdPos = thirdCol;
        UWORD *fourthPos = fourthCol;

		UWORD prevValue1 = 0;
		UWORD prevValue2 = 0;
		UWORD prevValue3 = 0;
		UWORD prevValue4 = 0;
		UWORD prevMask = 0;

		UWORD currValue1;
		UWORD currValue2;
		UWORD currValue3;
		UWORD currValue4;
		UWORD currMask;

		for (UWORD x = 0; x < xSteps; x++)
		{
			currValue1 = *(bmpRowPtr1+x);
			currValue2 = *(bmpRowPtr2+x);
			currValue3 = *(bmpRowPtr3+x);
			currValue4 = *(bmpRowPtr4+x);
			currMask = *(maskPtr+x);

			word1 = (prevValue1 << rightGap) + (currValue1 >> leftGap);
			word2 = (prevValue2 << rightGap) + (currValue2 >> leftGap);
			word3 = (prevValue3 << rightGap) + (currValue3 >> leftGap);
			word4 = (prevValue4 << rightGap) + (currValue4 >> leftGap);
			mask = (prevMask << rightGap) + (currMask >> leftGap);

			*firstPos = (word1 & mask) | (*firstPos & ~mask );
			*secondPos = (word2 & mask) | (*secondPos & ~mask );
			*thirdPos = (word3 & mask) | (*thirdPos & ~mask );
			*fourthPos = (word4 & mask) | (*fourthPos & ~mask );
			
			prevValue1 = currValue1;
			prevValue2 = currValue2;
			prevValue3 = currValue3;
			prevValue4 = currValue4;
			prevMask = currMask;


			
			#ifdef AMIGA
			firstPos++;
			secondPos++;
			thirdPos++;
			fourthPos++;
			#else
            firstPos+=4;
            secondPos+=4;
            thirdPos+=4;
            fourthPos+=4;
			#endif
		
		}

		word1 = prevValue1 << rightGap;
		word2 = prevValue2 << rightGap;
		word3 = prevValue3 << rightGap;
		word4 = prevValue4 << rightGap;
		mask = prevMask << rightGap;

		*firstPos = (word1 & mask) | (*firstPos & ~mask );
		*secondPos = (word2 & mask) | (*secondPos & ~mask );
		*thirdPos = (word3 & mask) | (*thirdPos & ~mask );
		*fourthPos = (word4 & mask) | (*fourthPos & ~mask );


        firstCol += PLANEWIDTHWORD;
        secondCol += PLANEWIDTHWORD;
        thirdCol += PLANEWIDTHWORD;
        fourthCol += PLANEWIDTHWORD;

		bmpRowPtr1 += wordWidth;
		bmpRowPtr2 += wordWidth;
		bmpRowPtr3 += wordWidth;
		bmpRowPtr4 += wordWidth;

		maskPtr += wordWidth;
	}
}

void DrawBitmap4bCenter(unsigned char *bLogo, BITMAPINFOHEADER *bhLogo)
{

	UWORD position;
	UWORD word1, word2, word3, word4;
	ULONG xx, yy;
#ifdef AMIGA
	position = ((PLANEHEIGHT-bhLogo->biHeight)/2) * PLANEWIDTHWORD + (320-bhLogo->biWidth)/32;
    UWORD *firstCol = engine.renderer.plane1W + position;
    UWORD *secondCol = engine.renderer.plane2W + position;
    UWORD *thirdCol = engine.renderer.plane3W + position;
    UWORD *fourthCol = engine.renderer.plane4W + position;
    #else 
	position = ((PLANEHEIGHT-bhLogo->biHeight)/2) * PLANEWIDTHWORD + (320-bhLogo->biWidth)/32*4;
    UWORD *firstCol = engine.renderer.planes + position;
    UWORD *secondCol = engine.renderer.planes + position + 1;
    UWORD *thirdCol = engine.renderer.planes + position + 2;
    UWORD *fourthCol = engine.renderer.planes + position + 3;
	#endif


	//position = startOffset;

	UWORD wordWidth = bhLogo->biWidth >> 4;

	UWORD *bmpPtr1 = (UWORD *)bLogo;
	UWORD *bmpPtr2 = (UWORD *)bLogo+bhLogo->biHeight*wordWidth;
	UWORD *bmpPtr3 = (UWORD *)bLogo+2*bhLogo->biHeight*wordWidth;
	UWORD *bmpPtr4 = (UWORD *)bLogo+3*bhLogo->biHeight*wordWidth;

	for (ULONG y = 0; y < bhLogo->biHeight; y++)
	{

        UWORD *firstPos = firstCol;
        UWORD *secondPos = secondCol;
        UWORD *thirdPos = thirdCol;
        UWORD *fourthPos = fourthCol;

		for (ULONG x = 0; x < wordWidth; x++)
		{

			word1 = *bmpPtr1++;
			word2 = *bmpPtr2++;
			word3 = *bmpPtr3++;
			word4 = *bmpPtr4++;

			*firstPos = word1;
			*secondPos = word2;
			*thirdPos = word3;
			*fourthPos = word4;

			 #ifdef AMIGA
            firstPos++;
            secondPos++;
            thirdPos++;
            fourthPos++;
            #else
            firstPos+=4;
            secondPos+=4;
            thirdPos+=4;
            fourthPos+=4;
			#endif
		}
        firstCol += PLANEWIDTHWORD;
        secondCol += PLANEWIDTHWORD;
        thirdCol += PLANEWIDTHWORD;
        fourthCol += PLANEWIDTHWORD;
		
	}
}

void DrawPixel(UWORD x, UWORD y, UBYTE color)
{
		UWORD posX = x/16;
	UWORD leftGap = x - posX*16;
	UWORD rightGap = 16 - leftGap;

	#ifdef AMIGA
	UWORD firstPos = y*PLANEWIDTHWORD+posX;
	UWORD secondPos = firstPos+1;
	#else
	UWORD firstPos = y*PLANEWIDTHWORD+posX*4;
	UWORD secondPos = firstPos+4;
	#endif

	UBYTE col = color & 15;
	WORD pattern = col|(col << 4)|(col << 8)|(col << 12);

	WORD leftPixelPattern = pattern >> leftGap;
	WORD leftScreenPattern = 0b1111111111111111 << rightGap;

	WORD rightPixelPattern = pattern << rightGap;
	WORD rightScreenPattern = 0b1111111111111111 >> leftGap;

	#ifdef AMIGA
	engine.renderer.plane1W[firstPos] = (leftPixelPattern) + (engine.renderer.plane1W[firstPos] & (leftScreenPattern));
	engine.renderer.plane2W[firstPos] = (leftPixelPattern) + (engine.renderer.plane2W[firstPos] & (leftScreenPattern));
	engine.renderer.plane3W[firstPos] = (leftPixelPattern) + (engine.renderer.plane3W[firstPos] & (leftScreenPattern));
	engine.renderer.plane4W[firstPos] = (leftPixelPattern) + (engine.renderer.plane4W[firstPos] & (leftScreenPattern));
	
	engine.renderer.plane1W[secondPos] = (rightPixelPattern) + (engine.renderer.plane1W[secondPos] & (rightScreenPattern));
	engine.renderer.plane2W[secondPos] = (rightPixelPattern) + (engine.renderer.plane2W[secondPos] & (rightScreenPattern));
	engine.renderer.plane3W[secondPos] = (rightPixelPattern) + (engine.renderer.plane3W[secondPos] & (rightScreenPattern));
	engine.renderer.plane4W[secondPos] = (rightPixelPattern) + (engine.renderer.plane4W[secondPos] & (rightScreenPattern));
	#else
	engine.renderer.planes[firstPos] = (leftPixelPattern) + (engine.renderer.planes[firstPos] & (leftScreenPattern));
	engine.renderer.planes[firstPos+1] = (leftPixelPattern) + (engine.renderer.planes[firstPos+1] & (leftScreenPattern));
	engine.renderer.planes[firstPos+2] = (leftPixelPattern) + (engine.renderer.planes[firstPos+2] & (leftScreenPattern));
	engine.renderer.planes[firstPos+3] = (leftPixelPattern) + (engine.renderer.planes[firstPos+3] & (leftScreenPattern));
	
	engine.renderer.planes[secondPos] = (rightPixelPattern) + (engine.renderer.planes[secondPos] & (rightScreenPattern));
	engine.renderer.planes[secondPos+1] = (rightPixelPattern) + (engine.renderer.planes[secondPos+1] & (rightScreenPattern));
	engine.renderer.planes[secondPos+2] = (rightPixelPattern) + (engine.renderer.planes[secondPos+2] & (rightScreenPattern));
	engine.renderer.planes[secondPos+3] = (rightPixelPattern) + (engine.renderer.planes[secondPos+3] & (rightScreenPattern));
	#endif
}

void DrawCrosshair(UWORD x, UWORD y)
{
	UWORD posX = x/16;
	UWORD leftGap = x - posX*16;
	UWORD rightGap = 16 - leftGap;

	#ifdef AMIGA
	UWORD firstPos = y*PLANEWIDTHWORD+posX;
	UWORD secondPos = firstPos+1;
	#else
	UWORD firstPos = y*PLANEWIDTHWORD+posX*4;
	UWORD secondPos = firstPos+4;
	#endif

	WORD leftPixelPattern = 0b1000100110010001 >> leftGap;
	WORD leftScreenPattern = 0b1111111111111111 << rightGap;

	WORD rightPixelPattern = 0b1000100110010001 << rightGap;
	WORD rightScreenPattern = 0b1111111111111111 >> leftGap;

	#ifdef AMIGA
	engine.renderer.plane1W[firstPos] = (leftPixelPattern) + (engine.renderer.plane1W[firstPos] & (leftScreenPattern));
	engine.renderer.plane2W[firstPos] = (leftPixelPattern) + (engine.renderer.plane2W[firstPos] & (leftScreenPattern));
	engine.renderer.plane3W[firstPos] = (leftPixelPattern) + (engine.renderer.plane3W[firstPos] & (leftScreenPattern));
	engine.renderer.plane4W[firstPos] = (leftPixelPattern) + (engine.renderer.plane4W[firstPos] & (leftScreenPattern));
	
	engine.renderer.plane1W[secondPos] = (rightPixelPattern) + (engine.renderer.plane1W[secondPos] & (rightScreenPattern));
	engine.renderer.plane2W[secondPos] = (rightPixelPattern) + (engine.renderer.plane2W[secondPos] & (rightScreenPattern));
	engine.renderer.plane3W[secondPos] = (rightPixelPattern) + (engine.renderer.plane3W[secondPos] & (rightScreenPattern));
	engine.renderer.plane4W[secondPos] = (rightPixelPattern) + (engine.renderer.plane4W[secondPos] & (rightScreenPattern));
	#else
	engine.renderer.planes[firstPos] = (leftPixelPattern) + (engine.renderer.planes[firstPos] & (leftScreenPattern));
	engine.renderer.planes[firstPos+1] = (leftPixelPattern) + (engine.renderer.planes[firstPos+1] & (leftScreenPattern));
	engine.renderer.planes[firstPos+2] = (leftPixelPattern) + (engine.renderer.planes[firstPos+2] & (leftScreenPattern));
	engine.renderer.planes[firstPos+3] = (leftPixelPattern) + (engine.renderer.planes[firstPos+3] & (leftScreenPattern));
	
	engine.renderer.planes[secondPos] = (rightPixelPattern) + (engine.renderer.planes[secondPos] & (rightScreenPattern));
	engine.renderer.planes[secondPos+1] = (rightPixelPattern) + (engine.renderer.planes[secondPos+1] & (rightScreenPattern));
	engine.renderer.planes[secondPos+2] = (rightPixelPattern) + (engine.renderer.planes[secondPos+2] & (rightScreenPattern));
	engine.renderer.planes[secondPos+3] = (rightPixelPattern) + (engine.renderer.planes[secondPos+3] & (rightScreenPattern));
	#endif
}

void DrawPixelWord(UWORD x, UWORD y, UBYTE color)
{
  
#ifdef AMIGA
  engine.renderer.plane1W[y * PLANEWIDTHWORD + x] = ( (color>>0) & 1) * 0xffff;
  engine.renderer.plane2W[y * PLANEWIDTHWORD + x] = ( (color>>1) & 1) * 0xffff;
  engine.renderer.plane3W[y * PLANEWIDTHWORD + x] = ( (color>>2) & 1) * 0xffff;
  engine.renderer.plane4W[y * PLANEWIDTHWORD + x] = ( (color>>3) & 1) * 0xffff;
  #else
  engine.renderer.planes[y * PLANEWIDTHWORD + x*4] = ( (color>>0) & 1) * 0xffff;
  engine.renderer.planes[y * PLANEWIDTHWORD + x*4 + 1] = ( (color>>1) & 1) * 0xffff;
  engine.renderer.planes[y * PLANEWIDTHWORD + x*4 + 2] = ( (color>>2) & 1) * 0xffff;
  engine.renderer.planes[y * PLANEWIDTHWORD + x*4 + 3] = ( (color>>3) & 1) * 0xffff;
  #endif
}



void ConvertIntToChar(int number, char *test, int size)
{
	int temp;
	int i = size-2;
	while (number != 0)
	{
		temp = number % 10;
		number /= 10;
		test[i] = '0' + temp;
		i--;
	}
	while (i >= 0)
	{
		test[i] = ' ';
		i--;
	}
	test[size-1] = 0;
}
