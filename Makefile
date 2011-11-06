all: osbdm-test

.PHONY: test

CFLAGS = -std=gnu99 -Wall -Werror
DGFLAGS = -MMD -MP -MT $@

-include config.mak

-include osbdm-test.d

osbdm-test: main.c osbdm.c
	$(CC) -o $@ $(CPPFLAGS) $(DGFLAGS) $(CFLAGS) main.c osbdm.c $(LDFLAGS) -lusb-1.0

test: osbdm-test
	./osbdm-test

clean:
	-rm osbdm-test *.d
