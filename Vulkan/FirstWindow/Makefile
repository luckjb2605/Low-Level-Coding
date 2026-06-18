CXX = g++

SRC = main.cpp
OUT = app.exe

VULKAN_SDK = C:/VulkanSDK/1.4.321.1

INCLUDES = ^
	-I$(VULKAN_SDK)/Include ^
	-I"C:/msys64/ucrt64/include"

LIBS = ^
	-L$(VULKAN_SDK)/Lib ^
	-lvulkan-1 ^
	-lglfw3

CXXFLAGS = -std=c++20

all:
	$(CXX) $(SRC) -o $(OUT) $(CXXFLAGS) $(INCLUDES) $(LIBS)