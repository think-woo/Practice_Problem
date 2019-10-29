#include <stdio.h>
#include <stdlib.h> //qsort()
#include <string.h> //strcmp()

int compare(const void *a, const void *b);

int main()
{
    char s[10][8] = {"india", "delta", "bravo", "kilo", "alfa", "echo", "hotel", "juliett", "golf", "charlie"};
	int i;

    qsort(s, sizeof(s) / sizeof(s[0]), sizeof(s[0]), compare);

    for (i = 0; i < sizeof(s) / sizeof(s[0]); i++)
    {
        printf("%s\n", s[i]);
    }

    return 0;
}

int compare(const void *a, const void *b){

	char *str1 = (char*)a;
	char *str2 = (char*)b;

	return strcmp(str1,str2);
	//str1 > str2이면 1 반환 >> 오름차순 정렬
	
}