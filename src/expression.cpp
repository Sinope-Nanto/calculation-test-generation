#include <cstring>
#include <malloc.h>
#include <base_struct.h>
#include <operator.h>
#include <stdexcept>
#include <stdlib.h>

List<char*>* _notation2List(char* notation){
    int left = 0;
    int right = 0;
    List<char*>* symbol = (List<char*>*)malloc(sizeof(List<char*>));
    while(notation[right] != '\0'){
        if(in(notation[right], operator_list)){
            if(left == right){
                if(notation[right] != ' '){
                    char* operators = (char*)malloc(2 * sizeof(char));
                    operators[0] = notation[right];
                    operators[1] = '\0';
                    symbol->insert(-1, operators);
                }
                left++;
                right++;
                continue;
            }
            char* number = (char*)malloc((right - left + 1) * sizeof(char));
            memcpy(number, notation + left, right - left);
            number[right - left] = '\0';
            symbol->insert(-1, number);
            if(notation[right] != ' '){
                char* operators = (char*)malloc(2 * sizeof(char));
                operators[0] = notation[right];
                operators[1] = '\0';
                symbol->insert(-1, operators);
            }
            left = (++right);
        }
        else right++;
    }
    if(left < strlen(notation)){
        char* number = (char*)malloc((right - left + 1) * sizeof(char));
        memcpy(number, notation + left, right - left);
        number[right - left] = '\0';
        symbol->insert(-1, number);
    }
    return symbol;
}