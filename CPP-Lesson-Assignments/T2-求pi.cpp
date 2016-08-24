#include<iostream>
#include<cstdlib>
using namespace std;
int main()
{
    int N=1000000,M=0;
    int i,j=1;
    double pi=100.0,residual=100.0,e=0.0000001,x=0.0,y=0.0,pi1=100.0;
    
    while(residual>e)
    {
        for(i=0;i<N;i++)
        {
            double x=double(rand())/double(RAND_MAX);
            double y=double(rand())/double(RAND_MAX);
            if(x*x+y*y<=1)
                ++M;
        }
      
        pi1=4*(double)M/(j*N);
        if(pi>=pi1)
            residual=pi-pi1;
        else
            residual=pi1-pi;
        pi=pi1;
        j++;
    }
    cout<<"The pi is "<<pi<<endl;
    return 0;
}

