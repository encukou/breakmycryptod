all: breakmycryptod

breakmycryptod: breakmycryptod.c
	gcc breakmycryptod.c -o breakmycryptod

clean:
	rm breakmycryptod
