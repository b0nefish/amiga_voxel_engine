
void LoadMap(const char *heightName, const char *colorName,
			 UWORD (*high)[MAPSIZE])
{
	BITMAPINFOHEADER tempHeader;
	unsigned char tempColorTable[16 * 4];
	unsigned char *heightMap, *colorMap;

	heightMap = LoadBitmapFile(heightName, &tempHeader, tempColorTable, 0, 0);
	colorMap = LoadBitmapFile(colorName, &tempHeader, tempColorTable, 0, 0);

	CombineMapsHigh(heightMap, colorMap,high);
						//GenerateMap(high);

	free(heightMap);
	free(colorMap);

	//ReadHeight(heightName, heightMap);
	//ReadColor(colorName, colorMap);

	//AddBumpToColorMap(colorMap,heightMap);
	//LimitColorMap(colorMap);
	//SmoothColorMap(colorMap);
	//SmoothHeightMap(heightMap);


	//SmoothHeightMap(heightMap);
	//SmoothColorMap(colorMap);
	//CombineMapsHigh(heightMap, colorMap, med);
	//SmoothHeightMap(heightMap);
	//SmoothColorMap(colorMap);
	//CombineMapsHigh(heightMap, colorMap, low);
}


// void MakeMap2(UBYTE bezierPoints [289] , UWORD (*high)[MAPSIZE])
// {

// 	UWORD powers[16] = 
// 	{
// 		0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225
// 	};
// 	UWORD powers2[16] = 
// 	{
// 		0, 28, 52, 72, 88, 100, 108, 112, 112, 108, 100, 88, 72, 52, 28, 0
// 	};
	
// 	for(UBYTE mapY = 0; mapY < 128; ++mapY)
// 	{

// 		UWORD v = mapY & 0xF;

// 		UWORD TV1 = powers[15-v];
// 		UWORD TV2 = powers2[v];
// 		UWORD TV3 = powers[v];

// 		UBYTE yStride = 16 - ((mapY/16)*2);
// 		for(UBYTE mapX = 0; mapX < 128; ++mapX)
// 		{
// 			UBYTE xStride = ((mapX/16)*2);

// 			UWORD u = mapX & 0xF;

// 			UWORD TU1 = powers[15-u];
// 			UWORD TU2 = powers2[u];
// 			UWORD TU3 = powers[u];


// 			UBYTE *bez = bezierPoints + yStride*17 + xStride;
// 			UWORD P1 = (TU1*(*bez) + TU2*(*(bez+1)) + TU3*(*(bez+2)))/225;
// 			bez -= 17;
// 			UWORD P2 = (TU1*(*bez) + TU2*(*(bez+1)) + TU3*(*(bez+2)))/225;
// 			bez -= 17;
// 			UWORD P3 = (TU1*(*bez) + TU2*(*(bez+1)) + TU3*(*(bez+2)))/225;
			
// 			UWORD P = ((TV1*P1) + (TV2*P2) + (TV3*P3))/225; 
			
// 			//UWORD oldValue = high[mapX][mapY];
// 			UWORD t = timerGetPrec();
// 			t *= 532;
// 			UWORD setP = P + (t%20) - 10;
// 			if(setP > 255)
// 			{
// 				setP = P;
// 			}
			
// 			setP |= ((( 29 -  (setP/28)) << 8) & 0xFF00);
// 			//UWORD newValue = (setP & 0xFF) + (oldValue & 0xFF00);
			
// 			 high[mapX][mapY] = setP;
// 		}
// 	}
// }

void MakeMap3(UBYTE bezierPoints [289] , UWORD (*high)[MAPSIZE])
{

	
	for(UBYTE mapY = 0; mapY < 128; ++mapY)
	{

		UWORD v = mapY & 0x7;

		UWORD TV1 = 8-v;
		UWORD TV2 = v;

		UBYTE yStride = (16 - ((mapY>>3)))*17;
		for(UBYTE mapX = 0; mapX < 128; ++mapX)
		{
			UBYTE xStride = ((mapX>>3));
			UBYTE *ptr = bezierPoints + yStride + xStride;

			UWORD u = mapX & 0x7;

			UWORD TU1 = 8-u;
			UWORD TU2 = u;


			UWORD bez = *((UWORD *)ptr);
			UWORD bez2 = *((UWORD *)(ptr-17));
			UWORD P1 = (TU1*((bez>>8)&0xFF) + TU2*(bez&0xFF));
			
			UWORD P2 = (TU1*((bez2>>8)&0xFF) + TU2*(bez2&0xFF));
			
			UWORD P = ((TV1*P1) + (TV2*P2))>>6; 
			
			//UWORD oldValue = high[mapX][mapY];
			UWORD t = timerGetPrec();
			t *= 532;
			UWORD setP = P + (t&0xF) - 10;
			if(setP > 255)
			{
				setP = P;
			}
			
			setP |= ((( 29 -  (setP/28)) << 8) & 0xFF00);
			//UWORD newValue = (setP & 0xFF) + (oldValue & 0xFF00);
			
			 high[mapX][mapY] = setP;
		}
	}
}

void SetupMaps()
{
	
	UBYTE bezier2[289] = 
	{
		255,	255,	255,	100,	24,		42,		144,	255,	84,		32,		12,		4,		8,		10,		180,	255,	255,

		255,	255,	100,	80,		48,		80,		255,	255,	255,	100,	40,		20,		30,		20,		124,	255,	255,
		
		255,	96,		64,		32,		24,		60,		255,	255,	112,	60,		30,		10,		10,		10,		30,		255,	255,
		
		255,	58,		36,		120,	50,		30,		255,	140,	32,		0,		0,		255,	20,		20,		20,		255,	255,
		
		255,	30,		24,		200,	80,		40,		255,	180,	64,		0,		0,		255,	255,	150,	32,		255,	255,
		
		255,	16,		20,		220,	220,	60,		50,		255,	100,	0,		0,		255,	255,	255,	16,		255,	255,
		
		255,	8,		12,		190,	255,	80,		44,		60,		80,		0,		255,	255,	255,	220,	34,		255,	255,
		
		255,	52,		22,		160,	255,	120,	14,		42,		52,		0,		255,	255, 	255,	240,	10,		255,	255,
		
		255,	80,		32,		40,		140,	110,	4,		36,		22,		255,	255,	255,	255,	220,	10,		255,	255,
		
		255,	128,	62,		28,		80,		100,	20,		30,		18,		255,	255,	255,	255,	200,	22,		255,	255,
		
		255,	200,	150,	42,		34,		64,		36,		48,		24,		255,	255,	255,	255,	180,	28,		255,	255,
		
		255,	255,	180,	140,	52,		28,		22,		64,		40,		68,		255,	255,	255,	186,	8,		255,	255,
		
		255,	255,	255,	165,	130,	84,		24,		136,	56,		74,		128,	255,	255,	196,	14,		255,	255,
		
		255,	255,	255,	255,	174,	60,		16,		158,	94,		60,		54,		128,	144,	64,		22,		255,	255,
		
		255,	255,	255,	255,	112,	20,		38,		200,	224,	70,		4,		100,	52,		26,		32,		255,	255,
		
		255,	255,	255,	126,	60,		32,		74,		220,	200,	50,		8,		50,		32,		18,		22,		255,	255,
		
		255,	255,	255,	100,	24,		42,		144,	255,	84,		32,		12,		4,		8,		10,		180,	255,	255,
};
	

	// LoadMap("data/h11", "data/c11", engine.renderer.mapSource[0]);
	// engine.renderer.mapLoaded0 = 1;
	// LoadMap("data/h10", "data/c10", engine.renderer.mapSource[1]);
	// engine.renderer.mapLoaded1=1;
	// LoadMap("data/h9", "data/c9", engine.renderer.mapSource[2]);
	// engine.renderer.mapLoaded2=1;
	// LoadMap("data/h8", "data/c8", engine.renderer.mapSource[3]);
	// engine.renderer.mapLoaded3=1;
	// LoadMap("data/h7", "data/c7", engine.renderer.mapSource[4]);
	// engine.renderer.mapLoaded4=1;
	// LoadMap("data/h6", "data/c6", engine.renderer.mapSource[5]);
	// engine.renderer.mapLoaded5=1;
	// LoadMap("data/h5", "data/c5", engine.renderer.mapSource[6]);
	// engine.renderer.mapLoaded6=1;
	// LoadMap("data/h4", "data/c4", engine.renderer.mapSource[7]);
	// engine.renderer.mapLoaded7=1;
	// LoadMap("data/h3", "data/c3", engine.renderer.mapSource[8]);
	// engine.renderer.mapLoaded8=1;
	// LoadMap("data/h7", "data/c7", engine.renderer.mapSource[9]);
	// engine.renderer.mapLoaded9=1;
	// LoadMap("data/h1", "data/c1", engine.renderer.mapSource[10]);
	// engine.renderer.mapLoaded10=1;
	MakeMap3(bezier2, engine.renderer.mapSource[0]);
	MakeMap3(bezier2, engine.renderer.mapSource[1]);
	MakeMap3(bezier2, engine.renderer.mapSource[2]);
	MakeMap3(bezier2, engine.renderer.mapSource[3]);
	MakeMap3(bezier2, engine.renderer.mapSource[4]);
	MakeMap3(bezier2, engine.renderer.mapSource[5]);
	MakeMap3(bezier2, engine.renderer.mapSource[6]);
	MakeMap3(bezier2, engine.renderer.mapSource[7]);
	MakeMap3(bezier2, engine.renderer.mapSource[8]);
	MakeMap3(bezier2, engine.renderer.mapSource[9]);
	MakeMap3(bezier2, engine.renderer.mapSource[10]);
	
	//prepare starting map
	CopyMapWord(engine.renderer.mapSource[0], engine.renderer.mapHigh);
	//CopyMapWord(mapMed0, mapMed);
	//CopyMapWord(mapLow0, mapLow);
}