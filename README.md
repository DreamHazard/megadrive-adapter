# megadrive-adapter

Arduino controller adapter using Micro/Pro Micro/Leonardo etc.

Sega Mega Drive controller USB adapter using Arduino

Thanks to [MHeironimus](https://github.com/MHeironimus/ArduinoJoystickLibrary) and [jonthysell](https://github.com/jonthysell/SegaController) for their libraries, links can be found in the source - Thanks also to [pyroesp](https://github.com/pyroesp) for pointing me in the right direction

## Preparation

Connect up the DB9 pins as per jonthysell's example, pinout can be found in the source as well - don't forget to hook up the ground and 5V (like I did initally: it doesn't work) - the Pro Micro needs the jumper shorting in J1 to allow the VCC pin to output 5V from the usb power source

You'll need to download the libraries as zip files and add them to your environment using

```
Sketch > Include Library > Add .ZIP Library
```

and then

```
Sketch > Include Libary > [Library Name]
```

for each of the libraries.

No change is needed to the board info etc, just compile and upload to the board and you're done

You can check joy.cpl to make sure that your controller is working properly - the device will be named "Arduino Micro
