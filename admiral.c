/*
 *  admiral.c
 *  
 *
 *  Created by Jop van Rooij on 13/12/2013.
 *  Copyright 2013 Utrecht University. All rights reserved.
 *
 */

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define Random() ((double)rand()/(double)RAND_MAX)
#define min(a,b) ((a<b) ? a : b)

static int nnodes,nedges;
static int **data=NULL;
static int *valid=NULL;
static int maxpaths;
static int **paths=NULL;

void allocateData()
{	
	int i;
	int size=nnodes+1;
	
	//allocate pointers to pointers to pointers
	if((data=(int **)calloc((size_t)size,sizeof(int *)))==NULL) {
		fprintf(stderr,"NewInt3D: error in memory allocation\n");
		exit(EXIT_FAILURE);
	}
	
	//allocate pointers to pointers
	if((data[0]=(int *)calloc((size_t)(size*size),sizeof(int)))==NULL) {
		fprintf(stderr,"NewInt3D: error in memory allocation\n");
		exit(EXIT_FAILURE);
	}
	
	//set pointers
	for(i=1;i<size;i++) {
		
		data[i]=data[0] + i * size;
	}
	
	printf("data allocated\n");
}

void allocatePaths()
{	
	int i;
	int size=maxpaths+1;
	int size2=pow(2,size);
	
	//allocate pointers to pointers to pointers
	if((paths=(int **)calloc((size_t)size2,sizeof(int *)))==NULL) {
		fprintf(stderr,"NewInt3D: error in memory allocation\n");
		exit(EXIT_FAILURE);
	}
	
	//allocate pointers to pointers
	if((paths[0]=(int *)calloc((size_t)(size*size2),sizeof(int)))==NULL) {
		fprintf(stderr,"NewInt3D: error in memory allocation\n");
		exit(EXIT_FAILURE);
	}
	
	//set pointers
	for(i=1;i<size2;i++) {
		
		paths[i]=paths[0] + i * size;
	}

	
	printf("paths allocated\n");
}

void allocateValid()
{	
	int size=nnodes+1;
	
	//allocate pointers to pointers
	if((valid=(int *)calloc((size_t)(size),sizeof(int)))==NULL) {
		fprintf(stderr,"NewInt3D: error in memory allocation\n");
		exit(EXIT_FAILURE);
	}
}

void resetValid()
{
	int i;
	
	for(i=0;i<=nnodes;i++) {
		valid[i]=0;
	}
}

void resetData()
{
	int i,j;
	for(i=0;i<=nnodes;i++) {
		for(j=0;j<=nnodes;j++) {
			
			data[i][j]=0;
		}
	}
	printf("data reset\n");
	
}

void resetPaths()
{
	int i,j;
	for(i=0;i<=maxpaths;i++) {
		for(j=0;j<=nnodes;j++) {
			
			paths[i][j]=0;
		}
	}
	printf("paths reset\n");
	
}

void findMaxPaths()
{
	int i;
	
	maxpaths=1;
	
	for(i=2;i<=nnodes;i++) {
		maxpaths*=i;
	}
	
}

void setData()
{
	nnodes=6;
	nedges=11;
	
	allocateData();
	allocatePaths();
	allocateValid();
	resetData();
	
	data[1][2]=23;
	data[1][3]=12;
	data[1][4]=99;
	data[2][5]=17;
	data[2][6]=73;
	data[3][5]=3;
	data[3][6]=21;
	data[4][6]=8;
	data[5][2]=33;
	data[5][4]=5;
	data[6][5]=20;
	
	printf("default data set\n");
}

//void addOne(int row_i){
//	int col_i;
//	int carry = 0;
//	
//	for(col_i=maxpaths; col_i>=1; col_i--){
//		if(col_i == maxpaths){
//			paths[row_i+1][col_i] = 1 ^ paths[row_i][col_i];
//			if paths[row_i][col_i] == 1
//				carry = 1;
//		}
//		else { 
//			
//		}
//		
//	}
//}

//void setPaths()
//{
//	int path_i, node_i;
//	for(path_i=1; path_i<=maxpaths; path_i++){
//		int cost = 0;
//		for(node_i=1; node_i<=nnodes; node_i++){
//			if 
//				}
//		
//		
//		
//	}
//}




int goForIt()
{
	int ship1,ship2;
	int mincost,cost;
	int i,step;
	int destination;
	
	
	ship1=1;
	ship2=1;
	
	mincost=100000000; //make better
	
	for(i=1;i<=10000000;i++) {
		
		ship1=1;
		ship2=1;
		cost=0;
		
		resetValid();
		
		for(step=1;step<=nnodes;step++) {
			
			if(ship1!=nnodes && ship1!=-1) {
				
				destination=1+rint(Random()*(nnodes-1));
				
				if((valid[destination]==0 && data[ship1][destination]) || (destination==nnodes && data[ship1][destination])) {
					
					cost+=data[ship1][destination];
					ship1=destination;
					valid[destination]=1;
				}
				else ship1=-1;
			}
			
			if(ship2!=nnodes && ship2!=-1) {
				
				destination=1+rint(Random()*(nnodes-1));
				
				if((valid[destination]==0 && data[ship2][destination]) || (destination==nnodes && data[ship2][destination])) {
					
					cost+=data[ship2][destination];
					ship2=destination;
					valid[destination]=1;
				}
				else ship2=-1;
			}
		}
		
		if(ship1==nnodes && ship2==nnodes) {
			mincost=min(cost,mincost);
		}
	}
	
	return mincost;
}


int main(){
	setData();
	printf("Total cost = %d\n", goForIt());
	return 0;
}
