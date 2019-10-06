#include <stdio.h>
#include <stdlib.h>

//Reference used: https://stackoverflow.com/questions/16753034/c-adding-one-char-to-buffer

int main()
{
    char list[1024];
    size_t current_size = 0;
    
    printf("Please input a letter:\n");
    fgets(list, 1024, stdin);

    if (list[0] == 'Q' || list[0] == 'q')
    {
        printf("Letter is Q\n");
    }
    else
    {
        printf("Letter is not Q\n");
        list[current_size++] = list[1024];
        printf("Letter has been added to buffer\n");
    }
    
    return(0);
}
