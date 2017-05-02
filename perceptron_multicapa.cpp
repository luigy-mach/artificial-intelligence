
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
	int _limit_iterator;

	void fill_vec_weight(double value, int m);
	void create_vec_weight(int m);
	double foo(double value);
	double sum_fil(int numfil ,int m);
	void update_weights(double temp_desired, double temp_getvalue, int numfil, int tam_vec);


public:
	perceptron(double **mat,int n ,int m ,double ratelearn,int limit_iterator=10000){
		_limit_iterator=limit_iterator;
		_ratelearn=ratelearn;
		_mat=mat;
		_n=n;	  _m=m;
		create_vec_weight(_m-1);
		fill_vec_weight(0,_m-1);
	}
	void learn();
	void learn2();
	void print_vec_weight();

};

void perceptron::create_vec_weight(int m){
	_vec_weight=new double [m];
}

void perceptron::fill_vec_weight(double value, int m){
	for (int i=0; i<m;i++)
		_vec_weight[i]=0;
}

double perceptron::foo(double value){
	return (value<0.5)?0:1;
}

double perceptron::sum_fil(int numfil ,int m){
	double sum=0;
	for(int i=0;i<m;i++)
		sum+=_mat[numfil][i]*_vec_weight[i];
	return sum;
}

void perceptron::learn(){

	double temp_desired;
	double temp_getvalue;
	double temp_value;
	int ite=0;
	int count;
	for(count=0; count<_n, ite<_limit_iterator ;count++,ite++){
		temp_desired = _mat[count][_m-1];
		temp_value = sum_fil(count,_m-1);

		temp_getvalue=foo(temp_value);
		if(temp_desired==temp_getvalue){
			if(count==(_m-1))
				break;
		}else{ //temp_desired!=temp_getvalue
			update_weights(temp_desired,temp_getvalue,count,_m-1);
			if(count==(_m-1))
				count=0;
		}
	}
}

void perceptron::learn2(){

	double temp_desired;
	double temp_getvalue;
	double temp_value;
	int ite=0;
	int count;
	for(count=0; count<_n, ite<_limit_iterator ;count++,ite++){
		temp_desired = _mat[count][_m-1];
		temp_value = sum_fil(count,_m-1);

		temp_getvalue=foo(temp_value);
		if(temp_desired==temp_getvalue){
			if(count==(_m-1))
				break;
		}else{ //temp_desired!=temp_getvalue
			update_weights(temp_desired,temp_getvalue,count,_m-1);
			if(count==(_m-1))
				count=0;
		}
	}
}


void perceptron::update_weights(double temp_desired, double temp_getvalue, int numfil, int tam_vec){
	for (int i=0; i<tam_vec ; ++i)
		_vec_weight[i]+= _ratelearn*(temp_desired-temp_getvalue)*_mat[numfil][i];
}

void perceptron::print_vec_weight(){
	for(int i=0;i<_m-1;i++)
			cout <<" "<< _vec_weight[i];	
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




class layer{

	perceptron * _perceptrons;
	int _num_perceptrons;

public:
	layer * _nextlayer;
	layer * _prevlayer;
	layer(int num_perceptrons){
		_num_perceptrons=num_perceptrons;
		_perceptrons=NULL;
		_nextlayer=NULL;
		_prevlayer=NULL;
	}

};




class multilayer{
	layer * _pRoot;
	layer * _pCurrent;
	layer * _pLast;
	int   * _vec_numlayers;
	int 	_numlayer;
	double **_mat;

public:
	multilayer(double **mat , int n ,int m){
		_pRoot = _pCurrent = _pLast = NULL;
	}
	void init(int num, int *vec_numlayers);
	void insert_layer(layer *pLayer , int num_perceptrons);
};


void multilayer::insert_layer(layer *pLayer , int num_perceptrons){
	if(_pRoot==NULL){
		_pRoot = new layer(num_perceptrons);
		_pCurrent=_pLast=_pRoot;
	}else{
		layer * ptemp = new layer(num_perceptrons);
		ptemp->_prevlayer = _pCurrent;
		_pCurrent = ptemp;
		_pLast = _pCurrent;
	}
}

void multilayer::init(int num, int *vec_numlayers){
	_numlayer=num;
	_vec_numlayers=vec_numlayers;
	for (int i = 0; i < _numlayer; ++i){
		layer * pTemp = new layer(_vec_numlayers[i]);
		insert_layer(pTemp,_vec_numlayers[i]);
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

	int num_layers=3;
	int * layers = new int[num_layers];
	layers[0]=3;layers[1]=2;layers[2]=4;
	multilayer mp();
	mp.init(num_layers,layers);


	return 0;
}
