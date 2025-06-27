# Redis 服务器 (C++ 实现)

这是一个使用 C++ 实现的简易、多线程的 Redis 服务器。

## 特性

*   支持 `SET` 和 `GET` 命令
*   使用多线程并发处理客户端连接
*   代码结构清晰，模块化设计：
    *   **网络 (Network)**: 负责处理 TCP 连接。
    *   **命令 (Command)**: 负责解析和执行 Redis 命令。
    *   **存储 (Storage)**: 负责数据的内存存储。

## 如何构建

本项目使用 CMake 进行构建。

```bash
# 1. 创建 build 目录
mkdir build

# 2. 进入 build 目录
cd build

# 3. 生成 Makefile
cmake ..

# 4. 编译
make
```

## 如何运行

编译成功后，`redis-server` 可执行文件会生成在 `build` 目录下。

```bash
./redis-server
```

服务器将在默认端口 `6379` 上启动并监听连接。

## 项目结构

```
.
├── CMakeLists.txt      # CMake 构建脚本
├── main.cpp            # 程序主入口
├── README.md           # 项目说明
└── src/                # 源代码目录
    ├── command.cpp
    ├── command.h
    ├── network.cpp
    ├── network.h
    ├── storage.cpp
    └── storage.h
```
