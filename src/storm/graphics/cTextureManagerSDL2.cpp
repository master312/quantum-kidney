#include "cTextureManagerSDL2.h"

cTextureManagerSDL2::cTextureManagerSDL2(){
}
cTextureManagerSDL2::~cTextureManagerSDL2(){
	UnloadAll();
}
uint cTextureManagerSDL2::LoadTexture(std::string filename){
	uint textureId = IsLoaded(filename);
	if(textureId > 0){
		textures[textureId]->usage ++;
		return textureId;
	}
	std::string fullFilename = (char*)STORM_DIR_GRAPHICS + filename;
	SDL_Surface *sur = IMG_Load(fullFilename.c_str());
	if(sur == NULL){
		StormPrintLog(STORM_LOG_ERROR, "cTextureManagerSDL2", 
					"Texture %s not found", fullFilename.c_str());
		return 0;
	}

	textureId = LoadTextureFromMemory(sur, filename);

	SDL_FreeSurface(sur);
	StormPrintLog(STORM_LOG_INFO, "cTextureManagerSDL2",
				"Texture: %s loaded. ID: %d", fullFilename.c_str(), textureId);
	PrintMemoryUsage();
	return textureId;
}
uint cTextureManagerSDL2::LoadTextureFromMemory(SDL_Surface *sur, 
			std::string filename){
	uint textureId;
	int maxH = graphics->GetTextureMaxHeight();
	int size = 0;
	if(sur->h > maxH){
		//Texture height is bigger then hardware supports
		int finalSize = 0;
		uint tmpTxId = 0;
		int chunks = (sur->h / maxH) + 1;
		for(int i = 0; i < chunks; i++){
			int tmpH = maxH;
			if(i + 1 == chunks){
				tmpH = sur->h - (maxH * i);
			}
			SDL_Surface *tmpCh = SDL_CreateRGBSurface(0, 
								sur->w, tmpH, 32, RMASK, GMASK, BMASK, AMASK);
			SDL_Rect srcRect = {0, maxH * i, sur->w, tmpH};
			SDL_BlitSurface(sur, &srcRect, tmpCh, NULL);

			SDL_Texture *tmpTx = MakeTexture(tmpCh, size); 
			finalSize += size;
			SDL_FreeSurface(tmpCh);
			if(tmpTx == NULL){
				StormPrintLog(STORM_LOG_ERROR, "cTextureManagerSDL2", 
					"Could not create texture '%s'", filename.c_str());
				return 0;
			}
			sTexture *tmpT = new sTexture(tmpTx, filename, 
											sur->w, sur->h, (size/1024));
			tmpT->usage ++;
			tmpTxId = GenId();
			if(i == 0)
				textureId = tmpTxId;
			textures[tmpTxId] = tmpT;
		}
		memoryUsage += (finalSize / 1024);
	}else{
		SDL_Texture *txture = MakeTexture(sur, size);
		if(txture == NULL){
			StormPrintLog(STORM_LOG_ERROR, "cTextureManagerSDL2", 
				"Could not create texture '%s'", filename.c_str());
			SDL_FreeSurface(sur);
			return 0;
		}
		memoryUsage += (size / 1024);
		sTexture *tmpT = new sTexture(txture, filename, 
										sur->w, sur->h, (size/1024));
		tmpT->usage ++;
		textureId = GenId();
		textures[textureId] = tmpT;
	}
	return textureId;
}
void cTextureManagerSDL2::ReloadTexture(sTexture *tx){
	if(tx->filename == "Texture created from memory"){
		StormPrintLog(STORM_LOG_WARNING, "cTextureManagerSDL2", 
					"Texture can not be reloaded. Reason: Texture created from memory");
		return;
	}
	std::cout << "TODO: Reload texture SDL2" << std::endl;
}
void cTextureManagerSDL2::UnloadTexture(uint textureId){
	if(textures.count(textureId) > 0){
		if(textures[textureId]->usage > 1){
			textures[textureId]->usage --;
			return;
		}
		
		int split = textures[textureId]->height / graphics->GetTextureMaxHeight();
		if(split > 0){
			for(int i = 0; i < split + 1; i++){
				SDL_DestroyTexture(textures[textureId + i]->sdlTexture);
				memoryUsage -= textures[textureId + i]->memory;
				delete textures[textureId + i];
				textures.erase(textureId + i);
			}
		}else{
			SDL_DestroyTexture(textures[textureId]->sdlTexture);
			memoryUsage -= textures[textureId]->memory;
			delete textures[textureId];
			textures.erase(textureId);
		}

		std::map<uint, sTextureSection>::iterator i;
		std::list<std::map<uint, sTextureSection>::iterator > iteratorList;
		for(i = sections.begin(); i != sections.end(); ++i){
			if(i->second.texture == textureId){
				iteratorList.push_back(i);
			}
		}
		for(auto i : iteratorList){
			sections.erase(i);
		}
	}else{
		StormPrintLog(STORM_LOG_WARNING, "cTextureManagerSDL2", 
					"Tried to unload not loaded texture");
	}
}
void cTextureManagerSDL2::UnloadAll(){
	std::map<uint, sTexture*>::iterator iter;
	for(iter = textures.begin(); iter != textures.end(); ++iter){
		memoryUsage -= iter->second->memory;
		SDL_DestroyTexture(iter->second->sdlTexture);
		delete iter->second;
	}
	textures.clear();
	sections.clear();
	StormPrintLog(STORM_LOG_INFO, "cTextureManagerSDL2", "All textures deleted");
	PrintMemoryUsage();
}
//Private
SDL_Texture *cTextureManagerSDL2::MakeTexture(SDL_Surface *sur, int &size){
	SDL_Texture *tmp = SDL_CreateTextureFromSurface(
							((cGraphicsSDL2*)graphics)->GetRenderer(), sur);
	if(tmp == NULL){
		StormPrintLog(STORM_LOG_ERROR, "cTextureManagerSDL2", "Could not create SDL_Texture!");
		return NULL;
	}
	size = sur->w * sur->h * sur->format->BytesPerPixel;
	SDL_SetTextureBlendMode(tmp, SDL_BLENDMODE_BLEND);
	return tmp;
}
//Protected
void cTextureManagerSDL2::DrawRaw(uint textureId, 
								int srcX, int srcY, int srcW, int srcH, 
								int destX, int destY, int destW, int destH, 
								int rotation, int opacity){
	if(rotation != 0)
		std::cout << "cTextureManagerSDL2 TODO: ROTATION!" << std::endl;
	sTexture *tmpT = textures[textureId];
	
	tmpRenderSrc.x = srcX;
	tmpRenderSrc.y = srcY;
	tmpRenderSrc.w = srcW;
	tmpRenderSrc.h = srcH;

	tmpRenderDest.x = destX;
	tmpRenderDest.y = destY;
	tmpRenderDest.w = destW;
	tmpRenderDest.h = destH;

	SDL_Texture *tmpTx = tmpT->sdlTexture;
	SDL_Renderer *gRenderer = ((cGraphicsSDL2*)graphics)->GetRenderer();
	if(opacity != 100){
		SDL_SetTextureAlphaMod(tmpTx, opacity);
		SDL_RenderCopy(gRenderer, tmpTx, &tmpRenderSrc, &tmpRenderDest);
		SDL_SetTextureAlphaMod(tmpTx, 100);
		return;
	}
	SDL_RenderCopy(gRenderer, tmpTx, &tmpRenderSrc, &tmpRenderDest);
}