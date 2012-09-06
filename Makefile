all: breakmycryptod

breakmycryptod: breakmycryptod.c
	gcc breakmycryptod.c -o breakmycryptod

clean:
	rm breakmycryptod

install: breakmycryptod
	cp breakmycryptod /usr/sbin
	cp breakmycryptod.service /usr/lib/systemd/system/
