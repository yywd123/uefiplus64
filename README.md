# UEFI++64

## 简介
这是一个轻量的,易于部署的,为amd64架构设计的uefi开发框架

![构建速度](res/fast_build.png)

## 注意事项
- 本项目依赖[xmake构建系统](https://xmake.io "xmake官方网站"),请自行安装
- 编译仅支持x86_64架构的linux工具链,如有需要请使用交叉编译器构建项目

## 使用方法
1. 在src目录下编写源码
2. 在项目根目录运行`xmake`以编译(编译输出将会被保存在`build`文件夹)

## 依赖
- [nanoprintf](https://github.com/charlesnicholson/nanoprintf)