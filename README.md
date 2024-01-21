# Display tablet to regular tablet
The purpose of this project is to use a tablet's display as mouse input to echo at another monitor, essentially working as a regular graphic tablet.

Language choosen: C
OS: Linux Mint 21.2

## Log
### **Preface**
This project has been on my mind for about 6 months now I'd say, didn't really track it from the beggining, and the idea occured to me as I was using a tablet with display that I bought as a motivator tog et back to drawing. Using C was decided as it is one of 2 languages I use at work, the other one being COBOL (_Yeah, you read that right, and I'm as zoomer by the way_) and so I thought it'd be good exercise and I'll probably be able to use some of the experience at work.
Anyways

### **The begining**
Set up the repo: Done
Figure out how to capture mouse input in C using Mint: Haven't figured that out yet
Create the graphical interface: Well I just read a GTK guide found at the Magpi site [Right here](https://magpi.raspberrypi.com/books/c-gui-programming-2), and kinda get the idea as to what I want to do
- It'll have a menu to display current monitors and let the user choose which monitor it wants to echo to input to.
-- Also gotta figure out how to get the available monitors
- It'll show the area from which all mouse(or touch) input will be captured from and echoed in relation to the size of the current window and the chosen monitor aspect reatio and measurements.
- The input area will be consistent to the aspect ratio of the choosen monitor.

So yeah, let;s do this.


