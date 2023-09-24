mkdir bin
cd bin
cmake ../backend -DBUILD_SHARED_LIBS=OFF -DBUILD_STATIC_LIBS=ON -DBUILD_TESTS=ON -DBUILD_EXAMPLES=OFF 
cmake --build .
