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
  * Index for parameter array
  */
  int i;

  /*
  * Twiddle iteration
  */
  int it;

  /*
  * Parameters and delta changes
  */
  //std::vector<double> p(3);
  //std::vector<double> dp(3);
  std::vector<double> p { std::vector<double>{0.0, 0.0, 0.0} };
  std::vector<double> dp { std::vector<double>{0.1, 0.01, 0.001} };

  /*
  * Controlles twiddle algorithm
  */
  bool initialize;
  bool increment;



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
  void Tune(double cte, std::vector<double> &p);
};

#endif /* TWIDDLE_H */
