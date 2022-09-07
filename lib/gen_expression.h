#ifndef GENEXPRESSION
#define GENEXPRESSION

#include "expression.h"
#include "gen_expression.h"
#include <cstring>
#include "prime_number.h"
#include <stdio.h>
#include <random>
#include <stdlib.h>
#include <math.h>
#include "tree.h"

int* recursionGenerateExper(int target, int depth, int max_depth, int* length);
char* generateExper(int target, int max_depth);
int* getAllPrimeFactor_test1(int target, int* factoryList);//此版本为临时版
char* getIntExpression(int* answer);
int getIntLength(int data);
char* getFloatExpression(double* answer, int max_depth);

int getIntLength(int data){
    int l = 1;
    if(data < 0){
        l++;
        data = -data;
    }
    while(data/=10) l++;
    return l;
}

int* getAllPrimeFactor_test1(int target, int* factorList){
    int i = 0;
    do{
        if(target == PrimeNumberListin1000[i]){
            factorList[i]++;
            return factorList;
        }
        else if(target % PrimeNumberListin1000[i] == 0){
            factorList[i]++;
            return getAllPrimeFactor_test1(target/PrimeNumberListin1000[i], factorList) ? factorList : nullptr;
        }
        i++;
    }while(PrimeNumberListin1000[i] != 997);
    return target==1 ?  factorList : nullptr;
}

int* recursionGenerateExper(int target, int depth, int max_depth, int* length){
    int base_bia = 1<<20;
    int possible_end = (100 * depth)/max_depth;
    int* result;
    int leftnum;
    int rightnum;
    int typeOpera;
reRand:
    int randint = rand()%100;
    if(randint < possible_end || !target){
        *length = 1;
        result = new int[1];
        result[0] = target;
        return result;
    }
    else if(randint < 20 + (3 * possible_end)/4){
        leftnum = rand()%target;
        if(leftnum == target || !leftnum) goto reRand;
        rightnum = target - leftnum;
        typeOpera = '+';
    }
    else if(randint < 40 + possible_end/2){
        leftnum = rand()%(target * 2) - (target >> 1);
        if(leftnum == target || !leftnum) goto reRand;
        rightnum = leftnum - target;
        typeOpera = '-';     
    }
    // 此处需要后续修改
    else if(randint < 75 + possible_end/4){
        //printf("enter\n");
        int* factor = new int[168];
        memset(factor, 0, 168*sizeof(int));
        if(!getAllPrimeFactor_test1(target, factor)){
            delete[] factor;
            goto reRand;
        }
        leftnum = 1;
        for(int i = 0; i < 168; i++){
            if(factor[i]){
                leftnum *= int(pow(PrimeNumberListin1000[i], rand()%(factor[i] + 1)));
            }
        }
        rightnum = target/leftnum;
        //printf("%d\n",leftnum);
        delete[] factor;  
        if(abs(leftnum) == 1 || leftnum == target) 
            goto reRand;
        typeOpera = '*';  
    }
    else{
        if(target >= 500)
            goto reRand;
        if(rand()%4 < 3){
            rightnum = rand()%10 + 2;
        }
        else{
            rightnum = rand()%20 + 2;
        }
        leftnum = target*rightnum;
        typeOpera = '/';   
    }
    int leftLength, rightLength;
    int* lEx = recursionGenerateExper(leftnum, depth + 1, max_depth, &leftLength);
    int* rEx = recursionGenerateExper(rightnum, depth + 1, max_depth, &rightLength);
    *length = 3 + leftLength + rightLength;
    result = new int[3 + leftLength + rightLength];
    result[0] = '(' + base_bia;
    memcpy(result + 1, lEx, leftLength * sizeof(int));
    result[leftLength + 1] = typeOpera + base_bia;
    memcpy(result + 2 + leftLength, rEx, rightLength * sizeof(int));
    result[2 + leftLength + rightLength] = ')' + base_bia;
    delete[] lEx;
    delete[] rEx;
    return result;
}

char* generateExper(int target, int max_depth){
    int base_bia = 1<<20;
    int length;
    int* expression = recursionGenerateExper(target, 0, max_depth, &length);
    char* re = new char[100];
    int point = 0;
    int numLength;
    for(int i=0; i<length; i++){
        if(expression[i] > base_bia){
            re[point] = expression[i] - base_bia;
            point++;
        }
        else{
            numLength = getIntLength(expression[i]);
            sprintf(re + point, "%d", expression[i]);
            point += numLength;
        }
    } 
    re[point] = '\0';
    delete[] expression;
    return re;
}

char* getIntExpression(int* answer, int max_depth){
    int randint = rand()%1000;
    *answer = randint;
    return removeParentheses(generateExper(*answer, max_depth));
}

char* getFloatExpression(double* answer, int max_depth){
    int length = rand()%max_depth + 1;
    int point = 0;
    char* re =  new char[100];
    char typeOpera;
    for(int i = 0; i < length; i++){
        int randint = rand()%100;
        int numLength = getIntLength(randint);
        sprintf(re + point, "%d", randint);
        point += numLength;
        int symbol = rand()%4;
        switch (symbol)
        {
        case 0:
            typeOpera = '+';
            break;
        case 1:
            typeOpera = '-';
            break;
        case 2:
            typeOpera = '*';
            break;
        case 3:
            typeOpera = '/';
            break;
        default:
            break;
        }
        re[point] = typeOpera;
        point++;
    }
    int randint = rand()%100;
    int numLength = getIntLength(randint);
    sprintf(re + point, "%d", randint);
    point += numLength;
    re[point] = '\0';
    *answer = load2Tree(_notation2List(re))->get_value();
    return re;
}
#endif