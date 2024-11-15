# Function Generator 5MHz

Simple low power waveform generator based in the **AD9833 module**, capable of producing sine, triangular, and square wave outputs.
An ESP32-S2 module controls the system with a rotary encoder, a potentiometer, some buttons and a rectangular 320x170 IPS display. It is powered with a USB-C connector. 

The frequency range goes from 1 Hz to 5 MHz and the amplitude can go from less than 100mV to 3.35V aproximately.
Above 4 Mhz the maximum amplitude decreases to about 1.6 V, but there will be a '*boost*' button to double the gain.

The sine wave looks good up to 5 MHz and then starts to show some distortion.

The signal is amplified with the high speed **LMH6658 opamp**. It has a 140 MHz GBWP and a slew rate of 700 V/μs.  These parameters are key in the opamp selection, otherwise it won't be able to amplify much the signal above 500 KHz.

This is the breadboard protoype, with the opamp soldered on a small SOIC-8 adapter with the gain and decoupling components (resistors and capacitors) soldered directly to the pins, to avoid problems with the breadboard at relative high frequencies.
To test you should set the oscilloscope probes to 10X.


![Function generator](/img/func_gen.jpg)

With the rotary encoder the frequency can be adjusted. It sweeps each digit separately.  The potentiometer is for the amplitude adjustment. 


Sine wave at 2.2 MHz:

![Function generator](/img/2_2MHz.jpg)


Sine wave at 5 KHz:

![Function generator](/img/5khz.jpg)

The schematic:

![Function generator](/img/func_gen_sch.jpg)

And the PCB:

![Function generator](/img/pcb.jpg)

I have already mounted the PCB and it works. But sometimes I there is some strange behaviour with the display that I have to investigate.

The user interface can still be improved.

For the version probably I will change the MCU by an ESP32-C3 module or even an small Attiny new series MCU, depending on the number of GPIO pins needed.
