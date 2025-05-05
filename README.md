# How the NES Zapper REALLY Works

Do you want to know how the NES Zapper REALLY works? I took a deep dive into the hardware to unlock its secrets.

![](https://raw.githubusercontent.com/nickbild/nes_zapper/refs/heads/main/media/logo.jpg)

Read on to find:
- Exactly what triggers a hit
- Why the Zapper will not work with a modern TV
- A schematic of the circuit
- Signal traces of the Zapper in action
- Tips for repurposing the hardware for other projects
- ...and lots more background information!

**Check out the video on YouTube:**
<a href="https://www.youtube.com/watch?v=cWvGYfH0B30">![](https://raw.githubusercontent.com/nickbild/nes_zapper/refs/heads/main/media/me_pointing_zapper_video_preview.jpg)</a>

## How It Works

If you have ever tried to cheat at a Zapper game by pointing it at a light bulb and pulling the trigger, you’ll know that that doesn’t work. Unlike earlier light guns, the Zapper had some simple yet effective mechanisms designed to prevent cheating. And it is these mechanisms that keep it from working on a modern TV, and that make it difficult to repurpose in general.

The first safeguard is in the way that the Zapper detects light. It doesn’t just trigger a hit when it sees brightness; rather it’s changes in brightness level at a specific frequency. Before going any further with this, it is helpful to consider how this worked with an NES and a CRT TV.

### An Example from Duck Hunt


![](https://raw.githubusercontent.com/nickbild/nes_zapper/refs/heads/main/media/duck_hunt_hit_1.png)

In Duck Hunt, for example, when the trigger is pulled, the screen will turn completely black for one frame:

![](https://raw.githubusercontent.com/nickbild/nes_zapper/refs/heads/main/media/duck_hunt_hit_2.png)

Then a white box is drawn immediately over where the duck was on the previous frame:

![](https://raw.githubusercontent.com/nickbild/nes_zapper/refs/heads/main/media/duck_hunt_hit_3.png)

Finally gameplay resumes with either a hit or a miss being registered, depending on what the light gun saw. 

![](https://raw.githubusercontent.com/nickbild/nes_zapper/refs/heads/main/media/duck_hunt_hit_5.png)

### CRT TV Operation

To understand what is really happening here, you need to know how a CRT TV works.

![](https://raw.githubusercontent.com/nickbild/nes_zapper/refs/heads/main/media/mario_tv.png)

When we look at the screen, we see an image. But it’s not really there, we only see it due to persistence of vision. Inside the TV, an electron beam moves very rapidly to excite the phosphorescent screen, one horizontal line at a time. If we could slow it way down, it would look something like this:

![](https://raw.githubusercontent.com/nickbild/nes_zapper/refs/heads/main/media/mario_scanline.png)

The current line being drawn is the only one that is actually lit up, and the rest are dark. Everything else is just a trick of the mind.

### What the Zapper Really "Sees"

So how is this relevant to the operation of the Zapper? Well, the NES Picture Processing Unit generated 60 frames of video per second, and that was at a 256x240 pixel resolution (plus 22 scanlines that are not visible).

So doing the math, that gives it (1 / 60) / 262 = 0.000063613 seconds to draw a single scanline. That is equivalent to a frequency of ~15.7 kilohertz (1 / 15722 = 0.000063605).

Back to Duck Hunt for a moment. The Zapper has a photodiode that senses light. It does not see white boxes. It sees the initial black frame as darkness, then it sees the individual, bright scanlines flashing on and off at 15.7 kilohertz, assuming the barrel is pointed at them. It’s this change from dark to bright at a high frequency that causes a hit to be counted. If this change in light happens at the exact right moment, when the frame containing the white square was being drawn after the trigger was pulled, you’ve got a dead duck.

This also explains why the gun does not work with modern TVs. LCD TVs don’t have an electron beam rapidly tracing out an image, but instead have individual LCD pixels that light up. And by comparison, they are very, very slow. Even a really high quality TV with a 1 millisecond pixel update time is 0.001 seconds. That’s way too slow!

### How Can the Zapper be Triggered Without an NES?

So if you want to repurpose a light gun, do you have to exactly mimic a CRT TV? That’s what I wanted to find out, so I built this test rig:

![](https://raw.githubusercontent.com/nickbild/nes_zapper/refs/heads/main/media/test_rig.png)

For reference, here is the pinout of the Zapper’s connector:

![](https://raw.githubusercontent.com/nickbild/nes_zapper/refs/heads/main/media/pinout.png)

Both the trigger and hit lines need pull-up resistors. The trigger is super simple — pull it and it grounds the signal. It is completely independent of light sensing even though a lot of explanations out there link them. That is definitely not the case.

To find out what exactly the light sensor responds to, I have a white LED being rapidly switched on and off at varying frequencies by an Arduino clone. That light shines right at the photodiode inside the Zapper.

I have it flashing the light at frequencies above and below the expected 15.7 kilohertz triggering frequency. I am monitoring the LED switching frequency and the response of the hit signal with a logic analyzer. Here is a signal trace (there is more detail in [the video](https://www.youtube.com/watch?v=cWvGYfH0B30), or see [here](https://github.com/nickbild/nes_zapper/blob/main/media/range_zoom.sal)):

![](https://raw.githubusercontent.com/nickbild/nes_zapper/refs/heads/main/media/trace.png)

The bottom trace is the hit signal, and when it goes high, it is registering a hit. What I found is that it transitions to high when the frequency is between about 20kHz and 13.5kHz, so there is some wiggle room in there.

### The Hardware Teardown

I completely disassembled the Zapper ([see the video](https://www.youtube.com/watch?v=cWvGYfH0B30)).

![](https://raw.githubusercontent.com/nickbild/nes_zapper/refs/heads/main/media/teardown.png)

After examining the hardware, I made this schematic:

![](https://raw.githubusercontent.com/nickbild/nes_zapper/refs/heads/main/media/zapper_schematic.svg)

The key component is the Sharp IR3T07A:

![](https://raw.githubusercontent.com/nickbild/nes_zapper/refs/heads/main/media/IR3T07A.png)

This chip clearly determines what frequencies of light the Zapper responds to, but unfortunately, it is completely undocumented. There is no datasheet, and it seems no one outside of Nintendo in the 1980s knows how it works. Possibly the values of the capacitors and resistors would modify the frequency range, but I don't know that. I don't want to fry a 40 year old chip that is long out of production, so I don't really want to try either.

### Best Bets for Repurposing the Hardware

The good news is that, even with an unknown chip handling the light detection, there are still some options for repurposing the hardware. If your application allows, you can set up an LED beacon that flashes somewhere in the acceptable frequency range to register a hit. This would be good for controlling things around your home, for example. If you do not have that luxury — like if you want to use the Zapper with a modern TV or another console — there might still be another option. The anode of the photodiode reports changes in light levels as chages in voltage. Here is a trace:

![](https://raw.githubusercontent.com/nickbild/nes_zapper/refs/heads/main/media/photodiode_trace.png)

This analog signal could be used to differentiate between bright and dark spots on even a modern TV, for example. There is no cheating protection, but for most personal projects, that is probably not a concern anyway. The hit pin could even be re-routed to connect to the photodiode to keep things neat. But of course, don't do this unless you understand what you are doing!

For more details, be sure to check out [the video](https://www.youtube.com/watch?v=cWvGYfH0B30).

## About the Author

[Nick A. Bild, MS](https://nickbild79.firebaseapp.com/#!/)
