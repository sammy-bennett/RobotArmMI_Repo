
const int servoPin1(27),servoPin2(14),servoPin3(12),servoPin4(13); //all servos on ADC2
const int potPin1(36),potPin2(39),potPin3(34),potPin4(35); //all pots on ADC1, 36and39 are sensVP and sensVN (input only)

/*
AI GENERATED SUMMERY of ADC2 conflict:
ADC2 / Wi-Fi conflict: The ESP32 has two ADCs, ADC1 (GPIO 1-10 on the S3) and
ADC2 (GPIO 11-20). The Wi-Fi driver needs ADC2 internally and takes priority, so
analogRead() on ADC2 pins becomes unreliable (constant values or errors) whenever
Wi-Fi is active. To be safe, all analog inputs (the pots) are on ADC1 pins. The
servos are on ADC2 pins, which is fine because the conflict only affects analog
reads, not digital or PWM output. This project doesn't use Wi-Fi, but keeping pots
on ADC1 means Wi-Fi can be added later without breaking the readings.
*/