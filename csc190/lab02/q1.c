#include <stdio.h>

int main()
{
	//Get input
	int lb;
	int ub;

	//Super repetitiv code, but we haven't learned methods yet
	fscanf(stdin, "%d", &lb);
		if(lb<0 || lb>1000){
			printf("Invalid Bound Entries!\n");
			return 1;
		}
	fscanf(stdin, "%d", &ub);
		if(ub<0 || ub>1000){
			printf("Invalid Bound Entries!\n");
			return 1;
		}

	//Determine Prime Numbers
		//initialize array with 1's
		//for each i from 2 to ub
			//Let m be element of integers	
			//while i*m < ub
				//set array[2*m] = 0
				//m++
	//Print prime numbers
	
	//Initialize array
	int p[ub+1];
	for(int i=0; i<ub+1; i++){
		p[i] = 1;
	}
	
	//Determine primes
	for(int i=2; i<ub; i++){
		int m = 2;
		while(i*m<=ub){
			p[i*m] = 0;
			m++;
		}
	}

	//Print primes
	for(int i=lb; i<ub+1; i++){
		if(1==p[i]){
			fprintf(stdout, "%3d ", i);
		}
	}

	printf("\n"); //Prettify
	return 0;
}
