CXX = g++
CXXFLAGS = -Wall

proj4: proj4.cpp CipherTool.o Cipher.o Scytale.o Ong.o Atbash.o
	$(CXX) $(CXXFLAGS) proj4.cpp CipherTool.o Cipher.o Scytale.o Ong.o Atbash.o -o proj4

CipherTool.o: CipherTool.h CipherTool.cpp Cipher.o Scytale.o Ong.o Atbash.o
	$(CXX) $(CXXFLAGS) -c CipherTool.cpp

Cipher.o: Cipher.h Cipher.cpp
	$(CXX) $(CXXFLAGS) -c Cipher.cpp

Scytale.o: Scytale.h Scytale.cpp Cipher.o
	$(CXX) $(CXXFLAGS) -c Scytale.cpp

Ong.o: Ong.h Ong.cpp Cipher.o
	$(CXX) $(CXXFLAGS) -c Ong.cpp

Atbash.o: Atbash.h Atbash.cpp Cipher.o
	$(CXX) $(CXXFLAGS) -c Atbash.cpp

val:
	valgrind ./proj4

run:
	./proj4

clean:
	rm *~
	rm *.o
submit:
	cp proj4.cpp CipherTool.h CipherTool.cpp Cipher.h Cipher.cpp Scytale.h Scytale.cpp Ong.h Ong.cpp Atbash.h Atbash.cpp ~/cs202proj/proj4

