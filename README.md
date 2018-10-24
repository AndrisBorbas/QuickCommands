# QuickCommands
Plugin for Unreal Engine 4 that adds a window what you can fill with console commands and you can execute them by clicking on them.

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
