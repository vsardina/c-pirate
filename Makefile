final: final.o finalfunc.o
	gcc final.o finalfunc.o gfx4.o -lm -lX11 -o final 

final.o: final.c finalfunc.h
	gcc -c final.c -o final.o

finalfunc.o: finalfunc.c
	gcc -c finalfunc.c gfx4.o -o finalfunc.o

clean:
	rm *.o final
