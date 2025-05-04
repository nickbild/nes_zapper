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

If you have ever tried to cheat at a Zapper game by pointing it at a light bulb and pulling the trigger, you’ll know that that doesn’t work. Unlike earlier light guns, the Zapper had some simple yet effective mechanisms designed to prevent cheating. And it is these mechanisms that keep it from working on a modern TV, and make it difficult to repurpose in general.

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


## About the Author

[Nick A. Bild, MS](https://nickbild79.firebaseapp.com/#!/)
