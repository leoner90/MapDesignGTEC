#include "MyGame.h"
#include <fstream>

using namespace std;

CMyGame::CMyGame(void) { newGameObject = NULL;  }

CMyGame::~CMyGame(void) {}

// --------  game initialisation --------
void CMyGame::OnInitialize()
{

	// Loading graphics and sound assets
	cout << "Loading assets" << endl;
	
	font.LoadDefault(); 
	
	// enable lighting
	Light.Enable();

	// ogro model
	ogro.LoadModel("tree/tree1.obj");
	ogro.SetScale( 3.5f);
	ogro.SetToFloor(0);
	
	//collidingTree
	collidingTree.LoadModel("tree/tree1.obj");
	collidingTree.SetScale(3.5f);
	collidingTree.SetToFloor(0);

	// rock model
	rock.LoadModel("rock2/rock3.obj"); 
	rock.SetY(0);
	rock.SetScale(1.f);

	// flowers model
	flowers.LoadModel("flowers/flowers2.obj");
	flowers.SetY(0);
	flowers.SetScale(22.f);

	// mushroom
	mushroom.LoadModel("mushroom/MushroomShiitake.obj");
	mushroom.SetScale(10.0f);
	mushroom.SetToFloor(0);

	// coin model
	//coin.LoadModel("flowers/flowers.obj");
	//coin.SetY(0);
	//coin.SetScale(22.0f);


	// coin model
	coin.LoadModel("grass/grass.obj");
	coin.SetY(50);
	coin.SetScale(1.0f);
	 
	// wall model
	wallSegment.LoadModel("wall/wall.obj");
	wallSegment.SetScale(10.0f);
	wallSegment.SetToFloor(0);



	
	// floor texture
	floor.LoadTexture("floor.jpg");
	floor.SetTiling(true);
	floor.SetSize(15000,15000);

	// menu screen
	menuScreen.LoadImage("menuScreen.bmp");
	menuScreen.SetPosition(Width/2.0f,Height/2.0f);

}
	

void CMyGame::LoadData()
{	
	// --- clear model lists ----
    modelList.clear();
	floor.SetSize(15000, 15000);
	// set size of the game world (2000x2000)
	//floor.SetSize(1000,1000);
	
	// move gameworld so that it starts at 0,0 and extends in positive xz-direction
	//floor.SetPosition(floor.GetWidth()/2,floor.GetDepth()/2);
	
    // declaring new file
    fstream myfile;
    // opening file for reading
    myfile.open("level3.txt", ios_base::in);

	int type, x, y, z, rot;
    // reading while the end of file has not been reached
    bool neof; // not end of file
    do
    {
      myfile >> type >> x >> y >> z >> rot;

	  neof = myfile.good();
      //cout << type << " " << x << " " << y << " " << z << " " << rot << endl;
      if (neof) // if not end of file
      {
		   if (type==1)   // wall segments
		  {
			   CModel* pWall = wallSegment.Clone(); // clone wall segment
			   pWall->SetPosition((float)x, (float)y, (float)z);
			   pWall->SetRotation(float(rot));
			   pWall->SetToFloor(0);
			   pWall->SetStatus(1); // indicate the type of object
			   modelList.push_back( pWall);
		  }
		  
		  if (type==2)  // coins
		  {
			  CModel* pCoin=coin.Clone();
              pCoin->SetPosition((float)x,(float)y,(float)z); pCoin->SetRotation((float)rot);
			  pCoin->SetStatus(2); // indicate the type of object
			  modelList.push_back( pCoin);  
		  }
		  
		  if (type==3) // ogros
		  {
			 CModel* pEnemy=ogro.Clone();
             pEnemy->SetPosition((float)x,(float)y,(float)z);
			 pEnemy->SetStatus(3); // indicate the type of object
			 modelList.push_back( pEnemy);   
		  }

		  if (type == 4) // rock
		  {
			  CModel* newRock = rock.Clone();
			  newRock->SetPosition((float)x, (float)y, (float)z);
			  newRock->SetStatus(4); // indicate the type of object
			  modelList.push_back(newRock);
		  }

		  if (type == 5) // flowers
		  {
			  CModel* newflowers = flowers.Clone();
			  newflowers->SetPosition((float)x, (float)y, (float)z);
			  newflowers->SetStatus(5); // indicate the type of object
			  modelList.push_back(newflowers);
		  }

		  if (type == 6) // mushroom
		  {
			  CModel* newMushroom = mushroom.Clone();
			  newMushroom->SetPosition((float)x, (float)y, (float)z);
			  newMushroom->SetStatus(5); // indicate the type of object
			  modelList.push_back(newMushroom);
		  }

		  if (type == 7) // collidingTree
		  {
			  CModel* newCollTree = collidingTree.Clone();
			  newCollTree->SetPosition((float)x, (float)y, (float)z);
			  newCollTree->SetStatus(5); // indicate the type of object
			  modelList.push_back(newCollTree);
		  }
	  } 
    }
    while(neof);
    myfile.close();
	cout << "Level data loaded" << endl;
	   
}

void CMyGame::SaveData()
{
	// declaring new file for output
	ofstream myfile;
	string filename("level3.txt");
	// opening file for writing
	myfile.open(filename);

	for (CModel* pModel : modelList)
	{
		// write out model type,position,rotation
		myfile << pModel->GetStatus() << " " << (int)pModel->GetX() << " " << (int)pModel->GetY() << " " << (int)pModel->GetZ() << " " << (int)pModel->GetRotation() << endl;
	}
	myfile.close();
	cout << "Level data saved" << endl;
}


void CMyGame::AddObject()
{
	
	// cloning curent game object becomes the new game object
	CModel* newGameObject1 = newGameObject->Clone();
	newGameObject1->SetPositionV(newGameObject->GetPositionV());
	newGameObject1->SetRotationV(newGameObject->GetRotationV());
	newGameObject1->SetStatus(newGameObject->GetStatus());
	// adding cloned game object 
	modelList.push_back(newGameObject1);
}

void CMyGame::RemoveObject(float x, float y)
{
	CVector pos;
	// remove model from list at mouse position
	for (CModel* pModel : modelList)
	{
		// transform 3D position to 2D screen position
		pos = WorldToScreenCoordinate(pModel->GetPositionV());
		// remove model if mouse clicked with 20 pixels of screen position
		if (pos.Distance(CVector(x, y, 0)) <= 20)
		{
			pModel->Delete();
		}
		

	}
	modelList.remove_if(deleted);
}
   
   
void CMyGame::OnStartLevel(int level)
{
}

// Game Logic in the OnUpdate function called every frame

void CMyGame::OnUpdate() 
{
	if (IsMenuMode() || IsGameOver()) return;
	
	long t =  GetTime();
	
	// --- updating models ----
	
	modelList.Update(t);

}

void CMyGame::PlayerControl()
{
}





//-----------------  Draw 2D overlay ----------------------
void CMyGame::OnDraw(CGraphics* g)
{
	if (IsMenuMode() || IsPaused())
	{
	  menuScreen.Draw(g);
	  return;
	}
	
	// draw GAME OVER if game over
   	if (IsGameOver())
   	{
		font.SetSize(48); font.SetColor( CColor::Red()); font.DrawText( 250,300, "GAME OVER");	
	}

	
}

// ----------------   Draw 3D world -------------------------
void CMyGame::OnRender3D(CGraphics* g)
{

	CameraControl(g);


	// ------- Draw your 3D Models here ----------

	floor.Draw(g);

	modelList.Draw(g);

	if (newGameObject != NULL) newGameObject->Draw(g);

	//ShowBoundingBoxes();
	ShowCoordinateSystem();
	
}

void CMyGame::CameraControl(CGraphics* g)
{
	static float xpos = floor.GetWidth() / 2;
	static float zpos = floor.GetDepth() / 2;

	float scrollspeed = 30;

	// ---- Keyboard control of camera view ------

	// scaling
	if (IsKeyDown(SDLK_z)) world.scale += 0.1f;
	if (IsKeyDown(SDLK_x)) world.scale -= 0.1f;

	// motion and rotation
	if (IsKeyDown(SDLK_UP) && IsKeyDown(SDLK_LCTRL)) world.rotation.x -= 2.0f;
	else if (IsKeyDown(SDLK_DOWN) && IsKeyDown(SDLK_LCTRL)) world.rotation.x += 2.0f;
	else if (IsKeyDown(SDLK_RIGHT) && IsKeyDown(SDLK_LCTRL)) world.rotation.y+=5;
	else if (IsKeyDown(SDLK_LEFT) && IsKeyDown(SDLK_LCTRL)) world.rotation.y-=5;
	else if (IsKeyDown(SDLK_DOWN))
	{
		xpos = xpos - scrollspeed * (float)sin(DEG2RAD(world.rotation.y));
		zpos = zpos + scrollspeed * (float)cos(DEG2RAD(world.rotation.y));
	}
	else if (IsKeyDown(SDLK_UP))
	{
		xpos = xpos + scrollspeed * (float)sin(DEG2RAD(world.rotation.y));
		zpos = zpos -scrollspeed * (float)cos(DEG2RAD(world.rotation.y));
	}
	else if (IsKeyDown(SDLK_RIGHT))
	{
		xpos = xpos + scrollspeed * (float)cos(DEG2RAD(world.rotation.y));
		zpos = zpos + scrollspeed * (float)sin(DEG2RAD(world.rotation.y));
	}
	else if (IsKeyDown(SDLK_LEFT))
	{
		xpos = xpos - scrollspeed * (float)cos(DEG2RAD(world.rotation.y));
		zpos = zpos - scrollspeed * (float)sin(DEG2RAD(world.rotation.y));
	}



	// ------ Global Transformation Functions -----
	glScalef(world.scale, world.scale, world.scale);  // scale the game world
	glTranslatef(world.position.x, world.position.y, world.position.z);  // translate game world
	glRotatef(world.rotation.x, 1, 0, 0);	// tilt: rotate game world around x-axis
	glRotatef(world.rotation.y, 0, 1, 0);	// rotate game world around y-axis
    // translate game world 
	glTranslatef(-xpos, 0, -zpos);

	 
	
	UpdateView();
	Light.Apply();
}


// called at the start of a new game - display menu here
void CMyGame::OnDisplayMenu()
{
	world.rotation.x = 70;     // tilt: rotation of game world around x-axis
	world.rotation.y = -90;    // rotation: rotation of game world around y-axis
	world.scale = 1.0f;	       // scaling the game world

}

// called when Game Mode entered
void CMyGame::OnStartGame()
{
    
}


// called when Game is Over
void CMyGame::OnGameOver()
{
	
}

// one time termination code
void CMyGame::OnTerminate()
{
	
}

// -------    Keyboard Event Handling ------------

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
 
	if (sym == SDLK_SPACE)
	{
		if (IsPaused()) ResumeGame();
		else PauseGame();

	}


 

	if (sym == SDLK_ESCAPE) // clear game object
	{
		if (newGameObject != NULL) {
			delete newGameObject; 
			newGameObject = NULL;
		}
	}
	if (sym == SDLK_F5) // add wall segment
	{
		if (newGameObject != NULL) delete newGameObject;
		newGameObject = wallSegment.Clone();
		newGameObject->SetStatus(1); // wall segment
		newGameObject->SetPosition(500, 100, 500);
	}
	if (sym == SDLK_F6) // add coin
	{
		if (newGameObject != NULL) delete newGameObject;
		newGameObject = coin.Clone();
		newGameObject->SetStatus(2); // coin
	}

	if (sym == SDLK_F7) // add ogro
	{
		if (newGameObject != NULL) delete newGameObject;
		newGameObject = ogro.Clone();
		newGameObject->SetStatus(3); // ogro
	}

	if (sym == SDLK_F1) // rock
	{
		if (newGameObject != NULL) delete newGameObject;
		newGameObject = rock.Clone();
		newGameObject->SetStatus(4); // rock
	}


	if (sym == SDLK_F2) // flowers
	{
		if (newGameObject != NULL) delete newGameObject;
		newGameObject = flowers.Clone();
		newGameObject->SetStatus(5); // rock
	}

	if (sym == SDLK_F3) // mushroom
	{
		if (newGameObject != NULL) delete newGameObject;
		newGameObject = mushroom.Clone();
		newGameObject->SetStatus(6); // rock
	}



	if (sym == SDLK_F4) // collidingTree
	{
		if (newGameObject != NULL) delete newGameObject;
		newGameObject = collidingTree.Clone();
		newGameObject->SetStatus(7); // rock
	}


	// changing the game object orientation 
	if (newGameObject != NULL)
	{
		if (sym == SDLK_a) newGameObject->Rotate(45); 
		if (sym == SDLK_d) newGameObject->Rotate(-45);
		if (sym == SDLK_f) newGameObject->SetToFloor(0);
	}

	// reading and writing level data 
	if (sym == SDLK_i) LoadData();  // input
	if (sym == SDLK_o) SaveData();  // output
  
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	
}

// -----  Mouse Events Handlers -------------

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
	if (IsGameMode())
	{
		// project screen to floor coordinates
		CVector pos = ScreenToFloorCoordinate(x, y);
	
		if (newGameObject != NULL)
		{
			newGameObject->SetPosition(pos.x, pos.z);
		}
	}
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{    
	
	if (IsMenuMode()) { LoadData();  StartGame(); }
	
	// add current object
	if (newGameObject != NULL)
	{
		AddObject();
	}
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
	// delete object
	if (newGameObject == NULL)
	{
		RemoveObject(x, y);
	}
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
