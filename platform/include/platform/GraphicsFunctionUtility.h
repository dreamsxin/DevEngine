/**
 * @file platform/GraphicsFunctionUtility.h
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

#pragma once

#include <core/Types.h>

namespace Platform
{
	class GraphicsFunctionUtility
	{
	public:

		GraphicsFunctionUtility();

		GraphicsFunctionUtility(const GraphicsFunctionUtility& graphicsFunctionUtility) = delete;
		GraphicsFunctionUtility(GraphicsFunctionUtility&& graphicsFunctionUtility) = delete;

		~GraphicsFunctionUtility();

		template<typename T>
		inline T getExtensionFunction(const Char8* name) const;

		template<typename T>
		inline T getStandardFunction(const Char8* name) const;

		GraphicsFunctionUtility& operator =(const GraphicsFunctionUtility& graphicsFunctionUtility) = delete;
		GraphicsFunctionUtility& operator =(GraphicsFunctionUtility&& graphicsFunctionUtility) = delete;

	private:

		class Implementation;

		using Function = void (*)();

		Implementation* _implementation;

		Function getExtensionFunctionInternal(const Char8* name) const;
		Function getStandardFunctionInternal(const Char8* name) const;
	};

#include "inline/GraphicsFunctionUtility.inl"
}