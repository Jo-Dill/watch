This watch has a few bugs. Nevertheless, I am not working on a second version. 
On the one hand, that would take a lot of time as well as I have way too many other ideas that I would like to realize. 
The power supply is the biggest problem so far. The circuit board is designed so that a Cr2032 coin cell supplies the clock with power.
Unfortunately, I didn't consider the early voltage drop to 2.7B and below.  2.8 V is the lowest voltage at which the LEDs still run reliably.
So I used a 3.7 V lipo whose voltage is regulated by the Xiao's internal voltage regulator (unfortunately an additional energy loss). 
The voltage measurement for the battery level display then had to be done via an external raster board. And now Everything is wired with enamelled copper wire. 
The LEDs are also not at all power-efficient (1.2 mA when they are all off - but in this case their power supply is cut by a transistor). 

What I have learned from this:
-The voltage source should be better adapted to components with a critical voltage range.
-Ws28 12b LEDs are NOT power saving.
-Coin Cells have a big capacity with their small package and a small drain. BUT their discharge curve isnt very horizontal

The Buzzer, driving the leds, the RTC, the light sensor and the power saving in standby worked well. 
After 2 months, mostly in standby, the battery is still more than a third of its capacity.
The operation via 2 buttons is possible, but can be improved in future projects, as it is not really intuitive due to multiple assignments.

In summary, I can say that I have learned a lot and will apply the knowledge in the next wearable project.
Maybe there will be a really smart watch with IOT functions or other wearable projects with low power requirements and small size.
