#include "engine.h"
#include "settings.h"

//TODO ProcessRayCastProgressiveNonInterleaved

void CalculateRayCasts(WORD (*rayCastX), WORD (*rayCastY), 
                        UBYTE xSize, UBYTE ySize, int stepSize)
{
	WORD sxx;
	WORD syy;
	WORD tzz; //depth step value
	WORD fovX = xSize/xFOV; //width FOV
	WORD fovY = ySize/yFOV;//5; //height FOV
	WORD sxxx;
	WORD xMiddle = xSize/2;
	WORD yMiddle = ySize/2;


	tzz = 1;
	for(int tz=1;tz<renderingDepth;tz++)
	{
        WORD offsetTZ = (20*tz)/renderingDepth;
		DrawPixelWord((offsetTZ), PLANEHEIGHT-8,(offsetTZ));
		DrawPixelWord((offsetTZ), PLANEHEIGHT-7,(offsetTZ));
		DrawPixelWord((offsetTZ), PLANEHEIGHT-6,(offsetTZ));
		DrawPixelWord((offsetTZ), PLANEHEIGHT-5,(offsetTZ));
		DrawPixelWord((offsetTZ), PLANEHEIGHT-4,(offsetTZ));
		DrawPixelWord((offsetTZ), PLANEHEIGHT-3,(offsetTZ));
		DrawPixelWord((offsetTZ), PLANEHEIGHT-2,(offsetTZ));
		DrawPixelWord((offsetTZ), PLANEHEIGHT-1,(offsetTZ));
		#ifdef AMIGA
			CopyFastToChipW(s_pBuffer->pBack);
		#endif
		//high - 2 - 8
		tzz += calculationDepthStep + tz / calculationDepthDivider; //+tz/16; //increase step with the distance from camera
		WORD *rayXPtr = rayCastX + tz;
        for(int sx=-xMiddle;sx<xMiddle;sx++)
		{
			sxx = (sx * tzz)/stepModifier; //make smaller steps
			sxxx = sxx/fovX;
            *rayXPtr = sxxx; 
            rayXPtr += TERRAINDEPTH;
            WORD *rayYPtr = rayCastY + tz;
			for(int sy=-yMiddle;sy<yMiddle;sy++)
			{
				syy = (sy*stepSize * tzz)/stepModifier;//make smaller steps
				*rayYPtr = syy/fovY;
                rayYPtr += TERRAINDEPTH;
			}
		}
	}

}



UBYTE ProcessWord1v6(UBYTE rounds, UBYTE sx, UBYTE sy, UWORD *_tz, UWORD *tzz, UBYTE px, UBYTE py,UBYTE ph,
UWORD *address1, UWORD *address2, 
WORD (*rayCastX), WORD (*rayCastY), UWORD (*map)[256], UBYTE threshold)
{
	UWORD mapValue;
	WORD slope;
	UBYTE c = 99;
	UBYTE th;
	UBYTE tz;
	UBYTE iHor=0;

	sx = sx + 2;
	tz = tzz[iHor];//set current depth - tz
    WORD *rayXPtr = rayCastX + sx*TERRAINDEPTH + tz;
    WORD *rayYPtr = rayCastY + sy*TERRAINDEPTH + tz;
	while(tz < threshold)//check depth step by step
	{
		mapValue = map[ (UBYTE)( px + *rayXPtr ) ][ (UBYTE)( py + (tz<<renderingDepthStep) ) ];//read color + height
		th = mapValue;//take just the height
		slope = th - (ph + *rayYPtr);//check if read height is higher than what we expect from the raycast table
		if(slope > 0)
		{
			c = (mapValue >> 8);
			tzz[iHor] = tz;//save the depth we've arrived at
			break;
		}
		else
		{	
			tz++;//go step in depth if no height hit
            ++rayXPtr;
            ++rayYPtr;
		}
	}

	if(c == 99) c = skyColor - ph/32 - sy/8; //draw sky if too deep
	*address1 = (c<<10) + (c<<5) + (c); *address2 = *address1;
	
	
	return tz;
}
UBYTE ProcessWord2v6(UBYTE rounds, UBYTE sx, UBYTE sy, UWORD *_tz, UWORD *tzz, UBYTE px, UBYTE py,UBYTE ph,
UWORD *address1, UWORD *address2, 
WORD (*rayCastX), WORD (*rayCastY), UWORD (*map)[256], UBYTE threshold)
{
	UWORD mapValue;
	WORD slope;
	UBYTE c[2];
	UBYTE th;
	UBYTE tz;

	sx = sx + 1;
	c[0] = 99;
	c[1] = 99;
    
    WORD *rayXPtr = rayCastX + sx*TERRAINDEPTH + tz;
    WORD *rayYPtr = rayCastY + sy*TERRAINDEPTH + tz;
	//process 1,2,3 or 6 rounds to find colors for this WORD = 16 pixels
	for(UBYTE iHor=0;iHor<2;iHor++)
	{
		
		tz = tzz[iHor];//set current depth - tz
		while(tz < threshold)//check depth step by step
		{
			mapValue = map[ (UBYTE)( px + *rayXPtr ) ][ (UBYTE)( py + (tz<<renderingDepthStep) ) ];//read color + height
			th = mapValue;//take just the height
			slope = th - (ph + *rayYPtr);//check if read height is higher than what we expect from the raycast table
			if(slope > 0)
			{
				c[iHor] = (mapValue >> 8);
				tzz[iHor] = tz;//save the depth we've arrived at
				break;
			}
			else
			{	
				tz++;//go step in depth if no height hit
                ++rayXPtr;
                ++rayYPtr;
			}
		}
		
		sx += 3;
	}
	if(c[0] == 99) c[0] = skyColor - ph/32 - sy/8; //draw sky if too deep
	if(c[1] == 99) c[1] = skyColor - ph/32 - sy/8; //draw sky if too deep
	*address1 = (c[0]<<10) + (c[0]<<5) + (c[0]); *address2 = (c[1]<<10) + (c[1]<<5) + (c[1]);

	return tz;
}
UBYTE ProcessWord3v6(UBYTE rounds, UBYTE sx, UBYTE sy, UWORD *_tz, UWORD *tzz, UBYTE px, UBYTE py,UBYTE ph,
UWORD *address1, UWORD *address2, 
WORD (*rayCastX)[TERRAINDEPTH], WORD (*rayCastY)[TERRAINDEPTH], UWORD (*map)[256], UBYTE threshold)
{
	UWORD mapValue;
	WORD slope;
	UBYTE c[3];
	UBYTE th;
	UBYTE tz;

	c[0] = 99;
	c[1] = 99;
	c[2] = 99;

    WORD *rayXPtr = rayCastX + sx*TERRAINDEPTH + tz;
    WORD *rayYPtr = rayCastY + sy*TERRAINDEPTH + tz;
	//process 1,2,3 or 6 rounds to find colors for this WORD = 16 pixels
	for(UBYTE iHor=0;iHor<3;iHor++)
	{
		
		tz = tzz[iHor];//set current depth - tz
		while(tz < threshold)//check depth step by step
		{
			mapValue = map[ (UBYTE)( px + *rayXPtr ) ][ (UBYTE)( py + (tz<<renderingDepthStep) ) ];//read color + height
			th = mapValue;//take just the height
			slope = th - (ph + *rayYPtr);//check if read height is higher than what we expect from the raycast table
			if(slope > 0)
			{
				c[iHor] = (mapValue >> 8);
				tzz[iHor] = tz;//save the depth we've arrived at
				break;
			}
			else
			{	
				tz++;//go step in depth if no height hit
                ++rayXPtr;
                ++rayYPtr;
			}
		}
		sx +=2;
	}
	if(c[0] == 99) c[0] = skyColor - ph/32 - sy/8; //draw sky if too deep
	if(c[1] == 99) c[1] = skyColor - ph/32 - sy/8; //draw sky if too deep
	if(c[2] == 99) c[2] = skyColor - ph/32 - sy/8; //draw sky if too deep
	*address1 = (c[0]<<10) + (c[0]<<5) + (c[1]); *address2 = (c[1]<<10) + (c[2]<<5) + (c[2]);

	return tz;
}

void ProcessRayCastsProgressive(WORD (*rayCastX), WORD (*rayCastY), UWORD (*map)[256],
	UBYTE px, UBYTE py, UBYTE ph, UBYTE screenStart, UBYTE screenEnd, UBYTE zStart)
{
	UBYTE sx,sy,mist;
	UWORD tz,tzz[6];
	UWORD address1,address2;
	UBYTE threshold1 = TERRAINDEPTH/2;
	UBYTE threshold2 = TERRAINDEPTH - TERRAINDEPTH/4;

	//UWORD positionStart =  (ySize-1)*20 + tableXStart/6;

	UBYTE verticalSteps;

	UBYTE iInit;


	//start with the buffor + vertical stripe start + turning amount
	sx = XTURNBUFFOR + xOffsetOdd;
	//currentScreenYStepSize = xCycles;


	//for each vertical line
    
    #if AMIGA

    UWORD *firstCol = plane1W + YSIZEODD*PLANEWIDTHWORD*2;
    UWORD *secondCol = plane2W + YSIZEODD*PLANEWIDTHWORD*2;
    UWORD *thirdCol = plane3W + YSIZEODD*PLANEWIDTHWORD*2;
    UWORD *fourthCol = plane4W + YSIZEODD*PLANEWIDTHWORD*2;

    #else

    UWORD *firstCol = planes + YSIZEODD*PLANEWIDTHWORD*4;
    UWORD *secondCol = planes + YSIZEODD*PLANEWIDTHWORD*4 + 1;
    UWORD *thirdCol = planes + YSIZEODD*PLANEWIDTHWORD*4 + 2;
    UWORD *fourthCol = planes + YSIZEODD*PLANEWIDTHWORD*4 + 3;

    #endif

    UWORD planeStride = PLANEWIDTHWORD*2;
    
	UWORD word1, word2, word3, word4;
	for(UBYTE iVert=screenStart;iVert<screenEnd;iVert++)
	{
        
        #if AMIGA
        UWORD *firstPos = firstCol + iVert;
        UWORD *secondPos = secondCol + iVert;
        UWORD *thirdPos = thirdCol + iVert;
        UWORD *fourthPos = fourthCol + iVert;
        #else
        UWORD *firstPos = firstCol + iVert*4;
        UWORD *secondPos = secondCol + iVert*4;
        UWORD *thirdPos = thirdCol + iVert*4;
        UWORD *fourthPos = fourthCol + iVert*4;
        #endif

		//start from the bottom
		sy = 0;
		//position = positionStart + iVert ;//+ 80*12;
		
		//init values for this vertical line
		tzz[0]=zStart;tzz[1]=zStart;tzz[2]=zStart;
		//tzz[3]=zStart;tzz[4]=zStart;tzz[5]=zStart;
		tz = zStart;

		//process this vertical line
		while(sy < YSIZEODD)
		{ 
			 if(tz < threshold1)			
			 {
	            UBYTE byte1, byte2, byte3, byte4;
				tz = ProcessWord1v6(1,sx,sy,&tz,tzz,px,py,ph,&address1,&address2,rayCastX, rayCastY, map, threshold1);
				byte1 = dither3x2EvenP1[ address1 ];
				word1 = (byte1<<8) + byte1;
				byte2 = dither3x2EvenP2[ address1 ];
				word2 = (byte2<<8) + byte2;
				byte3 = dither3x2EvenP3[ address1 ];
				word3 = (byte3<<8) + byte3;
				byte4 = dither3x2EvenP4[ address1 ];
				word4 = (byte4<<8) + byte4;

			 }
			else if(tz < threshold2)			
			 {
				tz = ProcessWord2v6(2,sx,sy,&tz,tzz,px,py,ph,&address1,&address2,rayCastX, rayCastY, map, threshold2);

				word1 = (dither3x2EvenP1[ address1 ]<<8) + dither3x2EvenP1[ address2 ];
				word2 = (dither3x2EvenP2[ address1 ]<<8) + dither3x2EvenP2[ address2 ];
				word3 = (dither3x2EvenP3[ address1 ]<<8) + dither3x2EvenP3[ address2 ];
				word4 = (dither3x2EvenP4[ address1 ]<<8) + dither3x2EvenP4[ address2 ];

			 }
			else if(tz < TERRAINDEPTH)			
			 {
				tz = ProcessWord3v6(3,sx,sy,&tz,tzz,px,py,ph,&address1,&address2,rayCastX, rayCastY, map, TERRAINDEPTH);

				word1 = (dither3x2EvenP1[ address1 ]<<8) + dither3x2EvenP1[ address2 ];

				word2 = (dither3x2EvenP2[ address1 ]<<8) + dither3x2EvenP2[ address2 ];
				word3 = (dither3x2EvenP3[ address1 ]<<8) + dither3x2EvenP3[ address2 ];
				word4 = (dither3x2EvenP4[ address1 ]<<8) + dither3x2EvenP4[ address2 ];
			 }
			 else 	
			 {
	            UBYTE byte1, byte2, byte3, byte4;
				UBYTE color = skyColor - ph/32 -sy/8;
				address1 = (color<<10) + (color<<5) + (color);
	
				byte1 = dither3x2EvenP1[ address1 ];
				word1 = (byte1<<8) + byte1;

				byte2 = dither3x2EvenP2[ address1 ];
				word2 = (byte2<<8) + byte2;

				byte3 = dither3x2EvenP3[ address1 ];
				word3 = (byte3<<8) + byte3;

				byte4 = dither3x2EvenP4[ address1 ];
				word4 = (byte4<<8) + byte4;


			 }

             
            *firstPos = word1;
            firstPos -= planeStride;
            *firstPos = word1;
            firstPos -= planeStride;
            *firstPos = word1;
            firstPos -= planeStride;
            *firstPos = word1;
            firstPos -= planeStride;
            
            *secondPos = word2;
            secondPos -= planeStride;
            *secondPos = word2;
            secondPos -= planeStride;
            *secondPos = word2;
            secondPos -= planeStride;
            *secondPos = word2;
            secondPos -= planeStride;
            
            *thirdPos = word3;
            thirdPos -= planeStride;
            *thirdPos = word3;
            thirdPos -= planeStride;
            *thirdPos = word3;
            thirdPos -= planeStride;
            *thirdPos = word3;
            thirdPos -= planeStride;

            *fourthPos = word4;
            fourthPos -= planeStride;
            *fourthPos = word4;
            fourthPos -= planeStride;
            *fourthPos = word4;
            fourthPos -= planeStride;
            *fourthPos = word4;
            fourthPos -= planeStride;
			//go step higher in the raycast table
            
            #if AMIGA
            sy+=8;
            #elif ATARI
            sy += 2;
            #endif
		}
		sx += 6;//go to the next vertical line
	}
}


void ProcessRayCastsProgressiveNonInterleaved(WORD (*rayCastX), WORD (*rayCastY), UWORD (*map)[256],
	UBYTE px, UBYTE py, UBYTE ph, UBYTE screenStart, UBYTE screenEnd, UBYTE zStart)
{
	UBYTE sx,sy,mist;
	UWORD tz,tzz[6];
	UWORD address1,address2;
	UBYTE threshold1 = TERRAINDEPTH/2;
	UBYTE threshold2 = TERRAINDEPTH - TERRAINDEPTH/4;

	//UWORD positionStart =  (ySize-1)*20 + tableXStart/6;

	UBYTE verticalSteps;

	UBYTE iInit;


	//start with the buffor + vertical stripe start + turning amount
	sx = XTURNBUFFOR + xOffsetOdd;
	//currentScreenYStepSize = xCycles;


	//for each vertical line
    
    #if AMIGA

    UWORD *firstCol = plane1W + YSIZEODD*PLANEWIDTHWORD*2;
    UWORD *secondCol = plane2W + YSIZEODD*PLANEWIDTHWORD*2;
    UWORD *thirdCol = plane3W + YSIZEODD*PLANEWIDTHWORD*2;
    UWORD *fourthCol = plane4W + YSIZEODD*PLANEWIDTHWORD*2;

    #else

    UWORD *firstCol = planes + YSIZEODD*PLANEWIDTHWORD*4;
    UWORD *secondCol = planes + YSIZEODD*PLANEWIDTHWORD*4 + 1;
    UWORD *thirdCol = planes + YSIZEODD*PLANEWIDTHWORD*4 + 2;
    UWORD *fourthCol = planes + YSIZEODD*PLANEWIDTHWORD*4 + 3;

    #endif

    UWORD planeStride = PLANEWIDTHWORD;
    
	UWORD word1, word2, word3, word4;
	for(UBYTE iVert=screenStart;iVert<screenEnd;iVert++)
	{
        
        #if AMIGA
        UWORD *firstPos = firstCol + iVert;
        UWORD *secondPos = secondCol + iVert;
        UWORD *thirdPos = thirdCol + iVert;
        UWORD *fourthPos = fourthCol + iVert;
        #else
        UWORD *firstPos = firstCol + iVert*4;
        UWORD *secondPos = secondCol + iVert*4;
        UWORD *thirdPos = thirdCol + iVert*4;
        UWORD *fourthPos = fourthCol + iVert*4;
        #endif

		//start from the bottom
		sy = 0;
		//position = positionStart + iVert ;//+ 80*12;
		
		//init values for this vertical line
		tzz[0]=zStart;tzz[1]=zStart;tzz[2]=zStart;
		//tzz[3]=zStart;tzz[4]=zStart;tzz[5]=zStart;
		tz = zStart;

		//process this vertical line
		while(sy < YSIZEODD)
		{ 
			 if(tz < threshold1)			
			 {
	            UBYTE byte1, byte2, byte3, byte4;
				tz = ProcessWord1v6(1,sx,sy,&tz,tzz,px,py,ph,&address1,&address2,rayCastX, rayCastY, map, threshold1);
				byte1 = dither3x2EvenP1[ address1 ];
				word1 = (byte1<<8) + byte1;
				byte2 = dither3x2EvenP2[ address1 ];
				word2 = (byte2<<8) + byte2;
				byte3 = dither3x2EvenP3[ address1 ];
				word3 = (byte3<<8) + byte3;
				byte4 = dither3x2EvenP4[ address1 ];
				word4 = (byte4<<8) + byte4;

			 }
			else if(tz < threshold2)			
			 {
				tz = ProcessWord2v6(2,sx,sy,&tz,tzz,px,py,ph,&address1,&address2,rayCastX, rayCastY, map, threshold2);

				word1 = (dither3x2EvenP1[ address1 ]<<8) + dither3x2EvenP1[ address2 ];
				word2 = (dither3x2EvenP2[ address1 ]<<8) + dither3x2EvenP2[ address2 ];
				word3 = (dither3x2EvenP3[ address1 ]<<8) + dither3x2EvenP3[ address2 ];
				word4 = (dither3x2EvenP4[ address1 ]<<8) + dither3x2EvenP4[ address2 ];

			 }
			else if(tz < TERRAINDEPTH)			
			 {
				tz = ProcessWord3v6(3,sx,sy,&tz,tzz,px,py,ph,&address1,&address2,rayCastX, rayCastY, map, TERRAINDEPTH);

				word1 = (dither3x2EvenP1[ address1 ]<<8) + dither3x2EvenP1[ address2 ];

				word2 = (dither3x2EvenP2[ address1 ]<<8) + dither3x2EvenP2[ address2 ];
				word3 = (dither3x2EvenP3[ address1 ]<<8) + dither3x2EvenP3[ address2 ];
				word4 = (dither3x2EvenP4[ address1 ]<<8) + dither3x2EvenP4[ address2 ];
			 }
			 else 	
			 {
	            UBYTE byte1, byte2, byte3, byte4;
				UBYTE color = skyColor - ph/32 -sy/8;
				address1 = (color<<10) + (color<<5) + (color);
	
				byte1 = dither3x2EvenP1[ address1 ];
				word1 = (byte1<<8) + byte1;

				byte2 = dither3x2EvenP2[ address1 ];
				word2 = (byte2<<8) + byte2;

				byte3 = dither3x2EvenP3[ address1 ];
				word3 = (byte3<<8) + byte3;

				byte4 = dither3x2EvenP4[ address1 ];
				word4 = (byte4<<8) + byte4;


			 }

            
            UWORD word11 = (word1 << 1)|((word1>>1) & 1);
            UWORD word21 = (word2 << 1)|((word2>>1) & 1);
            UWORD word31 = (word3 << 1)|((word3>>1) & 1);
            UWORD word41 = (word4 << 1)|((word4>>1) & 1);
             
            *firstPos = word1;
            firstPos -= planeStride;
            *firstPos = word11;
            firstPos -= planeStride;
            *firstPos = word1;
            firstPos -= planeStride;
            *firstPos = word11;
            firstPos -= planeStride;
            
            *secondPos = word2;
            secondPos -= planeStride;
            *secondPos = word21;
            secondPos -= planeStride;
            *secondPos = word2;
            secondPos -= planeStride;
            *secondPos = word21;
            secondPos -= planeStride;
            
            *thirdPos = word3;
            thirdPos -= planeStride;
            *thirdPos = word31;
            thirdPos -= planeStride;
            *thirdPos = word3;
            thirdPos -= planeStride;
            *thirdPos = word31;
            thirdPos -= planeStride;

            *fourthPos = word4;
            fourthPos -= planeStride;
            *fourthPos = word41;
            fourthPos -= planeStride;
            *fourthPos = word4;
            fourthPos -= planeStride;
            *fourthPos = word41;
            fourthPos -= planeStride;
			//go step higher in the raycast table
            
            #if AMIGA
            sy+=4;
            #elif ATARI
            sy += 1;
            #endif
		}
		sx += 6;//go to the next vertical line
	}
}

void ProcessRayCastsFull3x2(WORD (*rayCastX), WORD (*rayCastY), UWORD (*map)[256],
UBYTE px, UBYTE py, UBYTE ph, UBYTE screenStart, UBYTE screenEnd, UBYTE zStart)
{

    
	UWORD yOffset = (256 - YSIZEODD*2)/2 * PLANEWIDTHWORD;
    UBYTE baseX = XTURNBUFFOR + xOffsetOdd + screenStart*6;

	//for each vertical line
    

    for(UBYTE x = screenStart; x < screenEnd; ++x)
    {

        for(UBYTE i = 0; i < 6; ++i)
        {
            UBYTE sy = 0;
            UWORD tz = zStart;
            UWORD *rayXPtr = rayCastX + baseX*TERRAINDEPTH + tz;
            UWORD *rayYPtr = rayCastY + tz;
            UBYTE *screenPtr = screen3x2 + ((YSIZEODD)-1)*6 + i;
	        UBYTE mx,my;
	        UWORD mapValue;

            while(tz < renderingDepth)
            {
                mx = px + *rayXPtr;
                my = (py + (tz<<renderingDepthStep));
                mapValue = map[ mx ][ my ];
                UBYTE th = mapValue;

                WORD slope = th - (ph + *rayYPtr);

                if(slope > tz>>2)
                {
                    *screenPtr = ((mapValue >> 8) + ((slope/4) & 1));
                    sy+=1;//go step higher in the raycast table
                    rayYPtr += TERRAINDEPTH;
                    screenPtr-=6;//go step higher on screen
                    if(sy == YSIZEODD) tz=renderingDepth; //break if end of screen
                }
                else if(slope > 0)
                {
                    *screenPtr = (mapValue >> 8) + 2;
                    sy+=1;//go step higher in the raycast table
                    rayYPtr += TERRAINDEPTH;
                    screenPtr-=6;//go step higher on screen
                    if(sy == YSIZEODD) tz=renderingDepth; //break if end of screen
                }
                else
                {	
                    //screen[position] = 0;
                    tz++;//go step in depth if no height hit
                    rayXPtr++;
                    rayYPtr++;
                }
            }
            
            while(sy < YSIZEODD)
            {
                //if(screen[position] == 31)
                //	sy = YSIZE;
                //else
                {
                    *screenPtr =  32 - ph/32 -sy/8;
                    sy+=1;
                    screenPtr-=6;
                }

            }

            baseX++;
        }

        UWORD *planePos1 = plane1W + yOffset + x;
        UWORD *planePos2 = plane2W + yOffset + x;
        UWORD *planePos3 = plane3W + yOffset + x;
        UWORD *planePos4 = plane4W + yOffset + x;
        UWORD sp = 0;

        for(UBYTE y=0;y<YSIZEODD;y++)
	    {

			UWORD address1 = (screen3x2[sp]<<10) + (screen3x2[sp+1]<<5) + (screen3x2[sp+2]);
			UWORD address2 = (screen3x2[sp+3]<<10) + (screen3x2[sp+4]<<5) + (screen3x2[sp+5]);

            
			UWORD word = (dither3x2EvenP1[ address1 ]<<8) + dither3x2EvenP1[ address2 ];
			*planePos1 = word;
            planePos1 += PLANEWIDTHWORD;
			*planePos1 = (word << 1)|((word>>1) & 1);
            planePos1 += PLANEWIDTHWORD;
			word = (dither3x2EvenP2[ address1 ]<<8) + dither3x2EvenP2[ address2 ];
			*planePos2 = word;
            planePos2 += PLANEWIDTHWORD;
			*planePos2 = (word << 1)|((word>>1) & 1);
            planePos2 += PLANEWIDTHWORD;
			word = (dither3x2EvenP3[ address1 ]<<8) + dither3x2EvenP3[ address2 ];
			*planePos3 = word;
            planePos3 += PLANEWIDTHWORD;
			*planePos3 = word = (word << 1)|((word>>1) & 1);
            planePos3 += PLANEWIDTHWORD;
			word = (dither3x2EvenP4[ address1 ]<<8) + dither3x2EvenP4[ address2 ];
			*planePos4 = word;
            planePos4 += PLANEWIDTHWORD;
			*planePos4 = word = (word << 1)|((word>>1) & 1);
            planePos4 += PLANEWIDTHWORD;

            sp += 6;
        }

    }

}


void ProcessRayCastsFull4x4(WORD (*rayCastX), WORD (*rayCastY), UWORD (*map)[256],
UBYTE px, UBYTE py, UBYTE ph, UBYTE screenStart, UBYTE screenEnd, UBYTE zStart)
{

    
	UWORD yOffset = (256 - YSIZEEVEN*4)/2 * PLANEWIDTHWORD;
    UBYTE baseX = XTURNBUFFOR + xOffsetEven + screenStart*4;

	//for each vertical line
    

    for(UBYTE x = screenStart; x < screenEnd; ++x)
    {

        for(UBYTE i = 0; i < 4; ++i)
        {
            UBYTE sy = 0;
            UWORD tz = zStart;
            UWORD *rayXPtr = rayCastX + baseX*TERRAINDEPTH + tz;
            UWORD *rayYPtr = rayCastY + tz;
            UBYTE *screenPtr = screen4x4 + ((YSIZEEVEN)-1)*4 + i;
	        UBYTE mx,my;
	        UWORD mapValue;

            while(tz < renderingDepth)
            {
                mx = px + *rayXPtr;
                my = (py + (tz<<renderingDepthStep));
                mapValue = map[ mx ][ my ];
                UBYTE th = mapValue;

                WORD slope = th - (ph + *rayYPtr);

                if(slope > tz>>2)
                {
                    *screenPtr = ((mapValue >> 8) + ((slope/4) & 1));
                    sy+=1;//go step higher in the raycast table
                    rayYPtr += TERRAINDEPTH;
                    screenPtr-=4;//go step higher on screen
                    if(sy == YSIZEEVEN) tz=renderingDepth; //break if end of screen
                }
                else if(slope > 0)
                {
                    *screenPtr = (mapValue >> 8) + 2;
                    sy+=1;//go step higher in the raycast table
                    rayYPtr += TERRAINDEPTH;
                    screenPtr-=4;//go step higher on screen
                    if(sy == YSIZEEVEN) tz=renderingDepth; //break if end of screen
                }
                else
                {	
                    tz++;//go step in depth if no height hit
                    rayXPtr++;
                    rayYPtr++;
                }
            }
            
            while(sy < YSIZEEVEN)
            {
                *screenPtr =  32 - ph/32 -sy/8;
                sy+=1;
                screenPtr-=4;

            }

            baseX++;
        }

        UWORD *planePos1 = plane1W + yOffset + x;
        UWORD *planePos2 = plane2W + yOffset + x;
        UWORD *planePos3 = plane3W + yOffset + x;
        UWORD *planePos4 = plane4W + yOffset + x;
        UWORD sp = 0;

        for(UBYTE y=0;y<YSIZEEVEN;y++)
	    {

			UWORD address1 = ((screen4x4[sp])<<5) + (screen4x4[sp+1]);
			UWORD address2 = ((screen4x4[sp+2])<<5) + (screen4x4[sp+3]);

            
			UWORD word = (dither4x4EvenP1[ address1 ]<<8) + dither4x4EvenP1[ address2 ];
            UWORD otherWord = (word << 1)|((word>>1) & 1);
			*planePos1 = word;
            planePos1 += PLANEWIDTHWORD;
			*planePos1 = otherWord;
            planePos1 += PLANEWIDTHWORD;
            *planePos1 = word;
            planePos1 += PLANEWIDTHWORD;
            *planePos1 = otherWord;
            planePos1 += PLANEWIDTHWORD;
			word = (dither4x4EvenP2[ address1 ]<<8) + dither4x4EvenP2[ address2 ];
            otherWord = (word << 1)|((word>>1) & 1);
			*planePos2 = word;
            planePos2 += PLANEWIDTHWORD;
			*planePos2 = otherWord;
            planePos2 += PLANEWIDTHWORD;
			*planePos2 = word;
            planePos2 += PLANEWIDTHWORD;
			*planePos2 = otherWord;
            planePos2 += PLANEWIDTHWORD;
			word = (dither4x4EvenP3[ address1 ]<<8) + dither4x4EvenP3[ address2 ];
            otherWord = (word << 1)|((word>>1) & 1);
			*planePos3 = word;
            planePos3 += PLANEWIDTHWORD;
			*planePos3 = otherWord;
            planePos3 += PLANEWIDTHWORD;
			*planePos3 = word;
            planePos3 += PLANEWIDTHWORD;
			*planePos3 = otherWord;
            planePos3 += PLANEWIDTHWORD;
			word = (dither4x4EvenP4[ address1 ]<<8) + dither4x4EvenP4[ address2 ];
            otherWord = (word << 1)|((word>>1) & 1);
			*planePos4 = word;
            planePos4 += PLANEWIDTHWORD;
			*planePos4 = otherWord;
            planePos4 += PLANEWIDTHWORD;
			*planePos4 = word;
            planePos4 += PLANEWIDTHWORD;
			*planePos4 = otherWord;
            planePos4 += PLANEWIDTHWORD;

            sp += 4;
        }

    }

}

void ProcessRayCasts163x2(UBYTE *screen, WORD (*rayCastX), WORD (*rayCastY), UWORD (*map)[MAPSIZE],
UBYTE px, UBYTE py, UBYTE ph, UBYTE screenStart, UBYTE screenEnd, UBYTE zStart)
{

    
    
	UWORD yOffset = (256 - YSIZEODD*2)/2 * PLANEWIDTHWORD;
    UBYTE baseX = XTURNBUFFOR + xOffsetOdd + screenStart*6;

	//for each vertical line
    

    for(UBYTE x = screenStart; x < screenEnd; ++x)
    {

        for(UBYTE i = 0; i < 6; ++i)
        {
            UBYTE sy = 0;
            UWORD tz = zStart;
            UWORD *rayXPtr = rayCastX + baseX*TERRAINDEPTH + tz;
            UWORD *rayYPtr = rayCastY + tz;
            UBYTE *screenPtr = screen3x2 + ((YSIZEODD)-1)*6 + i;
	        UBYTE mx,my;
	        UWORD mapValue;

            while(tz < renderingDepth)
            {
                mx = px + *rayXPtr;
                my = (py + (tz<<renderingDepthStep));
                mapValue = map[ mx ][ my ];
                UBYTE th = mapValue;

                if(th > ph + *rayYPtr)//tz>>3)
                {
                    *screenPtr = (mapValue >> 8);// - (mist>>4);//+ ((slope/4) & 1);//( ( 13 - (mapValue >> 8) ) >> (mist>>5) )+ 13 + ((slope/4) & 1);// + (((tz+py)>>2) & 1);//write pixel color
                    
                    sy+=1;//go step higher in the raycast table
                    rayYPtr += TERRAINDEPTH;
                    screenPtr-=6;//go step higher on screen
                }
                else
                {	
                    //screen[position] = 0;
                    tz++;//go step in depth if no height hit
                    rayXPtr++;
                    rayYPtr++;
                }
            }
            
            while(sy < YSIZEODD)
            {
                //if(screen[position] == 31)
                //	sy = YSIZE;
                //else
                {
                    *screenPtr =  32 - ph/32 -sy/8;
                    sy+=1;
                    screenPtr-=6;
                }

            }

            baseX++;
        }

        UWORD *planePos1 = plane1W + yOffset + x;
        UWORD *planePos2 = plane2W + yOffset + x;
        UWORD *planePos3 = plane3W + yOffset + x;
        UWORD *planePos4 = plane4W + yOffset + x;
        UWORD sp = 0;

        for(UBYTE y=0;y<YSIZEODD;y++)
	    {

			UWORD address1 = (screen3x2[sp]<<10) + (screen3x2[sp+1]<<5) + (screen3x2[sp+2]);
			UWORD address2 = (screen3x2[sp+3]<<10) + (screen3x2[sp+4]<<5) + (screen3x2[sp+5]);

            
			UWORD word = (dither3x2EvenP1[ address1 ]<<8) + dither3x2EvenP1[ address2 ];
			*planePos1 = word;
            planePos1 += PLANEWIDTHWORD;
			*planePos1 = (word << 1)|((word>>1) & 1);
            planePos1 += PLANEWIDTHWORD;
			word = (dither3x2EvenP2[ address1 ]<<8) + dither3x2EvenP2[ address2 ];
			*planePos2 = word;
            planePos2 += PLANEWIDTHWORD;
			*planePos2 = (word << 1)|((word>>1) & 1);
            planePos2 += PLANEWIDTHWORD;
			word = (dither3x2EvenP3[ address1 ]<<8) + dither3x2EvenP3[ address2 ];
			*planePos3 = word;
            planePos3 += PLANEWIDTHWORD;
			*planePos3 = word = (word << 1)|((word>>1) & 1);
            planePos3 += PLANEWIDTHWORD;
			word = (dither3x2EvenP4[ address1 ]<<8) + dither3x2EvenP4[ address2 ];
			*planePos4 = word;
            planePos4 += PLANEWIDTHWORD;
			*planePos4 = word = (word << 1)|((word>>1) & 1);
            planePos4 += PLANEWIDTHWORD;

            sp += 6;
        }

    }
}

void ProcessRayCasts164x4(WORD (*rayCastX), WORD (*rayCastY), UWORD (*map)[256],
UBYTE px, UBYTE py, UBYTE ph, UBYTE screenStart, UBYTE screenEnd, UBYTE zStart)
{

    
	UWORD yOffset = (256 - YSIZEEVEN*4)/2 * PLANEWIDTHWORD;
    UBYTE baseX = XTURNBUFFOR + xOffsetEven + screenStart*4;

	//for each vertical line
    

    for(UBYTE x = screenStart; x < screenEnd; ++x)
    {

        for(UBYTE i = 0; i < 4; ++i)
        {
            UBYTE sy = 0;
            UWORD tz = zStart;
            UWORD *rayXPtr = rayCastX + baseX*TERRAINDEPTH + tz;
            UWORD *rayYPtr = rayCastY + tz;
            UBYTE *screenPtr = screen4x4 + ((YSIZEEVEN)-1)*4 + i;
	        UBYTE mx,my;
	        UWORD mapValue;

            while(tz < renderingDepth)
            {
                mx = px + *rayXPtr;
                my = (py + (tz<<renderingDepthStep));
                mapValue = map[ mx ][ my ];
                UBYTE th = mapValue;

                if(th > ph + *rayYPtr)//tz>>3)
                {
                    *screenPtr = (mapValue >> 8);// - (mist>>4);//+ ((slope/4) & 1);//( ( 13 - (mapValue >> 8) ) >> (mist>>5) )+ 13 + ((slope/4) & 1);// + (((tz+py)>>2) & 1);//write pixel color
                    
                    sy+=1;//go step higher in the raycast table
                    rayYPtr += TERRAINDEPTH;
                    screenPtr-=4;//go step higher on screen
                }
                else
                {	
                    //screen[position] = 0;
                    tz++;//go step in depth if no height hit
                    rayXPtr++;
                    rayYPtr++;
                }
            }
            
            while(sy < YSIZEEVEN)
            {
                *screenPtr =  32 - ph/32 -sy/8;
                sy+=1;
                screenPtr-=4;

            }

            baseX++;
        }

        UWORD *planePos1 = plane1W + yOffset + x;
        UWORD *planePos2 = plane2W + yOffset + x;
        UWORD *planePos3 = plane3W + yOffset + x;
        UWORD *planePos4 = plane4W + yOffset + x;
        UWORD sp = 0;

        for(UBYTE y=0;y<YSIZEEVEN;y++)
	    {

			UWORD address1 = ((screen4x4[sp])<<5) + (screen4x4[sp+1]);
			UWORD address2 = ((screen4x4[sp+2])<<5) + (screen4x4[sp+3]);

            
			UWORD word = (dither4x4EvenP1[ address1 ]<<8) + dither4x4EvenP1[ address2 ];
            UWORD otherWord = (word << 1)|((word>>1) & 1);
			*planePos1 = word;
            planePos1 += PLANEWIDTHWORD;
			*planePos1 = otherWord;
            planePos1 += PLANEWIDTHWORD;
            *planePos1 = word;
            planePos1 += PLANEWIDTHWORD;
            *planePos1 = otherWord;
            planePos1 += PLANEWIDTHWORD;
			word = (dither4x4EvenP2[ address1 ]<<8) + dither4x4EvenP2[ address2 ];
            otherWord = (word << 1)|((word>>1) & 1);
			*planePos2 = word;
            planePos2 += PLANEWIDTHWORD;
			*planePos2 = otherWord;
            planePos2 += PLANEWIDTHWORD;
			*planePos2 = word;
            planePos2 += PLANEWIDTHWORD;
			*planePos2 = otherWord;
            planePos2 += PLANEWIDTHWORD;
			word = (dither4x4EvenP3[ address1 ]<<8) + dither4x4EvenP3[ address2 ];
            otherWord = (word << 1)|((word>>1) & 1);
			*planePos3 = word;
            planePos3 += PLANEWIDTHWORD;
			*planePos3 = otherWord;
            planePos3 += PLANEWIDTHWORD;
			*planePos3 = word;
            planePos3 += PLANEWIDTHWORD;
			*planePos3 = otherWord;
            planePos3 += PLANEWIDTHWORD;
			word = (dither4x4EvenP4[ address1 ]<<8) + dither4x4EvenP4[ address2 ];
            otherWord = (word << 1)|((word>>1) & 1);
			*planePos4 = word;
            planePos4 += PLANEWIDTHWORD;
			*planePos4 = otherWord;
            planePos4 += PLANEWIDTHWORD;
			*planePos4 = word;
            planePos4 += PLANEWIDTHWORD;
			*planePos4 = otherWord;
            planePos4 += PLANEWIDTHWORD;

            sp += 4;
        }

    }

}