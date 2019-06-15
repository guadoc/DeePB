################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/train_lib/Evolution.cpp \
../src/train_lib/Session.cpp 

OBJS += \
./src/train_lib/Evolution.o \
./src/train_lib/Session.o 

CPP_DEPS += \
./src/train_lib/Evolution.d \
./src/train_lib/Session.d 


# Each subdirectory must supply rules for building sources it contributes
src/train_lib/%.o: ../src/train_lib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -lSDL2 -lSDL2_image -D_GLIBCXX_USE_CXX11_ABI=0 -I/home/walnutalgo/workspace/libtorch/include/torch/csrc/api/include -I/home/walnutalgo/workspace/libtorch/include -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


