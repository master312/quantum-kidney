#include "cFontManager.h"

bool cFontManager::Initialize(){
	if(TTF_Init() < 0){
		StormPrintLog(STORM_LOG_ERROR, "cFontManager", "Could not init SDL TTF");
		return false;
	}
	StormPrintLog(STORM_LOG_INFO, "cFontManager", "Font system initialized");
	return true;
}
void cFontManager::SetChars(std::string s){
	chars = s;
}
bool cFontManager::LoadFont(std::string filename, std::string fontName, int size){
	std::string tureFileName = (char*)STORM_DIR_FONT + filename;
	TTF_Font *font = TTF_OpenFont(tureFileName.c_str(), size);
	if(font == NULL){
		StormPrintLog(STORM_LOG_ERROR, "cFontManager", 
					"Font %s not found", tureFileName.c_str());
		return false;
	}
	if(fontName == ""){
		StormPrintLog(STORM_LOG_WARNING, "cFontManager", 
					"Font name not specified");
		fontName = filename;
	}
	sFont f = GenerateFont(font, size);
	TTF_CloseFont(font);

	f.name = fontName;

	fonts[fontName] = f;

	StormPrintLog(STORM_LOG_INFO, "cFontManager", "Font '%s' generated", fontName.c_str());
	return true;
}
void cFontManager::SetLetterSpacing(std::string fontName, int spacing){
	if(fonts.count(fontName) == 0)
		return;
	fonts[fontName].spacing = spacing;
}

void cFontManager::UnloadFont(std::string fontName){
	if(fonts.count(fontName) == 0)
		return;
	tManager->UnloadTexture(fonts[fontName].texture);
	fonts.erase(fonts.find(fontName));
}
void cFontManager::UnloadAll(){
	std::map<std::string, sFont>::iterator iter;
	for(iter = fonts.begin(); iter != fonts.end(); ++iter){
		tManager->UnloadTexture(iter->second.texture);
	}
	fonts.clear();
}

void cFontManager::DrawText(std::string font, std::string text, int x, int y, 
		float r, float g, float b, float scale, float rotation){
	if(fonts.count(font) == 0){
		return;
	}
	sFont *tmpF = &fonts[font];
	int firstX = x;
	for(int i = 0; i < (int)text.size(); i++){
		std::string tmpG = "";
		if(IsUtf8(text, i)){
			tmpG = text.substr(i, 2);
			i += 1;
		}else{
			tmpG += text.at(i);
		}
		if(tmpG == " "){	//Handle space
			x += (tmpF->spacing * 4);
			continue;
		}else if(tmpG == "\n"){	//Handle new line
			y += tmpF->newLine;
			x = firstX;
			continue;
		}
		if(tmpF->glyphs.count(tmpG) > 0){
			DrawSection(tmpF->glyphs[tmpG], x, y, scale, rotation, r, g, b);
			x += tManager->GetSection(tmpF->glyphs[tmpG])->width + tmpF->spacing;
		}
	}
}
sRect cFontManager::GetTextSize(std::string text, std::string font){
	sRect tmpRect;
	if(fonts.count(font) == 0){
		return tmpRect;
	}
	sFont *tmpF = &fonts[font];
	int longestX = 0;
	for(int i = 0; i < (int)text.size(); i++){
		std::string tmpG = "";
		if(IsUtf8(text, i)){
			tmpG = text.substr(i, 2);
			i += 1;
		}else{
			tmpG += text.at(i);
		}
		if(tmpG == " "){	//Handle space
			tmpRect.w += (tmpF->spacing * 4);
			continue;
		}else if(tmpG == "\n"){	//Handle new line
			tmpRect.h += tmpF->newLine;
			longestX = tmpRect.w;
			tmpRect.w = 0;
			continue;
		}
		if(tmpF->glyphs.count(tmpG) > 0){
			int tmpToAdd = tManager->GetSection(tmpF->glyphs[tmpG])->width;
			tmpToAdd += tmpF->spacing;
			if(tmpRect.w + tmpToAdd > longestX){
				tmpRect.w += tmpToAdd;
			}
		}
	}
	tmpRect.h += tmpF->newLine;
	return tmpRect;
}
void cFontManager::DrawSection(uint section, int x, int y, float scale, 
									float rotation,  float r, float g, float b){
	std::cout << "cFontManager::DrawSection TEMPLATE CALLED" << std::endl;
}
sFont *cFontManager::GetFont(std::string fontName){
	if(fonts.count(fontName) == 0)
		return NULL;
	return &fonts[fontName];
}
//Private
sFont cFontManager::GenerateFont(TTF_Font *font, int size){
	sFont tFont;
	int tmpWidth = size; 
	int tmpHeight = TTF_FontHeight(font);
	tFont.newLine = tmpHeight;
    Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
    int xMax = 0, yMax = 0;
	SDL_Surface *tmpSurface = SDL_CreateRGBSurface(0, 
					1024, 1024, 32, rmask, gmask, bmask, amask);
	xMax = 1024 / tmpWidth;
	yMax = 1024 / tmpHeight;
	SDL_FillRect(tmpSurface, NULL, SDL_MapRGBA(tmpSurface->format, 255, 255, 255, 0));

	SDL_Rect tmpRect = {0, 0, tmpWidth, tmpHeight};
	SDL_Color color = {255, 255, 255};
	std::vector<std::string> horLines;	//[0] Holds all character on first horizontal line
	std::vector<std::vector<sRect> > horLinesRect;//Holds position and size for each character
	bool isDone = false;
	uint tmpP = 0;						//Temp pointer for chars array
	for(int i = 0; i < yMax && !isDone; i++){
		tmpRect.y = (int)(i * tmpHeight);
		std::string tmpLine = "";
		std::vector<sRect> tmpRectVec;
		for(int j = 0; j < xMax; j++){
			tmpRect.x = (int)(j * tmpWidth);
			if(tmpP < chars.size() - 1){
				SDL_Surface *tmpSur;
				int minX = 0, maxX = 0, minY = 0, maxY = 0;;
				sRect tRect;
				tRect.x = tmpRect.x;
				tRect.y = tmpRect.y;
				tRect.w = 0;
				tRect.h = tmpRect.h;
				if(IsUtf8(chars, tmpP)){
					std::string ts = chars.substr(tmpP, 2);
					tmpSur = TTF_RenderUTF8_Solid(font, (char*)ts.c_str(), color);
					Uint16 ch = ts.c_str()[0] + ts.c_str()[1];
					ch =(ch<<8) | ts.c_str()[1];	//This may not work 
					ch =(ch<<8) | ts.c_str()[0];
					TTF_GlyphMetrics(font, ch, &minX, &maxX, &minY, &maxY, NULL);
					tmpP += 2;
					tmpLine += ts;
				}else{
					char tmpC[2];
					tmpC[0] = chars.at(tmpP);
					tmpC[1] = '\0';
					tmpSur = TTF_RenderUTF8_Solid(font, (char*)tmpC, color);
					TTF_GlyphMetrics(font, tmpC[0], &minX, &maxX, &minY, &maxY, NULL);
					if(tmpC[0] == 'j' || tmpC[0] == 'J'){
						maxX += 2;
					}
					tmpLine += chars.at(tmpP);
					tmpP += 1;
				}
				//tRect.y += maxY;
				tRect.x += minX;
				tRect.w = maxX - minX;
				tmpRectVec.push_back(tRect);
				SDL_BlitSurface(tmpSur, NULL, tmpSurface, &tmpRect);
				SDL_FreeSurface(tmpSur);
			}else{
				isDone = true;
				break;
			}
		}
		horLines.push_back(tmpLine);
		horLinesRect.push_back(tmpRectVec);
		tmpRectVec.clear();
	}

	tFont.spacing = DEF_SPACING;
	tFont.size = size;
	tFont.texture = tManager->LoadTextureFromMemory(tmpSurface);
	for(int i = 0; i < (int)horLinesRect.size(); i++){
		tmpP = 0;
		for(int j = 0; j < (int)horLinesRect[i].size(); j++){
			sRect *tmpR = &horLinesRect[i][j];
			uint tmpS = tManager->CreateSection(tFont.texture, 
												tmpR->x, tmpR->y, 
												tmpR->w, tmpR->h);
			if(IsUtf8(horLines[i], tmpP)){
				std::string tmpG = horLines[i].substr(tmpP, 2);
				tFont.glyphs[tmpG] = tmpS;
				tmpP += 2;
			}else{
				char tmpchar[2];
				tmpchar[0] = horLines[i].at(tmpP);
				tmpchar[1] = '\0';
				tFont.glyphs[(char*)tmpchar] = tmpS;
				tmpP += 1;
			}
		}
	}
	//SDL_SaveBMP(tmpSurface, "temp_font.bmp");
	SDL_FreeSurface(tmpSurface);
	return tFont;
}
bool cFontManager::IsUtf8(std::string str, int ch){
	return (uint)str.at(ch) > 510;
}