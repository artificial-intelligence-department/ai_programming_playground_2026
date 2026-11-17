#include <string.h>
#include <stdio.h>

const char SYMBOLS[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
const char SYMBOLS_AND_NUMBERS[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789";
const int KEYWORDS_QUANTITY = 59;
const char KEYWORDS[KEYWORDS_QUANTITY][10] = {
    "alignas", "alignof", "and", "and_eq", "asm",
    "auto", "bitand", "bitor", "bool", "break",
    "case", "catch", "char", "class", "const",
    "continue", "default", "delete", "do", "double",
    "else", "enum", "extern", "false", "float",
    "for", "friend", "goto", "if", "int",
    "long", "namespace", "new", "nullptr", "operator",
    "private", "protected", "public", "return", "short",
    "signed", "sizeof", "static", "struct", "switch",
    "template", "this", "throw", "true", "try",
    "typedef", "typename", "union", "unsigned", "using",
    "virtual", "void", "volatile", "while"
};

bool isIdentifier(char *token)
{
    if (token == NULL || strlen(token) == 0)
        return false;

    char *pointer = token;
    
    for (pointer; pointer < token + strlen(token); pointer++)
    {
        if (pointer == token)
        {
            if (strchr(SYMBOLS, *pointer) == NULL)
                return false;
        }
        else
        {
            if (strchr(SYMBOLS_AND_NUMBERS, *pointer) == NULL)
                return false;
        }
    }

    for (int i = 0; i < KEYWORDS_QUANTITY; i++)
        {
            if (strcmp(token, KEYWORDS[i]) == 0)
                return false;
        }

    return true;
}

int main()
{
    char _strichka[256] = "_zero 1cool money p-l linux! true@ false& ilovecpp int double bit";
    char _strichka_of_identifiers[256] = "";

    char *token = strtok(_strichka, " ");
    while (token != NULL)
    {
        bool identifier = isIdentifier(token);
        if (identifier)
        {
            strcat(_strichka_of_identifiers, token);
            strcat(_strichka_of_identifiers, " ");
        }
        token = strtok(NULL, " ");
    }

    puts(_strichka_of_identifiers);

    return 0;
}