/**
 * @file graphics/GraphicsConfig.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

namespace Platform
{
	class GraphicsConfigChooser;
}

namespace Graphics
{
	class GraphicsConfig final
	{
	public:

		GraphicsConfig();

		GraphicsConfig(const GraphicsConfig& graphicsConfig);

		GraphicsConfig(GraphicsConfig&& graphicsConfig);

		~GraphicsConfig();

		GraphicsConfig& operator =(GraphicsConfig graphicsConfig);

	private:

		friend class GraphicsContext;
		friend class Platform::GraphicsConfigChooser;

		class Impl;

		Impl* _impl;
	};
}