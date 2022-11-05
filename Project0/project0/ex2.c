#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void solve(char *fileName){
    FILE *ft = fopen(fileName, "r");
    if (ft == NULL)
    {
        printf("Cannot open file %s\n", fileName);
        fclose(ft);
        return ;
    }
    else
    {
        int digit_num = 0;
        int letter_num = 0;
        int line_num = 0;
        int hasData = 0;
        while (1)
        {
            char c = fgetc(ft);
            if (c != EOF)
                hasData = 1;
            else
                break;

            if (c >= '0' && c <= '9')
            {
                digit_num++;
            }
            else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            {
                letter_num++;
            }
            else if (c == '\n')
                {
                    line_num++;
                }
        }
        if (hasData)
            line_num++;
        printf("The file %s has: \n", fileName);
        printf("%d line\n", line_num);
        printf("%d digits\n", digit_num);
        printf("%d letters\n", letter_num);
        fclose(ft);
        return;
    }
}
int main(){
    char fileName[1024];
    printf("Case 1: File does not exist or cannot open file.\n");
    printf("Enter a file name: ");
    scanf("%s", fileName);
    solve(fileName);
    printf("-----------------------------\n");
    printf("Case 2: Read data from file.\n");
    printf("Enter a file name: ");
    scanf("%s", fileName);
    solve(fileName);
}