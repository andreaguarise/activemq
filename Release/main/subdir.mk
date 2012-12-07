################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../main/HelloWorldConsumer.cpp \
../main/HelloWorldProducer.cpp \
../main/main.cpp 

OBJS += \
./main/HelloWorldConsumer.o \
./main/HelloWorldProducer.o \
./main/main.o 

CPP_DEPS += \
./main/HelloWorldConsumer.d \
./main/HelloWorldProducer.d \
./main/main.d 


# Each subdirectory must supply rules for building sources it contributes
main/%.o: ../main/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/activemq-cpp-3.4.0 -O3 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


