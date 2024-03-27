#pragma once

#include "Game.h"

class CMyGame : public CGame
{
public:
	CMyGame();
	~CMyGame();

    // ----  Declare your game variables and objects here -------------

	// Variables
	
    // Models and Model Lists
	CModel ogro;		// animated ogro md2 model 
	CModel coin,rock, flowers, mushroom, collidingTree;
	CModel wallSegment;

	CModel* newGameObject;  // current selected game object
	
	CModelList modelList;   // list containing all models
	
	CSprite menuScreen;
	
	// game world floor
	CFloor floor;
	
	// Font
	CFont font;

   // -----   Add you member functions here ------
   
   void PlayerControl(); 
   
   void CameraControl(CGraphics* g);
   
   void LoadData();
   void SaveData();

   void AddObject();
   void RemoveObject(float x, float z);
	
	
   // ---------------------Event Handling --------------------------

	// Game Loop Funtions
	virtual void OnUpdate();
	virtual void OnDraw(CGraphics* g);
	virtual void OnRender3D(CGraphics* g);

	// Game Life Cycle
	virtual void OnInitialize();
	virtual void OnDisplayMenu();
	virtual void OnStartLevel(int level);
	virtual void OnStartGame();
	virtual void OnGameOver();
	virtual void OnTerminate();

	// Keyboard Event Handlers
	virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	// Mouse Events Handlers
	virtual void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	virtual void OnLButtonDown(Uint16 x,Uint16 y);
	virtual void OnLButtonUp(Uint16 x,Uint16 y);
	virtual void OnRButtonDown(Uint16 x,Uint16 y);
	virtual void OnRButtonUp(Uint16 x,Uint16 y);
	virtual void OnMButtonDown(Uint16 x,Uint16 y);
	virtual void OnMButtonUp(Uint16 x,Uint16 y);
};
