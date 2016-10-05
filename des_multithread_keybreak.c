#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<omp.h>
#include <time.h>

int power(int x, int y)
{
	int sum=1;
	int i;
	for(i=0;i<y;i++)
	{
		sum=sum*x;
	}
	//printf("\nsum: ",sum);
	return sum;
}




void logic()
{
int p=pow(2,16);
	int d[64]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			   0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0};
	int key[64];
	int i,j,k,l;
	for(i=0;i<p;i++)
	{
		int data=i;
		int sixteen=15;
		int flag=1;
		//printf("\ni: %d\t",i); 
		//usleep(10000);
		while(data != 0)
		{
			//printf("%d\t",sixteen);
			key[sixteen]=data%2;
			data=data/2;
			sixteen--;
		}
		while(sixteen != -1)
		{
			//printf("%d\t",sixteen);
			key[sixteen]= 0;
			sixteen--;
		}
		for(j=0;j<p;j++)
		{
			data=j;
			sixteen=31;
			//printf("\nj: %d\t",j); 
			//usleep(10000);
			while(data != 0)
			{
				printf("%d\t",sixteen);
				key[sixteen]=data%2;
				data=data/2;
				sixteen--;
			}
			while(sixteen != 15)
			{
			//	printf("%d\t",sixteen);
				key[sixteen]= 0;
				sixteen--;
			}
			for(k=0;k<p;k++)
			{
				data=k;
				sixteen=47;
				//printf("\nk: %d\t",k); 
				//usleep(10000);
				while(data != 0)
				{
				//	printf("%d\t",sixteen);
					key[sixteen]=data%2;
					data=data/2;
					sixteen--;
				}
				while(sixteen != 31)
				{	
				//	printf("%d\t",sixteen);
					key[sixteen]= 0;
					sixteen--;
				}
				for(l=0;l<p;l++)
				{
					data=l;
					sixteen=63;
				//	printf("\nl: %d\n",l); 
					//usleep(10000);
					while(data != 0)
					{
					//	printf("%d\t",sixteen);
						key[sixteen]=data%2;
						data=data/2;
						sixteen--;
					}
					while(sixteen != 47)
					{
					//	printf("%d\t",sixteen);
						key[sixteen]= 0;
						sixteen--;
					}
					//printf("\n");
					int x;
					//printf("key: \n");
					for(x=0;x<64;x++)
					{
						printf("%d",key[x]);
					}
					test(key);
				}
			}
		}
	}


}
int test(int* k)
{
	int pc1[56]={57,49,41,33,25,17,9,
               	 1,58,50,42,34,26,18,
              	 10,2,59,51,43,35,27,
                 19,11,3,60,52,44,36,
                 63,55,47,39,31,23,15,
                 7,62,54,46,38,30,22,
                 14,6,61,53,45,37,29,
                 21,13,5,28,20,12,4
		         };
	//int hex[16];
	int key[16];
	int i;
	/*printf("Enter Plane Text\n");
	for(i=0;i<16;i++)
	{
		scanf("%x",&hex[i]);
	}*/
	// Enter the message as 1 2 3 4 5 6 7 8 9 f f f f f f f
    // corresponding encrypted message is ba94daf36c82cf84 for key 0 0 0 0 0 0 0 0 0 0 0 0 0 0 f e
										  
	int hex[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,5};
	int encrypted[16]={14,8,15,13,15,15,1,10,11,1,9,4,10,12,0,1};
	int msg[64];
	
	for(i=0;i<16;i++)
	{
		int dec=hex[i];
		int j=3;
		while(dec != 0)
		{
			msg[i*4+j]=dec%2;
			dec=dec/2;
			j--;
		}
		while(j != -1)
		{
			msg[i*4+j]=0;
			j--;
		}
	}
/*
	printf("Msg: ");
	for(i=0;i<64;i++)
		printf("%d",msg[i]);
	printf("\n");
	printf("Key: ");
	for(i=0;i<64;i++)
		printf("%d",k[i]);
	printf("\n");   */
// -----------------------------------------//	
	int kplus[56];	
	//printf("K+ : ");
	for(i=0;i<56;i++)
	{
		kplus[i]=k[pc1[i]-1];
	//	printf("%d",kplus[i]);
	}
	//printf("\n");
// ------------------------------------------//

	int c0[28],d0[28];
	for(i=0;i<56;i++)
	{
		if(i < 28)
		{
			c0[i]=kplus[i];
		}
		else
		{
			d0[i-28]=kplus[i];
		}
	}
	//printf("C0: ");
	for(i=0;i<28;i++)
	{
	//	printf("%d",c0[i]);
	}
	//printf("\n");
	//printf("D0: ");
	for(i=0;i<28;i++)
	{
	//	printf("%d",d0[i]);
	}
	//printf("\n");

	int cndn[16][56];
	int shift[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
	for(i=0;i<16;i++)
	{
		int j,l;
		int firstBitC=c0[0];
		int firstBitD=d0[0];
		if(shift[i] == 1)
		{
			for(j=0;j<27;j++)
			{
				c0[j]=c0[j+1];
				d0[j]=d0[j+1];
			}
			c0[27]=firstBitC;
			d0[27]=firstBitD;
		
	//		printf("---------------C%d, D%d----------------\n",i+1,i+1);
			for(l=0;l<28;l++)
			{
	//			printf("%d",c0[l]);
				cndn[i][l]=c0[l];
			}
	//		printf("\n");
			for(l=0;l<28;l++)
			{
	//			printf("%d",d0[l]);
				cndn[i][28+l]=d0[l];
			}
	//		printf("\n");
		}
		else
		{
			int secondBitC=c0[1];
			int secondBitD=d0[1];
			for(j=0;j<26;j++)
			{
				c0[j]=c0[j+2];
				d0[j]=d0[j+2];
			}
			c0[26]=firstBitC;
			d0[26]=firstBitD;
			c0[27]=secondBitC;
			d0[27]=secondBitD;
	//		printf("---------------C%d, D%d----------------\n",i+1,i+1);
			for(l=0;l<28;l++)
			{
	//			printf("%d",c0[l]);
				cndn[i][l]=c0[l];
			}
	//		printf("\n");
			for(l=0;l<28;l++)
			{
	//			printf("%d",d0[l]);
				cndn[i][28+l]=d0[l];
			}
	//		printf("\n");
		}
	}
	//printf("cndn\n");
	for(i=0;i<16;i++)
	{
		int j;
		for(j=0;j<56;j++)
		{
	//		printf("%d",cndn[i][j]);
		}
	//	printf("\n");
	}
	int pc2[48]={
				 14,17,11,24,1,5,
                 3,28,15,6,21,10,
                 23,19,12,4,26,8,
                 16,7,27,20,13,2,
                 41,52,31,37,47,55,
                 30,40,51,45,33,48,
                 44,49,39,56,34,53,
                 46,42,50,36,29,32
				};	
	int keys[16][48];
	//printf("Keys:\n");
	for(i=0;i<16;i++)
	{	
		int j;
	//	printf("K%d:  ",i+1);
		for(j=0;j<48;j++)
		{
			keys[i][j]=cndn[i][pc2[j]-1];
	//		printf("%d",keys[i][j]);
		}
	//	printf("\n");
	}	

	int ip_array[64]={
				58,50,42,34,26,18,10,2,
            	60,52,44,36,28,20,12,4,
            	62,54,46,38,30,22,14,6,
            	64,56,48,40,32,24,16,8,
            	57,49,41,33,25,17,9,1,
            	59,51,43,35,27,19,11,3,
            	61,53,45,37,29,21,13,5,
            	63,55,47,39,31,23,15,7,
				};
	int ip[64];
	//int l0[32],r0[32];
	int L[17][32],R[17][32];
	for(i=0;i<64;i++)
	{
		ip[i]=msg[ip_array[i]-1];
		if(i<32)
		{
			L[0][i]=ip[i];
		}
		else
		{
			R[0][i-32]=ip[i];
		}
	}
	//printf("IP: ");
	for(i=0;i<64;i++)
	{
	//	printf("%d",ip[i]);
	}
	//printf("\n");
	//printf("L0: ");
	for(i=0;i<32;i++)
	{
	//	printf("%d",L[0][i]);
	}
	//printf("\n");
	for(i=0;i<32;i++)
	{
	//	printf("%d",R[0][i]);
	}
	//printf("\n");
	int E_table[48]={
					32,1,2,3,4,5,
                  	4,5,6,7,8,9,
                  	8,9,10,11,12,13,
                 	12,13,14,15,16,17,
                 	16,17,18,19,20,21,
                 	20,21,22,23,24,25,
                 	24,25,26,27,28,29,
                 	28,29,30,31,32,1
					};
	int sb[17][32];
	for(i=1;i<17;i++)
	{
		int exp_R[48];
		int q;
		for(q=0;q<48;q++)
		{
			exp_R[q]=R[i-1][E_table[q]-1];
		}
		int s_boxes[48];
		for(q=0;q<48;q++)
		{
			s_boxes[q]=keys[i-1][q] ^ exp_R[q];
		}
		
		int s[8][4][16]=
				{
					{
						{14 , 4 ,13 , 1,   2 ,15,  11 , 8 ,  3, 10,   6, 12 ,  5 , 9  , 0 , 7},
      					{0 ,15 ,  7 , 4 , 14 , 2 , 13 , 1 , 10  ,6 , 12 ,11,   9 , 5  , 3,  8},
     					{4  ,1  ,14 , 8 , 13,  6 ,  2, 11,  15, 12 ,  9 , 7 ,  3, 10 ,  5 , 0},
     					{15 ,12 ,  8 , 2  , 4 , 9 ,  1 , 7  , 5, 11 ,  3 ,14 , 10  ,0,   6, 13}
					},
					{
						{15,  1  , 8, 14,   6, 11 ,  3,  4,   9 , 7 ,  2, 13 , 12 , 0 ,  5, 10},
      					{3, 13 ,  4 , 7 , 15 , 2 ,  8, 14 , 12 , 0  , 1 ,10  , 6 , 9,  11 , 5},
     					{0 ,14 ,  7 ,11  ,10,  4,  13 , 1 ,  5,  8 , 12,  6 ,  9 , 3 ,  2 ,15},
     					{13 , 8 , 10  ,1 ,  3 ,15  , 4 , 2 , 11 , 6  , 7, 12  , 0  ,5 , 14 , 9}
					},
					{
						{10 , 0 ,  9, 14 ,  6 , 3,  15 , 5 ,  1, 13 , 12,  7 , 11 , 4 ,  2 , 8},
      					{13 , 7 ,  0 , 9 ,  3,  4,   6, 10,   2 , 8 ,  5, 14 , 12,11 , 15 , 1},
     					{13 , 6  , 4 , 9  , 8 ,15 ,  3 , 0 , 11 , 1 ,  2 ,12 ,  5 ,10 , 14 , 7},
     					{1 ,10  ,13 , 0 ,  6,  9 ,  8  ,7 ,  4 ,15 , 14,  3 , 11 , 5 ,  2 ,12},
					},
					{
						{7 ,13 , 14 , 3  , 0 , 6,   9 ,10,   1 , 2 ,  8 , 5 , 11, 12,   4, 15},
      					{13 , 8 , 11 , 5 ,  6 ,15  , 0 , 3 ,  4 , 7  , 2 ,12 ,  1, 10 , 14 , 9},
     					{10,  6  , 9 , 0 , 12 ,11  , 7, 13,  15, 1 ,  3, 14 ,  5 , 2 ,  8 , 4},
     					{3, 15 ,  0,  6 , 10 ,1 , 13 , 8  , 9,  4 ,  5, 11 , 12 , 7 ,  2, 14}
					},
					{
						{2 ,12 ,  4,  1 ,  7 ,10 , 11,  6,   8 , 5 ,  3, 15,  13 , 0  ,14 , 9},
      					{14, 11 , 2, 12  , 4 , 7,  13,  1 ,  5 , 0 , 15 ,10 ,  3 , 9 ,  8 , 6},
     					{4 , 2  , 1 ,11 , 10 ,13 ,  7 , 8 , 15 , 9 , 12 , 5 ,  6 , 3  , 0 ,14},
     					{11 , 8 , 12 , 7 ,  1 ,14 ,  2 ,13 ,  6 ,15 ,  0 , 9 , 10, 4  , 5 , 3}
					},
					{
						{12,  1 , 10 ,15 ,  9,  2,   6 , 8  , 0, 13 ,  3 , 4 , 14,  7 ,  5, 11},
      					{10 ,15 ,  4 , 2,   7 ,12 ,  9,  5,   6 , 1,  13, 14,   0 ,11 ,  3 , 8},
     					{9 ,14 , 15 , 5 ,  2 , 8 , 12,  3,   7,  0 ,  4, 10 ,  1, 13 , 11 , 6},
     					{4 , 3 ,  2 ,12 ,  9 , 5  ,15, 10  ,11 ,14 ,  1 , 7 ,  6 , 0 ,  8, 13}
					},
					{
						{4 ,11 ,  2 ,14 , 15,  0,   8 ,13  , 3, 12 ,  9 , 7 ,  5, 10 ,  6 , 1},
      					{13 , 0  ,11 , 7  , 4 , 9 ,  1, 10,  14,  3 ,  5, 12  , 2, 15,   8 , 6},
     					{1 , 4  ,11 ,13,  12 , 3 , 7, 14 , 10, 15,   6 , 8 ,  0 , 5 ,  9 , 2},
     					{6 ,11 , 13 , 8 ,  1,  4  ,10 , 7  , 9 , 5,   0, 15 , 14 , 2 ,  3 ,12}
					},
					{
						{13 , 2 ,  8 , 4  , 6, 15 , 11 , 1 , 10 , 9,   3 ,14 ,  5 , 0,  12,  7},
      					{1, 15 , 13 , 8 , 10 , 3 ,  7 , 4 , 12 , 5 ,  6, 11 ,  0 ,14,   9 , 2},
     					{7, 11 ,  4 , 1,   9, 12 , 14,  2 ,  0 , 6,  10, 13,  15 , 3 ,  5 , 8},
     					{2,  1 , 14 , 7,   4 ,10 ,  8 ,13,  15, 12 ,  9 , 0 , 3 , 5,  6, 11}
					},
				};
		
		
		for(q=0;q<48;q=q+6)
		{
			int row;
			int col;
			if(q<6)
			{
				row=s_boxes[0]*2+s_boxes[5];
				col=s_boxes[1]*(2*2*2) + s_boxes[2]*(2*2) + s_boxes[3]*(2)+s_boxes[4];
				int data = s[q/6][row][col];
				int iter=3;
				//int I=(q/6)*4;
				while(data != 0)
				{
					sb[i][iter] = data%2;
					data=data/2;
					iter--;
				}
				while(iter != -1)
				{
					sb[i][iter]=0;
					iter--;
				}
			}
			else if(q<12)
			{
				row=s_boxes[6]*2+s_boxes[11];
				col=s_boxes[7]*(2*2*2) + s_boxes[8]*(2*2) + s_boxes[9]*(2)+s_boxes[10];
				int data = s[q/6][row][col];
				int iter=7;
				//int I=(q/6)*4;
				while(data != 0)
				{
					sb[i][iter] = data%2;
					data=data/2;
					iter--;
				}
				while(iter != 3)
				{
					sb[i][iter]=0;
					iter--;
				}
			}
			else if(q<18)
			{
				row=s_boxes[12]*2+s_boxes[17];
				col=s_boxes[13]*(2*2*2) + s_boxes[14]*(2*2) + s_boxes[15]*(2)+s_boxes[16];
				int data = s[q/6][row][col];
				int iter=11;
				//int I=(q/6)*4;
				while(data != 0)
				{
					sb[i][iter] = data%2;
					data=data/2;
					iter--;
				}
				while(iter != 7)
				{
					sb[i][iter]=0;
					iter--;
				}
			}
			else if(q<24)
			{
				row=s_boxes[18]*2+s_boxes[23];
				col=s_boxes[19]*(2*2*2) + s_boxes[20]*(2*2) + s_boxes[21]*(2)+s_boxes[22];
				int data = s[q/6][row][col];
				int iter=15;
				//int I=(q/6)*4;
				while(data != 0)
				{
					sb[i][iter] = data%2;
					data=data/2;
					iter--;
				}
				while(iter != 11)
				{
					sb[i][iter]=0;
					iter--;
				}
			}
			else if(q<30)
			{
				row=s_boxes[24]*2+s_boxes[29];
				col=s_boxes[25]*(2*2*2) + s_boxes[26]*(2*2) + s_boxes[27]*(2)+s_boxes[28];
				int data = s[q/6][row][col];
				int iter=19;
				//int I=(q/6)*4;
				while(data != 0)
				{
					sb[i][iter] = data%2;
					data=data/2;
					iter--;
				}
				while(iter != 15)
				{
					sb[i][iter]=0;
					iter--;
				}
			}
			else if(q<36)
			{
				row=s_boxes[30]*2+s_boxes[35];
				col=s_boxes[31]*(2*2*2) + s_boxes[32]*(2*2) + s_boxes[33]*(2)+s_boxes[34];
				int data = s[q/6][row][col];
				int iter=23;
				//int I=(q/6)*4;
				while(data != 0)
				{
					sb[i][iter] = data%2;
					data=data/2;
					iter--;
				}
				while(iter != 19)
				{
					sb[i][iter]=0;
					iter--;
				}
			}
			else if(q<42)
			{
				row=s_boxes[36]*2+s_boxes[41];
				col=s_boxes[37]*(2*2*2) + s_boxes[38]*(2*2) + s_boxes[39]*(2)+s_boxes[40];
				int data = s[q/6][row][col];
				int iter=27;
				//int I=(q/6)*4;
				while(data != 0)
				{
					sb[i][iter] = data%2;
					data=data/2;
					iter--;
				}
				while(iter != 23)
				{
					sb[i][iter]=0;
					iter--;
				}
			}
			else
			{
				row=s_boxes[42]*2+s_boxes[47];
				col=s_boxes[43]*(2*2*2) + s_boxes[44]*(2*2) + s_boxes[45]*(2)+s_boxes[46];
				int data = s[q/6][row][col];
				int iter=31;
				//int I=(q/6)*4;
				while(data != 0)
				{
					sb[i][iter] = data%2;
					data=data/2;
					iter--;
				}
				while(iter != 27)
				{
					sb[i][iter]=0;
					iter--;
				}
			}
		
		}
		int j;
		int P[]={
				16,   7 , 20  ,21,
                29,  12 , 28,  17,
                1 , 15,  23 , 26,
                5 , 18 , 31  ,10,
                2 ,  8 , 24,  14,
                32 , 27 ,  3  , 9,
                19 , 13 , 30  , 6,
                22 , 11 ,  4 , 25
			  };
		for(j=0;j<32;j++)
		{
			L[i][j]=R[i-1][j];
			R[i][j]=L[i-1][j] ^ sb[i][P[j]-1];
		}
 	
	}
	
	int RL[64];
	for(i=0;i<64;i++)
	{
		if(i<32)
		{
			RL[i]=R[16][i];
		}
		else
		{
			RL[i]=L[16][i-32];
		}
	}
	//printf("RL: ");
	for(i=0;i<64;i++)
	{
	//	printf("%d",RL[i]); 
	}
	//printf("\n");
	int ip1[64]={
				40  ,   8  , 48   , 16 ,   56 ,  24  ,  64 ,  32,
            39  ,   7  , 47   , 15  ,  55 ,  23 ,   63 ,  31,
            38   ,  6 ,  46  ,  14  ,  54 ,  22  ,  62 ,  30,
            37  ,   5 ,  45  ,  13  ,  53 ,  21  ,  61  , 29,
            36  ,   4 ,  44 ,   12 ,   52 ,  20  ,  60 ,  28,
            35 ,    3  , 43 ,  11   , 51 ,  19   , 59,   27,
            34 ,    2 ,  42  ,  10  ,  50 ,  18 ,   58  , 26,
            33  ,   1 ,  41  ,   9  ,  49 ,  17  ,  57  , 25
				};
	int encrypt[64];
	//printf("Encrypted Text: ");
	for(i=0;i<64;i++)
	{
		encrypt[i]=RL[ip1[i]-1];
	//	printf("%d",encrypt[i]); 
	}
	printf("\n");
	int hex_encrypted[16];
	for(i=0;i<64;i=i+4)
	{
		int j;
		int num=0;
		for(j=0;j<4;j++)
		{
			int x= encrypt[i+j] * power(2,3-(j%4));
			num=num+x;
			//printf("Num: %d\n",num);
		}
		hex_encrypted[i/4]=num;
	}
	//printf("Hexadecimal Encrypted: ");
	for(i=0;i<16;i++)
	{
		//printf("%x",hex_encrypted[i]);
	}
	int status = 0;
	for(i=0;i<16;i++)
	{
		if(hex_encrypted[i] != encrypted[i])
		{
			status=1;
			break;
		}
	}
	if(status == 0)
	{
		printf("\nkey found\n");
		for(i=0;i<64;i++)
		{
			printf("%d",k[i]);
		}
		printf("\n");	
		exit(0);
	}
	printf("\n");	
return;

}

int main(int argc, char *argv[]) {
   time_t start, stop;
   clock_t ticks; long count;
 
   time(&start);
//int main()
//{
	int x=pow(2,16);
	//printf("%d\n",x);
	logic();
	
/*omp_set_num_threads(5);//set the number of threads here...
		#pragma omp parallel
		{
			//#pragma omp for
			
		logic();

		}
*/

 time(&stop);
 
   printf("Used %0.2f seconds of CPU time. \n", (double)ticks/CLOCKS_PER_SEC);
   printf("Finished in about %.0f seconds. \n", difftime(stop, start));
	return 0;	
	
}

// 00000000000000000000000000000000000000000000000000001
//00000000000000000000000000000000000000000000000000000000000
//0000000000000000000000000000000000000000000000000000000000100000
//0000000000000000000000000000000000000000000000000000000000000100
