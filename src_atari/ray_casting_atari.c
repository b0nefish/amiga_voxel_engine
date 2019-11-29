#include "../src/engine.h"

UBYTE ProcessWord1(UBYTE rounds, UBYTE sx, UBYTE sy, UWORD *_tz, UWORD *tzz, UBYTE px, UBYTE py,UBYTE ph,
UWORD *address1, UWORD *address2, 
WORD (*rayCastX)[TERRAINDEPTH], WORD (*rayCastY)[TERRAINDEPTH], UWORD (*map)[256])
{
	UWORD mapValue;
	WORD slope;
	UBYTE c;
	UBYTE th;
	UBYTE tz;
	UBYTE iHor=0;
	//process 1,2,3 or 6 rounds to find colors for this WORD = 16 pixels
	//for(UBYTE iHor=0;iHor<rounds;iHor++)
	{
		sx = sx + 2;
		tz = tzz[iHor];//set current depth - tz
		while(tz < TERRAINDEPTH)//check depth step by step
		{
			mapValue = map[ (UBYTE)( px + rayCastX[sx][tz] ) ][ (UBYTE)( py + (tz<<debugValue4) ) ];//read color + height
			th = mapValue;//take just the height
			slope = th - (ph + rayCastY[sy][tz]);//check if read height is higher than what we expect from the raycast table
			if(slope > 0)
			{
				c = (mapValue >> 8) + ((slope/16) & 1);
				tzz[iHor] = tz;//save the depth we've arrived at
				break;
			}
			else
			{	
				tz++;//go step in depth if no height hit
			}
		}
		if(tz == TERRAINDEPTH) c = 34 - ph/32 - sy/8; //draw sky if too deep
	}
	*address1 = (c<<10) + (c<<5) + (c); *address2 = *address1;
	
	
	return tz;
}
UBYTE ProcessWord2(UBYTE rounds, UBYTE sx, UBYTE sy, UWORD *_tz, UWORD *tzz, UBYTE px, UBYTE py,UBYTE ph,
UWORD *address1, UWORD *address2, 
WORD (*rayCastX)[TERRAINDEPTH], WORD (*rayCastY)[TERRAINDEPTH], UWORD (*map)[256])
{
	UWORD mapValue;
	WORD slope;
	UBYTE c[2];
	UBYTE th;
	UBYTE tz;

	sx = sx + 1;
	//process 1,2,3 or 6 rounds to find colors for this WORD = 16 pixels
	for(UBYTE iHor=0;iHor<2;iHor++)
	{
		
		tz = tzz[iHor];//set current depth - tz
		while(tz < TERRAINDEPTH)//check depth step by step
		{
			mapValue = map[ (UBYTE)( px + rayCastX[sx][tz] ) ][ (UBYTE)( py + (tz<<debugValue4) ) ];//read color + height
			th = mapValue;//take just the height
			slope = th - (ph + rayCastY[sy][tz]);//check if read height is higher than what we expect from the raycast table
			if(slope > 0)
			{
				c[iHor] = (mapValue >> 8) + ((slope/16) & 1);
				tzz[iHor] = tz;//save the depth we've arrived at
				break;
			}
			else
			{	
				tz++;//go step in depth if no height hit
			}
		}
		if(tz == TERRAINDEPTH) c[iHor] = 34 - ph/32 -sy/8; //draw sky if too deep
		sx = sx + 3;
	}
	*address1 = (c[0]<<10) + (c[0]<<5) + (c[0]); *address2 = (c[1]<<10) + (c[1]<<5) + (c[1]);

	return tz;
}
UBYTE ProcessWord3(UBYTE rounds, UBYTE sx, UBYTE sy, UWORD *_tz, UWORD *tzz, UBYTE px, UBYTE py,UBYTE ph,
UWORD *address1, UWORD *address2, 
WORD (*rayCastX)[TERRAINDEPTH], WORD (*rayCastY)[TERRAINDEPTH], UWORD (*map)[256])
{
	UWORD mapValue;
	WORD slope;
	UBYTE c[3];
	UBYTE th;
	UBYTE tz;

	//process 1,2,3 or 6 rounds to find colors for this WORD = 16 pixels
	for(UBYTE iHor=0;iHor<3;iHor++)
	{
		
		tz = tzz[iHor];//set current depth - tz
		while(tz < TERRAINDEPTH)//check depth step by step
		{
			mapValue = map[ (UBYTE)( px + rayCastX[sx][tz] ) ][ (UBYTE)( py + (tz<<debugValue4) ) ];//read color + height
			th = mapValue;//take just the height
			slope = th - (ph + rayCastY[sy][tz]);//check if read height is higher than what we expect from the raycast table
			if(slope > 0)
			{
				c[iHor] = (mapValue >> 8) + ((slope/16) & 1);
				tzz[iHor] = tz;//save the depth we've arrived at
				break;
			}
			else
			{	
				tz++;//go step in depth if no height hit
			}
		}
		if(tz == TERRAINDEPTH) c[iHor] = 34 - ph/32 -sy/8; //draw sky if too deep

		sx = sx + 2;
	}
	*address1 = (c[0]<<10) + (c[0]<<5) + (c[1]); *address2 = (c[1]<<10) + (c[2]<<5) + (c[2]);

	return tz;
}
UBYTE ProcessWord6(UBYTE rounds, UBYTE sx, UBYTE sy, UWORD *_tz, UWORD *tzz, UBYTE px, UBYTE py,UBYTE ph,
UWORD *address1, UWORD *address2, 
WORD (*rayCastX)[TERRAINDEPTH], WORD (*rayCastY)[TERRAINDEPTH], UWORD (*map)[256])
{
	UWORD mapValue;
	WORD slope;
	UBYTE c[6];
	UBYTE th;
	UBYTE tz;

	//process 1,2,3 or 6 rounds to find colors for this WORD = 16 pixels
	for(UBYTE iHor=0;iHor<6;iHor++)
	{
		
		tz = tzz[iHor];//set current depth - tz
		while(tz < TERRAINDEPTH)//check depth step by step
		{
			mapValue = map[ (UBYTE)( px + rayCastX[sx][tz] ) ][ (UBYTE)( py + (tz<<debugValue4) ) ];//read color + height
			th = mapValue;//take just the height
			slope = th - (ph + rayCastY[sy][tz]);//check if read height is higher than what we expect from the raycast table
			if(slope > 0)
			{
				c[iHor] = (mapValue >> 8);// + ((slope/4) & 1);
				tzz[iHor] = tz;//save the depth we've arrived at
				break;
			}
			else
			{	
				tz++;//go step in depth if no height hit
			}
		}
		if(tz == TERRAINDEPTH) c[iHor] = 34 - ph/32 -sy/8;; //draw sky if too deep

		sx += 1;
	}
	*address1 = (c[0]<<10) + (c[1]<<5) + (c[2]); *address2 = (c[3]<<10) + (c[4]<<5) + (c[5]);

	return tz;
}
void ProcessRayCasts3x2(WORD (*rayCastX)[TERRAINDEPTH], WORD (*rayCastY)[TERRAINDEPTH], UWORD (*map)[256],
	UBYTE px, UBYTE py, UBYTE ph, 
	UBYTE tableXStart, UBYTE xCycles, UBYTE zStep, UBYTE zStart, 
	UBYTE ySize, BYTE xOffset)
{
	UBYTE sx,sy,mist;
	UWORD tz,tzz[6];
	UWORD position,address1,address2;
	UBYTE threshold1 = TERRAINDEPTH/2;
	UBYTE threshold2 = TERRAINDEPTH - TERRAINDEPTH/4;
	//UBYTE threshold3 = TERRAINDEPTH;
	UWORD word;
	UBYTE color;
	UWORD positionStart =  ySize*20*2*4 + tableXStart/6*4;

	UBYTE verticalSteps;

	UBYTE iInit, iVert;

	//start with the buffor + vertical stripe start + turning amount
	sx = XTURNBUFFOR + tableXStart + xOffset;
	//currentScreenYStepSize = xCycles;


	//for each vertical line
	for(iVert=0;iVert<xCycles;iVert++)
	{
		//start from the bottom
		sy = 0;
		position = positionStart + iVert*4 ;//+ 80*12;
		
		//init values for this vertical line
		tzz[0]=zStart;tzz[1]=zStart;tzz[2]=zStart;
		//tzz[3]=zStart;tzz[4]=zStart;tzz[5]=zStart;
		tz = zStart;

		//process this vertical line
		while(sy < ySize)
		{
			 if(tz < threshold1)			
			 {
				tz = ProcessWord1(1,sx,sy,&tz,tzz,px,py,ph,&address1,&address2,rayCastX, rayCastY, map);

				word = (dither3x2EvenP1[ address1 ]<<8) + dither3x2EvenP1[ address2 ];
				planes[position] = word;
				planes[position-160] = word;
				planes[position-320] = word;
				word = (word << 1)|((word>>1) & 1);
				planes[position-80] = word;
				planes[position-240] = word;
				planes[position-400] = word;
				word = (dither3x2EvenP2[ address1 ]<<8) + dither3x2EvenP2[ address2 ];
				planes[position+1] = word;
				planes[position-160+1] = word;
				planes[position-320+1] = word;
				word = (word << 1)|((word>>1) & 1);
				planes[position-80+1] = word;
				planes[position-240+1] = word;
				planes[position-400+1] = word;
				word = (dither3x2EvenP3[ address1 ]<<8) + dither3x2EvenP3[ address2 ];
				planes[position+2] = word;
				planes[position-160+2] = word;
				planes[position-320+2] = word;
				word = (word << 1)|((word>>1) & 1);
				planes[position-80+2] = word;
				planes[position-240+2] = word;
				planes[position-400+2] = word;
				word = (dither3x2EvenP4[ address1 ]<<8) + dither3x2EvenP4[ address2 ];
				planes[position+3] = word;
				planes[position-160+3] = word;
				planes[position-320+3] = word;
				word = (word << 1)|((word>>1) & 1);
				planes[position-80+3] = word;
				planes[position-240+3] = word;
				planes[position-400+3] = word;
				position -= 480;

				sy+=3;
			 }
			else if(tz < threshold2)			
			 {
				tz = ProcessWord2(2,sx,sy,&tz,tzz,px,py,ph,&address1,&address2,rayCastX, rayCastY, map);
				word = (dither3x2EvenP1[ address1 ]<<8) + dither3x2EvenP1[ address2 ];
				planes[position] = word;
				planes[position-160] = word;
				planes[position-320] = word;
				word = (word << 1)|((word>>1) & 1);
				planes[position-80] = word;
				planes[position-240] = word;
				planes[position-400] = word;
				word = (dither3x2EvenP2[ address1 ]<<8) + dither3x2EvenP2[ address2 ];
				planes[position+1] = word;
				planes[position-160+1] = word;
				planes[position-320+1] = word;
				word = (word << 1)|((word>>1) & 1);
				planes[position-80+1] = word;
				planes[position-240+1] = word;
				planes[position-400+1] = word;
				word = (dither3x2EvenP3[ address1 ]<<8) + dither3x2EvenP3[ address2 ];
				planes[position+2] = word;
				planes[position-160+2] = word;
				planes[position-320+2] = word;
				word = (word << 1)|((word>>1) & 1);
				planes[position-80+2] = word;
				planes[position-240+2] = word;
				planes[position-400+2] = word;
				word = (dither3x2EvenP4[ address1 ]<<8) + dither3x2EvenP4[ address2 ];
				planes[position+3] = word;
				planes[position-160+3] = word;
				planes[position-320+3] = word;
				word = (word << 1)|((word>>1) & 1);
				planes[position-80+3] = word;
				planes[position-240+3] = word;
				planes[position-400+3] = word;
				position -= 480;

				sy+=3;
			 }
			else if(tz < TERRAINDEPTH)			
			 {
				tz = ProcessWord3(3,sx,sy,&tz,tzz,px,py,ph,&address1,&address2,rayCastX, rayCastY, map);
				word = (dither3x2EvenP1[ address1 ]<<8) + dither3x2EvenP1[ address2 ];
				planes[position] = word;
				planes[position-160] = word;
				planes[position-320] = word;
				word = (word << 1)|((word>>1) & 1);
				planes[position-80] = word;
				planes[position-240] = word;
				planes[position-400] = word;
				word = (dither3x2EvenP2[ address1 ]<<8) + dither3x2EvenP2[ address2 ];
				planes[position+1] = word;
				planes[position-160+1] = word;
				planes[position-320+1] = word;
				word = (word << 1)|((word>>1) & 1);
				planes[position-80+1] = word;
				planes[position-240+1] = word;
				planes[position-400+1] = word;
				word = (dither3x2EvenP3[ address1 ]<<8) + dither3x2EvenP3[ address2 ];
				planes[position+2] = word;
				planes[position-160+2] = word;
				planes[position-320+2] = word;
				word = (word << 1)|((word>>1) & 1);
				planes[position-80+2] = word;
				planes[position-240+2] = word;
				planes[position-400+2] = word;
				word = (dither3x2EvenP4[ address1 ]<<8) + dither3x2EvenP4[ address2 ];
				planes[position+3] = word;
				planes[position-160+3] = word;
				planes[position-320+3] = word;
				word = (word << 1)|((word>>1) & 1);
				planes[position-80+3] = word;
				planes[position-240+3] = word;
				planes[position-400+3] = word;
				position -= 480;

				sy+=3;
			 }
			//  else if(tz < TERRAINDEPTH)		
			//  {
			// 	 tz = ProcessWord6(6,sx,sy,&tz,tzz,px,py,ph,&address1,&address2,rayCastX, rayCastY, map);
			// 	 verticalSteps = 2;
			//  }
			 else 	
			 {
				color = 34 - ph/32 -sy/8;
				address1 = (color<<10) + (color<<5) + (color);
	

				word = (dither3x2EvenP1[ address1 ]<<8) + dither3x2EvenP1[ address1 ];
				planes[position] = word;
				planes[position-160] = word;
				word = (word << 1)|((word>>1) & 1);
				planes[position-80] = word;
				planes[position-240] = word;
				//position -= 80;
				word = (dither3x2EvenP2[ address1 ]<<8) + dither3x2EvenP2[ address1 ];
				planes[position+1] = word;
				planes[position-160+1] = word;
				word = (word << 1)|((word>>1) & 1);
				planes[position-80+1] = word;
				planes[position-240+1] = word;
				//position -= 80;
				word = (dither3x2EvenP3[ address1 ]<<8) + dither3x2EvenP3[ address1 ];
				planes[position+2] = word;
				planes[position-160+2] = word;
				word = (word << 1)|((word>>1) & 1);
				planes[position-80+2] = word;
				planes[position-240+2] = word;
				//position -= 80;
				word = (dither3x2EvenP4[ address1 ]<<8) + dither3x2EvenP4[ address1 ];
				planes[position+3] = word;
				planes[position-160+3] = word;
				word = (word << 1)|((word>>1) & 1);
				planes[position-80+3] = word;
				planes[position-240+3] = word;
				position -= 320;
				sy+=2;
			 }
			//go step higher in the raycast table
		}
		sx += 6;//go to the next vertical line
	}
}


void ProcessRayCastsFull(UBYTE *screen, WORD (*rayCastX)[TERRAINDEPTH], WORD (*rayCastY)[TERRAINDEPTH], UWORD (*map)[256],
UBYTE px, UBYTE py, UBYTE ph, UBYTE tableXStart,
UBYTE tableStepSizeX, UBYTE tableStepSizeY, UBYTE tableStepNumber, UBYTE xCycles, UBYTE zStep, UBYTE zStart, UBYTE ySize, BYTE xOffset)
{
	UBYTE sx,sy;
	UWORD tz;
	UBYTE th = 0;
	UWORD position;
	UBYTE mx,my;;
	UWORD mapValue;
	BYTE xvalue,yvalue;
	UWORD rayValue;
	UWORD startPosition = ((ySize/tableStepSizeY)-1)*xCycles;
	UBYTE mist;
	WORD slope;


	UWORD currentScreenYStepSize;

	//start with the buffor + vertical stripe start + turning amount
	sx = XTURNBUFFOR + tableXStart + xOffset;
	currentScreenYStepSize = xCycles;

	//for each vertical line
	for(UBYTE i=0;i<xCycles;i++)
	{
		sy = 0 + tableStepNumber;
		position = startPosition+i;
		tz = zStart;//rendering start
		mist = zStart*zStep;//rendering start

		//check depth step by step
		while(tz < renderingDepth)
		{

			//take x from the height map based on the raycast path step
			mx = (px + rayCastX[sx][tz]);
			//take y from tbe height map based on the depth step
			my = (py + (tz<<debugValue4));
			mapValue = map[ mx ][ my ];//read color + height
			th = mapValue;//take just the height

			//check if read height is higher than what we expect from the raycast table
			slope = th - (ph + rayCastY[sy][tz]);
			if(slope > tz>>3)
			{
				screen[position] = (mapValue >> 8) + ((slope/4) & 1);//( ( 13 - (mapValue >> 8) ) >> (mist>>5) )+ 13 + ((slope/4) & 1);// + (((tz+py)>>2) & 1);//write pixel color
				sy+=tableStepSizeY;//go step higher in the raycast table
				position-=currentScreenYStepSize;//go step higher on screen
				if(sy == ySize) tz=renderingDepth; //break if end of screen
			}
			else if(slope > 0)
			{
				screen[position] = (mapValue >> 8) + 2;//( ( 13 - (mapValue >> 8) ) >> (mist>>5) )+ 13 + ((slope/4) & 1);// + (((tz+py)>>2) & 1);//write pixel color
				sy+=tableStepSizeY;//go step higher in the raycast table
				position-=currentScreenYStepSize;//go step higher on screen
				if(sy == ySize) tz=renderingDepth; //break if end of screen
			}
			else
			{	
				//screen[position] = 0;
				tz++;//go step in depth if no height hit
				mist += zStep;
			}
		}
		//finish vertical line with SKY
		while(sy < ySize)
		{
			//if(screen[position] == 31)
			//	sy = YSIZE;
			//else
			{
				screen[position] = ph/32 + 0 +sy/8;
				sy+=tableStepSizeY;
				position-=currentScreenYStepSize;
			}

		}

		sx += tableStepSizeX;//go to the next vertical line
	}
}
void ProcessRayCasts16(UBYTE *screen, WORD (*rayCastX)[TERRAINDEPTH], WORD (*rayCastY)[TERRAINDEPTH], UWORD (*map)[256],
UBYTE px, UBYTE py, UBYTE ph, UBYTE tableXStart,
UBYTE tableStepSizeX, UBYTE tableStepSizeY, UBYTE tableStepNumber, UBYTE xCycles, UBYTE zStep, UBYTE zStart, UBYTE ySize, BYTE xOffset)
{
	UBYTE sx,sy;
	UWORD tz;
	UBYTE th = 0;
	UWORD position;
	UBYTE mx,my;;
	UWORD mapValue;
	BYTE xvalue,yvalue;
	UWORD rayValue;
	UWORD startPosition = ((ySize/tableStepSizeY)-1)*xCycles;
	UBYTE mist;
	//WORD slope;


	UWORD currentScreenYStepSize;

	//start with the buffor + vertical stripe start + turning amount
	sx = XTURNBUFFOR + tableXStart + xOffset;
	currentScreenYStepSize = xCycles;

	//for each vertical line
	for(UBYTE i=0;i<xCycles;i++)
	{
		sy = 0 + tableStepNumber;
		position = startPosition+i;
		tz = zStart;//rendering start
		//mist = zStart*zStep;//rendering start

		//check depth step by step
		while(tz < renderingDepth)
		{

			//take x from the height map based on the raycast path step
			mx = (px + rayCastX[sx][tz]);
			//take y from tbe height map based on the depth step
			my = (py + (tz<<debugValue4));
			mapValue = map[ mx ][ my ];//read color + height
			th = mapValue;//take just the height

			//check if read height is higher than what we expect from the raycast table
			
			if(th > ph + rayCastY[sy][tz])//tz>>3)
			{
				screen[position] = (mapValue >> 8);// - (mist>>4);//+ ((slope/4) & 1);//( ( 13 - (mapValue >> 8) ) >> (mist>>5) )+ 13 + ((slope/4) & 1);// + (((tz+py)>>2) & 1);//write pixel color
				sy+=tableStepSizeY;//go step higher in the raycast table
				position-=currentScreenYStepSize;//go step higher on screen
				if(sy == ySize) tz=renderingDepth; //break if end of screen
			}
			/*else if(slope > 0)
			{
				screen[position] = (mapValue >> 8) + 2;//( ( 13 - (mapValue >> 8) ) >> (mist>>5) )+ 13 + ((slope/4) & 1);// + (((tz+py)>>2) & 1);//write pixel color
				sy+=tableStepSizeY;//go step higher in the raycast table
				position-=currentScreenYStepSize;//go step higher on screen
				if(sy == ySize) tz=renderingDepth; //break if end of screen
			}*/
			else
			{	
				//screen[position] = 0;
				tz++;//go step in depth if no height hit
				//mist += zStep;
			}
		}
		//finish vertical line with SKY
		while(sy < ySize)
		{
			//if(screen[position] == 31)
			//	sy = YSIZE;
			//else
			{
				screen[position] = ph/32 + 0 +sy/4;
				sy+=tableStepSizeY;
				position-=currentScreenYStepSize;
			}

		}

		sx += tableStepSizeX;//go to the next vertical line
	}
}
/*
void ProcessRayCasts(UBYTE *screen, WORD (*rayCastX)[TERRAINDEPTH], WORD (*rayCastY)[TERRAINDEPTH],
UBYTE px, UBYTE py, UBYTE ph, UBYTE tableXStart,
UBYTE tableStepSizeX, UBYTE tableStepSizeY, UBYTE tableStepNumber, UBYTE xCycles)
{
	UBYTE sx,sy,tz;
	UBYTE th = 0;
	UWORD position;
	UBYTE mx,my;
	//UBYTE mipLevel;
	UBYTE color = 0;
	//UWORD currentTableYStepSize;
	UWORD currentScreenYStepSize;
	//UBYTE *heightMap, *colorMap;

	sx = tableXStart;//set the x position in the raycast table
	//set the start position (left bottom pixel) on the destination screen
	//screenStartPosition = (YSIZE-1)*xCycles;
	//currentTableYStepSize = tableStepSizeY*XSIZE;
	currentScreenYStepSize = xCycles; //the same as the numer of x steps
	//screenYStepSize = stepSize*XSIZE;





	for(UBYTE i=0;i<xCycles;i++)
	{
		//********* INITIALIZE INTERLACED CALCUTATIONS
		//sy = interlace/2 + modulo2[sx];
		sy = 0 + tableStepNumber;//YSIZE-1;//tableStepNumber;// + modulo2[sx];
		position = ((YSIZE/tableStepSizeY)-1)*xCycles+i;//tableStepNumber+sx-(XSIZE*sy);

		//********* INITIALIZE INTERLACED CALCUTATIONS
		//starting depth to look for height colission
		tz = 1;

		while(tz < renderingDepth && sy <YSIZE)
		{
			//***** set mipmap level
			//mipLevel = tz/8;

			// set x,y pooositions on source maps
			mx = (px + rayCastX[sx][tz]);
			my = (py + tz);

				th = heightMap0[ mx ][ my ];
			//*********** HEIGHT MIPMAP

			//*********** HEIGHT MIPMAP

			//height to look for at a given x,y terrain coordinate accounting for z depth
			//************************************************************


			if(th>ph + rayCastY[sy][tz])
			{
				//	screenDepth[position] = tz;
				//screenMid[position] = th/16 + sy/8;
				screen[position] = colorMap0[ mx ][ my ];
				//screenMid[position] = colorMap0[ mx ][ my ];
				//*************** COLOR MIPMAP

				//*************** COLOR MIPMAP

				sy+=tableStepSizeY; //move X pixels to the top in calculations
				position-=currentScreenYStepSize; //move X pixels to the top on the destination screen
			}
			else
			{
				tz+=1;//+mipLevel; //move a variable step in depth to look for next height colision
			}
		}
		//finish vertical line with SKY
		while(sy < YSIZE)
		{
			color = sy/4;//2
			//	screenDepth[position] = 0x01;
			screen[position] = color;
			sy+=tableStepSizeY;
			position-=currentScreenYStepSize;
		}
		//go to the next vertical line
		sx += tableStepSizeX;
	}
}
*/
void ProcessRayCastsSlow(UBYTE *screen, WORD *rayCastXY, UWORD (*map)[256],
UBYTE px, UBYTE py, UBYTE ph, UBYTE tableXStart,
UBYTE tableStepSizeX, UBYTE tableStepSizeY, UBYTE tableStepNumber, UBYTE xCycles, UBYTE adrSize, UBYTE zStep)
{
	UBYTE sy,tz;
	UBYTE th = 0;
	UWORD position;
	UBYTE mx,my;
	//UBYTE color = 0;
	UWORD mapValue;
	BYTE xvalue,yvalue;
	UWORD rayValue;
	UWORD startPosition = ((YSIZEEVEN/tableStepSizeY)-1)*xCycles;
	UWORD sxa,sya,tza;

	//UWORD currentScreenYStepSize;

//	sx = tableXStart;
	//currentScreenYStepSize = xCycles;

	for(UBYTE sx=0;sx<xCycles;sx++)
	{
		sxa = (sx<<adrSize);
		sya = 0;
		sy = 0;// + tableStepNumber;
		position = startPosition+sx;
		tz = 2;
		tza = tz<<(adrSize*2);

		while(tz < renderingDepth)
		{
			rayValue = rayCastXY[tza+sxa+sy];
			xvalue = rayValue>>8;
			yvalue = rayValue;

			mx = (px + xvalue);
			my = (py + tz);
			//if(mx == 0 || mx == 255 || my == 0 || my == 255)  tz=renderingDepth;
			mapValue = map[ mx ][ my ];//read color + height
			th = mapValue;//take just the height
			if(th>ph + yvalue)
			{
				screen[position] = mapValue >> 8;
				sy++;
			//	sya = sy;
				if(sy == YSIZEEVEN) tz=renderingDepth; //break
				//sya = (sy<<5);
				position-=xCycles;
			}
			else
			{
				tz+=zStep;
				tza = tz<<(adrSize*2);
			}
		}
		//finish vertical line with SKY
		while(sy < YSIZEEVEN)
		{
			if(screen[position] == 31)
				sy = YSIZEEVEN;
			else
			{
				screen[position] = 31;
				sy+=1;//tableStepSizeY;

				position-=xCycles;
			}

		}
		//go to the next vertical line
		//sx ++;//tableStepSizeX;
	}
}
/*
void ProcessRayCastsSlow2(UBYTE *screen, WORD (*rayCastX)[TERRAINDEPTH], WORD (*rayCastY)[TERRAINDEPTH],
UBYTE px, UBYTE py, UBYTE ph, UBYTE tableXStart,
UBYTE tableStepSizeX, UBYTE tableStepSizeY, UBYTE tableStepNumber, UBYTE xCycles)
{
	UBYTE sx,sy,tz;
	UBYTE th = 0;
	UWORD mapValue;
	UWORD rayCast;
	UWORD position;
	UWORD positionX, positionY;
	UBYTE mx,my;
	UBYTE color = 0;
	UWORD currentScreenYStepSize;
	UWORD ppx;
	UWORD sizeY = YSIZE/tableStepSizeY-1;

	ppx = px/4;

	sx = tableXStart;
	currentScreenYStepSize = xCycles;

	for(UBYTE i=0;i<xCycles;i++)
	{
		sy = 0 + tableStepNumber;
		position = sizeY*xCycles+i;
		positionY = 0;
		positionX = i*TERRAINDEPTH;
		tz = 0;

		while(tz < renderingDepth && sy <YSIZE)
		{
			//rayCast = rayCastXX[rayPosition];
			mx = ppx + rayCastXX[positionX] ;
			my = (py + tz)/4;
			mapValue = map[ mx ][ my ];//read color + height
			th = mapValue;//take just the height
			if(th>ph + rayCastYY[positionY])
			{
				screen[position] = mapValue >> 8;
				sy+=tableStepSizeY; //move X pixels to the top in calculations
				position-=currentScreenYStepSize; //move X pixels to the top on the destination screen
				positionY += TERRAINDEPTH;//increment Y
			}
			else
			{
				tz+=1;//+mipLevel; //move a variable step in depth to look for next height colision
				positionY++;//increment only Z
				positionX++;
			}
		}
		//finish vertical line with SKY
		while(sy < YSIZE)
		{
			if(screen[position] == 31) sy = YSIZE;
			else
			{
				screen[position] = 31;
				sy+=tableStepSizeY;
				position-=currentScreenYStepSize;
			}

		}
		//go to the next vertical line
		sx += tableStepSizeX;
	}
}
static inline WORD mul(BYTE a, BYTE b)
{
	WORD c=0;
	if(b & 0b00000001) c+=a;
	if(b & 0b00000010) c+=a<<1;
	if(b & 0b00000100) c+=a<<2;
	if(b & 0b00001000) c+=a<<3;
	if(b & 0b00010000) c+=a<<4;
	if(b & 0b00100000) c+=a<<5;
	return c;
}
*/
/*
void ProcessRayCastsSlow3(UBYTE *screen, WORD (*rayCastX)[TERRAINDEPTH], WORD (*rayCastY)[TERRAINDEPTH],
UBYTE px, UBYTE py, UBYTE ph, UBYTE tableXStart,
UBYTE tableStepSizeX, UBYTE tableStepSizeY, UBYTE tableStepNumber, UBYTE xCycles)
{
	UBYTE sx,sy,tz;
	UBYTE th = 0;
	UWORD mapValue;
	UWORD rayCast;
	UWORD position;
	UWORD positionX, positionY;
	UBYTE mx,my;
	UBYTE color = 0;
	UWORD currentScreenYStepSize;
	UWORD ppx;
	UWORD sizeY = YSIZE/tableStepSizeY-1;
	UBYTE hDifference = 0;

	ppx = px/4;

	sx = tableXStart;
	currentScreenYStepSize = xCycles;

	for(UBYTE i=0;i<xCycles;i++)
	{
		sy = 0 + tableStepNumber;
		position = ((YSIZE/tableStepSizeY)-1)*xCycles+i;
		tz = 1;

		while(tz < renderingDepth && sy <YSIZE)
		{
			mx = (px + ((sx-20)*tz)/8);
			my = (py + tz);
			th = heightMap0[ mx ][ my ];
			if(th>ph +  ((sy-16)*tz)/8)
			{
				screen[position] = colorMap0[ mx ][ my ];
				sy+=1; //move X pixels to the top in calculations
				position-=currentScreenYStepSize; //move X pixels to the top on the destination screen
			}
			else
			{
				tz+=1;//+mipLevel; //move a variable step in depth to look for next height colision
			}
		}
		//finish vertical line with SKY
		while(sy < YSIZE)
		{
			if(screen[position] == 31) sy = YSIZE;
			else
			{
				screen[position] = 31;
				sy+=tableStepSizeY;
				position-=currentScreenYStepSize;
			}

		}
		//go to the next vertical line
		sx += 1;
	}
}
*/
/*
void ProcessRayCastsSlowMul(UBYTE *screen, WORD (*rayCastX)[TERRAINDEPTH], WORD (*rayCastY)[TERRAINDEPTH],
UBYTE px, UBYTE py, UBYTE ph, UBYTE tableXStart,
UBYTE tableStepSizeX, UBYTE tableStepSizeY, UBYTE tableStepNumber, UBYTE xCycles)
{
	UBYTE sx,sy,tz;
	UBYTE th = 0;
	UWORD mapValue;
	UWORD rayCast;
	UWORD position;
	UWORD positionX, positionY;
	UBYTE mx,my;
	UBYTE color = 0;
	UWORD currentScreenYStepSize;
	UWORD ppx;
	UWORD sizeY = YSIZE/tableStepSizeY-1;
	UBYTE hDifference = 0;

	ppx = px/4;

	sx = tableXStart;
	currentScreenYStepSize = xCycles;

	for(UBYTE i=0;i<xCycles;i++)
	{
		sy = 0 + tableStepNumber;
		position = ((YSIZE/tableStepSizeY)-1)*xCycles+i;
		tz = 1;

		while(tz < renderingDepth && sy <YSIZE)
		{
			mx = (px + (mul(sx-20,tz))/8);
			my = (py + tz);
			th = heightMap0[ mx ][ my ];
			if(th>ph +  (mul(sy-16,tz))/8)
			{
				screen[position] = colorMap0[ mx ][ my ];
				sy+=1; //move X pixels to the top in calculations
				position-=currentScreenYStepSize; //move X pixels to the top on the destination screen
			}
			else
			{
				tz+=1;//+mipLevel; //move a variable step in depth to look for next height colision
			}
		}
		//finish vertical line with SKY
		while(sy < YSIZE)
		{
			if(screen[position] == 31) sy = YSIZE;
			else
			{
				screen[position] = 31;
				sy+=tableStepSizeY;
				position-=currentScreenYStepSize;
			}

		}
		//go to the next vertical line
		sx += 1;
	}
}
*/
/*
void ProcessRayCastsWithMipMaps(UBYTE *screen, WORD (*rayCastX)[TERRAINDEPTH], WORD (*rayCastY)[TERRAINDEPTH],
UBYTE px, UBYTE py, UBYTE ph,
	UBYTE tableXStart,	UBYTE tableStepSizeX, UBYTE tableStepSizeY, UBYTE tableStepNumber, UBYTE xCycles)
{
	UBYTE sx,sy,tz;
	UBYTE th = 0;
	UWORD position;
	UBYTE mx,my;
	UBYTE mipLevel;
	UBYTE color = 0;
	UWORD currentScreenYStepSize;
	UBYTE resolutionMip;

	sx = tableXStart;//set the x position in the raycast table
	currentScreenYStepSize = xCycles; //the same as the numer of x steps

	if(tableStepSizeY == 1)	resolutionMip = 0;
	else if (tableStepSizeY == 2)	resolutionMip = 1;
	else if (tableStepSizeY == 4)	resolutionMip = 2;

	for(UBYTE i=0;i<xCycles;i++)
	{
		//********* INITIALIZE INTERLACED CALCUTATIONS
		//sy = interlace/2 + modulo2[sx];
		sy = 0 + tableStepNumber;//YSIZE-1;//tableStepNumber;// + modulo2[sx];
		position = ((YSIZE/tableStepSizeY)-1)*xCycles+i;//tableStepNumber+sx-(XSIZE*sy);

		//********* INITIALIZE INTERLACED CALCUTATIONS
		//starting depth to look for height colission
		tz = 1;

		while(tz < renderingDepth && sy <YSIZE)
		{
			//***** set mipmap level
			mipLevel = tz/8 + resolutionMip;

			// set x,y pooositions on source maps
			mx = (px + rayCastX[sx][tz]);
			my = (py + tz);

			//*********** HEIGHT MIPMAP
			if(mipLevel == 0) th = heightMap0[ mx ][ my ];
			else if(mipLevel == 1)th = heightMap1[ mx/2 ][ my/2 ];
			else if(mipLevel == 2)th = heightMap2[ mx/4 ][ my/4 ];
			else if(mipLevel == 3)th = heightMap3[ mx/8 ][ my/8 ];
			else if(mipLevel > 3)th = heightMap4[ mx/16 ][ my/16 ];
			//*********** HEIGHT MIPMAP

			//height to look for at a given x,y terrain coordinate accounting for z depth
			//************************************************************


			if(th>ph + rayCastY[sy][tz])
			{

				//*************** COLOR MIPMAP
				if(mipLevel == 0)			color = colorMap0[ mx ][ my ];
				else if(mipLevel == 1)color = colorMap1[ mx/2 ][ my/2 ] + 1;
				else if(mipLevel == 2)color = colorMap2[ mx/4 ][ my/4 ] + 2;
				else if(mipLevel == 3)color = colorMap3[ mx/8 ][ my/8 ] + 3;
				else if(mipLevel > 3)	color = colorMap4[ mx/16 ][ my/16 ] + 4;
				screen[position] = color;
				//*************** COLOR MIPMAP

				sy+=tableStepSizeY; //move X pixels to the top in calculations
				position-=currentScreenYStepSize; //move X pixels to the top on the destination screen
			}
			else
			{
				tz+=1;//+mipLevel; //move a variable step in depth to look for next height colision
			}
		}
		//finish vertical line with SKY
		while(sy < YSIZE)
		{
			color = sy/4;//2
			//	screenDepth[position] = 0x01;
			screen[position] = color;
			sy+=tableStepSizeY;
			position-=currentScreenYStepSize;
		}
		//go to the next vertical line
		sx += tableStepSizeX;
	}
}
*/
