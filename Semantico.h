#ifndef SEMANTICO_H
#define SEMANTICO_H

#include "Token.h"

class Semantico
{
public:
    void executeAction(int action, const Token *token) noexcept(false);
    void limpaSemantico();
};

#endif
