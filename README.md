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

***

I can't believe I did it, honestly I'm not sure what I did, I just know it works
What works? You ask
I dunno... I was searching for ways to make this SDL2 library work so after searching for some tutorials I came around some scripts, has to tweak a bit here and there but after trying out different ones I kind of started understanding how this compiler thing works
The most difficult part was the compiler didn't find the library, no sure why, tried changing the header, different paramethers while compiling until one combination finally made sense, which was the library header <SDL2/SDL.h> while using the compiler indicating the library

'''
gcc mouseevent.cpp `pkg-config --libs sdl2` -o test
'''
the .cpp file is an example found online and that's basically all that I needed, for now.

This ought to work for now, so lets finnaly get our hands dirty, hopefully

Now I know, kind of, what's the deal with the make command and Makefile
// Note to self, this kind of stuff is case sensitive, just spent like 20 minutes figuring out why the make command didn't work only to realize it's "Makefile" and not "MakeFile"

So right now im kind of getting the hang of this make files, which will probably will come handy later on, for now we can build projects that include sdl library correctly, now on to set up a test for mouse events.

***
Am I writting C++, I dunno

'''
	    Uint32 buttons = SDL_GetGlobalMouseState(&x, &y);
	    printf("%u buttons, x:%d &  y:%d \n", buttons,x,y);
'''

so this thing actually gets the coordinates of the mouse  and the button pressed, I'm not so familiar with event driven coding soooo this ought to be interesting, but at least now I can capture the mouse position, also apparently 'SDL_GetMouseState(*x,*y)' gets the position relative to the created window, this will be useful to later map out waht happens inside the window to another monitor

***

As I'm reading this tutorials and documentation i think of this gameplan:
- Test a way to move the mouse to a certain position & make it click or something like that
- Make a loop to constantly get mouse position & events
- Find a way to get a monitor, it's specifications and a way to map it to point to it

***

I'm back at it, trying to test this list thing

So yeah, teh current version requires a bmp image to launch, while testing that I learned about the main loop in the application and that led me to look up what type of events one can be on the look for, which lead me to capture mouse motion, once I learned more about the event structure it was quite obvious the way to capture motion within the window, pog.

***

Mouse events can now be captured, inside and outside teh window, alse a new test case has been used to see how to identify different displays, currently testing to see how to get all necessary propoerties
Functionality wise the only thing that's left is figure out how to duplicate mouse input, either that or replicate the input onto the other display

***

PollEvent retreives the events in queue, while looking through the list of functions available I came accross PushEvent, now that is what I need, as the description says "The event queue can actually be used as a two way communication channel. Not only can events be read from the queue, but the user can also push their own events onto it. event is a pointer to the event structure you wish to push onto the queue."

Surely that's it

well I can now move the cursor  where i want to, but if i move the cursor away from my window how could it read the next input?
gotta poke around to create the mouse events without affeting the current state of the cursor, that way the cursor could be locked inside the window in the tablet and still have it create mpuse events, create mouse events... i can create mouse events, just not sure how to map it to outside the window

Just gotta figure that one out