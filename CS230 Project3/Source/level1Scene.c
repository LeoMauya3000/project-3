//------------------------------------------------------------------------------
//
// File Name:	StubScene.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 1
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "level2Scene.h"
#include "level1Scene.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "StubScene.h"
#include "stream.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Transform.h"
#include "DGL.h"
#include "Mesh.h"
#include "Entity.h"
#include "Physics.h"
#include "EntityFactory.h"
#include "SandboxScene.h"
#include "DemoScene.h"


//------------------------------------------------------------------------------
// Private Constants:
//
//------------------------------------------------------------------------------
 enum Monkeystates
{
	MonkeyInvalid = -1,
	MonkeyIdle,
	MonkeyWalk,
	MonkeyJump

};
	static const float groundHeight = -150.0f;
	static const float moveVelocity = 500.0f;
	static const float jumpVelocity = 1000.0f;
	static const Vector2D gravityNormal = { 0.0f, -1500.0f };
	static const Vector2D gravityNone = { 0.0f, 0.0f };

	static const Vector2D resetTranslation = { 0,-150.0f };
	static const Vector2D resetacelleration = { 0,0 };
	static const Vector2D resetvec = { 0,0 };
//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Level1Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;
	int numLives;


	// Add any scene-specific variables second.

} Level1Scene;
 static char livesBuffer[16];
 enum MonkeyStates monkeyState = MonkeyInvalid;
 static Mesh* createdMesh;
 static SpriteSource* createdSpriteSource;
 static Entity* createdEntity;
 static Sprite* createdSpirte;
 static const float wallDistance = 462.0f;
 static const float CheckSquareDistance = (75.0f * 75.0f);

 static Entity* monkeyEntity;
 static Mesh* monkeyMesh;
 static Sprite* monkeySprite;
 static SpriteSource* monkeySpriteSourceIdle;
 static SpriteSource* monkeySpriteSourceWalk;
 static SpriteSource* monkeySpriteSourceJump;

 static Entity* livesTextEntity;
 static Mesh* textMesh;
 static Sprite* textSprite;
 static SpriteSource* textSpriteSource;
 


//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void Level1SceneMovementController(Entity* entity);
static void Level1SceneLoad(void);
static void Level1SceneInit(void);
static void Level1SceneUpdate(float dt);
static void Level1SceneExit(void);
static void Level1SceneUnload(void);
static void Level1SceneRender(void);





//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static Level1Scene instance =
{
	// Initialize the base structure:
	{ "Level1", Level1SceneLoad, Level1SceneInit, Level1SceneUpdate, Level1SceneRender, Level1SceneExit, Level1SceneUnload},0 
	
	// Initialize any scene-specific variables:
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Level1 Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* Level1SceneGetInstance(void)
{
	return &(instance.base);
	
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void Level1SceneLoad(void)
{
	Stream streamFile = StreamOpen("Data/Level1_Lives.txt");
	if (&streamFile)
	{
		instance.numLives = StreamReadInt(streamFile);
		StreamClose(&streamFile);
	}

	createdMesh = MeshCreate();
	MeshBuildQuad(createdMesh, 0.5f, 0.5f, 1.0f, 1.0f, "Mesh1x1");
	createdSpriteSource = SpriteSourceCreate();
	SpriteSourceLoadTexture(createdSpriteSource, 1, 1, "PlanetTexture.png");
	
	
	monkeyMesh = MeshCreate();
	MeshBuildQuad(monkeyMesh, 0.5, 0.5, 1.0f / 3, 1.0f / 3, "Mesh3x3");
	monkeySpriteSourceIdle = SpriteSourceCreate();
	SpriteSourceLoadTexture(monkeySpriteSourceIdle, 1, 1, "MonkeyIdle.png");
	monkeySpriteSourceWalk = SpriteSourceCreate();
	SpriteSourceLoadTexture(monkeySpriteSourceWalk, 1, 1, "MonkeyJump.png");
	monkeySpriteSourceJump = SpriteSourceCreate();
	SpriteSourceLoadTexture(monkeySpriteSourceJump, 3, 3, "MonkeyWalk.png");

	

	MeshBuildQuad(textMesh, 0.5f, 0.5f, 1.0f, 1.0f, "Mesh16x8");
	textMesh = MeshCreate();
	textSpriteSource = SpriteSourceCreate();
	SpriteSourceLoadTexture(textSpriteSource, 16, 8, "Roboto_Mono_black.png");


	
}

// Initialize the entities and variables used by the scene.
static void Level1SceneInit(void)
{


	createdEntity = EntityFactoryBuild("./Data/PlanetJump.txt");
	if (createdEntity)
	{	
		SpriteSetMesh(EntityGetSprite(createdEntity), createdMesh);
		SpriteSetSpriteSource(EntityGetSprite(createdEntity), createdSpriteSource);
		SpriteSetFrame(EntityGetSprite(createdEntity), 0);
		DGL_Graphics_SetBackgroundColor(& (DGL_Color){ 1,1,1,1 });
		DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
	}
}


// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level1SceneUpdate(float dt)
{

	Level1SceneMovementController(createdEntity);
	EntityUpdate(createdEntity, dt);

	if (DGL_Input_KeyTriggered('1'))
	{

		TransformSetTranslation(EntityGetTransform(createdEntity), &resetTranslation);
		PhysicsSetVelocity(EntityGetPhysics(createdEntity), &resetacelleration);
		PhysicsSetAcceleration(EntityGetPhysics(createdEntity), &resetacelleration);
		SceneSystemSetNext(Level1SceneGetInstance());
		
	}
	if (DGL_Input_KeyTriggered('2'))
	{
		SceneSystemSetNext(level2SceneGetInstance());
	}

	if (DGL_Input_KeyTriggered('9'))
	{
		SceneSystemSetNext(SandBoxSceneGetInstance());
	}

	if (DGL_Input_KeyTriggered('0'))
	{
		SceneSystemSetNext(DemoSceneGetInstance());
	}

}

// Render any objects associated with the scene.
void Level1SceneRender(void)
{
	EntityRender(createdEntity);

}

// Free any objects associated with the scene.
static void Level1SceneExit(void)
{
	
	EntityFree(&createdEntity);
	

}

// Unload any resources used by the scene.
static void Level1SceneUnload(void)
{

	SpriteSourceFree(&createdSpriteSource);
	MeshFree(&createdMesh);

}

static void Level1SceneMovementController(Entity *entity)
{
	 const Physics *physics = (EntityGetPhysics(entity));
	 const Transform * transform = (EntityGetTransform(entity));

	if (EntityGetPhysics(entity) && EntityGetTransform(entity))
	{
		Vector2D velocity = *(PhysicsGetVelocity(physics));
		Vector2D translation = *(TransformGetTranslation(transform));
	
		if (DGL_Input_KeyDown(VK_LEFT))
		{
			velocity.x = -moveVelocity;
		}
		else if (DGL_Input_KeyDown(VK_RIGHT))
		{
			velocity.x = moveVelocity;
		}
		else
		{
			velocity.x = 0;
		}
		if (DGL_Input_KeyTriggered(VK_UP))
		{
			velocity.y = jumpVelocity;
			PhysicsSetAcceleration(EntityGetPhysics(entity), &gravityNormal);
			
		}
		if (translation.y < groundHeight)
		{
			translation.y = groundHeight;
			TransformSetTranslation(EntityGetTransform(entity), &translation);
			velocity.y = 0;
			PhysicsSetAcceleration(EntityGetPhysics(entity), &gravityNone);
			instance.numLives--;
			if (instance.numLives <= 0)
			{
				SceneSystemSetNext(level2SceneGetInstance());
			}
		}
	    PhysicsSetVelocity(EntityGetPhysics(entity),&velocity);
	}

}





