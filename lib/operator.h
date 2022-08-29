#ifndef OPEREATOR
#define OPEREATOR

char operator_list[] = "+-*/() N";
int operator_rank(char _operator){
    switch (_operator)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case 'N':
        return 9;
    case '(':
        return 0;
    case ')':
        return 10;
    default:
        return -1;
    }
}
bool in(char c, char* str){
    for(int i = 0; str[i] != '\0'; i++)
        if(c == str[i])
            return true;
    return false;
}

#endif