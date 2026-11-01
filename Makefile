# 誤ったアーキテクチャ(aarch64)の混入を防ぐため、正しいパスを明示的に指定します
export PKG_CONFIG_PATH := C:\msys64\mingw64\lib\pkgconfig;C:\msys64\mingw64\share\pkgconfig

CXX = g++
CC = gcc
CXXFLAGS = -Wall -Wextra -O2 -std=c++17 -Iinclude $(shell pkg-config --cflags gtkmm-4.0)
LIBS = $(shell pkg-config --libs gtkmm-4.0) -lole32 -loleaut32 -lpdh -lwlanapi -lrpcns4 -lrpcrt4
WIDL ?= widl

# 実行ファイル名
TARGET = MyLang.exe

# RPCインターフェース
RPC_IDL = src/logic/modules/WindowsAPIs/ServiceInterfacesController/MyInterface.idl
RPC_HEADER = src/logic/modules/WindowsAPIs/ServiceInterfacesController/MyInterface.h
RPC_SERVER_STUB = src/logic/modules/WindowsAPIs/ServiceInterfacesController/MyInterface_s.c
RPC_SERVER_STUB_OBJ = src/logic/modules/WindowsAPIs/ServiceInterfacesController/MyInterface_s.o

# ソースファイルのリスト
SRCS = main.cpp \
	   src/logic/modules/WindowsAPIs/ServiceInterfacesController/RpcServer.cpp \

ASM_SRCS = src/logic/modules/Mathematics/x86-64.ASM

# オブジェクトファイル名のリバース生成
OBJS = $(SRCS:.cpp=.o) $(ASM_SRCS:.ASM=.o) $(RPC_SERVER_STUB_OBJ)

ifeq ($(OS),Windows_NT)
RM = cmd /C del /Q /F
else
RM = rm -f
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

# RPCスタブをIDLから生成
$(RPC_HEADER): $(RPC_IDL)
	$(WIDL) --win64 -h -o $@ $<

$(RPC_SERVER_STUB): $(RPC_IDL) $(RPC_HEADER)
	$(WIDL) --win64 -s -o $@ $<

main.o src/logic/modules/WindowsAPIs/ServiceInterfacesController/RpcServer.o: $(RPC_HEADER)

$(RPC_SERVER_STUB_OBJ): $(RPC_SERVER_STUB) $(RPC_HEADER)
	$(CC) -Isrc/logic/modules/WindowsAPIs/ServiceInterfacesController -c $< -o $@

# 個別のコンパイルルール
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.ASM
	$(CXX) -x assembler -c $< -o $@

clean:
	$(RM) $(OBJS) $(TARGET) $(RPC_HEADER) $(RPC_SERVER_STUB)

# Windowsでの実行用
run: all
	./$(TARGET)

.PHONY: all clean run