#pragma once
#include <exception>

/// <summary>
/// Exception for when an invalid file is provided
/// </summary>
class invalidfileexception : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Invalid file provided";
	}
} invalidfile;