# Build

## Compiling
To compile the main program you want to first clone it you can do this by mainly copying files or running the command `git clone https://github.com/jamescraft10/Build.git` after that you will want to compile it with g++ (which i assume you have installed).
Then you will run the command from the root of the directorys `g++ -o build ./src/build.cpp` and that should work.
After just put it in your enviroment variables and it should be good to go.

## Documentation
To use this Build you will first have to go to your root directory off the project that your working on which im just gonna call ./a/
Once you have that what you will want to do to use it is make a ".build" file. Inside the .build file it should look something like this
```
compile-and-run-server:
g++ -o ./build/server ./src/server.cpp
./build/server
;

compile-and-run-client:
g++ -o ./build/client ./src/client.cpp
./build/client
;
```
You will have to use \ if you are on windows. To run those files do to the root directory of your project (./a/)
and run this.
```bash
build
```
Then you should see a screen that looks like this
```
Welcome to Build. To exit do the command "exit".
```
To run a command do this for example
```bash
Welcome to Build. To exit do the command "exit".
run:
Hello, World!
exit
```
Good job you now know how to use Build!
