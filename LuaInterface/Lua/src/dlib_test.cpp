#include <stdlib.h>
#include <iostream>

#include "dlib_test.h"

using namespace std;
using namespace dlib;


// returns a std::vector or predictions
static std::vector<float> dlib_example() {
	// based on http://dlib.net/dnn_introduction_ex.cpp.html

	std::vector<float> ret;

	using net_type = loss_multiclass_log<
		fc<1,
		relu<fc<2,
		input<matrix<double, 1, 2>>
		>>>>;

	// So with that out of the way, we can make a network instance.
	net_type net;
	// And then train it using the MNIST data.  The code below uses mini-batch stochastic
	// gradient descent with an initial learning rate of 0.01 to accomplish this.
	dnn_trainer<net_type> trainer(net);
	trainer.set_learning_rate(0.01);
	trainer.set_min_learning_rate(0.00001);
	trainer.set_mini_batch_size(1);
	trainer.be_verbose();




	matrix<double, 1, 2> in0;
	in0 = 0.0, 0.0;
	matrix<double, 1, 2> in1;
	in1 = 1.0, 0.0;
	matrix<double, 1, 2> in2;
	in2 = 0.0, 1.0;
	matrix<double, 1, 2> in3;
	in3 = 1.0, 1.0;
	matrix<double, 1, 1> out0;
	out0 = 0.0;
	matrix<double, 1, 1> out1;
	out1 = 1.0;
	matrix<double, 1, 1> out2;
	out2 = 1.0;
	matrix<double, 1, 1> out3;
	out3 = 0.0;

	std::vector<matrix<double, 1, 2>> in = { in0, in1, in2, in3 };
	std::vector<unsigned long> out = { 0, 1, 1, 0 };

	trainer.train(in, out);

	// check the output of the network
	std::vector<unsigned long> predicted_labels = net(in);
	for (size_t i = 0; i < predicted_labels.size(); ++i)
	{
		ret.push_back(predicted_labels[i]);
	}


	return ret;
}



