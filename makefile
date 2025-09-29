build: sqlite3.o
	rm -f a.out
	g++ -std=c++20 -g -Wall -pedantic -Werror main.cpp movie.cpp sqlite3.o -lm -Wno-unused-variable -Wno-unused-function

sqlite3.o:
	gcc -c -O2 sqlite3.c

run:
	./a.out

clean:
	rm -f sqlite3.o a.out

submit:
	/gradescope/gs submit 1130317 6854916 main.cpp movie.cpp
  
commit:
	git add .
	git commit -m "$(msg)"

push:
	git push origin main