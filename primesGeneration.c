#include<stdio.h>
#include<math.h>
void main()
{
	FILE *fp=fopen("primes.txt","w");
	for(int num=11;num<=181;num++)
	{
		int flag=0;
		for(int i=2;i<ceil(sqrt(num));i++)
		{
			if(num%i==0)
			{
				flag=1;	
				break;
			}
		}

		if(!flag)
			fprintf(fp,"%d\n",num);
	}
	
	fclose(fp);
}
	
