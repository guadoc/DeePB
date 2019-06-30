################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/table_lib/AbstractTable.cpp \
../src/table_lib/GUI.cpp \
../src/table_lib/State.cpp \
../src/table_lib/TableGUI.cpp \
../src/table_lib/TableLogs.cpp \
../src/table_lib/TableTrain.cpp \
../src/table_lib/Tracker.cpp 

OBJS += \
./src/table_lib/AbstractTable.o \
./src/table_lib/GUI.o \
./src/table_lib/State.o \
./src/table_lib/TableGUI.o \
./src/table_lib/TableLogs.o \
./src/table_lib/TableTrain.o \
./src/table_lib/Tracker.o 

CPP_DEPS += \
./src/table_lib/AbstractTable.d \
./src/table_lib/GUI.d \
./src/table_lib/State.d \
./src/table_lib/TableGUI.d \
./src/table_lib/TableLogs.d \
./src/table_lib/TableTrain.d \
./src/table_lib/Tracker.d 


# Each subdirectory must supply rules for building sources it contributes
src/table_lib/%.o: ../src/table_lib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -lSDL2 -lSDL2_image -D_GLIBCXX_USE_CXX11_ABI=0 -I/home/walnutalgo/workspace/libtorch/include/torch/csrc/api/include -I/home/walnutalgo/workspace/libtorch/include -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


