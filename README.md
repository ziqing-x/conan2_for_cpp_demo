<p align="center">
  <h3 align="center">conan2_for_cpp_demo</h3>
  <p align="center">
    个人使用的c++项目模版，用于快速搭建c++项目，并使用conan管理依赖
  <br>
</p>

<p align="center">
    <a href="#Language" alt="Language"><img src="https://img.shields.io/badge/language-cmake%20%7C%20shell%20%7C%20c%2Fc%2B%2B-blue" /></a>
    <a href="#arch" alt="arch"><img src="https://img.shields.io/badge/arch-arm|x86%20-important" /></a>
    <a href="#platform" alt="platform"><img src="https://img.shields.io/badge/platform-ubuntu|debian|kali-blueviolet" /></a>
</p>

***
- 索引
  - [工程结构](#工程结构)
  - [编译环境搭建](#编译环境搭建)
  - [构建代码](#构建代码)
  - [打包固件](#打包固件)
  - [安装固件](#安装固件)
  - [设备里常用命令](#设备里常用命令)

### 工程结构
```bash
├── cmake
│   ├── colors.cmake
│   ├── debug.cmake
│   ├── git_hash.cmake
│   ├── option.cmake
│   ├── pack.cmake            # deb打包
│   └── static_check.cmake
├── CMakeLists.txt
├── conanfile.txt             # 依赖管理
├── config
│   └── config.yaml
├── postinst                  # deb包安装后处理脚本
├── profiles                  # 交叉编译配置文件
│   ├── jetson                # jetson编译环境
│   └── pc                    # pc编译环境
├── README.md
├── scripts
│   ├── build.sh              # 编译脚本
│   ├── install_to_device.sh  # 编译、打包、并安装到目标设备脚本
│   └── pack.sh               # 打包脚本
├── service
│   └── app.service
└── src
    ├── app                   # 业务代码
    ├── CMakeLists.txt
    ├── main.cpp              # 主函数
    └── test                  # 单元测试
```

### 编译环境搭建
+ 安装交叉编译器，并把编译器的路径添加到环境变量中；
+ 安装 cmake
```bash
sudo apt install cmake make
```
+ 安装 conan 依赖管理器
```bash
sudo apt install python-pip
sudo pip install conan
```
+ 安装其他工具
```bash
sudo apt install git cppcheck sshpass
```

### 构建代码

```bash
./scripts/build.sh -b
或者
cd ./scripts && ./build.sh -b
# 绝对路径运行脚本也是可以的
```
### 打包固件

```bash
./scripts/pack.sh
或者
cd ./scripts && ./pack.sh
# 绝对路径运行脚本也是可以的
```

### 安装固件

```bash
./scripts/install_to_device.sh
或者
cd ./scripts && ./install_to_device.sh
# 绝对路径运行脚本也是可以的
```

### 设备里常用命令

```bash
sudo systemctl enable mydemo.service # 打开开机自启动
sudo systemctl disable mydemo.service # 关闭禁止自启动
sudo systemctl restart restart mydemo.service # 重启服务
sudo systemctl start mydemo.service # 启动服务
sudo systemctl stop mydemo.service # 停止服务
sudo systemctl status mydemo.service # 查看服务状态
sudo dpkg -r cn.xxx.mydemo # 卸载软件包
sudo dpkg -I cn.xxx.mydemo # 查看软件包信息
sudo dpkg -L cn.xxx.mydemo # 查看软件包的目录结构
sudo tail -n 200 -f /opt/cn.xxx.mydemo/log/mydemo.log # 查看日志
```

***
👩‍💻 <font color = green>问题反馈:</font> jassimxiong@gmail.com


<p align="center">Copyright (C), 2018-2024, xxx，版权所有.<p>
