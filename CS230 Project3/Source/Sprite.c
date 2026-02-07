//------------------------------------------------------------------------------
//
// File Name:	Sprite.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Sprite.h"
#include "DGL.h"
#include "Stream.h"
#include "SpriteSource.h"
#include "Mesh.h"
#include "Transform.h"
#include "Trace.h"
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Sprite
{
	// The frame currently being displayed (for sprite sheets).
	unsigned int frameIndex;

	// The alpha transparency to use when drawing the sprite.
	float alpha;

	// The sprite source used when drawing (NULL = simple colored mesh).
	const SpriteSource* spriteSource;

	// The mesh used to draw the sprite.
	const Mesh* mesh;

} Sprite;


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

Sprite* SpriteCreate(void)
{
	Sprite* sprite = calloc(1, sizeof(Sprite));
	if (sprite)
	{
		sprite->alpha = 1.0f;
		return sprite;
	}
	else
	{
		return NULL;
	}
}

void SpriteFree(Sprite** sprite)
{
	if (sprite)
	{
		free(*sprite);
		*sprite = NULL;
	}
}
void SpriteRead(Sprite* sprite, Stream stream)
{
	sprite->frameIndex = StreamReadInt(stream);
	sprite->alpha = StreamReadFloat(stream);
}
void SpriteRender(const Sprite* sprite, Transform* transform)
{
	const Vector2D* translate = TransformGetTranslation(transform);
	const Vector2D* scale = TransformGetScale(transform);
	float rotation = TransformGetRotation(transform);


	if (sprite->spriteSource != NULL)
	{
		DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE, DGL_VSM_DEFAULT);
		SpriteSourceSetTexture(sprite->spriteSource);
		SpriteSourceSetTextureOffset(sprite->spriteSource, sprite->frameIndex);	

	}
	else
	{
		DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);
	}

	DGL_Graphics_SetCB_TransformData(translate, scale, rotation);
	DGL_Graphics_SetCB_Alpha(sprite->alpha);
	DGL_Graphics_SetCB_TintColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 0.0f });
	MeshRender(sprite->mesh);
}
float SpriteGetAlpha(const Sprite* sprite)
{

	if (sprite)
	{
		return sprite->alpha;
	}
	else
	{
		return 0.0f;
	}
	
}
void SpriteSetAlpha(Sprite* sprite, float alpha)
{
	if (alpha > 1)
	{
		alpha = 1;
	}
	if (alpha < 0)
	{
		alpha = 0;
	}
	sprite->alpha = alpha;
}
void SpriteSetFrame(Sprite* sprite, unsigned int frameIndex)
{
	if (frameIndex <= sprite->frameIndex - 1)
	{
		sprite->frameIndex = frameIndex;
	}

	TraceMessage("SpriteSetFrame: frame index = %d", frameIndex);
}
void SpriteSetMesh(Sprite* sprite, const Mesh* mesh)
{
	sprite->mesh = mesh;

}
void SpriteSetSpriteSource(Sprite* sprite, const SpriteSource* spriteSource)
{
	sprite->spriteSource = spriteSource;
}

