
# Ubunut 16.04

<br />
<br />

### 安装依赖库以及构建工具

    sudo apt-get update
    sudo apt-get install build-essential cmake git libboost-dev libboost-all-dev libncurses5-dev libreadline-dev autoconf
  
<br />  
  
### 编译第三方依赖

    git clone https://github.com/cdcchain/cdc-core.git
    cd cdc-core
    git submodule update --init
    cd dependence
    git pull origin master
    sh build.sh
    cd ..

<br />

### 编译cdc正式链底层
    
    rm -rf CMakeCache.txt  CMakeFiles  cmake_install.cmake Makefile
    cmake .
    make

<br />

### 编译cdc测试链底层

    rm -rf CMakeCache.txt  CMakeFiles  cmake_install.cmake Makefile
    cmake -DTESTNET=ON .
    make
    
