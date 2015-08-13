#include "cTextureManager.h"

cTextureManager::cTextureManager(){
	memoryUsage = 0;
}
cTextureManager::~cTextureManager(){

}
bool cTextureManager::Initialize(){
	uint tmp = LoadTexture("default.png");
	return tmp != 0;
}
void cTextureManager::SetGraphics(cGraphics *gr){
	graphics = gr;
}
uint cTextureManager::LoadTexture(std::string filename){
	std::cout << "cTextureManager ERROR: Template class called" << std::endl;
	return 0;
}
uint cTextureManager::LoadTextureFromMemory(SDL_Surface *sur, std::string filename){
	std::cout << "cTextureManager ERROR: Template class called" << std::endl;
	return 0;
}
void cTextureManager::ReloadTextures(){
	std::map<uint, sTexture*>::iterator i;
	for(i = textures.begin(); i != textures.end(); ++i){
		ReloadTexture(i->first);
	}
	StormPrintLog(STORM_LOG_INFO, "cTextureManager",
								"%d textures reloaded", textures.size());
}
void cTextureManager::ReloadTexture(uint textureId){
	std::cout << "cTextureManager ERROR: Template class called" << std::endl;
}
void cTextureManager::UnloadTexture(uint textureId){
	std::cout << "cTextureManager ERROR: Template class called" << std::endl;
}
void cTextureManager::RemoveSection(uint sectionId){
	if(sections.count(sectionId) > 0){
		sections.erase(sectionId);
	}else{
		StormPrintLog(STORM_LOG_WARNING, "cTextureManager", 
										"Tried to remove non existing section");
	}
}
uint cTextureManager::CreateSection(uint textureId, int x, int y, int w, int h){
	sTextureSection s(textureId, x, y, w, h);
	if(sections.size() > 0){
		std::map<uint, sTextureSection>::iterator i = sections.end();
		--i;
		sections[i->first + 1] = s;
		return (uint)i->first + 1;
	}
	sections[1] = s;
	return 1;
}
uint cTextureManager::CreateSection(sTextureSection s){
	if(sections.size() > 0){
		std::map<uint, sTextureSection>::iterator i = sections.end();
		--i;
		sections[i->first + 1] = s;
		return (uint)i->first + 1;
	}
	sections[1] = s;
	return 1;
}
void cTextureManager::DrawTexture(uint textureId, int x, int y, float scale, 
														int rot, int opacity){
	if(textures.count(textureId) == 0){
		textureId = 1;
	}
	sTexture *tmpT = textures[textureId];
	DrawRaw(textureId, 0, 0, tmpT->width, tmpT->height, 
						x, y, tmpT->width * scale, tmpT->height * scale,
						rot, opacity);
}
void cTextureManager::DrawTextureScaled(uint textureId, sRect *destRect, 
														int rot, int opacity){
	if(textures.count(textureId) == 0){
		textureId = 1;
	}
	sTexture *tmpT = textures[textureId];
	DrawRaw(textureId, 0, 0, tmpT->width, tmpT->height, 
						destRect->x, destRect->y, destRect->w, destRect->h,
						rot, opacity);
}
void cTextureManager::DrawTextureCropped(uint textureId, sRect *srcRect, int x, int y, 
														int rot, int opacity){
	if(textures.count(textureId) == 0){
		textureId = 1;
	}
	DrawRaw(textureId, srcRect->x, srcRect->y, srcRect->w, srcRect->h, 
						x, y, srcRect->w, srcRect->h,
						rot, opacity);
}
void cTextureManager::DrawSection(uint sectionId, int x, int y, float scale, 
														int rot, int opacity){
	if(sections.count(sectionId) == 0){
		StormPrintLog(STORM_LOG_ERROR, "cTextureManager", 
						"No section with ID %d", sectionId);
		return;
	}
	sTextureSection *tmpS = &sections[sectionId];
	DrawRaw(tmpS->texture, tmpS->x, tmpS->y, tmpS->width, tmpS->height, 
						x, y, tmpS->width * scale, tmpS->height * scale,
						rot, opacity);
}
void cTextureManager::DrawSectionScaled(uint sectionId, sRect *destRect, 
														int rot, int opacity){
	if(sections.count(sectionId) == 0){
		StormPrintLog(STORM_LOG_ERROR, "cTextureManager", 
						"No section with ID %d", sectionId);
		return;
	}
	sTextureSection *tmpS = &sections[sectionId];
	DrawRaw(tmpS->texture, tmpS->x, tmpS->y, tmpS->width, tmpS->height, 
						destRect->x, destRect->y, destRect->w, destRect->h,
						rot, opacity);
}
void cTextureManager::DrawSectionCropped(uint sectionId, sRect *crop, 
											int x, int y, int rot, int opacity){
	if(sections.count(sectionId) == 0){
		StormPrintLog(STORM_LOG_ERROR, "cTextureManager", 
						"No section with ID %d", sectionId);
		return;
	}
	sTextureSection *tmpS = &sections[sectionId];
	DrawRaw(tmpS->texture, 
			tmpS->x + crop->x, tmpS->y + crop->y, crop->w, crop->h, 
			x, y, crop->w, crop->h, rot, opacity);
}

int cTextureManager::GetTextureWidth(uint textureId){
	if(textures.count(textureId) > 0){
		return textures[textureId]->width;
	}
	return -1;
}
int cTextureManager::GetTextureHeight(uint textureId){
	if(textures.count(textureId) > 0){
		return textures[textureId]->height;
	}
	return -1;
}
sTextureSection *cTextureManager::GetSection(uint sectionId){
	if(sections.count(sectionId) > 0){
		return &sections[sectionId]; 
	}
	return NULL;
}
sTexture *cTextureManager::GetTexture(uint textureId){
	if(textures.count(textureId) > 0){
		return textures[textureId]; 
	}
	return NULL;
}
void cTextureManager::UnloadAll(){
	std::cout << "cTextureManager ERROR: Template class called" << std::endl;
}
uint cTextureManager::IsLoaded(std::string filename){
	if(textures.size() == 0)
		return 0;
	std::map<uint, sTexture*>::iterator iter;
	for(iter = textures.begin(); iter != textures.end(); ++iter){
		if(iter->second->filename == filename){
			return iter->first;
		}
	}
	return 0;
}
void cTextureManager::PrintMemoryUsage(){
	if(memoryUsage < 4069){
		StormPrintLog(STORM_LOG_INFO, "cTextureManager", "Memory usage %dkb", memoryUsage);
	}else{
		StormPrintLog(STORM_LOG_INFO, "cTextureManager", "Memory usage %fmb", (float)memoryUsage/1024);
	}
}
uint cTextureManager::GenId(){
	if(textures.size() > 0){
		std::map<uint, sTexture*>::iterator i = textures.end();
		--i;
		return i->first + 1;
	}else{
		return 1;
	}
}
//Protected
void cTextureManager::DrawRaw(uint textureId, 
								int srcX, int srcY, int srcW, int srcH, 
								int destX, int destY, int destW, int destH,
								int rotation, int opacity){
	std::cout << "cTextureManager ERROR: Template class called" << std::endl;
}