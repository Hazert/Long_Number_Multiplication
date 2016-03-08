/*  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*  File Type :  main.c                                                                      */
/*  File Name : LongNumberMultiplication                                    */
/*  Student Name : Hazert                                                                */
/*  Student ID : 1330003036                                                            */
/*  Created by Hazert on 15/9/27.                                                    */
/*  Copyright © 2015年 Hazert. All rights reserved                        */
/*  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define N 10000

char* CombineLnm(char* a, char* b);
char* RmPoint(char* s, int* dot);
void toArray(int* a, char* s);
void Multiplication(int* a, int* b, int* result);
char* resultWithPoint(int* a, char* result, int adot, int bdot, int al, int bl);

int main (void) {
    char numberOne[N];
    char numberTwo[N];

    printf("**************************************\n");
    printf("***** Long Number Multiplication *****\n");
    printf("**************************************\n");
    printf("*                         Hazert     *\n");
    printf("*                         1330003036 *\n");
    printf("**************************************\n");
    printf("* Please Input Number1: ");
    scanf("%s",numberOne);
    printf("* Please Input Number2: ");
    scanf("%s",numberTwo);
    printf("**************************************\n");
    printf("\nresult: %s\n\n", CombineLnm(numberOne, numberTwo));

    return 0;
}

char* CombineLnm(char* numberOne, char* numberTwo) {
    int string1[N], string2[N], string[N * 2];
    int numberOnePoint = 0, numberTwoPoint = 0;

    char* result = (char*)malloc(sizeof(char) * (strlen(numberOne) + strlen(numberTwo)));

    toArray(string1, RmPoint(numberOne, &numberOnePoint));
    toArray(string2, RmPoint(numberTwo, &numberTwoPoint));

    Multiplication(string1, string2, string);//Multiplicate two Long Number
    return resultWithPoint(string, result, numberOnePoint, numberTwoPoint, strlen(numberOne), strlen(numberTwo));
}

char* RmPoint(char* number, int* point) {//Remove .(point) from user's input number
    int length = strlen(number);
    char* a = (char*)malloc(sizeof(char) * (length - 1));

    for (int i = length; i >= 0; i--) {
        *(a + i - 1) = *(number + i);
        if (*(number + i) == '.') {
            *point = i;//Used to save .(Point)
            break;
        }
    }
    if (*point != 0) {
        for (int i = *point; i >= 0; i--)
            *(a + i - 1) = *(number + i - 1);
        return a;
    } else
        return number;
}

void toArray(int* number, char* string) {
    int len = strlen(string);
    for (int i = 0; i < N; i++)
        *(number + i) = 0;
    for (int i = 0; i < len; i++)
        *(number + len - 1 - i) = *(string + i) - '0';
}

//Get the Result without .(point)
void Multiplication(int* numberOne, int* numberTwo, int* numberResult) {
    for (int i = 0; i < N * 2; i++){
        *(numberResult + i) = 0;
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            *(numberResult + i + j) += *(numberOne + i) * *(numberTwo + j);
        }
    }
    for (int k = 0; k < N * 2 - 1; k++) {
        *(numberResult + k + 1) += *(numberResult + k) / 10;
        *(numberResult + k) = *(numberResult + k) % 10;
    }
}

//Put . Back to Long Number Multiplication Result
char* resultWithPoint(int* number, char* numberResult, int numberOnePoint, int numberTwoPoint, int LengthOne, int LengthTwo) {
    int n = N * 2 - 1;
    while (number[n] == 0)
        n--;
    if (n < 0){
        return "0";
    }
    for (int i = n; i >= 0; i--) {
        char* tmp = (char*)malloc(sizeof(char) * 2);
        sprintf(tmp, "%d", number[i]);
        strcat(numberResult, tmp);
    }
    if (numberOnePoint == 0 && numberTwoPoint == 0) {
        return numberResult;
    } else {

        int length = strlen(numberResult);
        int mns = 0;

        if (numberOnePoint != 0 && numberTwoPoint == 0){
            mns = LengthOne - numberOnePoint - 1;
        }else if (numberOnePoint == 0 && numberTwoPoint != 0){
            mns = LengthTwo - numberTwoPoint - 1;
        }else{
            mns = LengthOne + LengthTwo - numberOnePoint - numberTwoPoint - 2;
        }

        int d = length - mns;
        char* finalResult = (char*)malloc(sizeof(char) * (length + 1));

        strcpy(finalResult, numberResult);

        for (int i = d; i < length + 1; i++){
            finalResult[i + 1] = numberResult[i];
        }
        *(finalResult + d) = '.';
        return finalResult;
    }
}
