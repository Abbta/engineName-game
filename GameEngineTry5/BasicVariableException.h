#include "BasicException.h"
#pragma once
namespace EngineName
{
    namespace Exceptions
    {
        /*
        * Basic variable exception template class
        * Builds on basic exception with the option to add variable parts to the error string
        * In construction the user can enter a parameter of type T
        * On accesing via typecast all dollar signs '$' in the string will be replaced with this parameter
        */
        template<class T>
        class BasicVariableException :
            public BasicException
        {
        private:
            std::unique_ptr<T> mpptr_variable;
        public:
            BasicVariableException(const char* explanation, const T& $) :
                BasicException(explanation), mpptr_variable(std::make_unique<T>($)) {}

            virtual operator std::string () const override;
        };
    }
}


