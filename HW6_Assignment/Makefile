CXX=g++
CLINK=$(CXX)
CXXFLAGS=-g -Wall -std=c++11 -fpic
LIB= -linput -lfirewall -L.
OBJS=ip.o port.o string-array.o string.o 

RM=rm -rf

firewall.exe: $(OBJS) main.o libfirewall.so
	$(CLINK) $(OBJS) main.o -o firewall.exe $(LIB)
	
main.o: main.cpp port.h ip.h input.h
	$(CLINK) $(CXXFLAGS) -c main.cpp

libfirewall.so: firewall.o
	$(CXX) -shared $(OBJS) -o libfirewall.so $(LIB)

firewall.o: string.h ip.h port.h string-array.h
	$(CXX) $(CXXFLAGS) -c string.cpp ip.cpp port.cpp string-array.cpp

ip.o: ip.cpp ip.h string.h generic-field.h string-array.h
	$(CXX) $(CXXFLAGS) -c ip.cpp


port.o: port.cpp string.h string-array.h generic-field.h
	$(CXX) $(CXXFLAGS) -c port.cpp

string.o: string.cpp string.h
	$(CXX) $(CXXFLAGS) -c string.cpp

string-array.o: string-array.cpp string-array.h 
	$(CXX) $(CXXFLAGS) -c string-array.cpp

clean:
	$(RM) *.o firewall.exe libfirewall.so:

