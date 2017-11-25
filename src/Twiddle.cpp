#include "Twiddle.h"
#include <iostream>
#include <limits>

using namespace std;

Twiddle::Twiddle() {
  double p[3] = {0.0, 0.0, 0.0};
  double dp[3] = {1.0, 1.0, 1.0};

  double best_err = std::numeric_limits<double>::max();
  double err = 0.0;

  double tolerance = 0.2;
  int it = 0;
  int step = 0;
  int max_steps = 200;
  int i = 0;

  bool initialize = true;
  bool increment = true;
  bool revert = true;
}

Twiddle::~Twiddle() {}

void Twiddle::Restart(uWS::WebSocket<uWS::SERVER> ws){
  std::string reset_msg = "42[\"reset\",{}]";
  ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
}


double[] Twiddle::Tune(double cte) {
  //x_trajectory, y_trajectory, best_err = run(robot, p)

  if (sum(dp) > tolerance) {

    err += cte*cte;

    // for i in range(len(p)) {
    if (step > max_steps) {
      cout << "Iteration " << it << ", best error = " << best_err << endl;

      if (true == initialize) {
        p[i] += dp[i];
        i = (i + 1) % 3;
        step = 0;
        initialize = false;
        increment = true;
        revert = true;
      }

      //x_trajectory, y_trajectory, err = run(robot, p)

      else {
        if (err < best_err && increment) {
            best_err = err;
            dp[i] *= 1.1;
            err = 0;
            initialize = true;
        }
        else {
          if (revert) {
            p[i] -= 2 * dp[i]
            revert = false;
            increment = false;
          }
          //robot = make_robot()
          //x_trajectory, y_trajectory, err = run(robot, p)

          if (err < best_err) {
              best_err = err
              dp[i] *= 1.1
              err = 0
              increment = false;
              initialize = true;
          }
          else {
              p[i] += dp[i]
              dp[i] *= 0.9
          }
        }
      }
    }

    it += 1
    }
  return p

}
