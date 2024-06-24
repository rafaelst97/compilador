#ifndef CONSTANTS_H
#define CONSTANTS_H

enum TokenId 
{
    EPSILON  = 0,
    DOLLAR   = 1,
    t_PARENTESES_ABRE = 2,
    t_PARENTESES_FECHA = 3,
    t_COLCHETES_ABRE = 4,
    t_COLCHETES_FECHA = 5,
    t_PONTO = 6,
    t_VIRGULA = 7,
    t_PONTO_VIRGULA = 8,
    t_CHAVE_ABRE = 9,
    t_CHAVE_FECHA = 10,
    t_INT = 11,
    t_ELSE = 12,
    t_IF = 13,
    t_FLOAT = 14,
    t_FOR = 15,
    t_CHAR = 16,
    t_STRING = 17,
    t_BOOL = 18,
    t_VOID = 19,
    t_RETURN = 20,
    t_WHILE = 21,
    t_DO = 22,
    t_COUT = 23,
    t_CIN = 24,
    t_MAIOR = 25,
    t_MENOR = 26,
    t_MAIOR_IGUAL = 27,
    t_MENOR_IGUAL = 28,
    t_IGUAL = 29,
    t_DIFERENTE = 30,
    t_COMENTARIO_MULTILINHA = 31,
    t_MAIS = 32,
    t_MENOS = 33,
    t_DIV = 34,
    t_MULT = 35,
    t_MOD = 36,
    t_ATRIBUICAO = 37,
    t_OUT_BIT = 38,
    t_IN_BIT = 39,
    t_XOR_BIT = 40,
    t_OR_BIT = 41,
    t_AND_BIT = 42,
    t_COMPLEMENTO_BIT = 43,
    t_E = 44,
    t_OU = 45,
    t_NOT = 46,
    t_COMENTARIO_LINHA = 47,
    t_CONST_DEC = 48,
    t_CONST_REAL = 49,
    t_CONST_BIN = 50,
    t_CONST_HEX = 51,
    t_CONST_CHAR = 52,
    t_CONST_STR = 53,
    t_ID = 54
};

const int STATES_COUNT = 102;

extern int SCANNER_TABLE[STATES_COUNT][256];

extern int TOKEN_STATE[STATES_COUNT];

extern const char *SCANNER_ERROR[STATES_COUNT];

const int FIRST_SEMANTIC_ACTION = 102;

const int SHIFT  = 0;
const int REDUCE = 1;
const int ACTION = 2;
const int ACCEPT = 3;
const int GO_TO  = 4;
const int ERROR  = 5;

extern const int PARSER_TABLE[258][160][2];

extern const int PRODUCTIONS[107][2];

extern const char *PARSER_ERROR[258];

#endif
