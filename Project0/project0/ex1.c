#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
void cpystr(char *s, char *t, int idx){
    while(*(t+idx) != '\0'){
        *s = *(t + idx);
        s++;
        idx++;
    }
    *s = '\0';
}

int cmpstr(const char *s1, const char *s2){
    while(*s1 != '\0'){
        if(*s1 < *s2)
            return -1;
        else{
            if(*s1 > *s2)
                return 1;
        }
        s1++;
        s2++;
    }
    return 0;
}

int isValid(const char *s){
    while(*s != '\0'){
        if(*s < '0' || *s > '9')
            return 0;
        s++;
    }
    return 1;
}

void solve(char *input_str){
    if (!isValid(input_str))
    {
        printf("Error: Not a number\n");
        return 0;
    }
    int len = strlen(input_str);
    int head = 0;
    int i = 0;
    while (head == 0 && input_str[i] == '0')
        i++;
    if (i < len)
    {
        char str[15];
        int new_len = len - i;
        cpystr(str, input_str, i);
        // str[new_len] = '\0';
        if (new_len > 10)
        {
            printf("Error: Number too long!\n");
            return 0;
        }
        else
        {
            if (new_len == 10)
            {
                if (str[0] > '2')
                {
                    printf("Error: Number too long!\n");
                    return 0;
                }
                else
                {
                    if (cmpstr(str, "2147483647") == 1)
                    {
                        printf("Error: Number too long!\n");
                        return 0;
                    }
                    else
                    {
                        int num = atoi(str);
                        printf("The number is: %d\n", num);
                        return 0;
                    }
                }
            }
            else
            {
                int num = atoi(str);
                printf("The number is: %d\n", num);
                return 0;
            }
        }
    }
}
int main(){
    char input_str[16];
    printf("Cas 1: Not a number\n");
    printf("Enter the number: ");
    scanf("%s", input_str);
    solve(input_str);
    printf("------------------------\n");
    printf("Case 2: Too long number\n");
    printf("Enter the number: ");
    scanf("%s", input_str);
    solve(input_str);
    printf("------------------------\n");
    printf("Case 3: Number in range(int)\n");
    printf("Enter the number: ");
    scanf("%s", input_str);
    solve(input_str);
}