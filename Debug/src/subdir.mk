################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/PQL.cpp 

OBJS += \
./src/PQL.o 

CPP_DEPS += \
./src/PQL.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -lSDL2 -lSDL2_image -D_GLIBCXX_USE_CXX11_ABI=0 -I/home/walnutalgo/workspace/libtorch/include/torch/csrc/api/include -I/home/walnutalgo/workspace/libtorch/include -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


