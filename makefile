CFLAGS = -Wall -g3 
CPPFLAGS = -O3 -Wall -march=i386 
LDLIBS = $(shell /bin/find /usr/lib -iname "libstdc++.a" -and -not -ipath "*debug*" -type f -print) $(shell /bin/find /usr/local/lib -iname "libstdc++.a" -and -not -ipath "*debug*" -type f -print)  
LDFLAGS = --strip-all

SOURCES = args.cpp main.cpp parser.cpp quoted.cpp string.cpp touplparser.cpp langs/cpp.cpp langs/csharp.cpp langs/java.cpp langs/js.cpp langs/lua.cpp langs/php.cpp langs/python.cpp langs/vb.cpp
APP = toupl

all: $(APP)

clean:
	rm -f *.o
	rm -f langs/*.o

$(APP): $(SOURCES:.cpp=.o)
	$(LINK.o) $^ $(LDLIBS) -o $@