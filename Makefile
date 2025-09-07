test: all
	/home/benwu25/Documents/mirror/llvm-project/debug-install/bin/clang++ -g -O1 -fplugin=./libClangPlugin.so main.cpp


all: my-pass.o
	/home/benwu25/Documents/mirror/llvm-project/debug-install/bin/clang++ -g -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -Werror -fPIC -shared -I/home/benwu25/Documents/mirror/llvm-project/debug-install/include/ -L/home/benwu25/Documents/mirror/llvm-project/debug-install/lib -o libClangPlugin.so clang-plugin.cpp my-pass.o

my-pass.o: my-pass.h
	/home/benwu25/Documents/mirror/llvm-project/debug-install/bin/clang++ -g -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -Werror -fPIC -I/home/benwu25/Documents/mirror/llvm-project/debug-install/include -c -o my-pass.o my-pass.cpp


clean:
	rm libClangPlugin.so

clean2: clean
	rm a.out my-pass.o
