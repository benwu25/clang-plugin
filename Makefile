all:
	clang++ -g -Wall -Wno-unused-variable -Werror -fPIC -shared -I/usr/lib/llvm-18/include -L/usr/lib/llvm-18/lib -o libClangPlugin.so clang-plugin.cpp

test: all
	clang++ -g -fplugin=./libClangPlugin.so -fplugin-arg-ClangPlugin-hi main.cpp

clean:
	rm libClangPlugin.so

clean2: clean
	rm a.out
