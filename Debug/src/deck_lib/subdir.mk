################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/deck_lib/Card.cpp \
../src/deck_lib/Deck.cpp \
../src/deck_lib/Hand.cpp \
../src/deck_lib/HandTest.cpp 

OBJS += \
./src/deck_lib/Card.o \
./src/deck_lib/Deck.o \
./src/deck_lib/Hand.o \
./src/deck_lib/HandTest.o 

CPP_DEPS += \
./src/deck_lib/Card.d \
./src/deck_lib/Deck.d \
./src/deck_lib/Hand.d \
./src/deck_lib/HandTest.d 


# Each subdirectory must supply rules for building sources it contributes
src/deck_lib/%.o: ../src/deck_lib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -lSDL2 -lSDL2_image -D_GLIBCXX_USE_CXX11_ABI=0 -I/home/walnutalgo/workspace/libtorch/include/torch/csrc/api/include -I/home/walnutalgo/workspace/libtorch/include -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


