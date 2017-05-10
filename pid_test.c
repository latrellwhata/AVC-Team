#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

bool has_run_once = false;
double last_error_value;
long last_error_time;
double total_error = 0;

double kp = 100;
double ki = 1;
double kd = 10;

double choose_velocities_pid(double error) {
  // Get the current time
  struct timeval now;
  gettimeofday(&now, 0);
  long error_time = now.tv_sec * 1000 * 1000 + now.tv_usec; // Combine sec and usec components

  double p = error;
  double d;

  // If this is our first error reading, we can't calculate the rate of change
  // of the error, so just assume it's zero.
  if (has_run_once) {
    d = (error - last_error_value) / (error_time - last_error_time) * 1000 * 1000;
    total_error += error / (error_time - last_error_time) * 1000 * 1000;
  } else {
    d = 0;
    has_run_once = true;
  }

  // Record the error and time for next time
  last_error_value = error;
  last_error_time = error_time;

  printf("p: %lf\ti: %lf\td: %lf\n", kp * p, ki * total_error, kd * d);

  // Apply coefficients and return
  return kp * p + kd * d;
}

int main() {
  printf("0: %lf\n", choose_velocities_pid(0));
  usleep(500 * 1000);
  printf("0.5: %lf\n", choose_velocities_pid(0.5));
  usleep(500 * 1000);
  printf("-0.5: %lf\n", choose_velocities_pid(-0.5));
  usleep(500 * 1000);
  printf("0.5: %lf\n", choose_velocities_pid(0.5));
}
