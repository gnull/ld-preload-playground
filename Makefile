lib = liboverlay.so

CFLAGS += -shared -fPIC -fPIE -ldl

LDFLAGS += -shared

$(lib): main.o lib.o open.o
	gcc $(CFLAGS) -o $@ $^

clean:
	@rm -rf $(tests) $(lib)

.PHONY: all test
