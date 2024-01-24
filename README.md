# Display tablet to regular tablet
The purpose of this project is to use a tablet's display as mouse input to echo at another monitor, essentially working as a regular graphic tablet.

Language choosen: C

OS: Linux Mint 21.2

## Log
### **Preface**
This project has been on my mind for about 6 months now I'd say, didn't really track it from the beggining, and the idea occured to me as I was using a tablet with display that I bought as a motivator tog et back to drawing. Using C was decided as it is one of 2 languages I use at work, the other one being COBOL (_Yeah, you read that right, and I'm as zoomer by the way_) and so I thought it'd be good exercise and I'll probably be able to use some of the experience at work.
Anyways

Also as a side note, I tried asking chatGPT to help me write code in C to track the user's mouse input and it responded with something like "Writing mouse loggers or anything that tracks down the user's activity without it's consent is against good ethics" smh.
Obviously explaining my objective did not help.

### **The begining**
Set up the repo: Done
Figure out how to capture mouse input in C using Mint: Haven't figured that out yet
Create the graphical interface: Well I just read a GTK guide found at the Magpi site [Right here](https://magpi.raspberrypi.com/books/c-gui-programming-2), and kinda get the idea as to what I want to do
- It'll have a menu to display current monitors and let the user choose which monitor it wants to echo to input to.
-- Also gotta figure out how to get the available monitors
- It'll show the area from which all mouse(or touch) input will be captured from and echoed in relation to the size of the current window and the chosen monitor aspect reatio and measurements.
- The input area will be consistent to the aspect ratio of the choosen monitor.

So yeah, let,s do this.

Well that was easy:
Typed "mouse input in ubuntu" in duckuckgo which lead me to [askUbuntu forum](https://askubuntu.com/questions/208106/how-to-get-mouse-buttons-to-work#263515) which pointed me to Xinput.

Now xinput, accordingly to HowToGeek is "An API launched in 2005 as a way to support Xbox 360 controllers on Windows.". Which can be found in their article [DirectInput vs. XInput for Game Controllers: What's the Difference?](https://www.howtogeek.com/792984/directinput-vs.-xinput-for-game-controllers-whats-the-difference/)

Well that wasn't as easy as I initially thought.
Xinput does give back the input from different devices, but now the question is how do I reproduce it?. This lead me to X11 and some test code courtsey of chatGPT pointed me xorg-dev & libx11-dev

Some really nice people at the notorious site known as 4chan have pointed me to SDL & SFML, don't say people there aren't nice sometimes ^-^

***

Another update before hitting the hay for the day
Started to look into SDL, apparently it's a library that lets developers access low level hardware, makes sense considering my current goal is to capture mouse events, and most of the documentation I could find seems pretty old but while looking around I realised a lot of this informations is aimed towards game development, which is interesting, first I get a sense of directino with xinput and know sdl is leading me towarsd that path.
Anyhow I found a tutorial about reading the mouse which is an aiming exercise for games, makes sense, and before I could try it out I found myself encountering something new: cmake
Cmake is an automation tool for creating builds and the game tutorials that seem more promesing use it to build on top of it, so I just spent quite some time figuring thiss thing out, also as a side note, I dont know c++ and apparently this thing is build towards C++ so it's taking more brain power to kinda get what's going on but as long as I make progress I can walk back on my steps and figure how it works, so far making it work is my first priiority.