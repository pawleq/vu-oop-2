app: main.o Student.o App.o
	g++ main.o Student.o App.o -o app

main.o: src/main.cpp
	g++ -c src/main.cpp

Student.o: src/Student.cpp
	g++ -c src/Student.cpp

App.o: src/App.cpp
	g++ -c src/App.cpp

clean:
	rm *.o app