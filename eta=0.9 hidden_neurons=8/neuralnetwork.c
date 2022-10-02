#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define tolerance pow(10,-2)
#include<time.h>

int main()
{
	FILE *err,*output,*input,*input1;
	err		=	fopen("error.txt","w");
	output	=	fopen("output.txt","w");
	input	=	fopen("input.txt","r");
	input1	=	fopen("input1.txt","r");
	
	int L,M,N,P,TP,D,p,i,j,k,t,iteration=0;
	float I[200][200],V[200][200],W[200][200],delW[200][200],delV[200][200],IH[200][200],OH[200][200],IO[200][200],OO[200][200],TO[200][200],error,MSE,eta=0.9,maxI[200],minI[200],maxTO[200],minTO[200];
	
	printf("Enter the following inputs:\n");
	
	printf("\nNo of Input Neurons (L):");
	scanf("%d",&L);
	printf("\nNo of Output Neurons (N):");
	scanf("%d",&N);
	printf("\nNo of Training Patterns (P):");
	scanf("%d",&P);
	printf("\nNo of Testing Patterns (TP) :");
	scanf("%d",&TP);
	M = (L + N)*2/3;
	D = P+TP;
	fprintf(output,"No. of Training Patterns (P)=%d\nNo. of Testing Patterns (TP)=%d\nInput Neurons (L)=%d\nHidden Neurons (M)=%d\nOutput Neurons (N)=%d\n\n",P,TP,L,M,N);

	// Scanning Data from Input file
	for(p=1;p<=D;p++)
	{
		for(i=1;i<=L;i++)
		{
			fscanf(input,"%f",&I[i][p]);
		}
	}
	printf("\n\nI[L][D]=I[%d][%d]",L,D);
	fprintf(output,"\n\nI[L][D]=I[%d][%d]",L,D);
	printf("\n");
	fprintf(output,"\n");
	for(i=1;i<=L;i++)
	{
		for(p=1;p<=D;p++)
		{
			printf("%f\t",I[i][p]);
			fprintf(output,"%f\t",I[i][p]);
		}
		printf("\n");
		fprintf(output,"\n");
	}
	
	
	// Connection Weights
	printf("\n\nV[L+1][M]=V[%d][%d]\n",L+1,M);
	fprintf(output,"\n\nV[L+1][M]=V[%d][%d]\n",L+1,M);
	srand(time(NULL));
	for(i=0;i<L+1;i++)
	{
		for(j=1;j<=M;j++)
		{
			//V[i][j]=((double)rand())/((double)RAND_MAX);
			V[i][j] = sin(rand());
		}
	}
	printf("\n");
	fprintf(output,"\n");
	
	for(i=0;i<=L;i++)
	{
		for(j=1;j<=M;j++)
		{
			printf("V[%d][%d]:%f\t",i,j,V[i][j]);
			fprintf(output,"V[%d][%d]:%f\t",i,j,V[i][j]);
		}
		printf("\n");
		fprintf(output,"\n");
	}
	printf("\n");
	fprintf(output,"\n");
	printf("\n\nW[M+1][N]=V[%d][%d]\n",M+1,N);
	fprintf(output,"\n\nW[M+1][N]=W[%d][%d]\n",M+1,N);
	for(j=0;j<M+1;j++)
	{
		for(k=1;k<=N;k++)
		{
			//W[j][k]=((double)rand())/((double)RAND_MAX);
			W[j][k] = sin(rand());
		}
	}
	for(j=0;j<M+1;j++)
	{
		for(k=1;k<=N;k++)
		{
			printf("W[%d][%d]:%f\t",j,k,W[j][k]);
			fprintf(output,"W[%d][%d]:%f\t",j,k,W[j][k]);
		}
		printf("\n");
		fprintf(output,"\n");
	}
	
	
	// Normalizing DataSet
	for(i=1;i<=L;i++)
	{
		maxI[i]=0;minI[i]=0;
		for(p=1;p<=D;p++)
		{
			if(I[i][p]>maxI[i])
			maxI[i]=I[i][p];
			if(I[i][p]<minI[i])
			minI[i]=I[i][p];
		}
	}
	for(p=1;p<=D;p++)
	{
		for(i=1;i<=L;i++)
		{
			I[i][p]=0.1+0.8*((I[i][p]-minI[i])/(maxI[i]-minI[i]));
		}
	}
	printf("\n\nNormalized I[L][D]=I[%d][%d] matrix",L,D);
	fprintf(output,"\n\nNormalized I[L][D]=I[%d][%d] matrix",L,D);
	printf("\n");
	fprintf(output,"\n");
	for(i=1;i<=L;i++)
	{
		for(p=1;p<=D;p++)
		{
			printf("%f\t",I[i][p]);
			fprintf(output,"%f\t",I[i][p]);
		}
		printf("\n");
		fprintf(output,"\n");
	}

	printf("\n\nTO[D][N]=TO[%d][%d]\n\n",D,N);
	fprintf(output,"\nTO[D][N]=TO[%d][%d]\n\n",D,N);
	for(p=1;p<=D;p++)
	{
		for(k=1;k<N+1;k++)
		{
			fscanf(input1,"%f",&TO[k][p]);
			printf("TO[%d][%d]:%f\t",k,p,TO[k][p]);
			fprintf(output,"TO[%d][%d]:%f\t",k,p,TO[k][p]);
		}
		printf("\n");
		fprintf(output,"\n");
	}
	for(k=1;k<N+1;k++)
	{
		maxTO[k]=0;
		minTO[k]=0;
		for(p=1;p<=D;p++)
		{
			if(TO[k][p]>maxTO[k])
			maxTO[k]=TO[k][p];
			if(TO[k][p]<minTO[k])
			minTO[k]=TO[k][p];
		}
	}
	for(p=1;p<=D;p++)
	{
		for(k=1;k<N+1;k++)
		{
			TO[k][p]=0.1+0.8*((TO[k][p]-minTO[k])/(maxTO[k]-minTO[k]));
		}
	}
	printf("\nNOrmalized TO[D][N]=TO[%d][%d] matrix\n\n",D,N);
	fprintf(output,"\n\nNormalized TO[D][N]=TO[%d][%d] matrix\n\n",D,N);
	for(p=1;p<=D;p++)
	{
		for(k=1;k<N+1;k++)
		{
			printf("TO[%d][%d]:%f\t",k,p,TO[k][p]);
			fprintf(output,"TO[%d][%d]:%f\t",k,p,TO[k][p]);
		}
		printf("\n");
		fprintf(output,"\n");
	}
	


	fprintf(output,"\n\nUpdated Connection Weights:\n");
	
	fprintf(err,"\nMSE\tIteration\n");
	// Forward Pass
	do
	{
		iteration++;
		for(p=1;p<=P+1;p++)
		{
			IH[j][p]=0;
			for(j=1;j<M+1;j++)
			{
				for(i=1;i<L+1;i++)
				{
					IH[j][p]=IH[j][p]+(I[i][p]*V[i][j]);
				}
				IH[j][p]=IH[j][p]+(1*V[0][j]);
				OH[j][p]=1.0/(1.0+exp(-IH[j][p]));
				IH[j][p]=0;
			}
			
		}
		printf("\n\n");

		// Calculating Output Layer Output
		for(p=1;p<=P;p++)
		{
			IO[k][p]=0;
			for(k=1;k<N+1;k++)
			{
				for(j=1;j<M+1;j++)
				{
					IO[k][p]+=OH[j][p]*W[j][k];
				}
				IO[k][p]+=(1*W[0][k]);
				OO[k][p]=(exp(IO[k][p])-exp(-1*IO[k][p]))/(exp(IO[k][p])+exp(-1*IO[k][p]));
				IO[k][p]=0;
			}
		}
		
		// Calculating delW
		for(j=0;j<=M;j++)
		{
			for(k=1;k<=N;k++)
			{
				delW[j][k]=0;
				for(p=1;p<=P-5;p++)
				{
					OH[0][p]=1.0;
					delW[j][k]=delW[j][k]+((eta/D)*(TO[k][p]-OO[k][p])*(1-(OO[k][p]*OO[k][p]))*OH[j][p]);
				}
				printf("delW[%d][%d]=%f\t",j,k,delW[j][k]);
			}
			printf("\n");
		}
		printf("\n");

		// Calculating delV
		for(i=0;i<=L;i++)
		{
			for(j=1;j<=M;j++)
			{
				delV[i][j]=0;
				for(p=1;p<=P;p++)
				{
					for(k=1;k<=N;k++)
					{
						I[0][p]=1.0;
						delV[i][j]=delV[i][j]+((eta/(P*N))*((TO[k][p]-OO[k][p])*(1-(OO[k][p]*OO[k][p]))*W[j][k]*OH[j][p]*(1-OH[j][p])*I[i][p]));
					}
				}
				printf("delV[%d][%d]=%f\t",i,j,delV[i][j]);
			}
			printf("\n");
		}
		
		// Calculating MSE
		MSE=0;
		for(p=1;p<=D;p++)
		{
			for(k=1;k<=N;k++)
			{
				error=pow((TO[k][p]-OO[k][p]),2)/2;
				MSE=MSE+error;
			}
		}
		MSE=MSE/(D);
		printf("\n%f\t%d\n",MSE,iteration);
		fprintf(err,"\n%f\t%d\n",MSE,iteration);
		
		
		// Updating Weights
		for(i=0;i<=L;i++)
		{
			for(j=1;j<=M;j++)
			{
				V[i][j]=V[i][j]+delV[i][j];
				printf("V[%d][%d]:%f\t",i,j,V[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		
		
		for(j=0;j<=M;j++)
		{
			for(k=1;k<=N;k++)
			{
				W[j][k]=W[j][k]+delW[j][k];
				printf("W[%d][%d]:%f\t",j,k,W[j][k]);
			}
			printf("\n");
		}
		
	}while(iteration<=300000);
	
		for(i=0;i<=L;i++)
		{
			for(j=1;j<=M;j++)
			{
				fprintf(output,"V[%d][%d]:%f\t",i,j,V[i][j]);
			}
			fprintf(output,"\n");
		}
		fprintf(output,"\n");
		
		
		for(j=0;j<=M;j++)
		{
			for(k=1;k<=N;k++)
			{
				fprintf(output,"W[%d][%d]:%f\t",j,k,W[j][k]);
			}
			fprintf(output,"\n");
		}
		
		
		// Testing
		printf("\n\nIH and OH matrix:\n");
		fprintf(output,"\n\nIH and OH matrix:\n");
				
		for(p=P+1;p<=D;p++)
		{
			IH[j][p]=0;
			for(j=1;j<M+1;j++)
			{
				for(i=1;i<L+1;i++)
				{
					IH[j][p]=IH[j][p]+(I[i][p]*V[i][j]);
				}
				IH[j][p]=IH[j][p]+(1*V[0][j]);
				OH[j][p]=1/(1+exp(-IH[j][p]));
				printf("\nIH[%d][%d]:%f\tOH[%d][%d]:%f",j,p,IH[j][p],j,p,OH[j][p]);
				fprintf(output,"\nIH[%d][%d]:%f\tOH[%d][%d]:%f",j,p,IH[j][p],j,p,OH[j][p]);
				IH[j][p]=0;
			}
			
		}
		printf("\n\n");
		fprintf(output,"\n\n");
		
		
		// Calculating Output Layer Outputs
		printf("Tested Results:");
		fprintf(output,"\nTested Results:\n");
		for(p=P+1;p<=D;p++)
		{
			IO[k][p]=0;
			for(k=1;k<N+1;k++)
			{
				for(j=1;j<M+1;j++)
				{
					IO[k][p]+=OH[j][p]*W[j][k];
				}
				IO[k][p]+=1.0*W[0][k];
				OO[k][p]=(exp(IO[k][p])-exp(-1*IO[k][p]))/(exp(IO[k][p])+exp(-1*IO[k][p]));
				printf("\nIO[%d][%d]:%f\tOO[%d][%d]:%f\tTO[%d][%d]:%f",k,p,IO[k][p],k,p,OO[k][p],k,p,TO[k][p]);
				fprintf(output,"\nIO[%d][%d]:%f\tOO[%d][%d]:%f\tTO[%d][%d]:%f",k,p,IO[k][p],k,p,OO[k][p],k,p,TO[k][p]);
				IO[k][p]=0;
			}
		}
		fprintf(output,"\n\n");
	fclose(input);
	fclose(err);
	fclose(output);
	return 0;
}
