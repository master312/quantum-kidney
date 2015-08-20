#include "cAnimationManager.h"

cAnimationManager::cAnimationManager(cTextureManager *_textureManager){
	tManager = _textureManager;
}
cAnimationManager::~cAnimationManager(){
	RemoveAll();
}
uint cAnimationManager::CreateAnimation(std::vector<uint> frames, 
			int fps, bool _useTextures){
	cAnimation tmpAnim;
	for(int i = 0; i < (int)frames.size(); i++){
		tmpAnim.AddFrame(frames[i]);
	}
	tmpAnim.SetFps(fps);
	tmpAnim.SetLastFrame(frames.size());
	tmpAnim.SetUseTextures(_useTextures);

	int toReturn = 0;
	if(animations.size() > 0){
		std::map<uint, cAnimation>::iterator i = animations.end();
		--i;
		animations[i->first + 1] = tmpAnim;
		toReturn = i->first + 1;
	}else{
		animations[1] = tmpAnim;
		toReturn = 1;
	}
	return toReturn;
}
uint cAnimationManager::LoadAnimation(std::string _filename){
	std::string fullFile = (char*)STORM_DIR_ANIMS + _filename;
	cBinaryFile tmpFile;
	tmpFile.Open(fullFile);
	if(!tmpFile.IsOpen()){
		StormPrintLog(STORM_LOG_ERROR, "cAnimation", 
			"Could not open file %s for loading", fullFile.c_str());
		return 0;
	}

	int tmpInt = 0;
	int tmpFps = 0;
	bool isUseTextures = true;

	//Beginning of file
	float tmpFloat = tmpFile.ReadFloat();
	if(tmpFloat != 16.20f){
		StormPrintLog(STORM_LOG_ERROR, "cAnimation", 
			"Invalid file format %s %f", fullFile.c_str(), tmpFloat);
		tmpFile.Close();
		return 0;
	}
	//File version
	if(tmpFile.ReadInt() != (int)STORM_ANIM_FILEVER){
		StormPrintLog(STORM_LOG_ERROR, "cAnimation", 
			"Invalid file version %s", fullFile.c_str());
		tmpFile.Close();
		return 0;
	}
	//FPS
	tmpFps = tmpFile.ReadInt();
	//Frames count
	tmpInt = tmpFile.ReadInt();
	//Is texture made from texture sections, or multiple textures
	if(tmpFile.ReadByte() == '1'){
		//Animations is made from multiple textures
		isUseTextures = true;
	}else{
		//Animations is made form texture sections
		isUseTextures = false;
	}

	//Load frames
	std::vector<uint> tmpFrames;
	//Used if animations is created from texture sections
	std::vector<sTextureSection> tmpSections;
	for(int i = 0; i < tmpInt; i++){
		if(!isUseTextures){
			//Animation is made from texture sections
			sTextureSection tmpS;
			tmpS.x = tmpFile.ReadInt();
			tmpS.y = tmpFile.ReadInt();
			tmpS.width = tmpFile.ReadInt();
			tmpS.height = tmpFile.ReadInt();
			tmpSections.push_back(tmpS);
		}else{
			//Animations is made from multiple textures
			std::string txFilename = tmpFile.ReadString();
			uint tmpFrame = tManager->LoadTexture(txFilename);
			if(tmpFrame == 0){
				StormPrintLog(STORM_LOG_ERROR, "cAnimation", 
					"Frame %s is missing. Animation can not be loaded", 
					txFilename.c_str());
				tmpFile.Close();
				return 0;
			}
			tmpFrames.push_back(tmpFrame);
		}
	}
	if(!isUseTextures){
		//Animations is made from texture sections
		//Load texture here
		std::string txFilename = tmpFile.ReadString();
		uint tmpTexture = tManager->LoadTexture(txFilename);
		if(tmpTexture == 0){
			StormPrintLog(STORM_LOG_ERROR, "cAnimation", 
				"Texture %s is missing. Animation can not be loaded", 
				txFilename.c_str());
			tmpFile.Close();
			tmpSections.clear();
			return 0;
		}
		for(int i = 0; i < (int)tmpSections.size(); i++){
			tmpSections[i].texture = tmpTexture;
			tmpFrames.push_back(tManager->CreateSection(tmpSections[i]));
		}
	}
	tmpFile.Close();
	uint animId = CreateAnimation(tmpFrames, tmpFps, isUseTextures);
	GetAnimation(animId)->SetFilename(_filename);
	GetAnimation(animId)->SetIsLoadedFromFile(true);
	StormPrintLog(STORM_LOG_INFO, "cAnimation", "Animation %s loaded", _filename.c_str());
	return animId;
}
void cAnimationManager::SaveAnimation(std::string _filename, uint animationId){
	cAnimation *tmpAni = GetAnimation(animationId);
	if(_filename == ""){
		StormPrintLog(STORM_LOG_ERROR, "cAnimation", 
			"Could not save animation. Filename name not specified");
		return;
	}
	if(tmpAni->GetTextureCount() == 0){
		StormPrintLog(STORM_LOG_ERROR, "cAnimation", 
			"Could not save animation. There are not any frames in this animation");
		return;
	}
	tmpAni->SetFilename(_filename);
	std::string fullFile = (char*)STORM_DIR_ANIMS + _filename;
	cBinaryFile tmpFile;
        std::ofstream a_file(fullFile);
        a_file.clear();
	tmpFile.Open(fullFile);
	if(!tmpFile.IsOpen()){
		StormPrintLog(STORM_LOG_ERROR, "cAnimation", 
			"Could not open file %s for saving", fullFile.c_str());
		return;
	}
	//Storm animation file always begin with 16.16 float
	tmpFile.WriteFloat(16.20f);
	//File version
	tmpFile.WriteInt((int)STORM_ANIM_FILEVER);
	//FPS
	tmpFile.WriteInt(tmpAni->GetFps());
	//Frames count
	tmpFile.WriteInt(tmpAni->GetTextureCount());
	//Use textures, or sections
	if(tmpAni->IsUseTextures()){
		tmpFile.WriteByte('1');
	}else{
		tmpFile.WriteByte('0');
	}
	//Write frames
	sTexture *tmpTexture = NULL;
	for(int i = 0; i < tmpAni->GetTextureCount(); i++){
		if(!tmpAni->IsUseTextures()){
			//Animation is made using texture sections
			sTextureSection *tmpSec = tManager->GetSection(tmpAni->GetTexture(i));
			tmpTexture = tManager->GetTexture(tmpSec->texture);
			//Write section details
			tmpFile.WriteInt(tmpSec->x);
			tmpFile.WriteInt(tmpSec->y);
			tmpFile.WriteInt(tmpSec->width);
			tmpFile.WriteInt(tmpSec->height);
			// // //
		}else{
			//Animation is made using multiple textures
			tmpTexture = tManager->GetTexture(tmpAni->GetTexture(i));
			//Filename length
			tmpFile.WriteString(tmpTexture->filename);
		}
	}
	if(!tmpAni->IsUseTextures()){
		//Animation is made using texture sections
		//Save texture filename
		tmpFile.WriteString(tmpTexture->filename.c_str());
	}
	//Integer 777 marks EOF
	tmpFile.WriteInt(777);
	tmpFile.Close();
	StormPrintLog(STORM_LOG_INFO, "cAnimation", "Animation %s saved", fullFile.c_str());
}
void cAnimationManager::UpdateAll(){
	std::map<uint, cAnimation>::iterator iter;
	for(iter = animations.begin(); iter != animations.end(); ++iter){
		iter->second.Update();
	}
}
void cAnimationManager::Remove(uint animationId){
	if(animations.count(animationId) == 0)
		return;

	if(animations[animationId].IsLoadedFromFile()){
		cAnimation *tmpAni = &animations[animationId];
		if(tmpAni->IsUseTextures()){
			//Animation is made from multiple textures
			for(int i = 0; i < tmpAni->GetTextureCount(); i++){
				tManager->UnloadTexture(tmpAni->GetTexture(i));
			}
		}else{
			//Animation is made from texture sections
			uint toRem = 0;
			toRem = tManager->GetSection(tmpAni->GetTexture(0))->texture;
			tManager->UnloadTexture(toRem);
		}
	}
	animations.erase(animationId);
}
void cAnimationManager::RemoveAll(){
	animations.clear();
}

void cAnimationManager::Pause(uint animationId){
	cAnimation *tmpA = GetAnimation(animationId);
	if(tmpA != NULL){
		tmpA->Pause();
	}
}
void cAnimationManager::PauseAll(){
	std::map<uint, cAnimation>::iterator iter;
	for(iter = animations.begin(); iter != animations.end(); ++iter){
		iter->second.Pause();
	}
}

void cAnimationManager::Resume(uint animationId){
	cAnimation *tmpA = GetAnimation(animationId);
	if(tmpA != NULL){
		tmpA->Resume();
	}
}
void cAnimationManager::ResumeAll(){
	std::map<uint, cAnimation>::iterator iter;
	for(iter = animations.begin(); iter != animations.end(); ++iter){
		iter->second.Resume();
	}
}
uint cAnimationManager::CloneAnimation(uint animationId){
	if(animations.count(animationId) == 0)
		return 0;
	cAnimation tmpA = animations[animationId];

	std::map<uint, cAnimation>::iterator i = animations.end();
	--i;
	animations[i->first + 1] = tmpA;
	return i->first + 1;
}

void cAnimationManager::SetRepetitions(uint animationId, int reps){
	cAnimation *tmpA = GetAnimation(animationId);
	if(tmpA != NULL){
		tmpA->SetRepetitions(reps);
	}
}

void cAnimationManager::Reset(uint animationId){
	cAnimation *tmpA = GetAnimation(animationId);
	if(tmpA != NULL){
		tmpA->Reset();
	}
}
void cAnimationManager::ResetAll(){
	std::map<uint, cAnimation>::iterator iter;
	for(iter = animations.begin(); iter != animations.end(); ++iter){
		iter->second.Reset();
	}
}
void cAnimationManager::JumpToFrame(uint animationId, int frame){
	cAnimation *tmpA = GetAnimation(animationId);
	if(tmpA != NULL){
		tmpA->JumpToFrame(frame);
	}
}

void cAnimationManager::DrawAnimation(uint animationId, int x, int y, 
												float scale, float rotation){
	cAnimation *tmpA = GetAnimation(animationId);
	if(tmpA == NULL)
		return;
	if(tmpA->IsUseTextures()){
		tManager->DrawTexture(tmpA->GetCurTexture(), x, y, scale, rotation);
	}else{
		tManager->DrawSection(tmpA->GetCurTexture(), x, y, scale, rotation);
	}
}
cAnimation *cAnimationManager::GetAnimation(uint animationId){
	if(animations.count(animationId) == 0){
		return NULL;
	}
	return &animations[animationId];
}