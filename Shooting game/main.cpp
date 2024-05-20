// Assessment1.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
using namespace tle;

#include <sstream>
using namespace std;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder("D:\\SOFTWARE ENGINEERING - 1ST YEAR\\SEM 2\\C01301 - Games Concepts\\TL-Engine\\Media");

	/**** Set up your scene here ****/

	//platform
	IMesh* platformMesh = myEngine->LoadMesh("platform.x");
	IModel* platformModel = platformMesh->CreateModel(0, -5.f, 0);

	//sphere1
	IMesh* sphere1Mesh = myEngine->LoadMesh("spheremesh.x");
	IModel* sphere1Model = sphere1Mesh->CreateModel(-85.0f, 10.0f, -85.0f);

	//set skin for the sphere1 
	sphere1Model->SetSkin("regular.jpg");

	//sphere2
	IMesh* sphere2Mesh = myEngine->LoadMesh("spheremesh.x");
	IModel* sphere2Model = sphere2Mesh->CreateModel(85.0f, 10.0f, 85.0f);

	//set skin for the sphere2
	sphere2Model->SetSkin("regular.jpg");

	//sphere3
	IMesh* sphere3Mesh = myEngine->LoadMesh("spheremesh.x");
	IModel* sphere3Model = sphere3Mesh->CreateModel(-85.0f, 10.0f, 85.0f);

	//set skin for the sphere3
	sphere3Model->SetSkin("super.jpg");

	//sphere4
	IMesh* sphere4Mesh = myEngine->LoadMesh("spheremesh.x");
	IModel* sphere4Model = sphere4Mesh->CreateModel(85.0f, 10.0f, -85.0f);

	//set skin for the sphere4
	sphere4Model->SetSkin("super.jpg");

	//cubemesh
	IMesh* cubeMesh = myEngine->LoadMesh("Cubemesh.x");
	IModel* cubeModel = cubeMesh->CreateModel(0, 5.0f, 0.0f);


	//camera
	ICamera* myCamera;
	myCamera = myEngine->CreateCamera(kManual);
	myCamera->SetPosition(0, 200.f, -170.f);
	myCamera->RotateX(45);

	//variables
	bool upwards = true;
	bool leftwards = false;
	bool downwards = false;
	bool rightwards = false;

	bool downwards2 = true;
	bool leftwards2 = false;
	bool upwards2 = false;
	bool rightwards2 = false;

	bool rightwards3 = true;
	bool downwards3 = false;
	bool leftwards3 = false;
	bool upwards3 = false;

	bool leftwards4 = true;
	bool upwards4 = false;
	bool rightwards4 = false;
	bool downwards4 = false;

	bool isPaused = false;
	bool isReverse = false;
	float sphere1XCoordinate = sphere1Model->GetX();
	float sphere1ZCoordinate = sphere1Model->GetZ();
	float sphere2XCoordinate = sphere2Model->GetX();
	float sphere2ZCoordinate = sphere2Model->GetZ();
	float sphere3XCoordinate = sphere3Model->GetX();
	float sphere3ZCoordinate = sphere3Model->GetZ();
	float sphere4XCoordinate = sphere4Model->GetX();
	float sphere4ZCoordinate = sphere4Model->GetZ();


	//text when game paused
	IFont* myFont = myEngine->LoadFont("Comic Sans MS", 36);

	//bulletModel
	IMesh* bulletMesh = myEngine->LoadMesh("Bullet.x");
	IModel* bulletModel = bulletMesh->CreateModel(0, 5.0f, 0);


	//increase and decrease of the speed of the spheres
	// 
	//I have put 0.7 as the initial movement speed because 0.1 is too slow since I have a problem with my laptop.
	//
	float sphereMovementSpeed = 0.7f;

	//rotation - variables
	// 
	//I have put 0.5 as the initial  rotational speed because 0.1 is too slow since I have a problem with my laptop.
	//
	float sphereRotationSpeed = 0.5f;


	//variable called bulletFired
	bool bulletFired = false;

	//variable for increasing and decreasing speed of the spheres
	float speed = 0.1f;

	//variable to keep track of the score
	float score = 0;

	//enums
	enum gamestate { Playing, Paused, GameIsWon, GameIsOver };
	gamestate gamestate = Playing;


	//variable for the bullet count
	int bulletCount = 10;

	//sphere 3 hits and changes skin
	float sphere3hits = 0;

	//sphere 3 hits and changes skin
	float sphere4hits = 0;


	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/

		// esc key to stop the program
		if (myEngine->KeyHit(Key_Escape))
		{
			myEngine->Stop();
		}


		//font displayed when game paused
		if (isPaused)
		{
			myFont->Draw("Paused", 640, 320, kBlue, kCentre, kVCentre);
		}


		if (gamestate == Playing)
		{
			if (!isPaused)
			{
				//SPHERE1

				//sphere movement upwards
				if (upwards)
				{
					sphere1Model->MoveZ(sphereMovementSpeed * speed);
					sphere1Model->RotateX(sphereRotationSpeed);
					if (sphere1Model->GetZ() >= 85.0f)
					{
						sphere1Model->MoveX(0.1f);
						sphere1Model->SetZ(85.f);
						sphere1Model->RotateX(sphereRotationSpeed * 0);
						upwards = false;
						rightwards = true;
					}

				}

				//sphere movement right
				if (rightwards)
				{
					sphere1Model->MoveX(sphereMovementSpeed * speed);
					sphere1Model->RotateZ(-sphereRotationSpeed);
					if (sphere1Model->GetX() >= 85.0f)
					{
						sphere1Model->MoveZ(0.1f);
						sphere1Model->SetZ(85.f);
						sphereRotationSpeed = 0.1f;
						rightwards = false;
						downwards = true;
					}

				}

				//sphere movement downwards
				if (downwards)
				{
					sphere1Model->MoveZ(-sphereMovementSpeed * speed);
					sphere1Model->RotateX(-sphereRotationSpeed);
					if (sphere1Model->GetZ() <= -85.0f)
					{
						sphere1Model->MoveX(0.1f);
						sphere1Model->SetZ(-85.f);
						sphereRotationSpeed = 0.1f;
						downwards = false;
						leftwards = true;
					}

				}

				//sphere movement left
				if (leftwards)
				{
					sphere1Model->MoveX(-sphereMovementSpeed * speed);
					sphere1Model->RotateZ(sphereRotationSpeed);
					if (sphere1Model->GetX() <= -85.0f)
					{
						sphere1Model->MoveZ(0.1f);
						sphere1Model->SetZ(-85.f);
						sphereRotationSpeed = 0.1f;
						leftwards = false;
						upwards = true;
					}

				}



				//SPHERE2

				// move backward until it reaches (85.0f, 10.0f, -85.0f)
				// then move leftward until it reaches (-85.0f, 10.0f, -85.0f)
				// then move forward until it reaches (-85.0f, 10.0f, 85.0f)
				// then move rightward until it reaches (85.0f, 10.0f, 85.0f)

				//sphere movement downwards
				if (downwards2)
				{
					sphere2Model->MoveZ(-sphereMovementSpeed * speed);
					sphere2Model->RotateX(-sphereRotationSpeed);
					if (sphere2Model->GetZ() <= -85.0f)
					{
						sphere2Model->MoveX(0.5f);
						sphere2Model->SetZ(-85.f);
						sphere2Model->RotateX(-sphereRotationSpeed);
						downwards2 = false;
						leftwards2 = true;
					}

				}

				//sphere movement left
				if (leftwards2)
				{
					sphere2Model->MoveX(-sphereMovementSpeed * speed);
					sphere2Model->RotateZ(sphereRotationSpeed);
					if (sphere2Model->GetX() <= -85.0f)
					{
						sphere2Model->MoveZ(0.5f);
						sphere2Model->SetX(-85.f);
						sphereRotationSpeed = 0.1f;
						leftwards2 = false;
						upwards2 = true;
					}

				}

				//sphere movement upwards
				if (upwards2)
				{
					sphere2Model->MoveZ(sphereMovementSpeed * speed);
					sphere2Model->RotateX(sphereRotationSpeed);
					if (sphere2Model->GetZ() >= 85.0f)
					{
						sphere2Model->MoveX(0.1f);
						sphere2Model->SetZ(85.f);
						sphere2Model->RotateX(sphereRotationSpeed * 0);
						upwards2 = false;
						rightwards2 = true;
					}

				}

				//sphere movement rightwards
				if (rightwards2)
				{
					sphere2Model->MoveX(sphereMovementSpeed * speed);
					sphere2Model->RotateZ(-sphereRotationSpeed);
					if (sphere2Model->GetX() >= 85.0f)
					{
						sphere2Model->MoveZ(0.1f);
						sphere2Model->SetZ(85.f);
						sphereRotationSpeed = 0.1f;
						rightwards2 = false;
						downwards2 = true;
					}

				}


				//SPHERE3

				// move right until it reaches (85.0f, 10.0f, 85.0f)
				// then move down until it reaches (85.0f, 10.0f, -85.0f)
				// then move left until it reaches (-85.0f, 10.0f, -85.0f)
				// then move up until it reaches (-85.0f, 10.0f, 85.0f)

				//sphere movement rightwards
				if (rightwards3)
				{
					sphere3Model->MoveX(sphereMovementSpeed * speed);
					sphere3Model->RotateZ(-sphereRotationSpeed);
					if (sphere3Model->GetX() >= 85.0f)
					{
						sphere3Model->MoveZ(0.1f);
						sphere3Model->SetZ(85.f);
						sphereRotationSpeed = 0.1f;
						rightwards3 = false;
						downwards3 = true;
					}

				}

				//sphere movement downwards
				if (downwards3)
				{
					sphere3Model->MoveZ(-sphereMovementSpeed * speed);
					sphere3Model->RotateX(-sphereRotationSpeed);
					if (sphere3Model->GetZ() <= -85.0f)
					{
						sphere3Model->MoveX(0.1f);
						sphere3Model->SetZ(-85.f);
						sphereRotationSpeed = 0.1f;
						downwards3 = false;
						leftwards3 = true;
					}

				}

				//sphere movement left
				if (leftwards3)
				{
					sphere3Model->MoveX(-sphereMovementSpeed * speed);
					sphere3Model->RotateZ(sphereRotationSpeed);
					if (sphere3Model->GetX() <= -85.0f)
					{
						sphere3Model->MoveZ(0.1f);
						sphere3Model->SetZ(-85.f);
						sphereRotationSpeed = 0.1f;
						leftwards3 = false;
						upwards3 = true;
					}

				}

				//sphere movement up
				if (upwards3)
				{
					sphere3Model->MoveZ(sphereMovementSpeed * speed);
					sphere3Model->RotateX(sphereRotationSpeed);
					if (sphere3Model->GetZ() >= 85.0f)
					{
						sphere3Model->MoveX(0.1f);
						sphere3Model->SetZ(85.f);
						sphere3Model->RotateX(sphereRotationSpeed * 0);
						upwards3 = false;
						rightwards3 = true;
					}

				}

				//SPHERE4

				// move left until it reaches (-85.0f, 10.0f, -85.0f)
				// then move up until it reaches (-85.0f, 10.0f, 85.0f)
				// then move right until it reaches (85.0f, 10.0f, 85.0f)
				// then move down until it reaches (85.0f, 10.0f, -85.0f)

				//sphere movement left
				if (leftwards4)
				{
					sphere4Model->MoveX(-sphereMovementSpeed * speed);
					sphere4Model->RotateZ(sphereRotationSpeed);
					if (sphere4Model->GetX() <= -85.0f)
					{
						sphere4Model->MoveZ(0.1f);
						sphere4Model->SetZ(-85.f);
						sphereRotationSpeed = 0.1f;
						leftwards4 = false;
						upwards4 = true;
					}

				}

				//sphere movement up
				if (upwards4)
				{
					sphere4Model->MoveZ(sphereMovementSpeed * speed);
					sphere4Model->RotateX(sphereRotationSpeed);
					if (sphere4Model->GetZ() >= 85.0f)
					{
						sphere4Model->MoveX(0.1f);
						sphere4Model->SetZ(85.f);
						sphere4Model->RotateX(sphereRotationSpeed * 0);
						upwards4 = false;
						rightwards4 = true;
					}

				}

				//sphere movement right
				if (rightwards4)
				{
					sphere4Model->MoveX(sphereMovementSpeed * speed);
					sphere4Model->RotateZ(-sphereRotationSpeed);
					if (sphere4Model->GetX() >= 85.0f)
					{
						sphere4Model->MoveZ(0.1f);
						sphere4Model->SetZ(85.f);
						sphereRotationSpeed = 0.1f;
						rightwards4 = false;
						downwards4 = true;
					}

				}

				//sphere movement downwards
				if (downwards4)
				{
					sphere4Model->MoveZ(-sphereMovementSpeed * speed);
					sphere4Model->RotateX(-sphereRotationSpeed);
					if (sphere4Model->GetZ() <= -85.0f)
					{
						sphere4Model->MoveX(0.1f);
						sphere4Model->SetZ(-85.f);
						sphereRotationSpeed = 0.1f;
						downwards4 = false;
						leftwards4 = true;
					}

				}

			}
		}



		// if iPaused is true, when P key is hit, game paused.
		if (myEngine->KeyHit(Key_P))
		{
			if (gamestate == Playing)
			{
				isPaused = !isPaused;
			}
			else if (isPaused = !isPaused)
			{
				gamestate == Playing;
			}

		}


		//increase and decrease of speeds of two sphere
		if (gamestate == Playing)
		{
			if (myEngine->KeyHit(Key_D))
			{
				sphereMovementSpeed += speed;

				sphereRotationSpeed += speed;

			}
			if (myEngine->KeyHit(Key_A))
			{
				sphereMovementSpeed -= speed;

				sphereRotationSpeed -= speed;

			}
		}


		//vector calculations
		float cubeXVector = cubeModel->GetX() - bulletModel->GetX();
		float cubeZVector = cubeModel->GetZ() - bulletModel->GetZ();
		float sphere1XVector = sphere1Model->GetX() - bulletModel->GetX();
		float sphere1ZVector = sphere1Model->GetZ() - bulletModel->GetZ();
		float sphere2XVector = sphere2Model->GetX() - bulletModel->GetX();
		float sphere2ZVector = sphere2Model->GetZ() - bulletModel->GetZ();
		float sphere3XVector = sphere3Model->GetX() - bulletModel->GetX();
		float sphere3ZVector = sphere3Model->GetZ() - bulletModel->GetZ();
		float sphere4XVector = sphere4Model->GetX() - bulletModel->GetX();
		float sphere4ZVector = sphere4Model->GetZ() - bulletModel->GetZ();


		//float distance = sqrt(pow(sphere1YVector, 2) + pow(sphere2YVector, 2));
		float distance = sqrt(cubeXVector * cubeXVector) + (cubeZVector * cubeZVector);
		float sphere1distance = sqrt(sphere1XVector * sphere1XVector) + (sphere1ZVector * sphere1ZVector);
		float sphere2distance = sqrt(sphere2XVector * sphere2XVector) + (sphere2ZVector * sphere2ZVector);
		float sphere3distance = sqrt(sphere3XVector * sphere3XVector) + (sphere3ZVector * sphere3ZVector);
		float sphere4distance = sqrt(sphere4XVector * sphere4XVector) + (sphere4ZVector * sphere4ZVector);



		//key up arrow sets bulletFire to true
		if (gamestate == Playing)
		{
			if (myEngine->KeyHit(Key_Up))
			{
				bulletFired = true;

				if (bulletCount == 0)
				{
					bulletFired = false;
				}
				if (bulletCount > 0)
				{
					bulletCount--;
				}
			}

			if (bulletFired)
			{
				bulletModel->MoveLocalZ(sphereMovementSpeed * 5);
				if (bulletModel->GetZ() >= 200.0f)
				{
					bulletModel->SetPosition(0, 5.0f, 0);
					bulletFired = false;


				}
				if (sphere1distance < 10.0f)
				{
					sphere1Model->SetY(500.0f);
					bulletModel->SetPosition(0, 5.0f, 0);
					bulletFired = false;
					//increasing score when bullet is hit
					score += 10;
					//increasing speed when bullet is hit 
					sphereMovementSpeed += 0.25;
					//increasing rotational speed when bullet is hit 
					sphereRotationSpeed += 0.25;


				}
				if (sphere2distance < 10.0f)
				{
					sphere2Model->SetY(500.0f);
					bulletModel->SetPosition(0, 5.0f, 0);
					bulletFired = false;
					//increasing score when bullet is hit
					score += 10;
					//increasing speed when bullet is hit 
					sphereMovementSpeed += 0.25;
					//increasing rotational speed when bullet is hit 
					sphereRotationSpeed += 0.25;


				}
				if (sphere3distance < 10.0f)
				{
					sphere3hits++;

					if (sphere3hits == 1)
					{
						//setting the skin of sphere 3 when hit once
						sphere3Model->SetSkin("regular.jpg");
						bulletModel->SetPosition(0, 5.0f, 0);
						bulletFired = false;
						//increasing score when bullet is hit
						score += 10;
						//increasing speed when bullet is hit 
						sphereMovementSpeed += 0.25;
						//increasing rotational speed when bullet is hit 
						sphereRotationSpeed += 0.25;

					}

					if (sphere3hits == 2)
					{
						sphere3Model->SetY(-500.0f);
						bulletModel->SetPosition(0, 5.0f, 0);
						bulletFired = false;
						//increasing score when bullet is hit
						score += 10;
						//increasing speed when bullet is hit 
						sphereMovementSpeed += 0.25;
						//increasing rotational speed when bullet is hit 
						sphereRotationSpeed += 0.25;

					}

				}
				if (sphere4distance < 10.0f)
				{
					sphere4hits++;

					if (sphere4hits == 1)
					{
						//setting the skin of sphere 3 when hit once
						sphere4Model->SetSkin("regular.jpg");
						bulletModel->SetPosition(0, 5.0f, 0);
						bulletFired = false;
						//increasing score when bullet is hit
						score += 10;
						//increasing speed when bullet is hit 
						sphereMovementSpeed += 0.25;
						//increasing rotational speed when bullet is hit 
						sphereRotationSpeed += 0.25;

					}

					if (sphere4hits == 2)
					{
						sphere4Model->SetY(-500.0f);
						bulletModel->SetPosition(0, 5.0f, 0);
						bulletFired = false;
						//increasing score when bullet is hit
						score += 10;
						//increasing speed when bullet is hit 
						sphereMovementSpeed += 0.25;
						//increasing rotational speed when bullet is hit 
						sphereRotationSpeed += 0.25;

					}

				}
			}
		}



		//displaying score
		stringstream displayScore;
		displayScore << "Score: " << score << endl;
		myFont->Draw(displayScore.str(), 0, 0, kBlack);

		//displaying speed of spheres
		stringstream displaySpeed;
		displaySpeed << "Speed: " << sphereMovementSpeed << endl;
		myFont->Draw(displaySpeed.str(), 0, 50, kBlack);

		//displaying the bulletcount
		stringstream displayBulletCount;
		displayBulletCount << "Bullets Left: " << bulletCount << endl;
		myFont->Draw(displayBulletCount.str(), 0, 100, kBlack);

		//display bullets over, gameover
		if (bulletCount <= 0)
		{
			myFont->Draw("Bullets Over", 0, 200, kBlue);

		}

		// space key to reset the game
		if (gamestate == GameIsOver || gamestate == GameIsWon)
		{
			if (myEngine->KeyHit(Key_Space))
			{
				bulletFired = false;
				score = 0;
				bulletCount = 10;
				sphereMovementSpeed = 0.5;
				sphere3hits = 0;
				sphere4hits = 0;
				gamestate = Playing;

				//skin turned to super again
				sphere3Model->SetSkin("super.jpg");
				sphere4Model->SetSkin("super.jpg");

				//movement reset
				bulletModel->SetPosition(0, 5.0f, 0);
				sphere1Model->SetPosition(-85.0f, 10.0f, -85.0f);
				sphere2Model->SetPosition(85.0f, 10.0f, 85.0f);
				sphere3Model->SetPosition(-85.0f, 10.0f, 85.0f);
				sphere4Model->SetPosition(85.0f, 10.0f, -85.0f);
			}
		}


		//display you win when score reach 60
		if (score == 60)
		{
			gamestate = GameIsWon;
			myFont->Draw("You Win, Congrats!", 640, 350, kYellow, kCentre, kVCentre);

		}
		if ((score < 60) && (bulletCount == 0))
		{
			gamestate = GameIsOver;
			myFont->Draw("Game is Over!", 640, 350, kGreen, kCentre, kVCentre);
			myFont->Draw("Press the Spcae Bar to Restart", 640, 450, kRed, kCentre, kVCentre);
			gamestate == isPaused;
		}

	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
