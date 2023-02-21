This is the BladeOMatic project which is to build a tester device for epee, foil and sabre blades.  Plug your blade in to the machine, select the correct blade type and the tests will run automatically.

It uses an ESP32 WROOM chip connected to a 3.5" TFT capacitative touch screen.  The screen is an ILI9488 and is driven by Bodmer's excellent TST_eSPI library. The touch chip is a GT911 and I hacked together a driver that just about works (for my purposes at least) from a variety of sources, see the GT911 repo that is a sibling of this one.

The screen is this one: https://www.aliexpress.com/item/1005004083478309.html?spm=a2g0o.order_list.order_list_main.17.21ef1802IGJi0I and has an ID on it JC3248S035R which is almost unsearchable for on the internet for example code.

The JC3248S035 does not seem to like interrupt based comms on the touch screen - it is an I2C interface so don't forget your 2k pull up resistors on SDA and SCL lines.  It is also quite touchy about which ESP32 pins are used, these pins seem to work OK:

#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS    14
#define TFT_DC    27
#define TFT_RST   19

#define TOUCH_SDA 21  
#define TOUCH_SCL 22  
#define TOUCH_INT 25 
#define TOUCH_RST 26 
#define TOUCH_CLOCK 400000

And don't forget a pull up 10K on the screen reset line.  I was having problems uploading new builds with some strange "board not in upload state" type messages and all I could do was power off and begin the compile/upload cycle afresh.  

The UI is put together using the GUISlice library that was also hacked to use the new GT911 driver.  


![20230210_183339-small](https://user-images.githubusercontent.com/101397734/220383486-0e2ab315-319c-4b83-9050-3033a0d2f19e.jpg)
