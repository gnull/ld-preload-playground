lib = liboverlay.so

PREFIX ?= /usr/

CFLAGS += -shared -fPIC -fPIE -ldl
LDFLAGS += -shared -pie

$(lib): main.o lib.o open.o dir.o
	ld $(LDFLAGS) -ldl -o $@ $^

install: $(lib)
	mkdir -p $(PREFIX)/lib/
	install --strip -m 755 $(lib) $(PREFIX)/lib/

clean:
	@rm -rf $(tests) $(lib)

.PHONY: all test
