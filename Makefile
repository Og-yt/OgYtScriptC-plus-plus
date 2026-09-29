# 誤ったアーキテクチャ(aarch64)の混入を防ぐため、正しいパスを明示的に指定します
export PKG_CONFIG_PATH := C:\msys64\mingw64\lib\pkgconfig;C:\msys64\mingw64\share\pkgconfig

CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++17 -Iinclude $(shell pkg-config --cflags gtkmm-4.0)
LIBS = $(shell pkg-config --libs gtkmm-4.0) -lpdh -lopengl32 -lglu32 -lm -lpsapi

# 実行ファイル名
TARGET = MyLang.exe

# ソースファイルのリスト
SRCS = main.cpp \
	   src/ui/ui.cpp \

# オブジェクトファイル名のリバース生成
OBJS = $(SRCS:.cpp=.o)

ifeq ($(OS),Windows_NT)
RM = cmd /C del /Q /F
else
RM = rm -f
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

# 個別のコンパイルルール
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(TARGET)

# Windowsでの実行用
run: all
	./$(TARGET)

.PHONY: all clean run