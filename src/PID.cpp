#include "PID.h"
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  PID::Kp = Kp;
  PID::Ki = Ki;
  PID::Kd = Kd;

  p_error = 0.0;
  i_error = 0.0;
  d_error = 0.0;
}

void PID::UpdateError(double cte, double dt) {
  d_error = (cte - p_error)/dt;
  p_error = cte;
  //cout << "p_error" << p_error << endl;
  i_error += cte*dt;
  //cout << "i_error" << i_error << endl;

  //cout << "d_error" << d_error << endl;

}

double PID::TotalError() {
  double total_error = -Kp * p_error - Kd * d_error - Ki * i_error;
  return total_error;
}
