// Assessment2.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
using namespace tle;
#include <sstream>
using namespace std;

// Struct to store 3D vectors
struct Vector3 {
	float x;
	float y;
	float z;
};

// Function to add two vectors
Vector3 AddVectors(const Vector3& v1, const Vector3& v2) {
	return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

// Function to subtract two vectors
Vector3 SubtractVectors(const Vector3& v1, const Vector3& v2) {
	return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

// Function to calculate the dot product of two vectors
float DotProduct(const Vector3& v1, const Vector3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Function to calculate the magnitude (length) of a vector
float Magnitude(const Vector3& v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Function to normalize a vector (make it a unit vector)
Vector3 Normalize(const Vector3& v) {
	float magnitude = Magnitude(v);
	return { v.x / magnitude, v.y / magnitude, v.z / magnitude };
}

// Function to scale a vector by a scalar value
Vector3 ScaleVector(const Vector3& v, float scalar) {
	return { v.x * scalar, v.y * scalar, v.z * scalar };
}

const float kPlayerCarMoveSpeed = 100.0f;
const float kPlayerCarRotateSpeed = 5.0f;
const float PlayerCarRadius = 0.986185f;

const float kPlayerCarInitXPos = 0;
const float kPlayerCarInitYPos = 0;
const float kPlayerCarInitZPos = 0;

enum CameraMode { Default, FirstPerson, ThirdPerson };


enum gamestate { Playing, Paused, GameIsWon };

struct CollisionData {
	bool isHit;
	bool isSideCollision;
};




void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder("D:\\SOFTWARE ENGINEERING - 1ST YEAR\\SEM 2\\C01301 - Games Concepts\\TL-Engine\\Media");

	/**** Set up your scene here ****/

	struct GameObject {
		IMesh* mesh;
		IModel* model;
		Vector3 position;
	};

	//ground
	IMesh* groundMesh = myEngine->LoadMesh("ground.x");
	IModel* groundModel = groundMesh->CreateModel(0, 0, 0);

	//sky
	IMesh* skybox01Mesh = myEngine->LoadMesh("skybox01.x");
	IModel* skybox01Model = skybox01Mesh->CreateModel(0, -960.0f, 0);

	//player's car
	IMesh* jeepMesh = myEngine->LoadMesh("4x4jeep.x");
	IModel* jeepModel = jeepMesh->CreateModel(0, 0, 0);

	//enemy car1
	IMesh* audi1Mesh = myEngine->LoadMesh("audi.x");
	IModel* audi1Model = audi1Mesh->CreateModel(-20, 0, 20);

	//enemy car2
	IMesh* audi2Mesh = myEngine->LoadMesh("audi.x");
	IModel* audi2Model = audi2Mesh->CreateModel(20, 0, 20);

	//enemy car3
	IMesh* audi3Mesh = myEngine->LoadMesh("audi.x");
	IModel* audi3Model = audi3Mesh->CreateModel(-20, 0, 0);

	//enemy car4
	IMesh* audi4Mesh = myEngine->LoadMesh("audi.x");
	IModel* audi4Model = audi4Mesh->CreateModel(20, 0, 0);

	//ball1
	IMesh* ball1Mesh = myEngine->LoadMesh("ball.x");
	IModel* ball1Model = ball1Mesh->CreateModel(0, 2.5, 0);

	//setskin for ball 1
	ball1Model->SetSkin("white.jpg");

	//ball2
	IMesh* ball2Mesh = myEngine->LoadMesh("ball.x");
	IModel* ball2Model = ball2Mesh->CreateModel(0, 2.5, 0);

	//setskin for ball2
	ball2Model->SetSkin("white.jpg");

	//ball3
	IMesh* ball3Mesh = myEngine->LoadMesh("ball.x");
	IModel* ball3Model = ball3Mesh->CreateModel(0, 2.5, 0);

	//setskin for ball 3
	ball3Model->SetSkin("white.jpg");

	//ball4
	IMesh* ball4Mesh = myEngine->LoadMesh("ball.x");
	IModel* ball4Model = ball4Mesh->CreateModel(0, 2.5, 0);

	//setskin for ball 4
	ball4Model->SetSkin("white.jpg");

	//backdrop
	ISprite* backdrop = myEngine->CreateSprite("backdrop.jpg", 300, 659);


	//variables
	bool isPaused = false;

	float TheScore = 0.0f;

	float prevPlayerCarXPos = kPlayerCarInitXPos;
	float prevPlayerCarYPos = kPlayerCarInitYPos;
	float prevPlayerCarZPos = kPlayerCarInitZPos;

	bool enemyCar1initialCollision = false;
	bool enemyCar2initialCollision = false;
	bool enemyCar3initialCollision = false;
	bool enemyCar4initialCollision = false;


	//text when messages are shown
	IFont* myFont = myEngine->LoadFont("Comic Sans MS", 36);

	//camera
	ICamera* myCamera;
	myCamera = myEngine->CreateCamera(kManual);
	myCamera->SetPosition(0, 15.0f, -60.0f);
	myCamera->RotateLocalX(15);

	CameraMode cameraMode = Default;

	myEngine->Timer();

	gamestate gamestate = Playing;

	// Create an array to store the enemy car models
	const int numEnemies = 4;
	IModel* staticEnemies[numEnemies] = { audi1Model, audi2Model, audi3Model, audi4Model };


	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		float frameTime = myEngine->Timer();

		/**** Update your scene each frame here ****/

		if (myEngine->KeyHit(Key_Escape))
		{
			myEngine->Stop();
		}

		if (isPaused)
		{
			myFont->Draw("Paused", 640, 320, kGreen, kCentre, kVCentre);
		}




		//movement of the player car

		//'W' moves the player’s car forward
		//'S' moves the player’s car backwards
		//'D' rotates the player’s car clockwise
		//'A' rotates the player’s car anti - clockwise

		if (gamestate == Playing)
		{
			if (!isPaused)
			{
				if (myEngine->KeyHeld(Key_W))
				{
					prevPlayerCarXPos = jeepModel->GetX(); // Store the previous X position before moving
					prevPlayerCarZPos = jeepModel->GetZ(); // Store the previous Z position before moving
					jeepModel->MoveLocalZ(kPlayerCarMoveSpeed * frameTime);
				}

				if (myEngine->KeyHeld(Key_S))
				{
					prevPlayerCarXPos = jeepModel->GetX(); // Store the previous X position before moving
					prevPlayerCarZPos = jeepModel->GetZ(); // Store the previous Z position before moving
					jeepModel->MoveLocalZ(-kPlayerCarMoveSpeed * frameTime);
				}

				if (myEngine->KeyHeld(Key_D))
				{
					jeepModel->RotateLocalY(kPlayerCarMoveSpeed * frameTime);
				}

				if (myEngine->KeyHeld(Key_A))
				{
					jeepModel->RotateLocalY(-kPlayerCarMoveSpeed * frameTime);
				}


				// Example usage of vector functions
				Vector3 playerCarPos = { jeepModel->GetX(), jeepModel->GetY(), jeepModel->GetZ() };
				Vector3 enemyCarPos = { audi1Model->GetX(), audi1Model->GetY(), audi1Model->GetZ() };
				Vector3 collisionDir = Normalize(SubtractVectors(enemyCarPos, playerCarPos));
				float dotProduct = DotProduct(collisionDir, SubtractVectors(enemyCarPos, playerCarPos));
				float magnitude = Magnitude(collisionDir);
				Vector3 scaledVector = ScaleVector(collisionDir, 10.0f);

				// Loop through each enemy car and check collision
				for (int i = 0; i < numEnemies; ++i)
				{
					IModel* enemyModel = staticEnemies[i];
					
					// Check collision with enemy car_1 and player car
					float PlayerCar1X = jeepModel->GetX();
					float PlayerCar1Y = jeepModel->GetY();
					float PlayerCar1Z = jeepModel->GetZ();

					//float enemyCarMinX = enemyCarModel->GetX() - (enemyCarWidth / 2);
					//float enemyCarMaxX = enemyCarModel->GetX() + (enemyCarWidth / 2);
					//float enemyCarMinY = enemyCarModel->GetY() - (enemyCarHeight / 2);
					//float enemyCarMaxY = enemyCarModel->GetY() + (enemyCarHeight / 2);
					//float enemyCarMinZ = enemyCarModel->GetZ() - (enemyCarDepth / 2);
					//float enemyCarMaxZ = enemyCarModel->GetZ() + (enemyCarDepth / 2);

					float enemyCar1MinX = audi1Model->GetX() + (-0.946118);
					float enemyCar1MaxX = audi1Model->GetX() + (0.946118);
					float enemyCar1MinY = audi1Model->GetY() + (0.0065695);
					float enemyCar1MaxY = audi1Model->GetY() + (1.50131);
					float enemyCar1MinZ = audi1Model->GetZ() + (-1.97237);
					float enemyCar1MaxZ = audi1Model->GetZ() + (1.97237);


					if (PlayerCar1X > enemyCar1MinX - PlayerCarRadius && PlayerCar1X < enemyCar1MaxX + PlayerCarRadius &&
						PlayerCar1Y > enemyCar1MinY - PlayerCarRadius && PlayerCar1Y < enemyCar1MaxY + PlayerCarRadius &&
						PlayerCar1Z > enemyCar1MinZ - PlayerCarRadius && PlayerCar1Z < enemyCar1MaxZ + PlayerCarRadius)
					{
						if (enemyCar1initialCollision == false)
						{

							// Calculate collision direction vector between player's car and enemy1 car
							float collisionDirX = audi1Model->GetX() - PlayerCar1X;
							float collisionDirY = 0;  // Assuming collision only happens on the same height level
							float collisionDirZ = audi1Model->GetZ() - PlayerCar1X;


							// Calculate collision direction vector between player's car and enemy1 car
							Vector3 playerCarPos = { jeepModel->GetX(), jeepModel->GetY(), jeepModel->GetZ() };
							Vector3 enemyCar1Pos = { audi1Model->GetX(), audi1Model->GetY(), audi1Model->GetZ() };
							Vector3 collisionDir = Normalize(SubtractVectors(enemyCar1Pos, playerCarPos));

							// Calculate the dot product between collision direction and enemy1's relative position
							float dotProduct = DotProduct(collisionDir, SubtractVectors(enemyCar1Pos, playerCarPos));

							if ((dotProduct > 3) || (dotProduct < 0))
							{
								TheScore += 10;  // Front/rear collision
								ball1Model->SetSkin("red.png");
							}

							else if (dotProduct > 0)
							{
								TheScore += 15;  // Side collision
								ball1Model->SetSkin("red.png");
							}
						}
						jeepModel->SetPosition(prevPlayerCarXPos, prevPlayerCarYPos, prevPlayerCarZPos);

						enemyCar1initialCollision = true;
					}

				}

				

				// Loop through each enemy car and check collision
				for (int i = 0; i < numEnemies; ++i)
				{
					IModel* enemyModel = staticEnemies[i];
					
					// Check collision with enemy car_2 and player car
					float PlayerCar2X = jeepModel->GetX();
					float PlayerCar2Y = jeepModel->GetY();
					float PlayerCar2Z = jeepModel->GetZ();

					float enemyCar2MinX = audi2Model->GetX() + (-0.946118);
					float enemyCar2MaxX = audi2Model->GetX() + (0.946118);
					float enemyCar2MinY = audi2Model->GetY() + (0.0065695);
					float enemyCar2MaxY = audi2Model->GetY() + (1.50131);
					float enemyCar2MinZ = audi2Model->GetZ() + (-1.97237);
					float enemyCar2MaxZ = audi2Model->GetZ() + (1.97237);

					if (PlayerCar2X > enemyCar2MinX - PlayerCarRadius && PlayerCar2X < enemyCar2MaxX + PlayerCarRadius &&
						PlayerCar2Y > enemyCar2MinY - PlayerCarRadius && PlayerCar2Y < enemyCar2MaxY + PlayerCarRadius &&
						PlayerCar2Z > enemyCar2MinZ - PlayerCarRadius && PlayerCar2Z < enemyCar2MaxZ + PlayerCarRadius)
					{
						if (enemyCar2initialCollision == false)
						{

							// Calculate collision direction vector between player's car and enemy1 car
							float collisionDirX = audi2Model->GetX() - PlayerCar2X;
							float collisionDirY = 0;  // Assuming collision only happens on the same height level
							float collisionDirZ = audi2Model->GetZ() - PlayerCar2X;


							// Calculate collision direction vector between player's car and enemy1 car
							Vector3 playerCarPos = { jeepModel->GetX(), jeepModel->GetY(), jeepModel->GetZ() };
							Vector3 enemyCar2Pos = { audi2Model->GetX(), audi2Model->GetY(), audi2Model->GetZ() };
							Vector3 collisionDir = Normalize(SubtractVectors(enemyCar2Pos, playerCarPos));

							// Calculate the dot product between collision direction and enemy1's relative position
							float dotProduct = DotProduct(collisionDir, SubtractVectors(enemyCar2Pos, playerCarPos));

							if ((dotProduct > 3) || (dotProduct < 0))
							{
								TheScore += 10;  // Front/rear collision
								ball2Model->SetSkin("red.png");
							}

							else if (dotProduct > 0)
							{
								TheScore += 15;  // Side collision
								ball2Model->SetSkin("red.png");
							}
						}
						jeepModel->SetPosition(prevPlayerCarXPos, prevPlayerCarYPos, prevPlayerCarZPos);

						enemyCar2initialCollision = true;
					}


				}

				
				// Loop through each enemy car and check collision
				for (int i = 0; i < numEnemies; ++i)
				{
					IModel* enemyModel = staticEnemies[i];
					
					// Check collision with enemy car_3 and player car
					float PlayerCar3X = jeepModel->GetX();
					float PlayerCar3Y = jeepModel->GetY();
					float PlayerCar3Z = jeepModel->GetZ();

					float enemyCar3MinX = audi3Model->GetX() + (-0.946118);
					float enemyCar3MaxX = audi3Model->GetX() + (0.946118);
					float enemyCar3MinY = audi3Model->GetY() + (0.0065695);
					float enemyCar3MaxY = audi3Model->GetY() + (1.50131);
					float enemyCar3MinZ = audi3Model->GetZ() + (-1.97237);
					float enemyCar3MaxZ = audi3Model->GetZ() + (1.97237);

					if (PlayerCar3X > enemyCar3MinX - PlayerCarRadius && PlayerCar3X < enemyCar3MaxX + PlayerCarRadius &&
						PlayerCar3Y > enemyCar3MinY - PlayerCarRadius && PlayerCar3Y < enemyCar3MaxY + PlayerCarRadius &&
						PlayerCar3Z > enemyCar3MinZ - PlayerCarRadius && PlayerCar3Z < enemyCar3MaxZ + PlayerCarRadius)
					{
						if (enemyCar3initialCollision == false)
						{

							// Calculate collision direction vector between player's car and enemy1 car
							float collisionDirX = audi3Model->GetX() - PlayerCar3X;
							float collisionDirY = 0;  // Assuming collision only happens on the same height level
							float collisionDirZ = audi3Model->GetZ() - PlayerCar3X;

							// Normalize the collision direction vector
							float collisionDirMagnitude = sqrt(collisionDirX * collisionDirX + collisionDirY * collisionDirY + collisionDirZ * collisionDirZ);
							collisionDirX /= collisionDirMagnitude;
							collisionDirY /= collisionDirMagnitude;
							collisionDirZ /= collisionDirMagnitude;

							// Calculate collision direction vector between player's car and enemy1 car
							Vector3 playerCarPos = { jeepModel->GetX(), jeepModel->GetY(), jeepModel->GetZ() };
							Vector3 enemyCar3Pos = { audi3Model->GetX(), audi3Model->GetY(), audi3Model->GetZ() };
							Vector3 collisionDir = Normalize(SubtractVectors(enemyCar3Pos, playerCarPos));

							// Calculate the dot product between collision direction and enemy1's relative position
							float dotProduct = DotProduct(collisionDir, SubtractVectors(enemyCar3Pos, playerCarPos));

							if ((dotProduct > 3) || (dotProduct < 0))
							{
								TheScore += 10;  // Front/rear collision
								ball3Model->SetSkin("red.png");
							}

							else if (dotProduct > 0)
							{
								TheScore += 15;  // Side collision
								ball3Model->SetSkin("red.png");
							}
						}
						jeepModel->SetPosition(prevPlayerCarXPos, prevPlayerCarYPos, prevPlayerCarZPos);

						enemyCar3initialCollision = true;
					}

				}

				
				// Loop through each enemy car and check collision
				for (int i = 0; i < numEnemies; ++i)
				{
					IModel* enemyModel = staticEnemies[i];
					
					// Check collision with enemy car_4 and player car
					float PlayerCar4X = jeepModel->GetX();
					float PlayerCar4Y = jeepModel->GetY();
					float PlayerCar4Z = jeepModel->GetZ();

					float enemyCar4MinX = audi4Model->GetX() + (-0.946118);
					float enemyCar4MaxX = audi4Model->GetX() + (0.946118);
					float enemyCar4MinY = audi4Model->GetY() + (0.0065695);
					float enemyCar4MaxY = audi4Model->GetY() + (1.50131);
					float enemyCar4MinZ = audi4Model->GetZ() + (-1.97237);
					float enemyCar4MaxZ = audi4Model->GetZ() + (1.97237);

					// Check collision with enemy car_4 and player car
					if (PlayerCar4X > enemyCar4MinX - PlayerCarRadius && PlayerCar4X < enemyCar4MaxX + PlayerCarRadius &&
						PlayerCar4Y > enemyCar4MinY - PlayerCarRadius && PlayerCar4Y < enemyCar4MaxY + PlayerCarRadius &&
						PlayerCar4Z > enemyCar4MinZ - PlayerCarRadius && PlayerCar4Z < enemyCar4MaxZ + PlayerCarRadius)
					{
						if (enemyCar4initialCollision == false)
						{

							// Calculate collision direction vector between player's car and enemy1 car
							float collisionDirX = audi4Model->GetX() - PlayerCar4X;
							float collisionDirY = 0;  // Assuming collision only happens on the same height level
							float collisionDirZ = audi4Model->GetZ() - PlayerCar4X;

							// Normalize the collision direction vector
							float collisionDirMagnitude = sqrt(collisionDirX * collisionDirX + collisionDirY * collisionDirY + collisionDirZ * collisionDirZ);
							collisionDirX /= collisionDirMagnitude;
							collisionDirY /= collisionDirMagnitude;
							collisionDirZ /= collisionDirMagnitude;

							// Calculate collision direction vector between player's car and enemy1 car
							Vector3 playerCarPos = { jeepModel->GetX(), jeepModel->GetY(), jeepModel->GetZ() };
							Vector3 enemyCar4Pos = { audi4Model->GetX(), audi4Model->GetY(), audi4Model->GetZ() };
							Vector3 collisionDir = Normalize(SubtractVectors(enemyCar4Pos, playerCarPos));

							// Calculate the dot product between collision direction and enemy1's relative position
							float dotProduct = DotProduct(collisionDir, SubtractVectors(enemyCar4Pos, playerCarPos));

							if ((dotProduct > 3) || (dotProduct < 0))
							{
								TheScore += 10;  // Front/rear collision
								ball4Model->SetSkin("red.png");
							}

							else if (dotProduct > 0)
							{
								TheScore += 15;  // Side collision
								ball4Model->SetSkin("red.png");
							}
						}
						jeepModel->SetPosition(prevPlayerCarXPos, prevPlayerCarYPos, prevPlayerCarZPos);

						enemyCar4initialCollision = true;
					}


				}

				
			}


			// Parenting to attach each ball to the enemy cars
			ball1Model->AttachToParent(audi1Model);
			ball2Model->AttachToParent(audi2Model);
			ball3Model->AttachToParent(audi3Model);
			ball4Model->AttachToParent(audi4Model);

			// Update camera mode based on key input
			if (myEngine->KeyHit(Key_1))
			{
				cameraMode = Default;
				if (cameraMode == Default)
				{
					myCamera->DetachFromParent();
					myCamera->SetLocalPosition(0, 15.0f, -60.0f);
				}
			}
			else if (myEngine->KeyHit(Key_2))
			{
				cameraMode = ThirdPerson;
				if (cameraMode == ThirdPerson)
				{
					myCamera->AttachToParent(jeepModel);
					myCamera->SetLocalPosition(0, 6.0f, -10.0f);
				}
			}
			else if (myEngine->KeyHit(Key_3))
			{
				cameraMode = FirstPerson;
				if (cameraMode == FirstPerson)
				{
					myCamera->AttachToParent(jeepModel);
					myCamera->SetLocalPosition(0, 3.0f, 0);
				}
			}
		}





		//Display the score 
		stringstream scoreText;
		scoreText << "Score: " << TheScore;

		myFont->Draw(scoreText.str(), 585, 659, kBlack);
		scoreText.str("");


		if (enemyCar1initialCollision == true && enemyCar2initialCollision == true && enemyCar3initialCollision == true && enemyCar4initialCollision == true)
		{
			gamestate = GameIsWon;
		}

		if (gamestate == GameIsWon)
		{
			// Display "You Win!" message
			myFont->Draw("You Win!", 640, 320, kYellow, kCentre, kVCentre);
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

	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
