#The µBar 
The µBar is a device that automates the process of mixing and pouring beverages. It was first implemented as an undergraduate senior design project, which is what we refer to as Version 1 of the µBar. After learning what worked, what can be improved, and what was missing from the project, we have decided to give a stab at this thing again - hopefully with much more success this time around. 

##Overview
A high level block diagram (found [here](https://github.com/comychitz/uBar/blob/master/files/diagrams/blockDiagram_system.jpg)) shows the µBar at the system level. There are two main components: a mobile application and the µBar device. There may be a central server introduced into the system that would host the µBar backend and user data, however, the decision has not been completely made. At this point we assume the mobile application will talk directly to the µBar device, via HTTP messages over a local WiFi network. 

###Mobile Application
It is planned that both iOS and Android applications be built. From the app users will be able to make drink orders based on custom input or choose a recipe based on the current inventory. 

###µBar Device
The µBar device can be broken down into four main componenets: the main computing board (Linux-based embedded computer), the I/O board (valve & motor controllers), the chassis/hardware, and the touchscreen input device. Most of the work for this project will be building the µBar device itself.

###Initial Version
A video showcasing the first implementation of the uBar can be seen on [here on YouTube](https://www.youtube.com/watch?v=hmA4LdbyjqQ).

![prototype](https://github.com/comychitz/uBar/blob/master/files/design/original_prototype.png)
