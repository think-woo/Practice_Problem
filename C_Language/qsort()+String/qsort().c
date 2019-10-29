#include <stdio.h>
#include <stdlib.h> //qsort()
#include <string.h> //strcmp()

int compare(const void *a, const void *b);

int main()
{
    char s1[10][8] = { 
        "india", "delta", "bravo", "kilo", "alfa",
        "echo", "hotel", "juliett", "golf", "charlie"
    };
	int i;

    qsort(s1, sizeof(s1) / sizeof(s1[0]), sizeof(s1[0]), compare);

    for (i = 0; i < 10; i++)
    {
        printf("%s ", s1[i]);
    }

    printf("\n");

    return 0;
}

int compare(const void *a, const void *b){

	char *str1 = (char*)a;
	char *str2 = (char*)b;

	return strcmp(str1,str2); //1을 반환한다 >> 순서를 바꾼다 >> 오름차순
	
}
