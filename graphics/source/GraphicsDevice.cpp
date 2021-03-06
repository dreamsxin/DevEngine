/**
 * @file graphics/GraphicsDevice.cpp
 *
 * DevEngine
 * Copyright 2015-2016 Eetu 'Devenec' Oinasmaa
 *
 * DevEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DevEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DevEngine. If not, see <http://www.gnu.org/licenses/>.
 */

#include <core/Memory.h>
#include <graphics/GraphicsDevice.h>
#include <graphics/GraphicsResource.h>

using namespace Graphics;

// Some members are defined in platform/*/*GraphicsDevice.cpp

// Public

void GraphicsDevice::destroyResource(GraphicsResource* resource)
{
	_resources.remove(resource);
	DE_DELETE(resource, GraphicsResource);
}

// Private

void GraphicsDevice::destroyResources() const
{
	for(GraphicsResourceList::const_reverse_iterator i = _resources.rbegin(), end = _resources.rend();
		i != end; ++i)
	{
		DE_DELETE(*i, GraphicsResource);
	}
}
