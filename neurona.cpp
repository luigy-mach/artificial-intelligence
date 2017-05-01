
/*	Ciencia de la Computación
	Luigy Machaca
	Arequipa-Perú
*/


#include <iostream>
#include <vector>

using namespace std;


class perceptron {
	double **_mat;
	int _n;
	int _m;
	double _ratelearn;
	double *_vec_weight;

	void fill_vec_weight(double value, int m);

	void create_vec_weight(int m);

	double foo(double value);
	void update_weights(double *vweight);

public:
	perceptron(double **mat,int n ,int m ,double ratelearn){
		_ratelearn=ratelearn;
		_mat=mat;
		_n=n;	  _m=m;

		create_vec_weight(_m-1);
		fill_vec_weight(0,_m-1);
	}

	void learn();

	void print_vec_weight();

};

void perceptron::create_vec_weight(int m){
	_vec_weight=new double [m];
}

void perceptron::fill_vec_weight(double value, int m){
	for (int i=0; i<m;i++){
		_vec_weight[i]=0;
	}
	
}

double perceptron::foo(double value){
	return (value<0.5)?0:1;
}


void perceptron::learn(){

	double temp_desired;
	double temp_getvalue;
	double temp_value;

	int count;
	int ite=0;
	for(count=0; count<_n, ite<50 ;count++/*,ite++*/){
		temp_desired=_mat[count][3];
		temp_value= _mat[count][0]*_vec_weight[0]+ 
					_mat[count][1]*_vec_weight[1]+
					_mat[count][2]*_vec_weight[2];

		temp_getvalue=foo(temp_value);
		if(temp_desired==temp_getvalue){
			if(count==(_m-1))
				break;
		}else{ //temp_desired!=temp_getvalue

			_vec_weight[0]+= _ratelearn*(temp_desired-temp_getvalue)*_mat[count][0];
			_vec_weight[1]+= _ratelearn*(temp_desired-temp_getvalue)*_mat[count][1];
			_vec_weight[2]+= _ratelearn*(temp_desired-temp_getvalue)*_mat[count][2];
			if(count==(_m-1))
				count=0;
		}
	}
}


void perceptron::print_vec_weight(){
	for(int i=0;i<_m-1;i++){
			cout <<" "<< _vec_weight[i];	
	}
	cout<<endl;
}

//-----Funciones

void create_mat(double **& mat,int n ,int m){
        mat = new double*[n];
        for(int i=0;i<n;i++){
           mat[i]=new double[m];
        }
}

void print_mat(double **& mat,int n ,int m){
        
        for(int i=0;i<n;i++){
        	for (int j = 0; j < m; ++j)
        	{
        		cout <<" "<< mat[i][j];
        	}
        	cout<<endl;
        }
}


int main(){
	
	double **mat=NULL;
	int n=4;
	int m=4;
	create_mat(mat,n,m);

	mat[0][0]=1;mat[0][1]=0;mat[0][2]=0;mat[0][3]=0;
	mat[1][0]=1;mat[1][1]=0;mat[1][2]=1;mat[1][3]=0;
	mat[2][0]=1;mat[2][1]=1;mat[2][2]=0;mat[2][3]=0;
	mat[3][0]=1;mat[3][1]=1;mat[3][2]=1;mat[3][3]=1;

	double rateup=0.5;
    cout<< "-----------MAT 1------------- "<<endl;
	print_mat(mat,n,m);
    cout<< "----------------------------- "<<endl;

	perceptron pp(mat,n,m,rateup);
	cout<< "------------PESOS 1------------ "<<endl;
    pp.print_vec_weight();

	pp.learn();

    cout<< "-----------MAT 2------------- "<<endl;
	print_mat(mat,n,m);
    
    cout<< "------------PESOS 2------------ "<<endl;
    pp.print_vec_weight();


	return 0;
}
