lib = overlay.so

tests_c = $(wildcard test_*.c)
tests = $(patsubst %.c, %, $(tests_c))

test: $(tests) $(lib)
	@for t in $(tests); do \
		echo "=== $$t ==="; \
		env LD_PRELOAD=$(lib) ./$$t; \
	done;

$(lib): overlay.c
	gcc $(CFLAGS) -shared -fPIC -fPIE -ldl -o $@ $^

clean:
	@rm -rf $(tests) $(lib)

.PHONY: all test
