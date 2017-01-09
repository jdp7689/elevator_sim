################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CS404_HW7.cpp \
../src/Elevator.cpp \
../src/ElevatorBase.cpp \
../src/ElevatorSim.cpp \
../src/Floor.cpp \
../src/Person.cpp 

OBJS += \
./src/CS404_HW7.o \
./src/Elevator.o \
./src/ElevatorBase.o \
./src/ElevatorSim.o \
./src/Floor.o \
./src/Person.o 

CPP_DEPS += \
./src/CS404_HW7.d \
./src/Elevator.d \
./src/ElevatorBase.d \
./src/ElevatorSim.d \
./src/Floor.d \
./src/Person.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


