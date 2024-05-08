# Rainbow Six Siege Freezing Fix
This program was created with the purpose of quickly fixing the Rainbow Six Siege freezing problem.

The manual way to fix this problem is: open the task manager and manually change the cpu affinity of the process and then change the affinity back to how it was before.

That's why I created this executable that does exactly the same thing but without opening the task manager and in a much faster way.

Since the moment your game starts to freeze, you will only have to minimize and execute the fix, and you will be able to continue playing normally.

In my case when my game started to freeze, it often happened at very critical moments or I wasted too much time minimizing, opening the task manager, and changing the process cpu affinity twice. That's why I decided to create this executable.

If you use peripheral control programs such as Logitech, Razer, Corsair, etc. You could create a macro that runs the executable with a key while you play, thus saving you the need to minimize.

## How it works
The program first looks for the process id of the "RainbowSix.exe" executable.
  
Then use the process id to change the process cpu affinity to processor 0.
  
After 0.5 seconds it reverts the process's cpu affinity to its original state.

In any case, if you have any questions about its operation, you can see the Main.cpp file of the repository in which everything is documented.

### I accept suggestions to improve the code :)
