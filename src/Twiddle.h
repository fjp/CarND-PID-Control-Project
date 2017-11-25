#ifndef TWIDDLE_H
#define TWIDDLE_H

#include <uWS/uWS.h>

class Twiddle {
public:
  /*
  * Errors
  */
  double best_err;
  double err = 0.0;

  /*
  * Tolerance criteria to stop twiddle
  */
  double tolerance;

  /*
  * Steps of the simulator and maximum number of iterations
  */
  int step;
  int iterations;

  /*
  * Parameters and delta changes
  */
  double p[3];
  double dp[3];


  /*
  * Constructor
  */
  Twiddle();

  /*
  * Destructor.
  */
  virtual ~Twiddle();

  /*
  * Reset the simulator.
  */
  void Restart(uWS::WebSocket<uWS::SERVER> ws);


  /*
  * Find tuned PID parameters
  */
  double[] Tune();
};

#endif /* TWIDDLE_H */
