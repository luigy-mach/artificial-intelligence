
#include <iostream>
#include <vector>

using namespace std;



class Perceptron {
	vector<double> v_inputs;
	vector<double> v_weights;

	double _y;

	int num_inputs;
	void init();	

public:
	Perceptron(){};
	Perceptron(vector<double> v_in, int num_in){
		num_inputs=num_in;
		v_inputs=v_in;
		init();
		cout<<"-----"<<endl;
	};
	double times(double a, double b);
	void learn();
	//void set_inputs(vector<double> v_in);
	void set_weights(vector<double> weights);
	vector<double> get_weights(){return v_weights;};
	double get_y(){return _y;};

	void fill_vector(vector<double>& v_in, int num_in, int fillwith);
	double dot(vector<double> a,vector<double> b);
};

void Perceptron::fill_vector(vector<double>& v_in, int num_in, int fillwith){
	for(int i;i<num_in;i++){
		v_in.push_back(fillwith);
	}
}

double Perceptron::times(double a, double b){
	return a*b;
}
double Perceptron::dot(vector<double> a,vector<double> b){
	double product=0.0;
	for(int i=0;i<num_inputs+1;i++){
		product+=a[i]*b[i];
		cout<<product<<endl;
	}
	return product;
}

void Perceptron::learn(){
	_y = dot(v_weights,v_inputs); 
}

void Perceptron::init(){
	fill_vector(v_weights,num_inputs+1,0);
	v_inputs.push_back(1); 
	learn();
}


void Perceptron::set_weights(vector<double> weights){
	v_weights.clear();
	v_weights=weights;
	//v_weights.push_back(1);
}


int main(){

	vector<double> nw;
	nw.push_back(1); nw.push_back(1); nw.push_back(1);

	vector<double> a;
	a.push_back(1); a.push_back(1);
	//a.push_back(0); a.push_back(1);
	//a.push_back(1); a.push_back(0);
	//a.push_back(1); a.push_back(1);

	Perceptron p(a,2);
	p.set_weights(nw);
	p.learn();
	cout<<">>>"<<p.get_y()<<endl;
	



	return 0;
}
