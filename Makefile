lib = liboverlay.so

CFLAGS += -shared -fPIC -fPIE -ldl

LDFLAGS += -shared -pie

$(lib): main.o lib.o open.o dir.o
	ld $(LDFLAGS) -ldl -o $@ $^

clean:
	@rm -rf $(tests) $(lib)

.PHONY: all test
