# hl_mai_23_grpc

#GRPC

sudo apt install -y build-essential autoconf libtool pkg-config

git clone --recurse-submodules -b v1.43.0 https://github.com/grpc/grpc

cd grpc

mkdir -p cmake/build

pushd cmake/build

cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
      ../..
      
make -j

make install

popd
 
