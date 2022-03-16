all:
	$(CXX) -std=c++17 add_custom_section.cc -l binaryen -l pthread -o add_custom_section

test:
	./add_custom_section example.wasm example-out.wasm myname mydata
	wasm-dis example-out.wasm | grep 'custom section "myname", size 6, contents: "mydata"'
