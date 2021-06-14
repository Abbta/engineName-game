#include "BasicVariableException.h"
namespace EngineName
{
	namespace Exceptions
	{
		BasicVariableException<int>::operator std::string () const
		{
			std::string explanation = mpstr_errorExplanation;
			char latest = '0';
			for(int i(0); i < explanation.size(); i++)
			{
				if (explanation[i] == '$' && latest != '\\')
				{
					explanation[i] = *mpptr_variable;
				}
				latest = explanation[i];
			}

			return explanation;
		}

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

		BasicVariableException<char*>::operator std::string () const
		{
			std::string explanation = mpstr_errorExplanation;
			char latest = '0';
			for (int i(0); i < explanation.size(); i++)
			{
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
