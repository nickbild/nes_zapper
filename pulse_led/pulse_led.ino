void setup(void) {
   pinMode(2, OUTPUT);
}

// 60 = 8kHz
// 50 = 9.6kHz
// 40 = 11.8kHz
// 30 = 15kHz
// 20 = 22kHz
// 10 = 41kHz

// Broad range finding.
// void loop(void) {
//   for (uint8_t time=10; time<=60; time=time+10) {
//     for (int i=0; i<100; i++) {
//       digitalWrite(2, HIGH);
//       delayMicroseconds(time);
//       digitalWrite(2, LOW);
//       delayMicroseconds(time);
//     }
//   }
// }

// Zoom in on range.
void loop(void) {
  for (uint8_t time=23; time<=43; time++) {
    for (int i=0; i<50; i++) {
      digitalWrite(2, HIGH);
      delayMicroseconds(time);
      digitalWrite(2, LOW);
      delayMicroseconds(time);
    }
  }
}
