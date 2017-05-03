
/*	Ciencia de la Computación
	Luigy Machaca
	Arequipa-Perú
*/

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

#define EULER 2.71828


///////////foo
double my_foo(double value){
	return 1/(1+pow(EULER,-1*value));
}
//////


class perceptron {
	int _tamIn;
	int _sum_dot;
	double *_vec_weight;

	void fill_vec_weight(double value, int tamIn);
	void create_vec_weight(int tamIn);


public:
	perceptron(int tamIn){
		_tamIn=tamIn;
		_sum_dot=0;
		create_vec_weight(_tamIn);
		fill_vec_weight(0,_tamIn);
	}
	double *get_vec_weight(){return _vec_weight;}
	void set_sum_dot(double value){_sum_dot=value;}

};


void perceptron::create_vec_weight(int tamIn){
	_vec_weight=new double [tamIn];
}

void perceptron::fill_vec_weight(double value, int tamIn){
	for (int i=0; i<tamIn;i++)
		_vec_weight[i]=0;
}





class layer{

	perceptron ** _perceptrons;
	double * _vec_outputs;
	int _num_perceptrons;
	int _tamIn;
	void create_vec_outputs();
	void fill_vec_outputs(int value);
	void learn(double *vec_inputs, double(*pFoo)(double));
	double vec_dot(double *a, double *b, int tam);
	

public:

	int _my_num_layer;

	layer * _nextlayer;
	layer * _prevlayer;
		

	layer(int num_perceptrons, int tamIn){
		_my_num_layer=-1;
		_num_perceptrons = num_perceptrons;
		_tamIn = tamIn;
		_perceptrons = NULL;
		_nextlayer = _prevlayer = NULL;
		init_layer();
	}

	void init_layer();
	double get_num_perceptrons(){return _num_perceptrons;}
	void forward_propagation(double *vec_inputs, double(*pFoo)(double));
	void back_propagation(double *vec_inputs, double(*pFoo)(double));
	void print_layer();


};

void layer::init_layer(){
	_perceptrons = new perceptron*[_num_perceptrons];
	create_vec_outputs();
	fill_vec_outputs(0);

	for(int i=0;i<_num_perceptrons;i++){
		perceptron * ptemp = new perceptron(_tamIn);
		_perceptrons[i]=ptemp;
	}	

}

void layer::create_vec_outputs(){
	_vec_outputs = new double[_num_perceptrons];
}

void layer::fill_vec_outputs(int value){
	for(int i=0;i<_num_perceptrons;i++)
		_vec_outputs[i]=value;
}

double layer::vec_dot(double *a, double *b, int tam){
	double dot;
	for(int i=0;i<tam;i++){
		dot+=a[i]*b[i];
	}
}

void layer::learn(double *vec_inputs, double(*pFoo)(double)){
	for(int i=0;i<_num_perceptrons;i++){
		double sum  = vec_dot(vec_inputs,_perceptrons[i]->get_vec_weight(),_tamIn);
		_perceptrons[i]->set_sum_dot(sum);
		_vec_outputs[i] = pFoo(sum);
	}
}


void layer::forward_propagation(double *vec_inputs, double(*pFoo)(double)){
	learn(vec_inputs, pFoo);
	print_layer();
	if(_nextlayer){
		_nextlayer->forward_propagation(_vec_outputs, pFoo);
	}
}

void layer::back_propagation(double *vec_inputs, double(*pFoo)(double)){
	learn(vec_inputs, pFoo);
	print_layer();
	if(_nextlayer){
		_nextlayer->forward_propagation(_vec_outputs, pFoo);
	}
}



void layer::print_layer(){
	cout<< "------------------------------"<<endl;
	cout<< "layer_ "<<_my_num_layer<<endl;

	for(int i=0;i<_num_perceptrons;i++){
		cout<<_vec_outputs[i]<<" ";
	}
	cout<<endl;
	cout<< "------------------------------"<<endl;
}






class multilayer{
	layer * _pRoot;
	layer * _pLast;
	int 	_numlayers;

	int _tamIn;
	void insert_layer(layer *pLayer);

public:
	multilayer(int tam_inputs){
		_tamIn=tam_inputs;
		_pRoot = _pLast = NULL;
	}
	void init(int num_layers, int *vec_tamlayers, int *vec_tamIn);
	void training(double *vec_inputs, double(*pFoo)(double));
};

void multilayer::insert_layer(layer *pLayer){
	if(_pRoot==NULL){
		_pRoot = _pLast = pLayer;
	}else{
		pLayer->_prevlayer = _pLast;
		_pLast->_nextlayer = pLayer;
		_pLast = pLayer;

	}
}


void multilayer::init(int num_layers, int *vec_tamlayers, int *vec_tamIn){
	_numlayers=num_layers;
	for (int i = 0; i < _numlayers; i++){
		layer * pTemp = new layer(vec_tamlayers[i],vec_tamIn[i]);
		pTemp->_my_num_layer=i;
		insert_layer(pTemp);
	}

}

void multilayer::training(double *vec_inputs, double(*pFoo)(double)){
	layer *pCurrentLayer=_pRoot;
	pCurrentLayer->forward_propagation(vec_inputs, pFoo);
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
	
	/*double **mat=NULL;
	int n=4;
	int m=3; // el sobrant es el resultado

	create_mat(mat,n,m);

	mat[0][0]=1;mat[0][1]=0;mat[0][2]=0;mat[0][3]=0;
	mat[1][0]=1;mat[1][1]=0;mat[1][2]=1;mat[1][3]=0;
	mat[2][0]=1;mat[2][1]=1;mat[2][2]=0;mat[2][3]=0;
	mat[3][0]=1;mat[3][1]=1;mat[3][2]=1;mat[3][3]=1;*/

	double **mat=NULL;
	int n=4;
	int m=2; // el sobrant es el resultado


	create_mat(mat,n,m);

	mat[0][0]=0;mat[0][1]=0;mat[0][2]=0;
	mat[1][0]=0;mat[1][1]=1;mat[1][2]=1;
	mat[2][0]=1;mat[2][1]=0;mat[2][2]=1;
	mat[3][0]=1;mat[3][1]=1;mat[3][2]=0;


	int num_layers=m;
	int * tam_layers = new int[num_layers];
	tam_layers[0]=3;tam_layers[1]=1;//tam_layers[2]=2;

	int * in_layers = new int[num_layers];
	in_layers[0]=2;in_layers[1]=3;//in_layers[2]=2;

	multilayer mp(m);
	mp.init(num_layers,tam_layers, in_layers);
	for(int i=0;i<n;i++)
		mp.training(mat[i],&my_foo);


	return 0;
}
