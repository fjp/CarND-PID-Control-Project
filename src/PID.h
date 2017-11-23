#ifndef PID_H
#define PID_H

#include <uWS/uWS.h>

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */
  double Kp;
  double Ki;
  double Kd;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte, double dt);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  /*
  * Find tuned PID parameters.
  */
  void Twiddle(double tol, uWS::WebSocket<uWS::SERVER> ws);

  /*
  * Reset the simulator.
  */
  void Restart(uWS::WebSocket<uWS::SERVER> ws);
};

#endif /* PID_H */
