//------------------------------------------------------------------------------
//
// File Name:	Stub.c
// Author(s):	Leo Mauya  0069791
// Project:		Project 0
// Course:		CS230S26
//
// Copyright © 2026 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Animation.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Animation
{
	// Pointer to the parent Entity associated with the Animation component.
	Entity* parent;

	// The current frame being displayed.
	unsigned int frameIndex;

	// The maximum number of frames in the sequence.
	unsigned int frameCount;

	// The time remaining for the current frame.
	float frameDelay;

	// The amount of time to display each successive frame.
	float frameDuration;

	// True if the animation is running; false if the animation has stopped.
	bool isRunning;

	// True if the animation loops back to the beginning.
	bool isLooping;

	// True if the end of the animation sequence has been reached, false otherwise.
	// (Hint: This should be true for only one game loop.)
	bool isDone;

} Animation;

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

Animation* AnimationCreate(void)
{
	Animation* animationComponent = calloc(1, sizeof(Animation));
	return animationComponent;
}

void AnimationFree(Animation** animation)
{
	animation;
}
void AnimationRead(Animation* animation, Stream stream)
{
	stream;
	animation;
}
void AnimationSetParent(Animation* animation, Entity* parent)
{
	animation;
	parent;
}
void AnimationPlay(Animation* animation, int frameCount, float frameDuration, bool isLooping)
{
	animation;
	frameCount;
	frameDuration;
	isLooping;
}

void AnimationUpdate(Animation* animation, float dt)
{
	animation;
	dt;
}
bool AnimationIsDone(const Animation* animation)
{
	animation;
	return true;
}




//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

