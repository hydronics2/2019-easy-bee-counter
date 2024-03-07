## Printed Circuit Board (PCB)

This PCB version has two footprints that accept the wider (0.8") Adafruit Feather micro-controllers such as the [esp32](https://www.adafruit.com/product/3405) and the narrower (0.6")[Adafruit ItsyBitsy](https://www.adafruit.com/category/1008) micro-controllers.

**UPDATE** The GERBER files were developed from the kicad board files so had to remove the gerber files. You now have to use the Eagle board files or generate gerber files from the eagle board files.... or a lot of PCB manufacturers will take eagle PCB files and you don't have to generate your own gerber files. You can still use the kicad files but you have to route a small trace for the SCK pin. See this bug report: https://github.com/hydronics2/2019-easy-bee-counter/issues/25 

![feather](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/pics/gerber_feather_2.PNG)

These files were created in Autocad EAGLE PCB software. The zipped files are the gerber files needed by the PCB manufacturer.

Right click and 'save link as' to download the files and then upload them to the PCB manufacturer. See the [ordering instructions here](https://github.com/hydronics2/2019-easy-bee-counter/tree/master/instructions/ordering_instructions). Most board shops require a minimum order of 3-5 boards and you'll need 2 boards to sandwich together to complete one bee counter.
