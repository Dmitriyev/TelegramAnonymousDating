mkdir bin_mds
cd bin_mds

build_aws=$1
aws_build_dir=$PWD/aws-sdk-cpp
aws_install_dir=$aws_build_dir/install

# aws sdk does not supports add_subdirectory function ¯\_(ツ)_/¯
if [ "$build_aws" == "build_aws" ]; then
    mkdir $aws_build_dir
    cd $aws_build_dir
    cmake ../../backend/thirdparty/aws-sdk-cpp -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=OFF -DENABLE_TESTING=OFF -DBUILD_ONLY="s3;sts" -DCMAKE_INSTALL_PREFIX=$aws_install_dir -DCMAKE_BUILD_TYPE=Release
    cmake --build .
    cmake --install .
    cd ../
fi

cmake ../backend/mds -DBUILD_SHARED_LIBS=OFF -DBUILD_STATIC_LIBS=ON -DBUILD_TESTS=ON -DBUILD_EXAMPLES=OFF -DCMAKE_BUILD_TYPE=Release -DAWS_SDK_PREFIX_PATH=$aws_install_dir
cmake --build .
