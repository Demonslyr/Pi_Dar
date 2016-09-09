#include <math.h>
#include <sys/resource.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <vector>

///////////////////////////////////////////////////////////////////
// Conditional Compilation Options
///////////////////////////////////////////////////////////////////
#define USE_TIMING_ITER 100
#define PEAKS 10
#define THRESHOLD 10
//#define MAT_X_DIM 1000
//#define X_LOOP (MAT_X_DIM-1)
//#define MAT_Y_DIM 1000
//#define Y_LOOP (MAT_Y_DIM-1)
//#define NUM_ELEM (MAT_X_DIM * MAT_Y_DIM)

using namespace std;


///////////////////////////////////////////////////////////////////
// Time difference method
///////////////////////////////////////////////////////////////////

timespec diff(timespec start, timespec end)
{
    timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}

///////////////////////////////////////////////////////////////////
// Main method
///////////////////////////////////////////////////////////////////


int main(int argc, char *argv[])
{

	double totalns=0,totals=0,itotalns=0,itotals=0;//timing vars
	struct timespec start, end, tstart, tend,istart, iend, itotal, total;//timing structs
	vector< vector<int> > times;
	vector<int> ltime (1);

int trial=0;
for(int t = 100;t<700;t=t+2)
{
trial++;
//cout<<"Trial "<<trial<<": Array size = "<<t<<endl;
int MAT_X_DIM = t;
int X_LOOP = (MAT_X_DIM-1);
int MAT_Y_DIM = t;
int Y_LOOP = (MAT_Y_DIM-1);
int NUM_ELEM = (MAT_X_DIM * MAT_Y_DIM);

#if USE_TIMING_ITER

for(int p=0; p < USE_TIMING_ITER; p++) {
#endif // USE_TIMING_ITER
	srand (time(NULL));
	int mat[NUM_ELEM];
	for(int i =0; i<NUM_ELEM;i++)
	{
		mat[i] = (rand()%THRESHOLD);	
	}

	for (int i=0;i<PEAKS;i++)
	{
		int x = rand()%NUM_ELEM;
		mat[x]=(rand()%20)+THRESHOLD;
		//cout<<(i+1)<<". Placed "<<mat[x]<<" @ "<<x<<endl;
	}
	//cout<<endl;
	vector< vector<int> > peaks;
	vector<int> peak  (3);
	int a=0,c=0,j=0,l=0;

clock_gettime(CLOCK_REALTIME, &tstart);
//cout<<"before for loops\n";
	for (int b = 1,a=0,c=2;b<Y_LOOP;b++,a++,c++)
	{
//cout<<"loop one\n";
		for(int k=1,j=0,l=2; k<X_LOOP;k++,j++,l++)
		{
//cout<<"loop two\n";
//cout<<"("<<b<<","<<k<<"),a="<<a<<",c="<<c<<",j="<<j<<",l="<<l<<endl;
			if(mat[b*MAT_Y_DIM+k]<THRESHOLD)
			{
			continue;
			}
			if(mat[b*MAT_Y_DIM+j]>=mat[b*MAT_Y_DIM+k])//one left
			{
				continue;
			}
			if(mat[b*MAT_Y_DIM+l]>=mat[b*MAT_Y_DIM+k])//one right
			{
				continue;
			}
			if(mat[a*MAT_Y_DIM+k]>=mat[b*MAT_Y_DIM+k])//one up
			{
				continue;
			}
			if(mat[c*MAT_Y_DIM+k]>=mat[b*MAT_Y_DIM+k])//one down
			{
				continue;
			}
			peak[0]=mat[b*MAT_Y_DIM+k];
			peak[1]=b;
			peak[2]=k;
			peaks.push_back(peak);
		}
	}
	clock_gettime(CLOCK_REALTIME, &tend);
    	total = diff(tstart, tend);
       	totals+=total.tv_sec;
       	totalns+=total.tv_nsec;

/*
cout<<"\n\nDetected Peaks:\n";
	for(int z = 0;z<peaks.size();z++)
	{
		cout<<"\t"<<"Locx: "<<peaks[z][1]<<"Locy: "<<peaks[z][2]<<", Mag: "<<peaks[z][0]<<endl;
	}
*/
}
	#if USE_TIMING_ITER
	//cout<<"\n\nDetected "<<peaks.size()<<" Peaks\n\n";
    	//cout<< "\tTime: "<< (totals)/(USE_TIMING_ITER);
    	//cout<<"sec " << (totalns/(USE_TIMING_ITER))/1000000 <<"msec\n";
	cout<<NUM_ELEM<<","<<(totalns/(USE_TIMING_ITER))/1000000<<",\n";
	//ltime[0] = (totals);
	//ltime[1] = (totalns);
	//times.push_back(ltime);
    #endif // USE_TIMING_ITER
}
//cout<<"Results:\n\n";
for(int y = 0;y<times.size();y++)
{
	//cout<<"\tS: "<<(double)(times[y][0]/(USE_TIMING_ITER))<<" MS: "<<(double)(times[y][1]/(USE_TIMING_ITER))<<endl;
}
}
