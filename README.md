- [Preface](#preface)
- [Requirements](#requirements)
- [Hardware setup](#hardware-setup)
- [Build or edit firmware](#build-or-edit-firmware)
- [How does it work?](#how-does-it-work)

# Preface

**Iron Man** is an attempt to reproduce the first version of Iron Man hart using NeoPixel ring for my son.

# Requirements

- [Platform IO](https://docs.platformio.org/en/latest/)
- [Trinket 3v](https://www.adafruit.com/product/1500)
- [Neo Pixel Ring](https://www.adafruit.com/product/1643)
- [Lipo Battery 3.7v](https://www.adafruit.com/product/258)
- [Battery Charger]()
- [Button]()

# Hardware setup

To build the hardware I've used a stripboard of

# Build or edit firmware

Just open the project with [Platform IO](https://docs.platformio.org/en/latest/) and you are ready to make your changes and upload it.

- `pio run -t upload`

# How does it work?

The project is making use of the famouse [FastLED]() library to managing the Neo Pixel ring. The only present effect for now is the `hartbeat` and is built with no-blocking in mind. This because the device has a button to control the colors of the ring.