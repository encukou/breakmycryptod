all: breakmycryptod

breakmycryptod: breakmycryptod.c
	gcc breakmycryptod.c -o breakmycryptod

clean:
	rm breakmycryptod

breakmycryptod.1: breakmycryptod.1.txt
	a2x --doctype manpage --format manpage $<

breakmycryptod.1.gz: breakmycryptod.1
	gzip -c $< > $@

install: breakmycryptod breakmycryptod.1.gz
	cp breakmycryptod /usr/sbin
	cp breakmycryptod.service /usr/lib/systemd/system/
	cp breakmycryptod.1.gz /usr/share/man/man1/
