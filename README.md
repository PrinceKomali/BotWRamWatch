
  

## WARNING!

<b>This code may not work for everyone! For reasons that I do not understand, different users sometimes have different memory addresses in Cemu, and therefore the values may be wrong</b>

<br>Also, looking at this code may result in severe mental damage as it is incredibly crude and inefficient. Sorry about that ;)


<i>Anyways...</i>

# Cemu Ram Watch for Breath of the Wild
![Example](https://github.com/PrinceKomali/BotWRamWatch/raw/main/spd.gif)
Hi so I got bored one day and decided to try my hand at making some sort of ram viewer to watch Link's speed while playing Breath of the Wild on Cemu Emulator. <br>Right now it shows <b>Link's Health</b>, <b>X position</b>, <b>Z position</b>, and <b>Calculated Speed (km/h) based off of X and Z</b>. I will most likely add Y position and vertical speed as well. <br>The goals of this are to make a program that is easily able to be edited for adding in RAM values and such, but also one with stylish and clear output methods.<br><br>
## Running and Building
<b>Warning! See notice at the top of README</b>
This program isn't really meant to ran by anyone else at the current moment, as there are lots of bugs and the output method                                   could be improved (understatement). However, it <i>might</i> work on another computer (emphasis on "might") so I may as well provide some rudimentary instructions.<br><br><small>(I'm not 100% sure on how to actually build it from an external perspective but this <i>should</i> in theory work)</small><br>[Visual Studio](https://visualstudio.microsoft.com/) is required to build the actual program. Once installed, simply open `./ram/ram.sln` and build it from there (make sure to build as x64). <b>Following compilation, move the executable from the folder it was compiled at to the root directory of the project, so that it is in the same directory as the `DLL` folder where the library is stored</b><br>The output method requires [Node.js](https://nodejs.org). Once downloaded, `cd` into the `Web` directory, run `npm i express ws express-ws` to install the required dependencies. To run, run `node post.js` and navigate to `localhost:3002` in your web browser (or add it as a browser source in OBS Studio). <br>Running the program should result in output being sent to the localhost page<br><br><small>Yes I know there are better output methods; sue me</small><br>
## Credits
This project would not have been possible without the help of [Makonede](https://github.com/Makonede), who helped teach me the labyrinth that is `Windows.h`, so a huge shoutout to them!
