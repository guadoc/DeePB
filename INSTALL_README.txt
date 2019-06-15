SDL:

PyTorch
	- add to Project -> Properties -> C/C++ Build -> settings -> GCC C++ Compiler -> includes -> (-l) -> add
		- /home/walnutalgo/workspace/libtorch/include
		- /home/walnutalgo/workspace/libtorch/include/torch/csrc/api/include
	- add to Project -> Properties -> C/C++ Build -> settings -> GCC C++ Compiler -> preprocessor -> (-D) -> add 
		- _GLIBCXX_USE_CXX11_ABI=0 
	- add libraries (libtorch)
		- libpath = /home/walnutalgo/workspace/libtorch/lib
	- add to Project -> Properties -> C/C++ Build -> settings -> GCC C++ Linker -> add
		- -rpath "/home/walnutalgo/workspace/libtorch/lib"
		