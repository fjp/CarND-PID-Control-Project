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

  tolerance = 0.2;
  it = 0;
  step = 0;
  iterations = 200;
  i = 0;

  initialize = true;
  increment = true;
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
    err = 0.0;
    p.at(i) += dp.at(i);
    i = (i + 1) % 3;
    increment = true;
    initialize = false;
    cout << "Init Twiddle i = " << i << endl;
  }

  // Update the curren terror
  err += cte*cte;
  step++;

  // for i in range(len(p)) {
  if (step > iterations) {
    double sum = std::accumulate(p.begin(), p.end(), 0, plus<double>());
    cout << "Sum " << sum << endl;
    if (sum > tolerance) {
      cout << "Iteration " << it << ", best error = " << best_err << endl;

      step = 0;

      //x_trajectory, y_trajectory, err = run(robot, p)

      if (err < best_err && increment) {
          best_err = err;
          dp.at(i) *= 1.1;
          err = 0;
          initialize = true;

          cout << "err < best_err && increment = " << increment << endl;
      }
      else {

        if (err > 0.0 && increment == true) {
          p.at(i) -= 2.0 * dp.at(i);
          err = 0.0;
          increment = false;
          cout << "err > 0.0 && increment = " << increment << endl;
        } else {
          //robot = make_robot()
          //x_trajectory, y_trajectory, err = run(robot, p)

          if (err < best_err) {
              best_err = err;
              dp.at(i) *= 1.1;

              cout << "err < best_err" << endl;
          }
          else {
              p.at(i) += dp.at(i);
              dp.at(i) *= 0.9;

              cout << "else" << endl;
          }
          err = 0.0;
          initialize = true;
        }
      }
    }
    it += 1;
  }

}
