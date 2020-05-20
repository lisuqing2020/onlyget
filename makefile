src = $(wildcard src/*.cc)
obj = $(patsubst src/%.cc, build/%.o, $(src))
tar = build/onlyget
ccc = g++ -std=c++11

$(tar):$(obj)
	$(ccc) $(obj) -o $(tar) -Iinclude -lpthread

build/%.o:src/%.cc
	$(ccc) -c $< -o $@ -Iinclude

.PHONY:clean
clean:
	rm -f build/*.o