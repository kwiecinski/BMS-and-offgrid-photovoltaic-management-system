#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Balancer-AVR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Balancer-AVR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=mcc_generated_files/adc/src/adc0.c mcc_generated_files/dac/src/dac0.c mcc_generated_files/i2c_host/src/twi0.c mcc_generated_files/system/src/clock.c mcc_generated_files/system/src/protected_io.S mcc_generated_files/system/src/pins.c mcc_generated_files/system/src/interrupt.c mcc_generated_files/system/src/config_bits.c mcc_generated_files/system/src/system.c mcc_generated_files/timer/src/tca0.c mcc_generated_files/timer/src/tcd0.c mcc_generated_files/timer/src/tcb0.c mcc_generated_files/timer/src/delay.c mcc_generated_files/uart/src/usart1.c mcc_generated_files/uart/src/usart0.c mcc_generated_files/vref/src/vref.c main.c uart_remap.c adc_conv.c ina226.c balance_cells.c inits.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/mcc_generated_files/adc/src/adc0.o ${OBJECTDIR}/mcc_generated_files/dac/src/dac0.o ${OBJECTDIR}/mcc_generated_files/i2c_host/src/twi0.o ${OBJECTDIR}/mcc_generated_files/system/src/clock.o ${OBJECTDIR}/mcc_generated_files/system/src/protected_io.o ${OBJECTDIR}/mcc_generated_files/system/src/pins.o ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o ${OBJECTDIR}/mcc_generated_files/system/src/system.o ${OBJECTDIR}/mcc_generated_files/timer/src/tca0.o ${OBJECTDIR}/mcc_generated_files/timer/src/tcd0.o ${OBJECTDIR}/mcc_generated_files/timer/src/tcb0.o ${OBJECTDIR}/mcc_generated_files/timer/src/delay.o ${OBJECTDIR}/mcc_generated_files/uart/src/usart1.o ${OBJECTDIR}/mcc_generated_files/uart/src/usart0.o ${OBJECTDIR}/mcc_generated_files/vref/src/vref.o ${OBJECTDIR}/main.o ${OBJECTDIR}/uart_remap.o ${OBJECTDIR}/adc_conv.o ${OBJECTDIR}/ina226.o ${OBJECTDIR}/balance_cells.o ${OBJECTDIR}/inits.o
POSSIBLE_DEPFILES=${OBJECTDIR}/mcc_generated_files/adc/src/adc0.o.d ${OBJECTDIR}/mcc_generated_files/dac/src/dac0.o.d ${OBJECTDIR}/mcc_generated_files/i2c_host/src/twi0.o.d ${OBJECTDIR}/mcc_generated_files/system/src/clock.o.d ${OBJECTDIR}/mcc_generated_files/system/src/protected_io.o.d ${OBJECTDIR}/mcc_generated_files/system/src/pins.o.d ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o.d ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o.d ${OBJECTDIR}/mcc_generated_files/system/src/system.o.d ${OBJECTDIR}/mcc_generated_files/timer/src/tca0.o.d ${OBJECTDIR}/mcc_generated_files/timer/src/tcd0.o.d ${OBJECTDIR}/mcc_generated_files/timer/src/tcb0.o.d ${OBJECTDIR}/mcc_generated_files/timer/src/delay.o.d ${OBJECTDIR}/mcc_generated_files/uart/src/usart1.o.d ${OBJECTDIR}/mcc_generated_files/uart/src/usart0.o.d ${OBJECTDIR}/mcc_generated_files/vref/src/vref.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/uart_remap.o.d ${OBJECTDIR}/adc_conv.o.d ${OBJECTDIR}/ina226.o.d ${OBJECTDIR}/balance_cells.o.d ${OBJECTDIR}/inits.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/mcc_generated_files/adc/src/adc0.o ${OBJECTDIR}/mcc_generated_files/dac/src/dac0.o ${OBJECTDIR}/mcc_generated_files/i2c_host/src/twi0.o ${OBJECTDIR}/mcc_generated_files/system/src/clock.o ${OBJECTDIR}/mcc_generated_files/system/src/protected_io.o ${OBJECTDIR}/mcc_generated_files/system/src/pins.o ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o ${OBJECTDIR}/mcc_generated_files/system/src/system.o ${OBJECTDIR}/mcc_generated_files/timer/src/tca0.o ${OBJECTDIR}/mcc_generated_files/timer/src/tcd0.o ${OBJECTDIR}/mcc_generated_files/timer/src/tcb0.o ${OBJECTDIR}/mcc_generated_files/timer/src/delay.o ${OBJECTDIR}/mcc_generated_files/uart/src/usart1.o ${OBJECTDIR}/mcc_generated_files/uart/src/usart0.o ${OBJECTDIR}/mcc_generated_files/vref/src/vref.o ${OBJECTDIR}/main.o ${OBJECTDIR}/uart_remap.o ${OBJECTDIR}/adc_conv.o ${OBJECTDIR}/ina226.o ${OBJECTDIR}/balance_cells.o ${OBJECTDIR}/inits.o

# Source Files
SOURCEFILES=mcc_generated_files/adc/src/adc0.c mcc_generated_files/dac/src/dac0.c mcc_generated_files/i2c_host/src/twi0.c mcc_generated_files/system/src/clock.c mcc_generated_files/system/src/protected_io.S mcc_generated_files/system/src/pins.c mcc_generated_files/system/src/interrupt.c mcc_generated_files/system/src/config_bits.c mcc_generated_files/system/src/system.c mcc_generated_files/timer/src/tca0.c mcc_generated_files/timer/src/tcd0.c mcc_generated_files/timer/src/tcb0.c mcc_generated_files/timer/src/delay.c mcc_generated_files/uart/src/usart1.c mcc_generated_files/uart/src/usart0.c mcc_generated_files/vref/src/vref.c main.c uart_remap.c adc_conv.c ina226.c balance_cells.c inits.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Balancer-AVR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=AVR64DD28
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/mcc_generated_files/adc/src/adc0.o: mcc_generated_files/adc/src/adc0.c  .generated_files/flags/default/c07f2ea74dbc519fa3900740e30eed5c756c5b66 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/adc/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc/src/adc0.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc/src/adc0.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/adc/src/adc0.o.d" -MT "${OBJECTDIR}/mcc_generated_files/adc/src/adc0.o.d" -MT ${OBJECTDIR}/mcc_generated_files/adc/src/adc0.o -o ${OBJECTDIR}/mcc_generated_files/adc/src/adc0.o mcc_generated_files/adc/src/adc0.c 
	
${OBJECTDIR}/mcc_generated_files/dac/src/dac0.o: mcc_generated_files/dac/src/dac0.c  .generated_files/flags/default/67e04ef1aa57aae0113072ae3ba156c3f7086a61 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/dac/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/dac/src/dac0.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/dac/src/dac0.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/dac/src/dac0.o.d" -MT "${OBJECTDIR}/mcc_generated_files/dac/src/dac0.o.d" -MT ${OBJECTDIR}/mcc_generated_files/dac/src/dac0.o -o ${OBJECTDIR}/mcc_generated_files/dac/src/dac0.o mcc_generated_files/dac/src/dac0.c 
	
${OBJECTDIR}/mcc_generated_files/i2c_host/src/twi0.o: mcc_generated_files/i2c_host/src/twi0.c  .generated_files/flags/default/6f42d47a5c278fc4ec62a28ec32c2f10b82ce072 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/i2c_host/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c_host/src/twi0.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c_host/src/twi0.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/i2c_host/src/twi0.o.d" -MT "${OBJECTDIR}/mcc_generated_files/i2c_host/src/twi0.o.d" -MT ${OBJECTDIR}/mcc_generated_files/i2c_host/src/twi0.o -o ${OBJECTDIR}/mcc_generated_files/i2c_host/src/twi0.o mcc_generated_files/i2c_host/src/twi0.c 
	
${OBJECTDIR}/mcc_generated_files/system/src/clock.o: mcc_generated_files/system/src/clock.c  .generated_files/flags/default/af7bc11daf5c6183e7dcc4b432ba932961827119 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/system/src/clock.o.d" -MT "${OBJECTDIR}/mcc_generated_files/system/src/clock.o.d" -MT ${OBJECTDIR}/mcc_generated_files/system/src/clock.o -o ${OBJECTDIR}/mcc_generated_files/system/src/clock.o mcc_generated_files/system/src/clock.c 
	
${OBJECTDIR}/mcc_generated_files/system/src/pins.o: mcc_generated_files/system/src/pins.c  .generated_files/flags/default/a93ff9a3a5ecef230f302db2f58a09cb2bda2f07 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/pins.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/pins.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/system/src/pins.o.d" -MT "${OBJECTDIR}/mcc_generated_files/system/src/pins.o.d" -MT ${OBJECTDIR}/mcc_generated_files/system/src/pins.o -o ${OBJECTDIR}/mcc_generated_files/system/src/pins.o mcc_generated_files/system/src/pins.c 
	
${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o: mcc_generated_files/system/src/interrupt.c  .generated_files/flags/default/963e004f8c7b4828bb078bec9ec2dfcc974768bd .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o.d" -MT "${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o.d" -MT ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o -o ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o mcc_generated_files/system/src/interrupt.c 
	
${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o: mcc_generated_files/system/src/config_bits.c  .generated_files/flags/default/5179086b2767e857e611628e8a14566a5ebfefc5 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o.d" -MT "${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o.d" -MT ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o -o ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o mcc_generated_files/system/src/config_bits.c 
	
${OBJECTDIR}/mcc_generated_files/system/src/system.o: mcc_generated_files/system/src/system.c  .generated_files/flags/default/11c264d3740a5f7043e5389d57d9164005c260d6 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/system/src/system.o.d" -MT "${OBJECTDIR}/mcc_generated_files/system/src/system.o.d" -MT ${OBJECTDIR}/mcc_generated_files/system/src/system.o -o ${OBJECTDIR}/mcc_generated_files/system/src/system.o mcc_generated_files/system/src/system.c 
	
${OBJECTDIR}/mcc_generated_files/timer/src/tca0.o: mcc_generated_files/timer/src/tca0.c  .generated_files/flags/default/a08e7202d0886ffc9def473d7bed1f0bc5960ed8 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/timer/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/timer/src/tca0.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/timer/src/tca0.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/timer/src/tca0.o.d" -MT "${OBJECTDIR}/mcc_generated_files/timer/src/tca0.o.d" -MT ${OBJECTDIR}/mcc_generated_files/timer/src/tca0.o -o ${OBJECTDIR}/mcc_generated_files/timer/src/tca0.o mcc_generated_files/timer/src/tca0.c 
	
${OBJECTDIR}/mcc_generated_files/timer/src/tcd0.o: mcc_generated_files/timer/src/tcd0.c  .generated_files/flags/default/81ad04fbf9d00b01b253dfb61165340d6dc531e2 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/timer/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/timer/src/tcd0.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/timer/src/tcd0.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/timer/src/tcd0.o.d" -MT "${OBJECTDIR}/mcc_generated_files/timer/src/tcd0.o.d" -MT ${OBJECTDIR}/mcc_generated_files/timer/src/tcd0.o -o ${OBJECTDIR}/mcc_generated_files/timer/src/tcd0.o mcc_generated_files/timer/src/tcd0.c 
	
${OBJECTDIR}/mcc_generated_files/timer/src/tcb0.o: mcc_generated_files/timer/src/tcb0.c  .generated_files/flags/default/164f358757d0b4ba1acb7eac7732a446d4d7ed24 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/timer/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/timer/src/tcb0.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/timer/src/tcb0.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/timer/src/tcb0.o.d" -MT "${OBJECTDIR}/mcc_generated_files/timer/src/tcb0.o.d" -MT ${OBJECTDIR}/mcc_generated_files/timer/src/tcb0.o -o ${OBJECTDIR}/mcc_generated_files/timer/src/tcb0.o mcc_generated_files/timer/src/tcb0.c 
	
${OBJECTDIR}/mcc_generated_files/timer/src/delay.o: mcc_generated_files/timer/src/delay.c  .generated_files/flags/default/a48ca303d9c08c87cec2e671669163c16316a250 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/timer/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/timer/src/delay.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/timer/src/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/timer/src/delay.o.d" -MT "${OBJECTDIR}/mcc_generated_files/timer/src/delay.o.d" -MT ${OBJECTDIR}/mcc_generated_files/timer/src/delay.o -o ${OBJECTDIR}/mcc_generated_files/timer/src/delay.o mcc_generated_files/timer/src/delay.c 
	
${OBJECTDIR}/mcc_generated_files/uart/src/usart1.o: mcc_generated_files/uart/src/usart1.c  .generated_files/flags/default/9583f184cf0f2f38620860d43566ed4b65b56f7f .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/uart/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart/src/usart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart/src/usart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/uart/src/usart1.o.d" -MT "${OBJECTDIR}/mcc_generated_files/uart/src/usart1.o.d" -MT ${OBJECTDIR}/mcc_generated_files/uart/src/usart1.o -o ${OBJECTDIR}/mcc_generated_files/uart/src/usart1.o mcc_generated_files/uart/src/usart1.c 
	
${OBJECTDIR}/mcc_generated_files/uart/src/usart0.o: mcc_generated_files/uart/src/usart0.c  .generated_files/flags/default/64c4c6e101db525be09bbbd863bc1c8a7208b651 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/uart/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart/src/usart0.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart/src/usart0.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/uart/src/usart0.o.d" -MT "${OBJECTDIR}/mcc_generated_files/uart/src/usart0.o.d" -MT ${OBJECTDIR}/mcc_generated_files/uart/src/usart0.o -o ${OBJECTDIR}/mcc_generated_files/uart/src/usart0.o mcc_generated_files/uart/src/usart0.c 
	
${OBJECTDIR}/mcc_generated_files/vref/src/vref.o: mcc_generated_files/vref/src/vref.c  .generated_files/flags/default/bf8c2b1fdec11b77d8b7d4721bda9bf20223cf51 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/vref/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/vref/src/vref.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/vref/src/vref.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/vref/src/vref.o.d" -MT "${OBJECTDIR}/mcc_generated_files/vref/src/vref.o.d" -MT ${OBJECTDIR}/mcc_generated_files/vref/src/vref.o -o ${OBJECTDIR}/mcc_generated_files/vref/src/vref.o mcc_generated_files/vref/src/vref.c 
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/6104feb6cef4b425933b92feb96dc05547c06fe0 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o -o ${OBJECTDIR}/main.o main.c 
	
${OBJECTDIR}/uart_remap.o: uart_remap.c  .generated_files/flags/default/fc5bf974db0aaf3e7b2bbab960253f2c25dd53d5 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart_remap.o.d 
	@${RM} ${OBJECTDIR}/uart_remap.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/uart_remap.o.d" -MT "${OBJECTDIR}/uart_remap.o.d" -MT ${OBJECTDIR}/uart_remap.o -o ${OBJECTDIR}/uart_remap.o uart_remap.c 
	
${OBJECTDIR}/adc_conv.o: adc_conv.c  .generated_files/flags/default/465b85a03f63f69ccebf3aade43317eefa959129 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/adc_conv.o.d 
	@${RM} ${OBJECTDIR}/adc_conv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/adc_conv.o.d" -MT "${OBJECTDIR}/adc_conv.o.d" -MT ${OBJECTDIR}/adc_conv.o -o ${OBJECTDIR}/adc_conv.o adc_conv.c 
	
${OBJECTDIR}/ina226.o: ina226.c  .generated_files/flags/default/b3985effaa3d73367a6603b66a74950f492d01fa .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ina226.o.d 
	@${RM} ${OBJECTDIR}/ina226.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/ina226.o.d" -MT "${OBJECTDIR}/ina226.o.d" -MT ${OBJECTDIR}/ina226.o -o ${OBJECTDIR}/ina226.o ina226.c 
	
${OBJECTDIR}/balance_cells.o: balance_cells.c  .generated_files/flags/default/b4ecd071e79bfc3fe472434c2b421059c3026425 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/balance_cells.o.d 
	@${RM} ${OBJECTDIR}/balance_cells.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/balance_cells.o.d" -MT "${OBJECTDIR}/balance_cells.o.d" -MT ${OBJECTDIR}/balance_cells.o -o ${OBJECTDIR}/balance_cells.o balance_cells.c 
	
${OBJECTDIR}/inits.o: inits.c  .generated_files/flags/default/7e6832b886b9b2bbc7a664776264a8aaa54bc0b9 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/inits.o.d 
	@${RM} ${OBJECTDIR}/inits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/inits.o.d" -MT "${OBJECTDIR}/inits.o.d" -MT ${OBJECTDIR}/inits.o -o ${OBJECTDIR}/inits.o inits.c 
	
else
${OBJECTDIR}/mcc_generated_files/adc/src/adc0.o: mcc_generated_files/adc/src/adc0.c  .generated_files/flags/default/3460826faeaf04b913bb1d8874dcd19caa26804a .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/adc/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc/src/adc0.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc/src/adc0.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/adc/src/adc0.o.d" -MT "${OBJECTDIR}/mcc_generated_files/adc/src/adc0.o.d" -MT ${OBJECTDIR}/mcc_generated_files/adc/src/adc0.o -o ${OBJECTDIR}/mcc_generated_files/adc/src/adc0.o mcc_generated_files/adc/src/adc0.c 
	
${OBJECTDIR}/mcc_generated_files/dac/src/dac0.o: mcc_generated_files/dac/src/dac0.c  .generated_files/flags/default/c54d3b3e7a0d0307e6216b998f910f0256fd6c1 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/dac/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/dac/src/dac0.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/dac/src/dac0.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/dac/src/dac0.o.d" -MT "${OBJECTDIR}/mcc_generated_files/dac/src/dac0.o.d" -MT ${OBJECTDIR}/mcc_generated_files/dac/src/dac0.o -o ${OBJECTDIR}/mcc_generated_files/dac/src/dac0.o mcc_generated_files/dac/src/dac0.c 
	
${OBJECTDIR}/mcc_generated_files/i2c_host/src/twi0.o: mcc_generated_files/i2c_host/src/twi0.c  .generated_files/flags/default/527d2296c4d4429be5bb09203bc340cd683f75b3 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/i2c_host/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c_host/src/twi0.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c_host/src/twi0.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/i2c_host/src/twi0.o.d" -MT "${OBJECTDIR}/mcc_generated_files/i2c_host/src/twi0.o.d" -MT ${OBJECTDIR}/mcc_generated_files/i2c_host/src/twi0.o -o ${OBJECTDIR}/mcc_generated_files/i2c_host/src/twi0.o mcc_generated_files/i2c_host/src/twi0.c 
	
${OBJECTDIR}/mcc_generated_files/system/src/clock.o: mcc_generated_files/system/src/clock.c  .generated_files/flags/default/cc2fe3be80da8c968470c9cc24ef1c429ec4aef2 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/system/src/clock.o.d" -MT "${OBJECTDIR}/mcc_generated_files/system/src/clock.o.d" -MT ${OBJECTDIR}/mcc_generated_files/system/src/clock.o -o ${OBJECTDIR}/mcc_generated_files/system/src/clock.o mcc_generated_files/system/src/clock.c 
	
${OBJECTDIR}/mcc_generated_files/system/src/pins.o: mcc_generated_files/system/src/pins.c  .generated_files/flags/default/d8b75044e9f17b19e57a8055dcfb4cb9bfc344c7 .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/pins.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/pins.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/system/src/pins.o.d" -MT "${OBJECTDIR}/mcc_generated_files/system/src/pins.o.d" -MT ${OBJECTDIR}/mcc_generated_files/system/src/pins.o -o ${OBJECTDIR}/mcc_generated_files/system/src/pins.o mcc_generated_files/system/src/pins.c 
	
${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o: mcc_generated_files/system/src/interrupt.c  .generated_files/flags/default/8a01774333c1b5358b124dc19bfb01b238b20fbd .generated_files/flags/default/164fbf645b0de52b75ec763c87295fcfe12b6036
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o.d" -MT "${OBJECTDIR}/