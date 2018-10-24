# QuickCommands
Plugin for Unreal Engine 4 that adds a window what you can fill with console commands and you can execute them by clicking on them.

<img src="https://github.com/AndrisBorbas/QuickCommands/blob/master/Resources/quickcommands.gif?raw=true" width="720" />

The window is resizable and dockable, the height of the cells is fixed, but you can scroll in the window if the cells don't fit.
The empty button is just an empty line in the file.

### Special thanks to Rens for the original code. https://twitter.com/artbyrens

## Building for your version of UE4 (tested with >4.19)

Prerequisites: Setup your environment so that you can build a C++ UE4 project

1. Create a new **C++** project
2. Create a folder named `Plugins` in the root of your new project (see below)
3. Clone the repo into the plugins folder, so that you get `Plugins/QuickCommands`

Your project folder should look like:

```
ProjectName
    \.vs
    \Binaries
    \Config
    \Content
    \Intermediate
    \Source
    \Plugins
        \QuickCommands
    \ProjectName.sln
    \ProjectName.uproject
```
  
4. Open the .uproject and it should prompt you to rebuild the plugin
5. Hopefully the build succeeds!
6. Configure the location of the file you want to use in editor preferences.

#### Example commands.txt:

```
stat fps

stat unit
stat Engine
stat Game
stat Memory

r.shadow.maxresolution 4096
r.shadow.maxresolution 1024
r.DepthOfFieldQuality 4
r.Streaming.PoolSize 8000
r.Streaming.Poolsize 6000
r.Streaming.Poolsize 4000
r.Streaming.Poolsize 2000
```
