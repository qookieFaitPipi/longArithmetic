#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define maxLen 2500
#define maxLenFact 10000
#pragma comment(linker, "/STACK:209715200")

char* addition(char* firstNum, char* secondNum);
char* subtraction(char* firstNum, char* secondNum);
char* multiply(char* firstNum, char* secondNum);
char* power(char* firstNum, char* secondNum);
char* fact(char* num);

int checkError(char* request, int requestLength);
int checkInterval(char* request, int requestLength);
char* fixInitialRequest(char* request, int requestLength);
void revString(char* num);
char* addNulls(char* num, int sign);
int swap(char* firstNum, char* secondNum);
void deleteNulls(char* num);

char* getFirstNum(char* fixedRequest, int sign);
char* getSecondNum(char* fixedRequest, int sign);
void interval(char* request,int sign);
void parse(char* fixedRequest);

int main() {
    char search;
    char request[1000];

    int requestLength = 0;
    while ((search = getchar()) != '\n') {
        request[requestLength++] = search;
    }
    request[requestLength] = '\0';
    if (checkError(request, requestLength)) {
        return 0;
    }

    if (checkInterval(request, requestLength)) {

    }
    else {
        char* fixedRequest = fixInitialRequest(request, requestLength);
        parse(fixedRequest);
        //printf("%s", addition(getFirstNum(fixedRequest, 1), getSecondNum(fixedRequest, 1)));
    }
}

int checkError(char* request, int requestLength) {
    for (int i = 0; i < requestLength; i++) {
        if (request[i] == '+' || request[i] == '-' || request[i] == '*' || request[i] == '^' || request[i] == '!' || request[i] == ' ' || isdigit(request[i])) {
            //printf("done\n");
        }
        else {
            return 1;
        }
    }
    return 0;
}

int checkInterval(char* request, int requestLength) {
    int error = 0;
    for (int i = 1; i < requestLength - 1; i++) {
        if (request[i] == ' ') {
            if (isdigit(request[i - 1]) && isdigit(request[i + 1]) || (isdigit(request[i - 1]) && !isdigit(request[0]))) {
                interval(request, i);
                error = 1;
                return error;
            }
        }
    }
    return 0;
}

char* fixInitialRequest(char* request, int requestLength) {
    char* fixedRequest = (char*)malloc(maxLen * sizeof(char));
    memset(fixedRequest, '\0', maxLen);
    int count = 0;
    for (int i = 0; i < requestLength; i++) {
        if (request[i] != ' ') {
            fixedRequest[count] = request[i];
            count++;
        }
    }
    return fixedRequest;
}

void revString(char* num) {
    int i, j, l;
    char t;
    l = strlen(num);
    i = 0;
    j = l - 1;
    while (i < j) {
        t = num[i];
        num[i] = num[j];
        num[j] = t;
        i++; j--;
    }
}

char* getFirstNum(char* fixedRequest, int sign) {
    char* firstNum = (char*)malloc(maxLen * sizeof(char));
    memset(firstNum, '\0', maxLen);
    int k = 0;

    for (int j = sign - 1; j >= 0; j--) {
        if (isdigit(fixedRequest[j])) {
            firstNum[k] = fixedRequest[j];
            k++;
        }
        else {
            break;
        }
    }
    revString(firstNum);
    return firstNum;
}

char* getSecondNum(char* fixedRequest, int sign) {
    char* secondNum = (char*)malloc(maxLen * sizeof(char));
    memset(secondNum, '\0', maxLen);
    int k = 0;
    for (int j = sign + 1; j < strlen(fixedRequest); j++) {
        if (isdigit(fixedRequest[j])) {
            secondNum[k] = fixedRequest[j];
            k++;
        }
        else {
            continue;
        }
    }
    return secondNum;
}

char* addNulls(char* num, int len) {
    char* a = (char*)malloc(maxLen * sizeof(char));
    memset(a, '\0', maxLen);

    strcpy(a, num);
    int delta = len - strlen(num);
    for (int i = strlen(num); i < strlen(num) + delta; i++) {
        a[i] = '0';
    }
    char* num1 = (char*)malloc(strlen(a));
    memset(num1, '\0', strlen(a));
    strcpy(num1, a);
    free(a);
    return num1;
}
int swap(char* firstNum, char* secondNum) {
    int flag = 0;
    for (int i = 0; i < strlen(firstNum); i++) {
        if (firstNum[i] + '0' > secondNum[i] + '0') {
            flag = 0;
            return flag;
        }
        else if (firstNum[i] + '0' < secondNum[i] + '0') {
            flag = 1;
            return flag;
        }
    }
    return flag;
}

void deleteNulls(char* num) {
    int sign = 0;
    for (int i = 0; i < strlen(num); i++) {
        if (num[i] != '0') {
            sign = i;
            break;
        }
    }
    char* fixedNum = (char*)malloc(maxLen * sizeof(char));
    memset(fixedNum, '\0', maxLen);

    for (int i = sign; i < strlen(num); i++) {
        fixedNum[i - sign] = num[i];
    }

    strcpy(num, fixedNum);
    free(fixedNum);
}

char* addition(char* firstNum, char* secondNum) {
    char* response = (char*)malloc(maxLen * sizeof(char));
    memset(response, '\0', maxLen);

    revString(firstNum);
    revString(secondNum);

    if (strlen(firstNum) == strlen(secondNum)) {
        int unit = 0;
        for (int i = 0; i < strlen(firstNum); i++) {
            int first = firstNum[i] - '0';
            int second = secondNum[i] - '0';
            int answer = first + second + unit;
            if (answer >= 10) {
                response[i] = answer % 10 + '0';
                unit = 1;
            }
            else {
                response[i] = answer + '0';
                unit = 0;
            }
        }
        if (unit == 1) {
            response[strlen(firstNum)] = unit + '0';
        }
    }
    else if (strlen(firstNum) > strlen(secondNum)) {
        char * secondNum1=addNulls(secondNum, strlen(firstNum));
        int unit = 0;
        for (int i = 0; i < strlen(firstNum); i++) {
            int first = firstNum[i] - '0';
            int second = secondNum1[i] - '0';
            int answer = first + second + unit;
            if (answer >= 10) {
                response[i] = answer % 10 + '0';
                unit = 1;
            }
            else {
                response[i] = answer + '0';
                unit = 0;
            }
        }
        if (unit == 1) {
            response[strlen(firstNum)] = unit + '0';
        }
    }
    else if (strlen(firstNum) < strlen(secondNum)) {
        char* firstNum1 = addNulls(firstNum, strlen(secondNum));
        int unit = 0;
        for (int i = 0; i < strlen(secondNum); i++) {
            int first = firstNum1[i] - '0';
            int second = secondNum[i] - '0';
            int answer = first + second + unit;
            if (answer >= 10) {
                response[i] = answer % 10 + '0';
                unit = 1;
            }
            else {
                response[i] = answer + '0';
                unit = 0;
            }
        }
        if (unit == 1) {
            response[strlen(secondNum)] = unit + '0';
        }
    }
    revString(response);
    return response;
}

char* subtraction(char* firstNum, char* secondNum) {
    char* response = (char*)malloc(maxLen * sizeof(char));
    memset(response, '\0', maxLen);

    if (strcmp(firstNum, secondNum) == 0) {
        return "0";
    }

    if (strlen(firstNum) == strlen(secondNum)) {
        if (swap(firstNum, secondNum)) {
            int size = 0;
            revString(firstNum);
            revString(secondNum);
            int unit = 0;
            for (int i = 0; i < strlen(secondNum); i++) {
                int first = firstNum[i] - '0';
                int second = secondNum[i] - '0';
                int answer = second - first - unit;
                if (answer < 0) {
                    unit = 1;
                    answer += 10;
                }
                else {
                    unit = 0;
                }
                response[i] = answer + '0';
                size = i;
            }
            revString(response);
            response[strlen(response)] = '-';
            deleteNulls(response);
        }
        else {
            revString(firstNum);
            revString(secondNum);
            int unit = 0;
            for (int i = 0; i < strlen(secondNum); i++) {
                int first = firstNum[i] - '0';
                int second = secondNum[i] - '0';
                int answer = first - second - unit;
                if (answer < 0) {
                    unit = 1;
                    answer += 10;
                }
                else {
                    unit = 0;
                }
                response[i] = answer + '0';
            }
        }
    }
    else if (strlen(firstNum) > strlen(secondNum)) {
        revString(firstNum);
        revString(secondNum);
        char* secondNum1 = addNulls(secondNum, strlen(firstNum));
        int unit = 0;
        for (int i = 0; i < strlen(secondNum1); i++) {
            int first = firstNum[i] - '0';
            int second = secondNum1[i] - '0';
            int answer = first - second - unit;
            if (answer < 0) {
                unit = 1;
                answer += 10;
            }
            else {
                unit = 0;
            }
            response[i] = answer + '0';
        }
    }
    else if (strlen(firstNum) < strlen(secondNum)) {
        revString(firstNum);
        revString(secondNum);
        char* firstNum1 = addNulls(firstNum, strlen(secondNum));
        int size = 0;
        int unit = 0;
        for (int i = 0; i < strlen(secondNum); i++) {
            int first = firstNum1[i] - '0';
            int second = secondNum[i] - '0';
            int answer = second - first - unit;
            if (answer < 0) {
                unit = 1;
                answer += 10;
            }
            else {
                unit = 0;
            }
            response[i] = answer + '0';
            size = i;
        }
        response[size + 1] = '-';
    }
    revString(response);
    deleteNulls(response);
    return response;
}

char* multiply(char* firstNum, char* secondNum) {
    char* response = (char*)malloc(maxLen * sizeof(char));
    memset(response, '0', maxLen);

    revString(firstNum);
    revString(secondNum);

    int i, j = 0;
    for (i = 0; i < strlen(firstNum); i++) {
        int carry = 0;
        for (j = 0; j < strlen(secondNum); j++) {
            int temp = (firstNum[i] - '0') * (secondNum[j] - '0') + carry + (response[i + j] - '0');
            carry = temp / 10;
            response[i + j] = temp % 10 + '0';
        }
        if (carry > 0) {
            int k = response[i + j] - '0';
            k += carry;
            response[i + j] = k + '0';
        }
    }

    int m = strlen(firstNum) + strlen(secondNum) - 1;
    while (m >= 0 && response[m] == '0') {
        m--;
    }
    m += 1;
    char* n3 = (char*)malloc(maxLen * sizeof(char));
    memset(n3, '\0', maxLen);

    int count = 0;
    for (int i = m - 1; i >= 0; i--) {
        n3[count] = response[i];
        count++;
    }
    strcpy(response, n3);
    return response;
}

char* power(char* firstNum, char* secondNum) {
    char* response = (char*)malloc(maxLen * sizeof(char));
    memset(response, '\0', maxLen);

    if (strcmp(secondNum, "1") == 0) {
        return firstNum;
    }
    if (strcmp(secondNum, "0") == 0) {
        return "1";
    }
    if (strcmp(firstNum, "1") == 0) {
        return firstNum;
    }
    if (strcmp(firstNum, "0") == 0) {
        return firstNum;
    }
    strcpy(response, firstNum);
    while (strcmp(secondNum, "1") != 0) {
        char* num1 = multiply(response, firstNum);
        revString(firstNum);
        strcpy(response, num1);
        char* num2 = subtraction(secondNum, "1");
        strcpy(secondNum, num2);
    }
    return response;
}

char *fact(char *num) {
  char *response = (char *)malloc(maxLenFact*sizeof(char));
  memset(response, '\0', maxLenFact);
  char* num1 = (char*)malloc(maxLenFact * sizeof(char));
  memset(num1, '\0', maxLenFact);
  strcpy(response, num);
  strcpy(num1, num);
  
  while(strcmp(response, "1") != NULL) {
    char *tmpNum = subtraction(response, "1");
    char* num2 = multiply(tmpNum, num1);
    strcpy(num1, num2);
    revString(tmpNum); 
    strcpy(response, tmpNum);
  }
  return num1;
}
void interval(char* request, int sign) {
    char* firstNum = getFirstNum(request, sign);
    char* secondNum = getSecondNum(request, sign);
    if (request[0] == '-') {
        revString(firstNum);
        firstNum[strlen(firstNum)] = '-';
        revString(firstNum);
    }
    if (request[sign + 1] == '-') {
        revString(secondNum);
        secondNum[strlen(secondNum)] = '-';
        revString(secondNum);
    }
    if (firstNum[0] == '-' && strlen(firstNum)==strlen(secondNum)) {
        int flag = 0;
        for (int i = 0; i < strlen(secondNum); i++) {
            if (secondNum[i] != firstNum[i + 1]) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            printf('0');
            return;
        }
    }
    if (firstNum[0] == '-') {
            if (secondNum[0] == '-') {
                char* first = (char*)malloc(maxLen * sizeof(char));
                memset(first, '\0', maxLen * sizeof(char));
                char* second = (char*)malloc(maxLen * sizeof(char));
                memset(second, '\0', maxLen * sizeof(char));
                for (int i = 1; i < strlen(firstNum); i++) {
                    second[i - 1] = firstNum[i];
                }
                for (int i = 1; i < strlen(secondNum); i++) {
                    first[i - 1] = secondNum[i];
                }
                char* responce= (char*)malloc(maxLen * sizeof(char));
                memset(responce, '\0', maxLen * sizeof(char));
                strcpy(responce, first);
                if (strcmp(first, second) == 0) {
                    printf("0");
                    return;
                }
                while (strcmp(first, second) != 0) {
                    char* n1 = addition(first, "1");
                    char* n2 = addition(n1, responce);
                    strcpy(responce, n2);
                    revString(n1);
                    strcpy(first, n1);
                }
                printf("%c",'-');
                printf("%s", responce);
                return;
            }
            else {
                char* first = (char*)malloc(maxLen * sizeof(char));
                memset(first, '\0', maxLen * sizeof(char));
                char* second = (char*)malloc(maxLen * sizeof(char));
                memset(second, '\0', maxLen * sizeof(char));
                for (int i = 1; i < strlen(firstNum); i++) {
                    second[i - 1] = firstNum[i];
                }
                first[0] = '1';
                char* responce1 = (char*)malloc(maxLen * sizeof(char));
                memset(responce1, '\0', maxLen * sizeof(char));
                strcpy(responce1, first);
                if (strcmp(first, second) == 0) {
                    responce1[0] = '1';
                }
                else {
                    while (strcmp(first, second) != 0) {
                        char* n1 = addition(first, "1");
                        char* n2 = addition(n1, responce1);
                        strcpy(responce1, n2);
                        revString(n1);
                        strcpy(first, n1);
                    }
                }
                char* first1 = (char*)malloc(maxLen * sizeof(char));
                memset(first1, '\0', maxLen * sizeof(char));
                char* second1 = (char*)malloc(maxLen * sizeof(char));
                memset(second1, '\0', maxLen * sizeof(char));
                first1[0] = '1';
                strcpy(second1, secondNum);
                char* responce2 = (char*)malloc(maxLen * sizeof(char));
                memset(responce2, '\0', maxLen * sizeof(char));
                responce2[0] = '1';
                while (strcmp(first1, second1) != 0) {
                    char* n12 = addition(first1, "1");
                    char* n22 = addition(n12, responce2);
                    strcpy(responce2, n22);
                    revString(n12);
                    strcpy(first1, n12);
                }
                printf("%s", subtraction(responce2, responce1));
                return;
            }
        }
    else {
        char* first = (char*)malloc(maxLen * sizeof(char));
        memset(first, '\0', maxLen * sizeof(char));
        char* second = (char*)malloc(maxLen * sizeof(char));
        memset(second, '\0', maxLen * sizeof(char));
        strcpy(first, firstNum);
        strcpy(second, secondNum);
        char* responce = (char*)malloc(maxLen * sizeof(char));
        memset(responce, '\0', maxLen * sizeof(char));
        strcpy(responce, first);
        if (strcmp(first, second) == 0) {
            printf("0");
            return;
        }
        while (strcmp(first, second) != 0) {
            char* n1 = addition(first, "1");
            char* n2 = addition(n1, responce);
            strcpy(responce, n2);
            revString(n1);
            strcpy(first, n1);
        }
        printf("%s", responce);
     }
}

void parse(char* fixedRequest) {
    char a[5] = { '\0' };
    int nums[5];

    int count = 0;
    for (int i = 0; i < strlen(fixedRequest); i++) {
        if (!isdigit(fixedRequest[i])) {
            a[count] = fixedRequest[i];
            nums[count] = i;
            count++;
        }
    }

    if (strlen(a) == 1) {
        if (a[0] == '+') {
            printf("%s", addition(getFirstNum(fixedRequest, nums[0]), getSecondNum(fixedRequest, nums[0])));
        }
        else if (a[0] == '-') {
            printf("%s", subtraction(getFirstNum(fixedRequest, nums[0]), getSecondNum(fixedRequest, nums[0])));
        }
        else if (a[0] == '*') {
            printf("%s", multiply(getFirstNum(fixedRequest, nums[0]), getSecondNum(fixedRequest, nums[0])));
        }
        else if (a[0] == '!') {
            printf("%s", fact(getFirstNum(fixedRequest, nums[0])));
        }
        else if (a[0] == '^') {
            printf("%s", power(getFirstNum(fixedRequest, nums[0]), getSecondNum(fixedRequest, nums[0])));
        }
    }
    else if (strlen(a) == 2) {
        if (a[0] == '-' && a[1] == '+') {
            printf("%s", subtraction(getSecondNum(fixedRequest, nums[1]), getFirstNum(fixedRequest, nums[1])));
        }
        if (a[0] == '-' && a[1] == '-') {
            printf("%c", '-');
            printf("%s", addition(getSecondNum(fixedRequest, nums[1]), getFirstNum(fixedRequest, nums[1])));
        }
        if (a[0] == '-' && a[1] == '*') {
            printf("%c", '-');
            printf("%s", multiply(getSecondNum(fixedRequest, nums[1]), getFirstNum(fixedRequest, nums[1])));
        }
    }
}
