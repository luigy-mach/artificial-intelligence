
#include <iostream>

using namespace std;

int i0[3];
int i1[3];
int i2[3];
int i3[3];

double foo(double x){

 return x;
}

double w[3];


void fill_w(double *pw, int n){
 pw[0]=1;
 pw[1]=0.5;
 pw[2]=0.5;
}

void fill_input(int x,int y,int z){
   	
};

double f(int *pi,double *pw, int n){
 double s=0;
 for(int i=0;i<n;i++){
  s=s+(double)pi[i]*pw[i];
 } 	
 return s; 	
} 


void update_w(double w1,double w2){
				
}



void foo(int *pInt){
	int * p = pInt;
	cout<<pInt<<endl;
}

void (*pfoo)(int *pInt);


int main(){
 i0[0]=1; i0[1]=0; i0[2]=0;
 i1[0]=1; i1[1]=0; i1[2]=1;
 i2[0]=1; i2[1]=1; i2[2]=0;
 i3[0]=1; i3[1]=1; i3[2]=1;
 fill_w(w,3);
 	
 int d[4];
 d[0]=1;
 d[1]=1;
 d[2]=1;
 d[3]=0;	

 int temp[4];
 temp[0]=1;
 temp[1]=1;
 temp[2]=1;
 temp[3]=0;	

 int * pInt=NULL;
 cout<<pInt<<endl;
 pfoo=&foo;
 pfoo(pInt);


 return 0;
}
