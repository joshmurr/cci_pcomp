# Week 2

### Lab 00
#### Resistors in Series

I could get 2 LEDs (yellow) to light up in series before the voltage runs out. Instinctively this is what I assumed, which is good, but I struggle to prove it mathematicall. It should be simple... But I couldn't get my head around: if the resistance of the resistor is constant, and the current is also constant, why would the voltage over the resistor change as more LEDs are added to the circuit? I presume the current isn't constant, and the circuit draws more and shares it differently.. I should check this.

Either way, it makes sense, as the ideal forward voltage for an LED is approx 2.2V, and with 5V maximum, there is only enough voltage for 2 LEDs to light up.
[2LED](photos/2LED.jpg)
[3LED](photos/2LED.jpg)
[Series Maths](photos/my_series_maths.jpg)
[Stu and Aleksi](photos/stu&aleksi.jpg)
[Aleksi Maths](photos/aleksi_maths.jpg)

#### Resistors in Parallel

This was also a lot tricker that it first appeared... _My_ final maths got me to __13 LEDs__.
[Parallel Maths](photos/my_parallel_maths.jpg)

### Lab 01

I spent __way__ too much time on this. Serial.read() is actually not a simple thing! Couple with the fact that manipulating char arrays in Arduino Language (C++) is also not that simple. I tried to get a simple text adventure style thing working, and it _nearly_ is, but something is not quite right. All the code is in the repo, and here is a video of the next best thing:

[![Roses are red](https://img.youtube.com/vi/WhojQjw3Kp0/0.jpg)](https://www.youtube.com/watch?v=WhojQjw3Kp0)

### Lab 02

[![Potentiometer Brightness](https://img.youtube.com/vi/twnjQgp-GuA/0.jpg)](https://www.youtube.com/watch?v=twnjQgp-GuA)

### Lab 03

[![LDR](https://img.youtube.com/vi/DZW99re93kg/0.jpg)](https://www.youtube.com/watch?v=DZW99re93kg)

### Lab 04

[![Ultrasonic](https://img.youtube.com/vi/_i36l2ZLifU/0.jpg)](https://www.youtube.com/watch?v=_i36l2ZLifU)
