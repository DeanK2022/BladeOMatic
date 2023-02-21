This is the BladeOMatic project which is to build a tester device for epee, foil and sabre blades.  Plug your blade in to the machine, select the correct blade type and the tests will run automatically.

It uses an ESP32 WROOM chip connected to a 3.5" TFT capacitative touch screen.  The screen is an ILI9488 and is driven by Bodmer's excellent TST_eSPI library. The touch chip is a GT911 and I hacked together a driver that just about works (for my purposes at least) from a variety of sources, see the GT911 repo that is a sibling of this one.

