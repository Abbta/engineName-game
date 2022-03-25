#include "BasicVariableException.h"
#include "Constants.h"
namespace EngineName
{
	namespace Exceptions
	{
		///Note: All specialisations follow <int> syntax and logic, the difference is typecasts and insertion techniques

		/* BasicVariableException::std::string operator
		*	returns explanation where '$' is replaced by the variable
		*/
		BasicVariableException<int>::operator std::string () const
		{
			std::string explanation = mpstr_errorExplanation;
			//latest is to check that there is no '\' before the '$'
			char latest = '0';
			for(int i(0); i < explanation.size(); i++)
			{
				//iterate through the explanation and if there is a '$'
					//without a '\' before it, replace it with the var
				if (explanation[i] == '$' && latest != '\\')
				{
					explanation[i] = *mpptr_variable;
				}
				latest = explanation[i];
			}

			return explanation;
		}

		//same as <int> but explicitly casts to int
		BasicVariableException<size_t>::operator std::string () const
		{
			std::string explanation = mpstr_errorExplanation;
			char latest = '0';
			for (int i(0); i < explanation.size(); i++)
			{
				if (explanation[i] == '$' && latest != '\\')
				{
					explanation[i] = static_cast<int>(*mpptr_variable);
				}
				latest = explanation[i];
			}

			return explanation;
		}

		//same as <int> but adds all characters one at a time
		BasicVariableException<char*>::operator std::string () const
		{
			std::string explanation = mpstr_errorExplanation;
			char latest = '0';
			for (int i(0); i < explanation.size(); i++)
			{
				//if user enters '$' in the explanation, it would create an infinite loop and crash the program
				//therefore check that it has not looped unreasonably many times
				if (i >= Base::c_maxIterationCount)
					throw Exceptions::BasicException("Infinite loop in variable exception, possibly variable identifier was used in the variable");
				if (explanation[i] == '$' && latest != '\\')
				{
					explanation.insert(i, *mpptr_variable);
					i += sizeof((*mpptr_variable)[0]) / sizeof(*mpptr_variable);
				}
				latest = explanation[i];
			}

			return explanation;
		}
	}
}
