CFLAGS = -g `pkg-config --cflags opencv` `pkg-config --libs opencv` 

all:
	gcc -c ../src/tpl.c -o tpl.o
	gcc $(CFLAGS) tplTest.c tpl.o

clean:
	rm -f *.o
	rm -f -r a.out*
	rm -f *.jpg
	rm -f *.dat
	rm -f *.tpl


