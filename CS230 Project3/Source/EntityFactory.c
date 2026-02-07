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
#include "EntityFactory.h"
#include "Stream.h"
#include "Entity.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

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

Entity* EntityFactoryBuild(const char* filename)
{
	Entity* entity = NULL;
	Stream streamFile = NULL;
	const char* token = NULL;

	if (filename)
	{
		streamFile = StreamOpen(filename);
		
		if (streamFile)
		{
			token = StreamReadToken(streamFile);

			if (!strncmp(token, "Entity", _countof("Entity")))
			{
				entity = EntityCreate();
				EntityRead(entity, streamFile);
				StreamClose(&streamFile);
			}
			

		}
	}
	else
	{
		return NULL;
	}
	return entity;
	
}

