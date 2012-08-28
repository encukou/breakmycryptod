all: breakmycryptod

breakmycryptod:
	gcc breakmycryptod.c -o breakmycryptod

clean:
	rm breakmycryptod
