// Assignment.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
using namespace tle;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( ".\\Media" );

	/**** Set up your scene here ****/
	bool isPaused = false;
	ICamera* myCamera;
	myCamera = myEngine->CreateCamera(kManual, 0, 120, -200);
	myCamera->RotateX(20);
	IModel* floor;
	IMesh* floorMesh;
	IModel* sphereA;
	IMesh* sphereAMesh;
	IModel* sphereB;
	IMesh* sphereBMesh;
	IModel* sphereC;
	IMesh* sphereCMesh;
	IModel* sphereD;
	IMesh* sphereDMesh;

	// FLOOR
	floorMesh = myEngine->LoadMesh("floor.x");
	floor = floorMesh->CreateModel(0, 0, 0);
	
	//Create spheres
	//Sphere A
	sphereAMesh = myEngine->LoadMesh("ball.x");
	sphereA = sphereAMesh->CreateModel(-50, 10, 50);
	sphereA->SetSkin("blue.png");
	//Sphere B
	sphereBMesh = myEngine->LoadMesh("ball.x");
	sphereB = sphereBMesh->CreateModel(50, 10, 50);
	//Sphere C
	sphereCMesh = myEngine->LoadMesh("ball.x");
	sphereC = sphereCMesh->CreateModel(0, 10, 100);
	sphereC->SetSkin("indigo.png");
	//Sphere D
	sphereDMesh = myEngine->LoadMesh("ball.x");
	sphereD = sphereDMesh->CreateModel(0, 10, 0);
	sphereD->SetSkin("fawn.png");

	//SKIN
	float skinCount = 0;

	//SPHERE SPEEDS
	const float kGameSpeed = 0.05f; //Constant unchangable speed (Originally 0.006f)
	float sphereSpeed = kGameSpeed * 1; //A changeable variable based off kGameSpeed
	float mouseSpeed = sphereSpeed;

	float maxSpeed = mouseSpeed * 5;
	float mousespeedFour = mouseSpeed * 4;
	float mousespeedThree = mouseSpeed * 3;
	float mousespeedTwo = mouseSpeed * 2;
	float minimumSpeed = mouseSpeed / 2;
	
	//MOUSE
	float mouseWheel = myEngine->GetMouseWheelMovement();

	//SPHERE SPEEDS
	float sphereaxSpeed = sphereSpeed; //Give each sphere its own individual speed based off sphereSpeed
	float sphereazSpeed = sphereSpeed; 
	float spherebxSpeed = sphereSpeed;
	float spherebzSpeed = sphereSpeed;
	float spherecxSpeed = sphereSpeed;
	float sphereczSpeed = sphereSpeed;
	float spheredxSpeed = sphereSpeed;
	float spheredzSpeed = sphereSpeed;

	//enum sphereDirection {UP, DOWN, LEFT, RIGHT};

	float goRotation = 0.5f;
	float stopRotation = 0.0f;
	float sphereRotation = 0.5f; //Speed the spheres should rotate

	//	Sphere Rotation variables
	float sphereaxRotation = sphereRotation; //X and Z beginning values of each rotation
	float sphereazRotation = sphereRotation;
	
	float spherebxRotation = sphereRotation;
	float spherebzRotation = sphereRotation;

	float spherecxRotation = sphereRotation;
	float sphereczRotation = sphereRotation;

	float spheredxRotation = sphereRotation;
	float spheredzRotation = sphereRotation;

	//BOUNDARIES
	float diamondTop = 99.99f; //Boundaries of the diamond shape the balls travel in
	float diamondRight = 49.99f;
	float diamondBottom = 00.01f;
	float diamondLeft = -49.99f;

	//Y Axis Upper and Lower boundaries for held key movement
	float yUpper = 29.99f; //Upeer and lower boundarys for the balls Y movements
	float yLower = 10.01f;
	float yaxisSpeed = kGameSpeed / 2;
	
	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		if (!isPaused) //Check state
		{
			// Draw the scene
			myEngine->DrawScene();
			
			//MOUSEWHEEL
			if (mouseWheel == 0.0f) //Calls the mousewheel, if moved the game SHOULD get faster or slower
			{
				sphereSpeed = kGameSpeed;
			}
			if (mouseWheel == 1.0f)
			{
				sphereSpeed = mousespeedTwo;
			}
			if (mouseWheel == 2.0f)
			{
				sphereSpeed = mousespeedThree;
			}
			if (mouseWheel == 3.0f)
			{
				sphereSpeed = mousespeedFour;
			}
			if (mouseWheel == 4.0f)
			{
				sphereSpeed = maxSpeed;
			}
			if (mouseWheel == -1.0f)
			{
				sphereSpeed = minimumSpeed;
			}

			//Set balls off moving
			sphereA->MoveX(sphereaxSpeed); //Set the balls off
			sphereA->MoveZ(sphereazSpeed);

			sphereB->MoveX(-spherebxSpeed);
			sphereB->MoveZ(-spherebzSpeed);
			
			sphereC->MoveX(spherecxSpeed);
			sphereC->MoveZ(-sphereczSpeed);
			
			sphereD->MoveX(-spheredxSpeed);
			sphereD->MoveZ(spheredzSpeed);

			/**** Update your scene each frame here ****/

			//BOUNDARIES
			//TOP
			if (sphereA->GetZ() > diamondTop || sphereB->GetZ() > diamondTop)
			{
				sphereaxSpeed = sphereaxSpeed;
				sphereazSpeed = -sphereazSpeed;
				spherebxSpeed = spherebxSpeed;
				spherebzSpeed = -spherebzSpeed;
				spherecxSpeed = -spherecxSpeed;
				sphereczSpeed = sphereczSpeed;
				spheredxSpeed = -spheredxSpeed;
				spheredzSpeed = spheredzSpeed;
			}

			//RIGHT
			if (sphereA->GetX() > diamondRight || sphereB->GetX() > diamondRight)
			{
				sphereaxSpeed = -sphereaxSpeed;
				sphereazSpeed = sphereazSpeed;
				spherebxSpeed = -spherebxSpeed;
				spherebzSpeed = spherebzSpeed;
				spherecxSpeed = spherecxSpeed;
				sphereczSpeed = -sphereczSpeed;
				spheredxSpeed = spheredxSpeed;
				spheredzSpeed = -spheredzSpeed;
			}

			

			//ROTATION
			//Set them rolling
			sphereA->RotateX(sphereaxRotation);
			sphereA->RotateZ(-sphereazRotation);
			sphereB->RotateX(-spherebxRotation);
			sphereB->RotateZ(spherebzRotation);
			sphereC->RotateX(-spherecxRotation);
			sphereC->RotateZ(-sphereczRotation);
			sphereD->RotateX(spheredxRotation);
			sphereD->RotateZ(spheredzRotation);
			
			//Sphere A Rotation Pattern
			if (sphereA->GetX() < diamondLeft)
			{
				sphereA->RotateX(sphereaxRotation);
				sphereA->RotateZ(sphereazRotation = -sphereazRotation);
			}
			if (sphereA->GetZ() > diamondTop)
			{
				sphereA->RotateX(sphereaxRotation = -sphereaxRotation);
				sphereA->RotateZ(sphereazRotation);
			}
			if (sphereA->GetX() > diamondRight)
			{
				sphereA->RotateX(sphereaxRotation);
				sphereA->RotateZ(sphereazRotation = -sphereazRotation);
			}
			if (sphereA->GetZ() < diamondBottom)
			{
				sphereA->RotateX(sphereaxRotation = -sphereaxRotation);
				sphereA->RotateZ(sphereazRotation);
			}

			//Sphere B Rotation Pattern
			if (sphereB->GetX() < diamondLeft)
			{
				sphereB->RotateX(spherebxRotation = spherebxRotation);
				sphereB->RotateZ(spherebzRotation = -spherebzRotation);
			}
			if (sphereB->GetZ() > diamondTop)
			{
				sphereB->RotateX(spherebxRotation = -spherebxRotation);
				sphereB->RotateZ(spherebzRotation);
			}
			if (sphereB->GetX() > diamondRight)
			{
				sphereB->RotateX(spherebxRotation);
				sphereB->RotateZ(spherebzRotation = -spherebzRotation);
			}
			if (sphereB->GetZ() < diamondBottom)
			{
				sphereB->RotateX(spherebxRotation = -spherebxRotation);
				sphereB->RotateZ(spherebzRotation = spherebzRotation);
			}
			
			//Sphere C Rotation Pattern
			if (sphereC->GetX() < diamondLeft)
			{
				sphereC->RotateX(spherecxRotation = spherecxRotation);
				sphereC->RotateZ(sphereczRotation = -sphereczRotation);
			}
			if (sphereC->GetZ() > diamondTop)
			{
				sphereC->RotateX(spherecxRotation = -spherecxRotation);
				sphereC->RotateZ(sphereczRotation);
			}
			if (sphereC->GetX() > diamondRight)
			{
				sphereC->RotateX(spherecxRotation);
				sphereC->RotateZ(sphereczRotation = -sphereczRotation);
			}
			if (sphereC->GetZ() < diamondBottom)
			{
				sphereC->RotateX(spherecxRotation = -spherecxRotation);
				sphereC->RotateZ(sphereczRotation = sphereczRotation);
			}

			//Sphere D Rotation Pattern
			if (sphereD->GetX() < diamondLeft)
			{
				sphereD->RotateX(spheredxRotation);
				sphereD->RotateZ(spheredzRotation = -spheredzRotation);
			}
			if (sphereD->GetZ() > diamondTop)
			{
				sphereD->RotateX(spheredxRotation = -spheredxRotation);
				sphereD->RotateZ(spheredzRotation);
			}
			if (sphereD->GetX() > diamondRight)
			{
				sphereD->RotateX(spheredxRotation);
				sphereD->RotateZ(spheredzRotation = -spheredzRotation);
			}
			if (sphereD->GetZ() < diamondBottom)
			{
				sphereD->RotateX(spheredxRotation = -spheredxRotation);
				sphereD->RotateZ(spheredzRotation);
			}

			//Y AXIS MOVEMENT
			if (myEngine->KeyHeld(Key_Up))
			{
				if (sphereA->GetY() < yUpper)
				{
					sphereA->MoveY(yaxisSpeed);
					sphereB->MoveY(yaxisSpeed);
					sphereC->MoveY(yaxisSpeed);
					sphereD->MoveY(yaxisSpeed);
				}
			}

			if (myEngine->KeyHeld(Key_Down))
			{
				if (sphereA->GetY() > yLower)
				{
					sphereA->MoveY(-yaxisSpeed);
					sphereB->MoveY(-yaxisSpeed);
					sphereC->MoveY(-yaxisSpeed);
					sphereD->MoveY(-yaxisSpeed);
				}

				//SKINS
				
				/*while (skinCount < 5)
				{
					if (myEngine->KeyHit(Key_E))
					{
						skinCount++;
						
						if (skinCount <= 1)
						{
							sphereA->SetSkin("blue.png");
							sphereB->SetSkin("ball.x");
							sphereC->SetSkin("indigo.png");
							sphereD->SetSkin("fawn.png");
						}
						if (skinCount == 2)
						{
							sphereA->SetSkin("fawn.png");
							sphereB->SetSkin("blue.png");
							sphereC->SetSkin("ball.x");
							sphereD->SetSkin("indigo.png");
						}
						if (skinCount == 3)
						{
							sphereA->SetSkin("indigo.png");
							sphereB->SetSkin("fawn.png");
							sphereC->SetSkin("blue.png");
							sphereD->SetSkin("ball.x");
						}
						if (skinCount == 4)
						{
							sphereA->SetSkin("ball.x");
							sphereB->SetSkin("indigo.png");
							sphereC->SetSkin("fawn.png");
							sphereD->SetSkin("blue.png");

							skinCount = 0;
						}
					}
				}*/

			}
		
		} //Pause state

		if (myEngine->KeyHit(Key_P))
		{
			isPaused = !isPaused;
		}

		if (myEngine->KeyHit(Key_Escape))
		{
			myEngine->Stop();
		}

	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}



//DUMP
//SPHERE A
//if (sphereA->GetX() > 0)
//{
//sphereaSpeed = -sphereaSpeed;
//}

/*Sphere A Reverse*/

//if (sphereA->GetX() < -50)
//{
//sphereaSpeed = -sphereaSpeed;
//}

//SPHERE B
//if (sphereB->GetX() > 0)
//{
	//spherebSpeed = -spherebSpeed;
//}
//if (sphereB->GetX() < 50)
//{
	//spherebSpeed = -spherebSpeed;
//}