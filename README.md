# t3
An open source toy game framework build by [tictactoe game developer community](https://discord.gg/68Av3VXYsr).

### prerequisites
* LLVM clang compiler for your preferred platform. (You can run with others tbh. But you should compile & build with your own way.)
* SDL 2.28 + and SDL_Image extension 2.8.1 + versions installed on your system. Here is a good tutorial: [Lazy Foo's SDL Tutorials](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php)

### how to install
* If you have the prerequisites, go to `t3-build.c` file. Set your `ENGINE_ROOT` path there.
* Make sure `INCLUDE_DIRECTORIES` macro has correct paths for your environment.
* Make sure `LINKER` macro is appropriate for your environment.
* Go to your cmd / terminal / etc and inside project root type `cd`.  type `clang -o t3-build t3-build.c`
* run t3-build with .`/t3-build` or `t3-build.exe` . Your project build will be inside `ENGINE_ROOT/Build`

### documentation
* Yes, we have one at [here](docs/welcome.md)

### contribute ?
* Join our discord community [tictactoe](https://discord.gg/xPNvy3ZHgw)
* t3 channel is the place you're looking for.
* Read the coding standards
* If you have an idea to implement, let's discuss it on discord. 
If you don't have an idea but want to contribute, we have a projects page. 
Check it for any todo's that you can do. 
