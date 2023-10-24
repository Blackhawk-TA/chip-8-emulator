build-linux:
	rm -rf ./build
	mkdir -p ./build
	cmake -DCMAKE_BUILD_TYPE=RELEASE -S . -B ./build
	cmake --build ./build --parallel 16
