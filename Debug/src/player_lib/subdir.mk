################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/player_lib/AbstractPlayer.cpp \
../src/player_lib/PlayerBot.cpp \
../src/player_lib/PlayerBotV1.cpp \
../src/player_lib/PlayerBotV2.cpp \
../src/player_lib/PlayerGUI.cpp \
../src/player_lib/PlayerLogs.cpp \
../src/player_lib/PlayerRandom.cpp \
../src/player_lib/StatPlayer.cpp 

OBJS += \
./src/player_lib/AbstractPlayer.o \
./src/player_lib/PlayerBot.o \
./src/player_lib/PlayerBotV1.o \
./src/player_lib/PlayerBotV2.o \
./src/player_lib/PlayerGUI.o \
./src/player_lib/PlayerLogs.o \
./src/player_lib/PlayerRandom.o \
./src/player_lib/StatPlayer.o 

CPP_DEPS += \
./src/player_lib/AbstractPlayer.d \
./src/player_lib/PlayerBot.d \
./src/player_lib/PlayerBotV1.d \
./src/player_lib/PlayerBotV2.d \
./src/player_lib/PlayerGUI.d \
./src/player_lib/PlayerLogs.d \
./src/player_lib/PlayerRandom.d \
./src/player_lib/StatPlayer.d 


# Each subdirectory must supply rules for building sources it contributes
src/player_lib/%.o: ../src/player_lib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -lSDL2 -lSDL2_image -D_GLIBCXX_USE_CXX11_ABI=0 -I/home/walnutalgo/workspace/libtorch/include/torch/csrc/api/include -I/home/walnutalgo/workspace/libtorch/include -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


