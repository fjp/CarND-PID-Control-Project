#include "Twiddle.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <vector>

using namespace std;

Twiddle::Twiddle() : p(3) {
  //p = {0.0, 0.0, 0.0};
  //dp = {1.0, 1.0, 1.0};

  best_err = std::numeric_limits<double>::max();

  err = 0.0;

  tolerance = 0.001;
  it = 0;
  step = 0;
  iterations = 200;
  i = -1;

  initialize = true;
  increment = true;
  finish = false;
}

Twiddle::~Twiddle() {}

void Twiddle::Restart(uWS::WebSocket<uWS::SERVER> ws){
  std::string reset_msg = "42[\"reset\",{}]";
  ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
}


void Twiddle::Tune(double cte, std::vector<double> &p) {
  //x_trajectory, y_trajectory, best_err = run(robot, p)

  //cout << "first best_err " << best_err << endl;

  if (true == initialize) {
    // for i in range(len(p)) {
    i = (i + 1) % 3;
    err = 0.0;
    p.at(i) += dp.at(i);
    increment = true;
    initialize = false;
    if (0 == i)
      cout << "Init Twiddle, tuning Kp" << endl;
    else if (1 == i)
      cout << "Init Twiddle, tuning Ki" << endl;
    else if (2 == i)
      cout << "Init Twiddle, tuning Kd" << endl;
  }

  // Update the current error
  err += cte*cte;
  step++;

  if (step > iterations && !finish) {
    // while sum(dp) > tol
    //double sum = std::accumulate(dp.begin(), dp.end(), 0, plus<double>());
    double sum = dp.at(0) + dp.at(1) + dp.at(2);
    cout << "Sum " << sum << endl;
    if (sum > tolerance) {
      cout << "Iteration " << it << ", best error = " << best_err << endl;

      err = err/step;
      step = 0;

      //x_trajectory, y_trajectory, err = run(robot, p)

      if (err < best_err && increment) {
          best_err = err;
          dp.at(i) *= 1.1;
          err = 0.0;
          initialize = true;

          cout << "err < best_err --> increment" << endl;
      }
      else {

        if (err > 0.0 && increment == true) {
          p.at(i) -= 2.0 * dp.at(i);
          err = 0.0;
          increment = false;
          cout << "err > best_err --> reset/reduce current parameter and rerun" << endl;
        } else {
          //robot = make_robot()
          //x_trajectory, y_trajectory, err = run(robot, p)

          if (err < best_err) {
              best_err = err;
              dp.at(i) *= 1.1;

              cout << "Now err < best_err" << endl;
          }
          else {
              p.at(i) += dp.at(i);
              dp.at(i) *= 0.9;

              cout << "err is still larger than best_err, use smaller step size" << endl;
          }
          err = 0.0;
          initialize = true;
        }
      }
    } else {
      finish = true;
      std::cout << "Twiddle finished and found the following optimal parameters:" << std::endl;
      std::cout << "Kp: " << p.at(0) << " Ki: " << p.at(1) << ", Kd: " << p.at(2)  << std::endl;
    }
    if (!finish) {
      it += 1;
      std::cout << "Kp: " << p.at(0) << " Ki: " << p.at(1) << ", Kd: " << p.at(2)  << std::endl;
    }
  }

}
