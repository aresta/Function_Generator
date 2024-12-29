# Function Generator 5MHz

Simple low power waveform generator based in the **AD9833 module**, capable of producing sine, triangular, and square wave outputs.
An Attiny3224 IC controls the system with a rotary encoder, a potentiometer, some buttons and a small display. It is powered with a USB-C connector. 

The frequency range goes from 1 Hz to 5 MHz and the amplitude can go from less than 100mV to 3.35V aproximately.
Above 4 Mhz the maximum amplitude decreases to about 1.6 V. There is a '*boost*' button to double the gain, and another one to reduce it to achieve waves with small amplitude.

The sine wave looks good up to 5 MHz and then starts to show some distortion.

The AD9833 module produces a signal with an amplitude of about 600mV. To amplify it we need a very fast opamp, the **LMH6658 opamp**. It has a 140 MHz GBWP and a slew rate of 700 V/μs. With we achive an amplitude of about 2.5V peak to peak. A *regular* opamp won't be able to amplify much the signal above 500 KHz.

To test in a breadboard you should solder the opamp on a small SOIC-8 adapter, and solder the gain resistors and decoupling capacitors directly to the adapter pins, to avoid problems with the breadboard at relative high frequencies.
And you should aslo set the oscilloscope probes to 10X.


![Function generator](/img/func_gen.jpg)

With the rotary encoder the frequency can be adjusted. It sweeps each digit separately.  The potentiometer is for the amplitude adjustment. 


Sine wave at 2.2 MHz:

![Function generator](/img/2_2MHz.jpg)


Sine wave at 5 KHz:

![Function generator](/img/5khz.jpg)

The schematic:

![Function generator](/img/func_gen_sch.jpg)

And the PCB:

![Function generator](/img/func_gen_pcb.jpg)

I have already mounted the PCB and it works.  It can be better arranged and reduced, and the software improved, but it's already fully functional.

![Function generator](/img/function_generator_attiny.jpg)

