################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../expression.cpp \
../main.cpp \
../parser.cpp \
../term.cpp \
../var.cpp 

OBJS += \
./expression.o \
./main.o \
./parser.o \
./term.o \
./var.o 

CPP_DEPS += \
./expression.d \
./main.d \
./parser.d \
./term.d \
./var.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


