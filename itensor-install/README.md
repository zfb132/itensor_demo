## 1. 安装ITensor步骤
1. 下载ITensor源码  
`git clone https://github.com/ITensor/ITensor itensor`  
注意：可以把此itensor文件夹移动到任何你想安装到的位置。另外，也可以下载[release版本](https://github.com/ITensor/ITensor/releases)的代码压缩包并解压
2. 进入该目录  
`cd itensor`
3. 安装blas和lapack包用于itensor的编译  
`sudo apt-get install libblas-dev liblapack-dev`
4. 创建并修改make的配置文件  
`cp options.mk.sample options.mk`  
`gedit options.mk`  
然后修改此文件：  
根据文件中的提示，分别更改三个部分  
    * 第一步：选择编译器，使用`GNU GCC compiler`，把其他的注释掉
    * 第二步：选择`BLAS/LAPACK`相关选项，使用`GNU/LINUX systems`，其他注释
    * 第三步：选择编译选项，保持默认即可，不需要修改
5. 编译源代码  
`make`  
6. 此时即可正常使用itensor  

修改后的`options.mk`文件关键部分示例：  
```txt
#########
## [1]
##
## Set which compiler to use by defining CCCOM:
## GNU GCC compiler
CCCOM=g++ -m64 -std=c++17 -fconcepts -fPIC

#########
## [2]
##
## BLAS/LAPACK Related Options
##

##
## Example using a C interface to LAPACK on GNU/LINUX systems
## (Path to lib/ folder may differ on your system)
##
PLATFORM=lapack
BLAS_LAPACK_LIBFLAGS=-lpthread -L/usr/lib -lblas -llapack
```


## 2. 如何创建和编译itensor项目
### 2.1 第一种方法（推荐）
1. 编写代码文件myappname.cpp和头文件myclass.h
2. 创建文件命名为Makefile，内容在下面
3. 编译项目
`make`
4. 此时项目文件夹下回生成myappname文件，运行代码
`./myappname`

Makefile文件的所有内容
```makefile
# 你的itensor在安装时的路径
LIBRARY_DIR=/home/zfb/itensor
# 如果你的main()函数在myappname.cpp文件中，那么就把此处设置为myappname
APP=myappname
# 如果你调用了myclass.h的自定义头文件，那么把它写在这里
HEADERS=myclass.h
# 如果还有其他cpp文件，也写在CCFILES里面，以空格分隔文件
CCFILES=$(APP).cpp

#--------- 以下内容无需修改 -----------
include $(LIBRARY_DIR)/this_dir.mk
include $(LIBRARY_DIR)/options.mk
TENSOR_HEADERS=$(LIBRARY_DIR)/itensor/core.h
#Mappings --------------
OBJECTS=$(patsubst %.cpp,%.o, $(CCFILES))
GOBJECTS=$(patsubst %,.debug_objs/%, $(OBJECTS))
#Rules ------------------
%.o: %.cpp $(HEADERS) $(TENSOR_HEADERS)
        $(CCCOM) -c $(CCFLAGS) -o $@ $<

.debug_objs/%.o: %.cpp $(HEADERS) $(TENSOR_HEADERS)
        $(CCCOM) -c $(CCGFLAGS) -o $@ $<
#Targets -----------------
build: $(APP)
debug: $(APP)-g
$(APP): $(OBJECTS) $(ITENSOR_LIBS)
        $(CCCOM) $(CCFLAGS) $(OBJECTS) -o $(APP) $(LIBFLAGS)
$(APP)-g: mkdebugdir $(GOBJECTS) $(ITENSOR_GLIBS)
        $(CCCOM) $(CCGFLAGS) $(GOBJECTS) -o $(APP)-g $(LIBGFLAGS)
clean:
        rm -fr .debug_objs *.o $(APP) $(APP)-g
mkdebugdir:
        mkdir -p .debug_objs
```
**注意**：这里换行之后必须用TAB键缩进，不能用空格
### 2.2 第二种方法
1. 编写代码文件test.cpp和头文件myclass.h
2. 编译项目
```bash
g++ -m64 -std=c++17 -fPIC -c -I. -I/home/zfb/itensor -o test.o test.cpp
g++ -m64 -std=c++17 -fPIC -I. -I/home/zfb/itensor test.o -o test -L/home/zfb/itensor/lib -litensor -lpthread -L/usr/lib -lblas -llapack
```
3. 此时项目文件夹下回生成test文件，运行代码
`./test`
