# 2019-easy-bee-counter

This version of the bee counter is all through hole components.  I really wanted to make an easy to assemble bee counter for folks just starting out. I haven't tested this yet but I wanted to get it out early with a few improvemnets.  The code is pretty simple and I'll post it as soon as I can test it with a few bees flying.

I've posted two versions. One with an [Adafruit Itsy-bitsy](https://www.adafruit.com/product/3727) uController and one with an [Adafruit Feather](https://www.adafruit.com/product/3405) footprint. The ItsyBitys features a SAMD21 32bit uController and one with a feather footprint.  There's a nice esp32 feather as well as a few other options.

All The other componets are similar.  Powered by 5V.


### Bill of Materials
#### uController
itsyBitsy M0 32bit SAMD from [mouser](https://www.mouser.com/ProductDetail/485-3727)
feather Huzzah from [mouser](https://www.mouser.com/ProductDetail/485-3591)
#### PCB
[JLCP](https://jlcpcb.com/quote#/) ~$16-25 with shipping. See instructions for ordering below
#### Parts and Pieces from [mouser](https://www.mouser.com/ProjectManager/ProjectDetail.aspx?AccessID=054286973a)
- [qre1113 Reflective Sensors](https://www.mouser.com/ProductDetail/512-QRE1113f) qty(48)
- [22ohm resistors](https://www.mouser.com/ProductDetail/Xicon/266-22-RC?qs=sGAEpiMZZMvrmc6UYKmaNXFefT4dxyTCwtpTxTI0yoo%3D), bussed, qty(3)
SIP Packaged, bussed
- [100k ohm resistors](https://www.mouser.com/ProductDetail/IRC-TT-Electronics/L091S104LF?qs=sGAEpiMZZMvrmc6UYKmaNdnTrsZX%2FuSiyGduauH5Qpc%3D) bussed, qty(6)
SIP-9, 8 resistors, 9 pins
- Shift resgisters, qty(6)
[74HC165](https://www.mouser.com/ProductDetail/Texas-Instruments/CD74HC165EE4?qs=%2Fha2pyFadui%2FKTy9HJ5lB%2FBJ0Xswdr%252BnXu7asThazxrcGD%2FXuYTSNA%3D%3D)
- [3.3V Regulator](https://www.mouser.com/ProductDetail/Microchip-Technology/MCP1826S-3302E-AB?qs=sGAEpiMZZMsGz1a6aV8DcJ7KfjtCj7Xd5CqQpyOghgk%3D), (input, ground, output - IGO, pinout), qty(1)
- [0.1 uF Ceramic Capacitor](https://www.mouser.com/ProductDetail/594-K104K15X7RF53H5), through hole
- [1 uF Ceramic Capacitor](https://www.mouser.com/ProductDetail/594-K105Z20Y5VF5TL2), through hole
- [560uF, 6.3V Capacitor](https://www.mouser.com/ProductDetail/661-APSC6R3L561MH08S)
low esr, 3.5mm lead spacing, 8mm diameter
- N-Channel Mosfet [FQP30N06](https://www.mouser.com/ProductDetail/512-FQP30N06L), qty(2)

#### Alternative pricing
Someone pointed out some alternative pricing that can really bring the parts cost
- [QRE1113 Reflectance Sensors](https://lcsc.com/product-detail/Photo-Interrupter_Everlight-Elec-ITR8307_C63451.html) ~$0.13/each
- [6 pin female headers](https://lcsc.com/product-detail/Pin-Header-Female-Header_BOOMELE-Boom-Precision-Elec-C40877_C40877.html) 8.5mm high. These are 1.5mm taller than the mouser ones.
