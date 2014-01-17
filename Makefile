all: breakmycryptod breakmycryptod.8.gz

breakmycryptod: breakmycryptod.c
	gcc breakmycryptod.c -o breakmycryptod

clean:
	rm breakmycryptod || :
	rm breakmycryptod.8 || :
	rm breakmycryptod.8.gz || :

breakmycryptod.8: breakmycryptod.8.txt
	a2x --doctype manpage --format manpage $<

breakmycryptod.8.gz: breakmycryptod.8
	gzip -c $< > $@

install: breakmycryptod breakmycryptod.8.gz
	cp breakmycryptod /usr/sbin
	cp breakmycryptod.service /usr/lib/systemd/system/
	cp breakmycryptod.8.gz /usr/share/man/man8/
