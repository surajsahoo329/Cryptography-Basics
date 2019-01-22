//TITLE : TO ENCRYPT AND DECRYPT A MESSAGE (CRYPTOGRAPHY BASICS) IN C
//NAME : SURAJ KUMAR SAHOO

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int check_prime(int,int);//PROTOTYPE OF check_prime FUNCTION DECLARED

int phi_function(int);//PROTOTYPE OF phi_function FUNCTION DECLARED

int gcd(int,int);//PROTOTYPE OF gcd FUNCTION DECLARED

int successive_squaring(int,int,int);//PROTOTYPE OF successive_squaring FUNCTION DECLARED

int kth_roots_mod_m(int,int,int);//PROTOTYPE OF kth_roots_mod_m FUNCTION DECLARED

void encryption();//PROTOTYPE OF encryption FUNCTION DECLARED

void decryption();//PROTOTYPE OF decryption FUNCTION DECLARED

void encryption_and_decryption();//PROTOTYPE OF encryption_and_decryption FUNCTION DECLARED

int generate_random_key(int,int);//PROTOTYPE OF generate_random_key FUNCTION DECLARED

void write_key_to_file(int);//PROTOTYPE OF write_key_to_file FUNCTION DECLARED

void write_enc_codes_to_file(int [],int,int,int);//PROTOTYPE OF write_enc_codes_to_file FUNCTION DECLARED

int read_key_from_file();//PROTOTYPE OF read_key_from_file FUNCTION DECLARED

void start_program();//PROTOTYPE OF start_program FUNCTION DECLARED

void start_program()
{
	int choice;
	do
	{
				  
		printf("\nWELCOME TO CRYPTOGRAPHY\n");
		printf("-----------------------\n");
		printf("ENTER '1' TO ENCRYPT YOUR MESSAGE.\n");
		printf("ENTER '2' TO DECRYPT THE MESSAGE.\n");
		printf("ENTER '3' TO ENCRYPT AND DECRYPT YOUR MESSAGE.\n");
		printf("ENTER '0' TO EXIT.\n");
		printf("\nENTER YOUR CHOICE : ");
		scanf("%d",&choice);

		printf("\n");

		if(choice==1) encryption();
		else if(choice==2) decryption();
		else if(choice==3) encryption_and_decryption();
		else if(choice!=0) printf("INVALID CHOICE.PLEASE ENTER A VALID CHOICE !!!\n");

	}while(choice!=0);		 


	printf("EXIT\n");
	printf("THANK YOU\n\n");

}

int read_key_from_file()
{
	int key;
	FILE *fptr = fopen("private_key.txt","r");

	if(fptr == NULL)
	{
		printf("\nERROR! 'private_key.txt' FILE IS MISSING!!!\n"); 
		printf("TERMINATING PROGRAM...\n\n");  
		exit(0);             
	}

	fscanf(fptr,"PRIVATE KEY : %d\n",&key);
	return key;
	fclose(fptr);
}

void write_enc_codes_to_file(int enc_code[],int p,int q,int size)
{

	FILE *fptr = fopen("encrypted_codes.txt","w");
	int i=0;

	if(fptr == NULL)
	{
		printf("\nERROR! 'encrypted_codes.txt' FILE IS MISSING!!!\n"); 
		printf("TERMINATING PROGRAM...\n\n");  
		exit(0);             
	}

	fprintf(fptr,"VALUE OF P : %d\n",p);
	fprintf(fptr,"VALUE OF Q : %d\n",q);
	fprintf(fptr,"NUMBER OF ENCRYPTED CODES : %d",size);
	fprintf(fptr,"\nENCRYPTED CODES : \n");

	for(i=0;i<size;i++)
		fprintf(fptr,"%d ",enc_code[i]);

	fclose(fptr);
}

void write_key_to_file(int num)
{
	FILE *fptr = fopen("private_key.txt","w");

	if(fptr == NULL)
	{
		printf("\nERROR! 'private_key.txt' FILE IS MISSING!!!\n"); 
		printf("TERMINATING PROGRAM...\n\n");  
		exit(0);             
	}

	fprintf(fptr,"PRIVATE KEY : %d\n",num);
	fclose(fptr);
}

int generate_random_key(int lower, int upper)
{
	int num;  
	num=(rand()+lower)%(upper+1);//GENERATES A RANDOM NUMBER BETWEEN 'lower' AND 'upper' VALUES
	return num;    
}

void encryption_and_decryption()
{
	printf("TO ENCRYPT AND DECRYPT THE MESSAGE (CRYPTOGRAPHY)\n");
	printf("-------------------------------------------------\n"); 

	FILE *fptr=fopen("primes.txt","r");
	
	if(fptr==NULL)
	{
		printf("\n'primes.txt' FILE IS MISSING!!!\n");
		printf("TERMINATING PROGRAM...\n\n");  
		exit(0);
	}

	int m,p,q,k;//HERE THE VALUES OF 'p' AND 'q' ARE USED TO CALCULATE KEY VALUE 'm' 
	int x,ss_res,count=0,enc_code[100],kth_root,key=2,phi_m,attempt=3,count1=0,count2=0;
	char msg[100],ascii_value,line[256],private_key[10];

	srand(time(0));

	printf("ENTER YOUR MESSAGE: ");
	scanf(" %[^\t\n]s",msg);//READS THE MESSAGE FROM KEYBOARD AND CAN ALSO TAKE [SPACE] AS A CHARACTER

	int random1=rand()%42+1,random2=rand()%42+1;

	while (fgets(line, sizeof(line),fptr)) /* read a line */
	{
		count1++;
		count2++;
		if (count1 == random1)
			fscanf(fptr,"%d\n",&p);
		if(count2 == random2)
			fscanf(fptr,"%d\n",&q);
 	}

	m=p*q;//GENERATING THE PUBLIC KEY 'm' FOR ENCRYPTING AND DECRYPTING A MESSAGE
	phi_m=phi_function(m); 

	do
	{
		key=generate_random_key(2,m-1);

	}while(gcd(key,phi_m)!=1);

	k=key;//A RANDOM PRIVATE KEY IS GENERATED AND IS STORED IN 'k'

	printf("\nPRIVATE KEY HAS BEEN GENERATED.\n"); 

	write_key_to_file(k);//PRIVATE KEY HAS BEEN STORED IN A FILE  

	int copy_msg[100]={},i=0,j;

	while(msg[i]!='\0') 
	{
		copy_msg[i]=msg[i];//'copy_msg' ARRAY COPIES THE ASCII VALUES OF 'msg' ARRAY
		i++;
	}

	for(j=0;j<i;j++) 
	{
		x=copy_msg[j];
		ss_res=successive_squaring(x,k,m);//'successive_squaring(x,k,m)' RETURNS THE ENCRYPTED CODES TO 'ss_res'
		enc_code[j]=ss_res;
		count++;//COUNTS THE NUMBER OF ENCRYPTED CODES
	}  

	printf("\nYOUR MESSAGE HAS BEEN ENCRYPTED.\n");

	write_enc_codes_to_file(enc_code,p,q,count);

	printf("\nENTER THE PRIVATE KEY : ");
	scanf("%s",private_key);
	 
	while(atoi(private_key)!=k)
	{
		
		if(attempt==0)
	  	{ 
			remove("private_key.txt");
			remove("encrypted_codes.txt");
			printf("\nTHE HIDDEN MESSAGE HAS BEEN DELETED.EXIT !!! \n\n"); 
			exit(0);
	   	}

		printf("\nINCORRECT KEY !!!");
		printf("\nPLEASE ENTER THE CORRECT KEY ( %d ATTEMPT/ATTEMPTS ARE REMAINING ) : ",attempt);
		scanf("%s",private_key);

		attempt--;

	 }


	printf("\nYOUR MESSAGE HAS BEEN DECRYPTED.\n");
	printf("\nYOUR MESSAGE IS : ");

	for(j=0;j<count;j++) 
	{
		x=enc_code[j];
		kth_root=kth_roots_mod_m(k,x,m);//'kth_roots_mod_m(k,x,m)' RETURNS THE DECRYPTED CODES TO 'kth_root'
		ascii_value=kth_root;
		printf("%c",ascii_value);//PRINTS THE DECRYPTED CODES
	}

	fclose(fptr);
	printf("\n\nGENERATING MENU AGAIN...\n");
	
}

void decryption()
{

	printf("\nTO DECRYPT A MESSAGE (CRYPTOGRAPHY)\n");
	printf("------------------------------------\n");

	int code[100],i=0,j,num,attempt=3,check_p,check_q,p,q,k,size,key;
	char ascii_value,private_key[10];
	int m,x,kth_root,phi_m;//HERE THE VALUES OF 'p' AND 'q' ARE USED TO CALCULATE KEY VALUE 'm' 

	FILE *fptr = fopen("encrypted_codes.txt","r");

	if(fptr == NULL)
	{
		 printf("\nERROR! 'encrypted_codes.txt' FILE IS MISSING!!!\n");  
		 exit(0);             
	}

	fscanf(fptr,"VALUE OF P : %d\n",&p);
	fscanf(fptr,"VALUE OF Q : %d\n",&q);
	fscanf(fptr,"NUMBER OF ENCRYPTED CODES : %d",&size);
	fscanf(fptr,"\nENCRYPTED CODES : \n");

	for(i=0;i<size;i++)
		fscanf(fptr,"%d ",&code[i]);

	m=p*q;//GENERATING THE PUBLIC KEY 'm' FOR DECRYPTING A MESSAGE
	phi_m=phi_function(m);

	printf("\nENTER THE PRIVATE KEY : ");
	scanf("%s",private_key);

	k=read_key_from_file();

	while(atoi(private_key)!=k)
	{
		if(attempt==0)
	  	{ 
			remove("private_key.txt");
			remove("encrypted_codes.txt");
			printf("\nTHE HIDDEN MESSAGE HAS BEEN DELETED.EXIT !!! \n\n"); 
			exit(0);
	   	}

		printf("\nINCORRECT KEY !!!");
		printf("\nPLEASE ENTER THE CORRECT KEY ( %d ATTEMPT/ATTEMPTS ARE REMAINING ) : ",attempt);
		scanf("%s",private_key);

		attempt--;
	}

	printf("\nTHE MESSAGE HAS BEEN DECRYPTED.\n");
	printf("\nTHE MESSAGE IS : ");
        
	for(j=0;j<size;j++) 
	{
		x=code[j];
		kth_root=kth_roots_mod_m(k,x,m);//'kth_roots_mod_m(k,x,m)' RETURNS THE DECRYPTED CODES TO 'kth_root'
		ascii_value=kth_root;
		printf("%c",ascii_value);//PRINTS THE DECRYPTED CODES
	}

        
	fclose(fptr);

	printf("\n\nGENERATING MENU AGAIN...\n");
}

void encryption()
{
	printf("TO ENCRYPT THE MESSAGE (CRYPTOGRAPHY)\n");
	printf("-------------------------------------\n"); 

	FILE *fptr=fopen("primes.txt","r");
	
	if(fptr==NULL)
	{
		printf("\n'primes.txt' FILE IS MISSING!!!\n");
		printf("TERMINATING PROGRAM...\n\n");  
		exit(0);
	}


	int m,p,q,k,x,ss_res,key,phi_m;//HERE THE VALUES OF 'p' AND 'q' ARE USED TO CALCULATE KEY VALUE 'm' 
	char msg[100],line[10];
	int size,count=0,enc_code[100],copy_msg[100]={},i=0,j,count1=0,count2=0;

	srand(time(0));

	printf("ENTER YOUR MESSAGE : ");
	scanf(" %[^\t\n]s",msg);

	int random1=rand()%42+1,random2=rand()%42+1;

	while (fgets(line, sizeof(line),fptr)) /* read a line */
	{
		count1++;
		count2++;
		if(count1 == random1)
			fscanf(fptr,"%d\n",&p);
		if(count2 == random2)
			fscanf(fptr,"%d\n",&q);
 	}

        m=p*q;//GENERATING THE PUBLIC KEY 'm' FOR ENCRYPTING A MESSAGE
        phi_m=phi_function(m);
        
        do
        {
    
          key=generate_random_key(2,m-1);

         }while(gcd(key,phi_m)!=1);

         k=key;//A RANDOM PRIVATE KEY IS GENERATED AND IS STORED IN 'k'

         printf("\nPRIVATE KEY HAS BEEN GENERATED.\n");  

         write_key_to_file(k);//PRIVATE KEY HAS BEEN STORED IN A FILE   



	while(msg[i]!='\0') 
	{
		copy_msg[i]=msg[i];//'copy_msg' ARRAY COPIES THE ASCII VALUES OF 'msg' ARRAY
		i++;
	}

	for(j=0;j<i;j++) 
	{
		x=copy_msg[j];
		ss_res=successive_squaring(x,k,m);//'successive_squaring(x,k,m)' RETURNS THE ENCRYPTED CODES TO 'ss_res'
		enc_code[j]=ss_res;
		count++;
	}   

	printf("\nYOUR MESSAGE HAS BEEN ENCRYPTED.\n");

	write_enc_codes_to_file(enc_code,p,q,count);
	fclose(fptr);

	printf("\nGENERATING MENU AGAIN...\n");

	


}

int kth_roots_mod_m(int k,int b,int m)
{
        //FUNCTION THAT FINDS A SOLUTION FOR 'x' TO THE POWER 'k' CONGRUENT TO 'b' (MOD 'm')
	//----------------------------------------------------------------------------------

	int phi,u0,v0,x=0,y=1,lastx=1,lasty=0,temp,q,r,final_ans,org_k,org_b;
	
        org_k=k;
        org_b=b;
	
     	if(check_prime(m,m/2)==1)
		phi=m-1;
	else
		phi=phi_function(m);
	
	
	if(gcd(k,phi)==1)
	{
		int a=k;
		int b=phi;
		while (phi != 0)
		{
			q = k/phi;
			r = k%phi;
			k=phi;
			phi=r;
			temp = x;
			x = lastx-q*x;
			lastx = temp;
			temp = y;
			y = lasty-q*y;
			lasty = temp;            

		}

		if((lastx>0)&&(lasty<0))
		      lasty=0-lasty;
	
		if((lastx<0)&&(lasty>0))
		{
			lasty=0-lasty;		  
			lastx=lastx+b;
			lasty=lasty+a;		    
		}

                
		// ROOTS ARE u :'lastx' AND v : 'lasty' OF THE EQUATION ku-phi(m)v=1.

		final_ans=successive_squaring(org_b,lastx,m);
		// IF X TO THE POWER 'org_k' IS  CONGRUENT TO 'org_b' MODULO 'm', THEN X IS CONGRUENT TO 'final_ans' MODULO 'm'

		return final_ans;//RETURNS final_ans AFTER FINDING KTH ROOTS MODULO M		
	}

        else
		return 0;
       	  
}

int successive_squaring(int a,int k,int m)
{

   //FUNCTION THAT GENERATES NUMBERS BY SUCCESSIVE SQUARING ALGORITHM ( 'a' TO THE POWER 'k' MOD 'm' )
   //-------------------------------------------------------------------------------------------------

	int b=1;
        
	while(k>0)
	{
		if(k%2!=0) b=(b*a)%m;
		a=(a*a)%m;
		k=k/2;
	}

       return b; //returns the value of 'a1' to the power 'k1' modulo m 
}

int gcd(int a, int b)
{
      //FUNCTION THAT RETURNS THE GREATEST COMMON DIVISOR (GCD) OF TWO NUMBERS 'a' AND 'b' BY RECURSION METHOD
      //------------------------------------------------------------------------------------------------------
	if (a==0) return b;
	else return gcd(b%a,a);
}
 

int phi_function(int n)
{
	//FUNCTION THAT RETURNS THE EULER'S PHI FUNCTION VALUE 
	//EULER'S PHI(TOTIENT) FUNCTION, phi(n)=result,WHERE result COUNTS THE NUMBERS i SUCH THAT GCD(i,n)=1 GIVEN 2<i<n 
	//---------------------------------------------------------------------------------------------------------------

	int result=1,i;
	for (i=2;i<n;i++)
		if (gcd(i,n)==1) result++;
	return result;
}
       
int check_prime(int num,int i)
{
	//CHECKS A NUMBER 'num' IS PRIME OR NOT BY RECURSION METHOD
	//---------------------------------------------------

	if(i==1)
		return 1;
	else
	{
	     if((num%i)==0)
		return 0;
	     else 
		return check_prime(num,i-1);
	}
}	

void main()
{
   start_program();
}      
