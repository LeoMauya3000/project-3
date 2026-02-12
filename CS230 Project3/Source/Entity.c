//------------------------------------------------------------------------------
//
// File Name:	Entity.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Entity.h"
#include "Physics.h"
#include "Sprite.h"
#include "Stream.h"
#include "Transform.h"
#include "Animation.h"


//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Entity
{
	// The name of the entity.
	// A buffer is used to allow each entity to have a unique name.
	// The buffer is hardcoded to an arbitrary length that will be sufficient
	//	 for all CS230 assignments.  You may, instead, use dynamically-allocated
	//	 arrays for this purpose but the additional complexity is unnecessary
	//	 and it is your responsibility to ensure that the memory is successfully
	//	 allocated and deallocated in all possible situations.
	// [NOTE: When setting the name, use strcpy_s() to reduce the risk of
	//	 buffer overruns. Additionally, do NOT hardcode the number "32" when
	//	 calling this function!  Instead, use the _countof() macro to get the
	//	 size of the "name" array.]
	char name[32];

	// Pointer to an attached physics component.
	Physics* physics;

	// Pointer to an attached sprite component.
	Sprite* sprite;

	// Pointer to an attached transform component.
	Transform* transform;

	Animation* animation;

} Entity;



//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

Entity* EntityCreate(void)
{
	
	Entity* entity = calloc(1, sizeof(Entity));
	if (entity)
	{
		
	   return entity;
	}
	else
	{
		return NULL;
	}
}
void EntityFree(Entity** entity)
{
	free(*entity);
	*entity = NULL;
}
void EntityRead(Entity* entity, Stream stream)
{
	const char* entityName;
	const char* token = StreamReadToken(stream);

	if (entity && stream)
	{
		entityName = StreamReadToken(stream);
		while(token)
		{
			if (!strncmp(token, "Transform", _countof("Transform")))
			{
				entity->transform = TransformCreate();
				TransformRead(entity->transform, stream);
			}
			else if (!strncmp(token, "Physics", _countof("Physics")))
			{
				entity->physics = PhysicsCreate();
				PhysicsRead(entity->physics, stream);
			}
			else if (!strncmp(token, "Sprite", _countof("Sprite")))
			{
				entity->sprite = SpriteCreate();
				SpriteRead(entity->sprite, stream);
			}
			else if (!strncmp(token, "Animation", _countof("Animation")))
			{

				entity->animation = AnimationCreate();
				AnimationRead(entity->animation, stream);
				EntityAddAnimation(entity, entity->animation);
			}
			else if (strcmp(token, "") == 0)
			{
				return;
			}
		
			 token = StreamReadToken(stream);
		}
			
	}
}
void EntityAddPhysics(Entity* entity, Physics* physics)
{
	if (entity && physics)
	{
	 entity->physics = physics;

	}
}
void EntityAddSprite(Entity* entity, Sprite* sprite)
{
	if (entity && sprite)
	{
	 entity->sprite = sprite;

	}
}
void EntityAddTransform(Entity* entity, Transform* transform)
{
	if (entity && transform)
	{
	  entity->transform = transform;

	}
}
void EntitySetName(Entity* entity, const char* name)
{
	if (entity && name)
	{
		strcpy_s(entity->name, _countof(entity->name), name);
	}
}
const char* EntityGetName(const Entity* entity)
{
    
	return entity->name;
}
Physics* EntityGetPhysics(const Entity* entity)
{
	
	return entity->physics;
}
Sprite* EntityGetSprite(const Entity* entity)
{

	return entity->sprite;
}
Transform* EntityGetTransform(const Entity* entity)
{
	
	return entity->transform;
}
void EntityUpdate(Entity* entity, float dt)
{

	if (entity->physics && entity->transform && entity->sprite)
	{
		PhysicsUpdate(entity->physics, entity->transform, dt);
	}
	if (entity->animation)
	{
		AnimationUpdate(entity->animation, dt);
	}

	
}
void EntityRender(Entity* entity)
{
	if (entity)
	{
		SpriteRender(entity->sprite, entity->transform);
	}
}


void EntityAddAnimation(Entity* entity, Animation* animation)
{
	if (entity && animation)
	{
		AnimationSetParent(animation, entity);
		entity->animation = animation;
	}
}




Animation* EntityGetAnimation(const Entity* entity)
	{
	if (entity)
	{
		Animation* entityAnimation = entity->animation;
		return entityAnimation;
	}
	else
	{
		return NULL;
	}
}

