test: all
	clang++ -g -O1 -fplugin=./libClangPlugin.so main.cpp

all: my-pass.o
	clang++ -g -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -Wno-unused-but-set-variable -Werror -fPIC -shared -I/usr/local/include/ -L/usr/local/lib -o libClangPlugin.so clang-plugin.cpp my-pass.o

my-pass.o: my-pass.h
	clang++ -g -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -Werror -fPIC -I/usr/local/include -c -o my-pass.o my-pass.cpp

clean:
	rm libClangPlugin.so

clean2: clean
	rm a.out my-pass.o
