#pragma once
#include "_BaseIncludeLibraries.h"
namespace EngineName
{
	namespace Exceptions
	{
		/*
		* Basic exception class
		* Serves as base for custom exceptions
		* Can at construction be assigned a string which is printed on catch
		* Stores a std::string
		* String is accesed via operator std::string
		*/
		class BasicException
		{
		protected:
			std::string mpstr_errorExplanation;
		public:
			BasicException(const char *explanation = "unknown error"): mpstr_errorExplanation(explanation) {}

			virtual operator std::string () const { return mpstr_errorExplanation; }
		};
	}
}

