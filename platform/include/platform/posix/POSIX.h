/**
 * @file platform/posix/POSIX.h
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

#include <errno.h>
#include <core/ConfigInternal.h>
#include <core/Types.h>
#include <core/UtilityMacros.h>

#if defined(DE_INTERNAL_BUILD_DEVELOPMENT)
	#define DE_ERROR_POSIX(errorCode) \
		Platform::invokePOSIXError(errorCode, DE_FILE, DE_LINE, DE_FUNCTION)

	#define DE_ERROR_POSIX_CODE(errorCode, posixErrorCode) \
		errno = posixErrorCode; \
		Platform::invokePOSIXError(errorCode, DE_FILE, DE_LINE, DE_FUNCTION)
#else
	#define DE_ERROR_POSIX(errorCode) \
		Platform::invokePOSIXError(errorCode)

	#define DE_ERROR_POSIX_CODE(errorCode, posixErrorCode) \
		errno = posixErrorCode; \
		Platform::invokePOSIXError(errorCode)
#endif

namespace Platform
{
	extern const Int32 POSIX_RESULT_OK;

	void invokePOSIXError(const Uint32 errorCode);

	void invokePOSIXError(const Uint32 errorCode, const Char8* file, const Uint32 line,
		const Char8* function);
}
