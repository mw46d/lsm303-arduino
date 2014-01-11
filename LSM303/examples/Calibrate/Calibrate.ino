#include <Wire.h>
#include <LSM303.h>

LSM303 compass;
LSM303::vector<int16_t> running_min = {32767, 32767, 32767}, running_max = {-32768, -32768, -32768};

void setup() {
  SerialUSB.begin();
  Wire.begin(14, 15);
  compass.init();
  compass.enableDefault();
}

void loop() {  
  compass.read();
  
  running_min.x = min(running_min.x, compass.m.x);
  running_min.y = min(running_min.y, compass.m.y);
  running_min.z = min(running_min.z, compass.m.z);

  running_max.x = max(running_max.x, compass.m.x);
  running_max.y = max(running_max.y, compass.m.y);
  running_max.z = max(running_max.z, compass.m.z);
  
  SerialUSB.print("min: {");
  SerialUSB.print(running_min.x); SerialUSB.print(", ");
  SerialUSB.print(running_min.y); SerialUSB.print(", ");
  SerialUSB.print(running_min.z);
  SerialUSB.print("}  max: {");
  SerialUSB.print(running_max.x); SerialUSB.print(", ");
  SerialUSB.print(running_max.y); SerialUSB.print(", ");
  SerialUSB.print(running_max.z);
  SerialUSB.println("}");
  
  delay(100);
}
