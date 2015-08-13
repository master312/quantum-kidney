#include "cTextureManagerOpenGL.h"
#if BUILD_OPENGL > 0

cTextureManagerOpenGL::cTextureManagerOpenGL(){
}
cTextureManagerOpenGL::~cTextureManagerOpenGL(){
	UnloadAll();
}
uint cTextureManagerOpenGL::LoadTexture(std::string filename){
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
	StormPrintLog(STORM_LOG_INFO, "cTextureManagerOpenGL",
				"Texture: %s loaded. ID: %d", fullFilename.c_str(), textureId);
	PrintMemoryUsage();
	return textureId;
}

uint cTextureManagerOpenGL::LoadTextureFromMemory(SDL_Surface *sur, 
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

			uint glTxtId = MakeTexture(tmpCh, size);

			finalSize += size;
			SDL_FreeSurface(tmpCh);

			if(glTxtId == 0) {
				StormPrintLog(STORM_LOG_ERROR, "cTextureManagerOpenGL", 
					"Could not create texture '%s'", filename.c_str());
				return 0;
			}
			sTexture *tmpT = new sTexture(glTxtId, filename, 
												sur->w, sur->h, (size / 1024));
			tmpT->usage ++;
			tmpTxId = GenId();
			if(i == 0)
				textureId = tmpTxId;
			textures[tmpTxId] = tmpT;
		}
		memoryUsage += (finalSize / 1024);
	}else{
		uint glTxtId = MakeTexture(sur, size);
		if(glTxtId == 0){
			StormPrintLog(STORM_LOG_ERROR, "cTextureManagerOpenGL", 
				"Could not create texture '%s'", filename.c_str());
			SDL_FreeSurface(sur);
			return 0;
		}
		memoryUsage += (size / 1024);
		sTexture *tmpT = new sTexture(glTxtId, filename, 
												sur->w, sur->h, (size / 1024));
		tmpT->usage ++;
		textureId = GenId();
		textures[textureId] = tmpT;
	}
	return textureId;
}

void cTextureManagerOpenGL::ReloadTexture(sTexture *tx){
	if(tx->filename == "Texture created from memory"){
		StormPrintLog(STORM_LOG_WARNING, "cTextureManagerOpenGL", 
			"Texture can not be reloaded. Reason: Texture created from memory");
		return;
	}
	std::string fullFilename = (char*)STORM_DIR_GRAPHICS + tx->filename;
	SDL_Surface *tmpSur = IMG_Load(fullFilename.c_str());
	if(tmpSur == NULL){
		StormPrintLog(STORM_LOG_WARNING, "cTextureManagerOpenGL", 
					"Texture can not be reloaded. File:%s not found", 
					fullFilename.c_str());
		return;
	}
	glDeleteTextures(1, &tx->glTexture);
	int size = 0;
	tx->glTexture = MakeTexture(tmpSur, size);
	memoryUsage -= tx->memory;
	tx->memory = size / 1024;
	memoryUsage += tx->memory;
	SDL_FreeSurface(tmpSur);
}
void cTextureManagerOpenGL::UnloadTexture(uint textureId){
	if(textures.count(textureId) > 0){
		if(textures[textureId]->usage > 1){
			textures[textureId]->usage --;
			return;
		}
		
		int split = textures[textureId]->height / graphics->GetTextureMaxHeight();
		if(split > 0){
			for(int i = 0; i < split + 1; i++){
				glDeleteTextures(1, &textures[textureId + i]->glTexture);
				memoryUsage -= textures[textureId + i]->memory;
				delete textures[textureId + i];
				textures.erase(textureId + i);
			}
		}else{
			glDeleteTextures(1, &textures[textureId]->glTexture);
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
		StormPrintLog(STORM_LOG_WARNING, "cTextureManagerOpenGL", 
						"Tried to unload not loaded texture");
	}
}

void cTextureManagerOpenGL::UnloadAll(){
	std::map<uint, sTexture*>::iterator iter;
	for(iter = textures.begin(); iter != textures.end(); ++iter){
		memoryUsage -= iter->second->memory;
		glDeleteTextures(1, &iter->second->glTexture);
		delete iter->second;
	}
	textures.clear();
	sections.clear();
	StormPrintLog(STORM_LOG_INFO, "cTextureManagerOpenGL", 
					"All textures deleted");
	PrintMemoryUsage();
}

//Private 
uint cTextureManagerOpenGL::MakeTexture(SDL_Surface *sur, int &size){
	uint m_Texture = 0;	//Temperory texture ID holder
	GLfloat m_Width = 0;
	GLfloat m_Height = 0;
	glPixelStorei(GL_UNPACK_ALIGNMENT,4);

	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//setup all the information
	m_Width = (GLfloat)sur->w;
	m_Height = (GLfloat)sur->h;

	if (sur->format->BytesPerPixel == 4){	//if there is alpha
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, m_Width, m_Height,
							GL_RGBA, GL_UNSIGNED_BYTE, sur->pixels);
	}else{				// no alpha
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Width, m_Height,
							GL_RGB, GL_UNSIGNED_BYTE, sur->pixels);
	}
	size = sur->w * sur->h * sur->format->BytesPerPixel;
	return m_Texture;
}

//Protected
void cTextureManagerOpenGL::DrawRaw(uint textureId, int srcX, int srcY, 
								int srcW, int srcH, 
								int destX, int destY, int destW, int destH,
								int rotation, int opacity){
	sTexture *tmpT = textures[textureId];
	glBindTexture(GL_TEXTURE_2D, tmpT->glTexture);
	glPushMatrix();
	if(rotation != 0){
		int tmpX = destX + (tmpT->width / 2);
		int tmpY = destY + (tmpT->height / 2);
		glTranslatef(tmpX, tmpY, 0);
		glRotatef(rotation, 0.0, 0.0, 1.0);
		glTranslatef(-tmpX, -tmpY, 0);
	}

	GLfloat tSX = (GLfloat)1.0 / ((GLfloat)tmpT->width / srcX);
	GLfloat tSY = (GLfloat)1.0 / ((GLfloat)tmpT->height / srcY);
	GLfloat tEX = (GLfloat)1.0 / ((GLfloat)tmpT->width / (srcX + srcW));
	GLfloat tEY = (GLfloat)1.0 / ((GLfloat)tmpT->height / (srcY + srcH));

	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(1, 1, 1, (float)opacity / 100);
	glBegin(GL_QUADS);
		glTexCoord2f(tSX, tEY);	//bottom-left vertex (corner)
		glVertex2f(destX, destY + destH);
		glTexCoord2f(tEX, tEY);	//bottom-right vertex (corner)
		glVertex2f(destX + destW, destY + destH);
		glTexCoord2f(tEX, tSY);	//top-right vertex (corner)
		glVertex2f(destX + destW, destY);
		glTexCoord2f(tSX, tSY);	//top-left vertex (corner)
		glVertex2f(destX, destY);
	glEnd();
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
	glPopMatrix();
}

#endif