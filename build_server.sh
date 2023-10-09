mkdir bin_server
cd bin_server
cmake ../backend/server -DBUILD_SHARED_LIBS=OFF -DBUILD_STATIC_LIBS=ON -DBUILD_TESTS=ON -DBUILD_EXAMPLES=OFF -DCMAKE_BUILD_TYPE=Release 
cmake --build .
