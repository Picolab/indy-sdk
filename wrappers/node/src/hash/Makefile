
libhash.a: hash.o
	@ar ru $@ $^
	@ranlib $@
	@cp -r $@ ../../include

hash.o: hash.c
	@$(CC) -std=c99 -mmacosx-version-min=10.7 -c $^ -o $@

test:
	@$(CC) -std=c99 -DTEST_HASH hash.c -o $@
	@./test

clean:
	@rm ./*.{o,a}
	@rm -f test hash.o libhash.a
