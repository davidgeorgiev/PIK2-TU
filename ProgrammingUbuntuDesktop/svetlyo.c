#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int number;
    char name[15];
    char faculNumber[10];
    float reating;
}person;
int main()
{


   FILE *fb;
   if((fb = fopen("bin.bin","wb"))== NULL)
   {
    exit(1);
   }

   while(1)
   {
   	printf("Loop starts\n");
    int i,counterOne= 0,counterTwo= 0;
    person one;
    scanf("%d",&one.number);
    while((one.name[counterOne]=getchar())!='-')
    {
        counterOne++;
    }

    while((one.faculNumber[counterTwo]= getchar())!= '-')
    {
      counterTwo++;
    }
    scanf("%f",&one.reating);
    //zapis v faila
    if((fwrite(&one.number,sizeof(int),1,fb))!= 1)
    {
        exit(2);
    }


    if((fwrite(one.name,1,counterOne + 1,fb))!= counterOne +1)
    {
        exit(2);
    }

    if((fwrite(one.faculNumber,1,counterTwo + 1,fb))!= counterTwo +1)
    {
        exit(2);
    }
     if((fwrite(&one.reating,4,1,fb))!= 1)
    {
        exit(2);
    }



   }
   fclose(fb);
    return 0;
}
