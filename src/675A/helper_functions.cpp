#include "main.h"
using namespace pros;
int get_flywheel_temp() { return flywheel.get_temperature(); }
int get_intake_temp() { return intake.get_temperature(); }
double get_flywheel_velocity() { return flywheel.get_actual_velocity(); }
void flywheel_power(double percent) { flywheel.move(120 * percent); }
void intake_power(double percent) { intake.move(120 * percent); }
void feedforward_control_function(double target_speed) {
  currentVelocity = get_flywheel_velocity();
  error = target_speed - currentVelocity;
  derivative = error - lastError;
  integral = integral + error;
  power =
      (kP * error) + (kI * integral) + (kD * derivative) + (target_speed * kF);
  flywheel.move_voltage(power);
  std::cout << voltage << std::endl;
  lastError = error;
}
void pid_control(double target_value) {
  double kP1 = .5;
  double kV1 = 2;
  double error = target_value - get_flywheel_velocity();
  double output = kP1 * error - kV1 * target_value;
  flywheel.move_voltage(output);
}
void joseph_code(double input) {
  
}
void autonomous_data_export() {
  while (true) {
    master.print(0, 0, "Alliance: %s", alliance);
    pros::delay(50);
    master.print(1, 0, "Fly Speed: %f",
                 abs(flywheel.get_actual_velocity() / 10) * 60);
    pros::delay(50);
    master.print(2, 0, "Fly: %i | Int: %i", get_flywheel_temp(),
                 get_intake_temp());
    pros::delay(250);
  }
}
void driver_data_export() {
  while (true) {
    master.print(0, 0, "Drive: %s", drive_lock_type);
    pros::delay(50);
    master.print(1, 0, "Fly Speed: %f",
                 abs(flywheel.get_actual_velocity() / 10) * 60);
    pros::delay(50);
    master.print(2, 0, "Fly: %i | Int: %i", get_flywheel_temp(),
                 get_intake_temp());
    pros::delay(250);
  }
}
