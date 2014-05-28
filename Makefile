DESTDIR ?= /usr
SBINDIR ?= $(DESTDIR)/sbin
LIBDIR ?= $(DESTDIR)/lib
UNITDIR ?= $(LIBDIR)/systemd/system
MANDIR ?= $(DESTDIR)/share/man

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
	mkdir -p $(SBINDIR)
	cp breakmycryptod $(SBINDIR)/
	mkdir -p $(UNITDIR)
	cp breakmycryptod.service $(UNITDIR)/
	mkdir -p $(MANDIR)/man8/
	cp breakmycryptod.8.gz $(MANDIR)/man8/
