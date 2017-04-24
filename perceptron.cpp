
#include <iostream>
#include <vector>

using namespace std;



class Perceptron {
	vector<double> v_inputs;
	vector<double> v_weights;

	double _y;
	double _d;

	int num_inputs;
	void init();	
	void init2();	

	double error;

public:
	Perceptron(int num_in){
			fill_weight(num_inputs+1, 0);
			error=-2;
	};
	Perceptron(vector<double> v_in, int num_in, double d){
		_d=d;
		num_inputs=num_in;
		v_inputs=v_in;
		error=-2;
		init();
	};

 	void push_new(vector<double> v_in, int num_in, double d){
		_d=d;
		num_inputs=num_in;
		v_inputs=v_in;
		//init2();
	};

	double times(double a, double b);
	void learn();
	//void set_inputs(vector<double> v_in);
	void set_weights_plus_one(vector<double> weights);
	vector<double> get_weights(){return v_weights;};
	double get_y(){return _y;};

	void fill_vector(vector<double>& v_in, int num_in, int fillwith);
	void fill_weight(int num_in, int fillwith);
	double dot(vector<double> a,vector<double> b);
	double get_d(){return _d;};
	void update(double obt);
	double get_error(){return error;};
};

void Perceptron::fill_vector(vector<double>& v_in, int num_in, int fillwith){
	for(int i;i<num_in;i++){
		v_in.push_back(fillwith);
	}
}
void Perceptron::fill_weight(int num_in, int fillwith){
	for(int i=0;i<num_in;i++){
		//cout<<"!!!!!!"<<v_weights.size()<<endl;	
		v_weights.push_back(fillwith);
	}
}

double Perceptron::times(double a, double b){
	return a*b;
}

double Perceptron::dot(vector<double> a, vector<double> b){
	double product=0.0;
	for(int i=0; i<num_inputs+1 ;i++){
		product+=a[i]*b[i];
	}
	return product;
}

void Perceptron::learn(){
	_y = dot(v_weights,v_inputs); 
	return;
}


void Perceptron::update(double obt){
	for(int i=0;i<v_weights.size();i++){
		error=_d-obt;
		v_weights[i]=v_weights[i]+0.9*error*v_inputs[i];

	}
	learn();
}

void Perceptron::init(){
	fill_weight(num_inputs+1, 0.5);
	v_inputs.push_back(1); 
	learn();
	//_y = dot(v_weights,v_inputs); 
}

void Perceptron::init2(){
	v_inputs.push_back(1); 
	learn();
}


void Perceptron::set_weights_plus_one(vector<double> weights){
	v_weights.clear();
	v_weights=weights;
	//v_weights.push_back(1);
}



void  learn(int apren){
	//AND
	vector<double> vec1;
	vec1.push_back(1);vec1.push_back(1);vec1.push_back(1);
	vector<double> vec2;
	vec2.push_back(0);vec2.push_back(1);vec2.push_back(0);
	vector<double> vec3;
	vec3.push_back(1);vec3.push_back(0);vec3.push_back(0);
	vector<double> vec4;
	vec4.push_back(0);vec4.push_back(0);vec4.push_back(0);

	vector< vector<double> > mat;
	mat.push_back(vec1);
	mat.push_back(vec2);
	mat.push_back(vec3);
	mat.push_back(vec4);


	int m=4;
	int n=2;

	/////////////////////////////
	Perceptron p(2);	
	//cout<<">>>"<<p.get_y()<<endl;
	for(int i=0;i<apren;i++){
		for(int j=0;j<m;j++){
			p.push_new(mat[j],n,mat[j][2]);
			double d= p.get_y();
			p.update(d);
		}
	}
/*
	vector<double> temp;
	temp=p.get_weights();
	for(int i=0;i<temp.size();i++){
		cout<<"> "<<temp[i]<<endl;
	}
*/

		cout<<p.get_error()<<endl;

}


int main(){
	
	learn(26);


	return 0;
}
