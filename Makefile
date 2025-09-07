all:
	/home/benwu25/Documents/mirror/llvm-project/install/bin/clang++ -g -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -Werror -fPIC -shared -I/home/benwu25/Documents/mirror/llvm-project/install/include/ -L/home/benwu25/Documents/mirror/llvm-project/install/lib -o libClangPlugin.so clang-plugin.cpp

test: all
	/home/benwu25/Documents/mirror/llvm-project/install/bin/clang++ -g -fplugin=./libClangPlugin.so -fplugin-arg-ClangPlugin-hi main.cpp

clean:
	rm libClangPlugin.so

clean2: clean
	rm a.out
