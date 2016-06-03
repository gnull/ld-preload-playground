lib  = liboverlay.so
objs = main.o lib.o open.o dir.o

PREFIX ?= /usr/

CFLAGS += -shared -fPIC -fPIE -ldl
LDFLAGS += -shared -pie

$(lib): $(objs)
	ld $(LDFLAGS) -ldl -o $@ $^

install: $(lib)
	mkdir -p $(PREFIX)/lib/
	install --strip -m 755 $(lib) $(PREFIX)/lib/

clean:
	@rm -rf $(objs) $(lib)

.PHONY: all test
