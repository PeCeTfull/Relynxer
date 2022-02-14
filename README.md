# Relynxer #

Relynxer is a wizard program designed especially for vintage PCs for 'shortening' website URLs by generating new (typically shorter) ones on Lynx.re thanks to its API. The application itself was written in C++ and uses wxWidgets GUI library. The Lynx.re service is based on Shrinky by Hassan.

### Getting to work in Windows 95 ###

In order to make the software work properly on your Windows 95 computer, you must have Windows Sockets 2 (Winsock 2) installed there. It is generally required by the network libraries included with the program.

### Handling the program ###

The program greets you with its wizard window. From there, you are able to enter your valid URL of the website you want to create a shortened link of. After completion, you can always go back to the previous step and create another Lynx.re link without having to restart the application.

### Additional options ###

Relynxer, just like Lynx.re, allows you to customise your link by adjusting the following parameters: 

* password, 

* number of usages, 

* expiration date, 

* visibility state (public by default), 

* custom name.

All of these parameters are fully optional.

### Program options ###

You can change the UI language and show or hide the HTTP warning on program launch.

### Recommended programming setup ###

Source and target OS: Windows

IDE: Code::Blocks Release 13.12 rev 9501 (2013/12/25 19:25:45) gcc 4.7.1 Windows/unicode - 32 bit

wxWidgets version: 2.8.12 (SHARED=0 MONOLITHIC=1 UNICODE=1 MSLU=1)

Additional info: The post-build script for Release contains the line that launches UPX (if it exists) in order to compress the executable file. Please change UPX directory to your desired one or simply remove the line if you do not have the program, otherwise the files from the "common" directory may not be successfully copied after compiling.

### Program licence ###

Relynxer is published under The MIT License. Please refer to the LICENSE.txt file of this repository for more information regarding it.

This program also includes libraries and source codes that are necessary to successfully compile and launch the software. The licensing information regarding those are located in the Licenses directory.