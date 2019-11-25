#include "engine.h"
void OverwriteMap()
{
	UBYTE mapNumber;
	
	UWORD (*_mapHigh)[256];

	mapNumber = (p1y/256) % 11 ;


	if(mapNumber == 0)
	{
		_mapHigh = mapHigh1;
		if(mapLoaded1 == 0)
		{
			systemUse();
			LoadMap("height1.raw", "color1.raw", mapHigh1);
			systemUnuse();
			mapLoaded1 = 1;
			deltaTime=0;
		}
		
	}
	else if(mapNumber == 1)
	{
		_mapHigh = mapHigh2;
		if(mapLoaded2 == 0)
		{
			systemUse();
			LoadMap("height2.raw", "color2.raw", mapHigh2);
			systemUnuse();
			mapLoaded2 = 1;
			deltaTime=0;
		}
		
	}
	else if(mapNumber == 2)
	{
		_mapHigh = mapHigh3;
		if(mapLoaded3 == 0)
		{
			systemUse();
			LoadMap("height3.raw", "color3.raw", mapHigh3);
			systemUnuse();
			mapLoaded3 = 1;
			deltaTime=0;
		}
		
	}
	else if(mapNumber == 3)
	{
		_mapHigh = mapHigh4;
		if(mapLoaded4 == 0)
		{
			systemUse();
			LoadMap("height4.raw", "color4.raw", mapHigh4);
			systemUnuse();
			mapLoaded4 = 1;
			deltaTime=0;
		}
		
	}
	else if(mapNumber == 4)
	{
		_mapHigh = mapHigh5;
		if(mapLoaded5 == 0)
		{
			systemUse();
			LoadMap("height5.raw", "color5.raw", mapHigh5);
			systemUnuse();
			mapLoaded5 = 1;
			deltaTime=0;
		}
		
	}
	else if(mapNumber == 5)
	{
		_mapHigh = mapHigh6;
		if(mapLoaded6 == 0)
		{
			systemUse();
			LoadMap("height6.raw", "color6.raw", mapHigh6);
			systemUnuse();
			mapLoaded6 = 1;
			deltaTime=0;
		}
		
	}
	else if(mapNumber == 6)
	{
		_mapHigh = mapHigh7;
		if(mapLoaded7 == 0)
		{
			systemUse();
			LoadMap("height7.raw", "color7.raw", mapHigh7);
			systemUnuse();
			mapLoaded7 = 1;
			deltaTime=0;
		}
		
	}
	else if(mapNumber == 7)
	{
		_mapHigh = mapHigh8;
		if(mapLoaded8 == 0)
		{
			systemUse();
			LoadMap("height8.raw", "color8.raw", mapHigh8);
			systemUnuse();
			mapLoaded8 = 1;
			deltaTime=0;
		}
		
	}
	else if(mapNumber == 8)
	{
		_mapHigh = mapHigh9;
		if(mapLoaded9 == 0)
		{
			systemUse();
			LoadMap("height9.raw", "color9.raw", mapHigh9);
			systemUnuse();
			mapLoaded9 = 1;
			deltaTime=0;
		}
		
	}
	else if(mapNumber == 9)
	{
		_mapHigh = mapHigh10;
		if(mapLoaded10 == 0)
		{
			systemUse();
			LoadMap("height10.raw", "color10.raw", mapHigh10);
			systemUnuse();
			mapLoaded10 = 1;
			deltaTime=0;
		}
		
	}
	else if(mapNumber == 10)
	{
		_mapHigh = mapHigh0;
		
	}

	for(UWORD y=lastOverwrittenLine;y<p1y;y++)
	for(UWORD x=0;x<256;x++)
		{
			//int x = 0;
			//CopyMem(&_mapHigh[x][(UBYTE)y], &mapHigh[x][(UBYTE)y], 256);
			
			mapHigh[x][(UBYTE)y] = _mapHigh[x][(UBYTE)y];
			//mapLow[x][(UBYTE)y] =  _mapLow[x][(UBYTE)y];
		}

	lastOverwrittenLine = p1y;
	
}