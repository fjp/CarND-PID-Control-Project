# PID parameters

P is the proportinal gain of the controller which penalizes deviations from the center lane, also known as cross track error (cte).
I is the integral gain and is used to reduce the steady offset errors. This part is used to reduce past errors caused by unmodeled disturbances.
D is the differential gain, which penalizes strong changes in the cross track error. Therefore it compensates "future" errors.

# PID tuning

The parameters were tuned manually, starting with the P component. Therfore this term was increased until the
vehicle stayed in the center of the lane. Furthermore it was kept small enought to avoid instable behavior.
Afterwards the D term was increased slightly and was kept low to avoid oscillating behavior of the steering.
Finally the I component was increased until the cross track error was reduced further.

For fine tuning, the taught twiddle algorithm from the udacity lessons was used.
This led to the following parameters of the pid controller.

Kp: 0.22 Ki: 0.0189, Kd: 0.0058165

Furthermore the throttle is controlled by another P controller which sets the speed to 35 mph and slows down if the cross track error gets too large.

# Additional reading

- [PID Controller](https://en.wikipedia.org/wiki/PID_controller)