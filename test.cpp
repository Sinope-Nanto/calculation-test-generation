#include <base_struct.h>
#include <gen_expression.h>
#include <cstdio>
#include <fstream>
#include <cstring>

using namespace std;
int main(){
    int answer;
    char* text;
    char test_text[100];
    char answer_text[100];
    char test_file_name[100];
    char answer_file_name[100];
    ofstream test_file, answer_file;
    for(int j = 0; j < 100; j++){
        sprintf(test_file_name, "text/test/%d.doc", j);
        sprintf(answer_file_name, "text/answer/%d-answer.doc", j);
        test_file.open(test_file_name);
        answer_file.open(answer_file_name);
        for(int i = 0; i < 100; i++){
            text = getIntExpression(&answer, 3);
            sprintf(test_text, "%s=", text);
            sprintf(answer_text, "%s=%d", text, answer);
            delete text;
            // printf("%s\n%s\n", test_text, answer_text);
            test_file<<test_text;
            answer_file<<answer_text;
            for(int k = strlen(test_text); k <= 35; k++) test_file<<' ';
            for(int k = strlen(answer_text); k <= 35; k++) answer_file<<' ';
            if(i % 2){
                test_file<<endl;
                answer_file<<endl;
            }
        }
        test_file.close();
        answer_file.close();
    }
    return 0;
}