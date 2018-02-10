#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  VectorXd rmse(4);
	rmse << 0, 0, 0, 0;

	if (estimations.size() == 0)
	{
		cout << "Error - estimations size is 0" << endl;
		return rmse;
	}
	if (ground_truth.size() == 0)
	{
		cout << "Error - ground_truth size is 0" << endl;
		return rmse;
	}
	if (ground_truth.size() != estimations.size())
	{
		cout << "Error - ground_truth size and estimates size are not equal" << endl;
		return rmse;
	}

	//accumulate squared residuals
	for (int i = 0; i < estimations.size(); ++i)
	{
		VectorXd res = estimations[i] - ground_truth[i];

		res = res.array() * res.array();
		rmse += res;
	}

	//calculate the mean
	rmse = rmse.array() / estimations.size();

	//calculate the squared root
	rmse = rmse.array().sqrt();

	//return the result
	return rmse;
}