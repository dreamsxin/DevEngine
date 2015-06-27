/**
 * @file platform/wgl/WGLTemporaryGraphicsContext.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// TODO: change to internal header
#include <platform/windows/Windows.h>
#include <gl/GL.h>

#define GL_MAJOR_VERSION 0x821B
#define GL_MINOR_VERSION 0x821C
// /TODO

#include <core/Error.h>
#include <core/Log.h>
#include <platform/wgl/WGLTemporaryGraphicsContext.h>

using namespace Core;
using namespace Platform;

// Public

TemporaryGraphicsContext::TemporaryGraphicsContext(HWND windowHandle)
	: Base(windowHandle) { }

void TemporaryGraphicsContext::deinitialise()
{
	destroyContext();
}

void TemporaryGraphicsContext::initialise()
{
	initialisePixelFormat();
	createContext();
	makeCurrent();
	validateOpenGLVersion();
}

// Private

const Char8* TemporaryGraphicsContext::COMPONENT_TAG = "[Platform::TemporaryGraphicsContext - WGL]";

void TemporaryGraphicsContext::initialisePixelFormat() const
{
	const PIXELFORMATDESCRIPTOR pixelFormatDescriptor = createPixelFormatDescriptor();
	const Int32 pixelFormatIndex = choosePixelFormat(pixelFormatDescriptor);
	validatePixelFormat(pixelFormatIndex);
	setPixelFormat(pixelFormatIndex);
}

void TemporaryGraphicsContext::createContext()
{
	_graphicsContextHandle = wglCreateContext(_deviceContextHandle);

	if(_graphicsContextHandle == nullptr)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to create the context." << Log::Flush();
		DE_ERROR_WINDOWS(0x0); // TODO: set errorCode
	}
}

Int32 TemporaryGraphicsContext::choosePixelFormat(const PIXELFORMATDESCRIPTOR& pixelFormatDescriptor) const
{
	const Int32 pixelFormatIndex = ChoosePixelFormat(_deviceContextHandle, &pixelFormatDescriptor);

	if(pixelFormatIndex == 0)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to choose a pixel format." << Log::Flush();
		DE_ERROR_WINDOWS(0x0); // TODO: set errorCode
	}

	return pixelFormatIndex;
}

void TemporaryGraphicsContext::validatePixelFormat(const Int32 pixelFormatIndex) const
{
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;

	const Int32 result = DescribePixelFormat(_deviceContextHandle, pixelFormatIndex, sizeof(PIXELFORMATDESCRIPTOR),
		&pixelFormatDescriptor);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to get the description of a pixel format." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0); // TODO: set errorCode
	}

	if((pixelFormatDescriptor.dwFlags & PFD_SUPPORT_OPENGL) == 0u)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " The device context does not support OpenGL." <<
			Log::Flush();

		DE_ERROR(0x0); // TODO: set errorCode
	}
}

// Static

// TODO: add OpenGL error checking
void TemporaryGraphicsContext::validateOpenGLVersion()
{
	// TODO: change GL_MAJOR_VERSION and GL_MINOR_VERSION to glGetString(GL_VERSION), since the former are not
	// supported until OpenGL 2.x
	Int32 majorVersion;
	glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
	Int32 minorVersion;
	glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
	Bool isVersionUnsupported = false;

	if(majorVersion < MIN_SUPPORTED_OPENGL_VERSION_MAJOR)
		isVersionUnsupported = true;
	else if(majorVersion == MIN_SUPPORTED_OPENGL_VERSION_MAJOR && minorVersion < MIN_SUPPORTED_OPENGL_VERSION_MINOR)
		isVersionUnsupported = true;

	if(isVersionUnsupported)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " The OpenGL version " << majorVersion << '.' <<
			minorVersion << " is not supported. The minimum supported version is " <<
			MIN_SUPPORTED_OPENGL_VERSION_MAJOR << '.' << MIN_SUPPORTED_OPENGL_VERSION_MINOR << '.' << Log::Flush();

		DE_ERROR_WINDOWS(0x0); // TODO: set errorCode
	}
}

PIXELFORMATDESCRIPTOR TemporaryGraphicsContext::createPixelFormatDescriptor()
{
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor = PIXELFORMATDESCRIPTOR();
	pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDescriptor.nVersion = 1u;

	return pixelFormatDescriptor;
}