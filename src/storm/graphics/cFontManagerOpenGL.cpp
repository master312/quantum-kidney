#include "cFontManagerOpenGL.h"
#if BUILD_OPENGL > 0

cFontManagerOpenGL::cFontManagerOpenGL(cTextureManager *tm){
	tManager = tm;
}
cFontManagerOpenGL::~cFontManagerOpenGL(){
	UnloadAll();	
	TTF_Quit();
}

void cFontManagerOpenGL::DrawSection(uint section, int x, int y, float scale, float rotation, 
			float r, float g, float b){
	glPushMatrix();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4f(r, g, b, 1);

	if(scale <= 0)
		scale = 1.0;
	uint textureId = 0;
	if(tManager->GetSection(section) == NULL){
		StormPrintLog(STORM_LOG_ERROR, "cFontManagerSDL2", 
				"No section with ID %d", section);
		return;
	}
	sTextureSection *tmpS = tManager->GetSection(section);
	textureId = tmpS->texture;

	sTexture *tmpT = tManager->GetTexture(textureId);
	glBindTexture(GL_TEXTURE_2D, tmpT->glTexture);


	GLfloat tSX = (GLfloat)1.0 / ((GLfloat)tmpT->width / tmpS->x);
	GLfloat tSY = (GLfloat)1.0 / ((GLfloat)tmpT->height / tmpS->y);
	GLfloat tEX = (GLfloat)1.0 / ((GLfloat)tmpT->width / (tmpS->x + tmpS->width));
	GLfloat tEY = (GLfloat)1.0 / ((GLfloat)tmpT->height / (tmpS->y + tmpS->height));

	glBegin(GL_QUADS);
		glTexCoord2f(tSX, tEY);	//bottom-left vertex (corner)
		glVertex2f(x, y + (tmpS->height * scale));
		glTexCoord2f(tEX, tEY);	//bottom-right vertex (corner)
		glVertex2f(x + (tmpS->width * scale), y + (tmpS->height * scale));
		glTexCoord2f(tEX, tSY);	//top-right vertex (corner)
		glVertex2f(x + (tmpS->width * scale), y);
		glTexCoord2f(tSX, tSY);	//top-left vertex (corner)
		glVertex2f(x, y);
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
	glEnable(GL_BLEND);
}

#endif