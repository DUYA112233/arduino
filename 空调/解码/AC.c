#include <stdio.h>
#include <math.h>

int main()
{
	int	input[2];
  	int two[96];  //3~194
  	int hex;
  	int i, j, m = 0;
  	int temp;
  	while(1)
  	{
	 	for(i = -2 ; i < 195 ; i++)
  		{
  			if(i < 0 || i > 191)
  			{
		  		scanf("%d", &temp);
		  		continue;
  			}
   	 	for(j = 0 ; j < 2 ; j++)
   	 	{
		    	scanf("%d", &input[j]);
					input[j] = abs(input[j]);
		    }
		    if(input[0] < 1000 && input[1] > 1000)
		    {
   	 		two[i/2] = 1;
   	 	}
   	 	else
   	 	{
		    	two[i/2] = 0;
		    }
		    printf("%d ", two[i/2]);
		    i++;
  		}
  		printf("\n\n");
 	 	for(i = 0 ; i < 24 ; i++)
 	 	{
			if(i%4 == 2 || i%4 == 3)  continue;
  			hex = 0;
	  		for(j = 0 ; j < 4 ; j++)
	  		{
	  			hex += two[4*i+j] * pow(2, 3-j);
	  		}
	  		switch(hex)
	  		{
	  			case 10: printf("A");
	  			break;
	  			case 11: printf("B");
	  			break;
	  			case 12: printf("C");
	  			break;
	  			case 13: printf("D");
	  			break;
	  			case 14: printf("E");
	  			break;
	  			case 15: printf("F");
	  			break;
	  		}
	  		if(hex < 10)
	  		{
	  			printf("%d", hex);
	  		}
				/*
	  		if(i%8 == 5)
	  		{
	  			printf("\n\n");
	  		}
				*/
 		}
 	}
}
