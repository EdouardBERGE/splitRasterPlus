
splitRaster+

raw sources from 2019 version + hardware sprites bugfix + Win/MacOS/Linux compatibility

this software is designed to run with colorful images, avoid conversion from Atari/Amiga

USAGE: splitsdl.exe picture.png (or bmp files)

input file must be PNG with 384 pixels width (mode 1 ratio) and from 16 to 273 pixels height
if the picture does not fit required size, a crappy resize will be done, AVOID THIS!

## CONTROLS DURING QUANTIZATION
click in the picture to add an hardware sprite
click&move an hardware sprite in the picture to move it
left-click and draw in the magnified sprite to enable/disable transparency
right-click to fill or unfill transparency on the very same color
G generate files and save settings
L lock screen in order to edit pixels
B toggle between Floyd Steinberg dithering and Bayer Matrix dithering
ESC press twice to quit

## CONTROLS DURING PIXEL EDITION
keypad 0 or . to select current pencil (like OCP)
cursor to move current pixel position
shift or ctrl + cursor to move current pixel position faster
space to put pixel in the background OR the hardware sprite
B to put a background pixel on a hardware sprite (will enable transparency)
U unlock screen and goes back to quantization mode (all modifications will be lost)
G generate files and save settings
ESC press twice to quit



![preview](https://github.com/EdouardBERGE/splitRasterPlus/blob/main/split.jpg)

Vidéo de démonstration sur MacOS
[![IMAGE demonstration sur MacOS](https://github.com/EdouardBERGE/splitRasterPlus/blob/main/macOS.png)](https://www.youtube.com/watch?v=NX9KVfwzKjQ)
