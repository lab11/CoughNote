EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:lab11_adc
LIBS:lab11_battery_chargers
LIBS:lab11_comparators
LIBS:lab11_connectors
LIBS:lab11_diodes
LIBS:lab11_ldo
LIBS:lab11_level_shifters
LIBS:lab11_mcu
LIBS:lab11_microphones
LIBS:lab11_opamps
LIBS:lab11_receptacles
LIBS:lab11_rlc
LIBS:lab11_switches
LIBS:lab11_voltage_references
LIBS:lab11_nucleum
LIBS:lab11_buffers
LIBS:coughcatcher_v0-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 850  750  3050 1700
U 57573360
F0 "filters" 60
F1 "filters.sch" 60
$EndSheet
$Comp
L nucleum U1
U 1 1 57585D3A
P 8450 3950
F 0 "U1" H 6700 4950 60  0000 C CNN
F 1 "nucleum" H 9500 4900 60  0000 C CNN
F 2 "nucleum:NUCLEUM" H 7650 5400 60  0001 C CNN
F 3 "" H 6700 4950 60  0000 C CNN
	1    8450 3950
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR19
U 1 1 57588876
P 6400 2850
F 0 "#PWR19" H 6400 2700 50  0001 C CNN
F 1 "+3.3V" H 6400 2990 50  0000 C CNN
F 2 "" H 6400 2850 50  0000 C CNN
F 3 "" H 6400 2850 50  0000 C CNN
	1    6400 2850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR26
U 1 1 57588C24
P 10650 3150
F 0 "#PWR26" H 10650 2900 50  0001 C CNN
F 1 "GND" H 10650 3000 50  0000 C CNN
F 2 "" H 10650 3150 50  0000 C CNN
F 3 "" H 10650 3150 50  0000 C CNN
	1    10650 3150
	1    0    0    -1  
$EndComp
$Comp
L MicroSD J1
U 1 1 57588D84
P 1500 3800
F 0 "J1" H 1000 4300 60  0000 C CNN
F 1 "MicroSD" V 900 3900 60  0000 C CNN
F 2 "lab11-connectors:2201778-1" H 1500 4550 60  0001 C CNN
F 3 "" H 1250 3550 60  0000 C CNN
F 4 "Digikey" H 1450 4750 60  0001 C CNN "Vendor 1"
F 5 "A118117CT-ND" H 1550 4650 60  0001 C CNN "Vendor 1 Part Number"
	1    1500 3800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR3
U 1 1 57588E93
P 1500 2750
F 0 "#PWR3" H 1500 2600 50  0001 C CNN
F 1 "+3.3V" H 1500 2890 50  0000 C CNN
F 2 "" H 1500 2750 50  0000 C CNN
F 3 "" H 1500 2750 50  0000 C CNN
	1    1500 2750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR1
U 1 1 57588EC7
P 1250 4550
F 0 "#PWR1" H 1250 4300 50  0001 C CNN
F 1 "GND" H 1250 4400 50  0000 C CNN
F 2 "" H 1250 4550 50  0000 C CNN
F 3 "" H 1250 4550 50  0000 C CNN
	1    1250 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 2850 6400 3150
Wire Wire Line
	9900 3150 10650 3150
Wire Wire Line
	1500 2750 1500 3150
Wire Wire Line
	1000 4450 1000 4550
Wire Wire Line
	1000 4550 2150 4550
Wire Wire Line
	1100 4450 1100 4550
Connection ~ 1100 4550
Wire Wire Line
	1200 4450 1200 4550
Connection ~ 1200 4550
Wire Wire Line
	1650 4550 1650 4450
Connection ~ 1250 4550
Wire Wire Line
	1300 4450 1300 4550
Connection ~ 1300 4550
Wire Wire Line
	1400 4450 1400 4550
Connection ~ 1400 4550
Wire Wire Line
	1500 4450 1500 4550
Connection ~ 1500 4550
Text GLabel 2300 3700 2    60   Input ~ 0
SD_CS
Text GLabel 2300 3900 2    60   Input ~ 0
SD_MOSI
Text GLabel 2850 3800 2    60   Input ~ 0
SD_SCLK
Text GLabel 2300 3400 2    60   Input ~ 0
SD_MISO
Wire Wire Line
	2150 3800 2850 3800
Wire Wire Line
	2150 3900 2300 3900
Wire Wire Line
	2150 3700 2300 3700
Wire Wire Line
	2150 3400 2300 3400
$Comp
L ADP160AUJZ-1.2-R7 U9
U 1 1 57604698
P 3450 5650
F 0 "U9" H 3250 5900 60  0000 C CNN
F 1 "ADP160AUJZ-1.2-R7" H 3450 5400 60  0000 C CNN
F 2 "lab11-ic:TSOT-5" H 3550 6200 60  0001 C CNN
F 3 "http://www.analog.com/media/en/technical-documentation/data-sheets/ADP160_161_162_163.pdf" H 4000 6300 60  0001 C CNN
F 4 "Digikey" H 3450 6500 60  0001 C CNN "Vendor 1"
F 5 "ADP160AUJZ-1.2-R7CT-ND" H 3500 6400 60  0001 C CNN "Vendor 1 Part Number"
	1    3450 5650
	1    0    0    -1  
$EndComp
$Comp
L C_0.1u_0402_10V_10%_JB C22
U 1 1 57604A00
P 2300 5650
F 0 "C22" H 2325 5750 50  0000 L CNN
F 1 "C_0.1u_0402_10V_10%_JB" H 1850 6400 50  0001 L CNN
F 2 "Capacitors_SMD:C_0402" H 2350 6150 50  0001 C CNN
F 3 "" H 2325 5750 50  0000 C CNN
F 4 "0.1uF" H 2425 5550 60  0000 C CNN "Capacitance"
F 5 "Digikey" H 2325 6225 60  0001 C CNN "Vendor 1"
F 6 "445-10894-1-ND" H 2325 6300 60  0001 C CNN "Vendor 1 Part Number"
	1    2300 5650
	1    0    0    -1  
$EndComp
$Comp
L C_0.1u_0402_10V_10%_JB C23
U 1 1 57604A44
P 4350 5650
F 0 "C23" H 4375 5750 50  0000 L CNN
F 1 "C_0.1u_0402_10V_10%_JB" H 3900 6400 50  0001 L CNN
F 2 "Capacitors_SMD:C_0402" H 4400 6150 50  0001 C CNN
F 3 "" H 4375 5750 50  0000 C CNN
F 4 "0.1uF" H 4475 5550 60  0000 C CNN "Capacitance"
F 5 "Digikey" H 4375 6225 60  0001 C CNN "Vendor 1"
F 6 "445-10894-1-ND" H 4375 6300 60  0001 C CNN "Vendor 1 Part Number"
	1    4350 5650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR8
U 1 1 57604AE4
P 2850 5650
F 0 "#PWR8" H 2850 5400 50  0001 C CNN
F 1 "GND" H 2850 5700 50  0000 C CNN
F 2 "" H 2850 5650 50  0000 C CNN
F 3 "" H 2850 5650 50  0000 C CNN
	1    2850 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 5650 2850 5650
Wire Wire Line
	3000 5800 2650 5800
Wire Wire Line
	2650 5800 2650 5500
Wire Wire Line
	2300 5500 3000 5500
Wire Wire Line
	3900 5500 4350 5500
$Comp
L GND #PWR13
U 1 1 57604ED5
P 4350 5900
F 0 "#PWR13" H 4350 5650 50  0001 C CNN
F 1 "GND" H 4350 5750 50  0000 C CNN
F 2 "" H 4350 5900 50  0000 C CNN
F 3 "" H 4350 5900 50  0000 C CNN
	1    4350 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 5800 4350 5900
$Comp
L +3.3V #PWR12
U 1 1 57604F19
P 4350 5500
F 0 "#PWR12" H 4350 5350 50  0001 C CNN
F 1 "+3.3V" H 4350 5640 50  0000 C CNN
F 2 "" H 4350 5500 50  0000 C CNN
F 3 "" H 4350 5500 50  0000 C CNN
	1    4350 5500
	1    0    0    -1  
$EndComp
Connection ~ 2650 5500
$Comp
L GND #PWR7
U 1 1 5760515B
P 2300 5900
F 0 "#PWR7" H 2300 5650 50  0001 C CNN
F 1 "GND" H 2300 5750 50  0000 C CNN
F 2 "" H 2300 5900 50  0000 C CNN
F 3 "" H 2300 5900 50  0000 C CNN
	1    2300 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 5800 2300 5900
Text Label 2300 5500 0    60   ~ 0
BATT
$Comp
L JST_2_CONN_SIDE J2
U 1 1 576054B8
P 950 6750
F 0 "J2" H 900 6900 60  0000 C CNN
F 1 "JST_2_CONN_SIDE" H 950 6600 60  0000 C CNN
F 2 "lab11-connectors:CONN_JST-2_SMD_SIDE" H 1000 7050 60  0001 C CNN
F 3 "" H 900 6900 60  0001 C CNN
F 4 "Digikey" H 1000 7250 60  0001 C CNN "Vendor 1"
F 5 "455-1749-1-ND" H 950 7150 60  0001 C CNN "Vendor 1 Part Number"
	1    950  6750
	1    0    0    -1  
$EndComp
$Comp
L MAX1555 U11
U 1 1 5760692C
P 2800 7000
F 0 "U11" H 2600 7200 60  0000 C CNN
F 1 "MAX1555" H 2800 6800 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5" H 2800 7575 60  0001 C CNN
F 3 "" H 2875 7675 60  0001 C CNN
F 4 "Digikey" H 2800 7775 60  0001 C CNN "Vendor 1"
F 5 "MAX1555EZK+TCT-ND" H 2800 7875 60  0001 C CNN "Vendor 1 Part Number"
	1    2800 7000
	1    0    0    -1  
$EndComp
Text Label 1250 6700 0    60   ~ 0
BATT
$Comp
L GND #PWR2
U 1 1 57606F7B
P 1450 6800
F 0 "#PWR2" H 1450 6550 50  0001 C CNN
F 1 "GND" H 1450 6650 50  0000 C CNN
F 2 "" H 1450 6800 50  0000 C CNN
F 3 "" H 1450 6800 50  0000 C CNN
	1    1450 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 6800 1450 6800
Wire Wire Line
	1250 6700 1450 6700
Text Label 1500 5550 0    60   ~ 0
VBUS
$Comp
L GND #PWR4
U 1 1 576076FA
P 1550 6050
F 0 "#PWR4" H 1550 5800 50  0001 C CNN
F 1 "GND" H 1550 5900 50  0000 C CNN
F 2 "" H 1550 6050 50  0000 C CNN
F 3 "" H 1550 6050 50  0000 C CNN
	1    1550 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 6050 1550 6050
Wire Wire Line
	1350 5950 1550 5950
Wire Wire Line
	1550 5950 1550 6050
Wire Wire Line
	1350 5550 1750 5550
Text Label 2100 6900 0    60   ~ 0
VBUS
Wire Wire Line
	2350 6900 2100 6900
$Comp
L GND #PWR6
U 1 1 5760818E
P 2100 7250
F 0 "#PWR6" H 2100 7000 50  0001 C CNN
F 1 "GND" H 2100 7100 50  0000 C CNN
F 2 "" H 2100 7250 50  0000 C CNN
F 3 "" H 2100 7250 50  0000 C CNN
	1    2100 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 7200 2100 7250
$Comp
L GND #PWR9
U 1 1 5760847B
P 3250 7200
F 0 "#PWR9" H 3250 6950 50  0001 C CNN
F 1 "GND" H 3250 7050 50  0000 C CNN
F 2 "" H 3250 7200 50  0000 C CNN
F 3 "" H 3250 7200 50  0000 C CNN
	1    3250 7200
	1    0    0    -1  
$EndComp
$Comp
L LED_GREEN_0402_20mA D1
U 1 1 576084CB
P 3650 7000
F 0 "D1" H 3600 7050 50  0000 L CNN
F 1 "LED_GREEN_0402_20mA" H 3325 6900 50  0001 L CNN
F 2 "Capacitors_SMD:C_0402" H 3275 7350 50  0001 L CNN
F 3 "http://rohmfs.rohm.com/en/products/databook/datasheet/opto/led/chip_mono/sml-p1.pdf" H 2050 7425 50  0001 L CNN
F 4 "Digikey" H 3650 7625 60  0001 C CNN "Vendor 1"
F 5 "511-1592-1-ND" H 3700 7525 60  0001 C CNN "Vendor 1 Part Number"
	1    3650 7000
	-1   0    0    1   
$EndComp
$Comp
L GENERIC_R_0402 R25
U 1 1 576087A2
P 4000 7000
F 0 "R25" H 4000 7075 50  0000 C CNN
F 1 "GENERIC_R_0402" H 4025 7700 50  0001 C CNN
F 2 "Resistors_SMD:R_0402" H 4000 7550 50  0001 C CNN
F 3 "" H 4100 7625 50  0001 C CNN
F 4 "1k" H 4000 6925 60  0000 C CNN "Resistance"
F 5 "Digikey" H 4000 7450 60  0001 C CNN "Vendor 1"
F 6 "Placeholder" H 4000 7350 60  0001 C CNN "Vendor 1 Part Number"
	1    4000 7000
	1    0    0    -1  
$EndComp
Text Label 4250 7000 0    60   ~ 0
VBUS
Wire Wire Line
	4200 7000 4500 7000
Wire Wire Line
	3800 7000 3750 7000
Wire Wire Line
	3350 7000 3250 7000
Wire Wire Line
	3250 7100 3250 7200
$Comp
L GND #PWR11
U 1 1 57608FB3
P 3800 6700
F 0 "#PWR11" H 3800 6450 50  0001 C CNN
F 1 "GND" H 3800 6550 50  0000 C CNN
F 2 "" H 3800 6700 50  0000 C CNN
F 3 "" H 3800 6700 50  0000 C CNN
	1    3800 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 6650 3800 6700
Wire Wire Line
	3250 6900 3250 6350
Wire Wire Line
	3250 6350 3800 6350
Text Label 3600 6350 0    60   ~ 0
BATT
Text GLabel 10150 4200 2    60   Input ~ 0
ADC_SCLK
Text GLabel 10150 4050 2    60   Input ~ 0
ADC_SDATA
Wire Wire Line
	9900 4050 10150 4050
Wire Wire Line
	9900 4200 10150 4200
Text GLabel 10150 3900 2    60   Input ~ 0
ADC_CS
Wire Wire Line
	9900 3900 10150 3900
Text GLabel 10150 3750 2    60   Input ~ 0
SD_CS
Wire Wire Line
	9900 3750 10150 3750
$Comp
L +3.3V #PWR18
U 1 1 5760CB03
P 6300 5750
F 0 "#PWR18" H 6300 5600 50  0001 C CNN
F 1 "+3.3V" H 6300 5890 50  0000 C CNN
F 2 "" H 6300 5750 50  0000 C CNN
F 3 "" H 6300 5750 50  0000 C CNN
	1    6300 5750
	1    0    0    -1  
$EndComp
$Comp
L SN74AUP1T157 U13
U 1 1 5761A672
P 5200 1950
F 0 "U13" H 5100 2150 60  0000 C CNN
F 1 "SN74AUP1T157" H 5250 1650 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SC-70-6" H 5400 2450 60  0001 C CNN
F 3 "" H 5100 2150 60  0000 C CNN
F 4 "Digikey" H 5200 2550 60  0001 C CNN "Vendor 1"
F 5 "296-27393-1-ND" H 5300 2350 60  0001 C CNN "Vendor 1 Part Number"
	1    5200 1950
	1    0    0    -1  
$EndComp
$Comp
L SN74AUP1T157 U14
U 1 1 5761A711
P 5900 6350
F 0 "U14" H 5800 6550 60  0000 C CNN
F 1 "SN74AUP1T157" H 5950 6050 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SC-70-6" H 6100 6850 60  0001 C CNN
F 3 "" H 5800 6550 60  0000 C CNN
F 4 "Digikey" H 5900 6950 60  0001 C CNN "Vendor 1"
F 5 "296-27393-1-ND" H 6000 6750 60  0001 C CNN "Vendor 1 Part Number"
	1    5900 6350
	1    0    0    -1  
$EndComp
$Comp
L C_0.1u_0402_10V_10%_JB C26
U 1 1 5761A854
P 5800 1400
F 0 "C26" H 5825 1500 50  0000 L CNN
F 1 "C_0.1u_0402_10V_10%_JB" H 5350 2150 50  0001 L CNN
F 2 "Capacitors_SMD:C_0402" H 5850 1900 50  0001 C CNN
F 3 "" H 5825 1500 50  0000 C CNN
F 4 "0.1uF" H 5925 1300 60  0000 C CNN "Capacitance"
F 5 "Digikey" H 5825 1975 60  0001 C CNN "Vendor 1"
F 6 "445-10894-1-ND" H 5825 2050 60  0001 C CNN "Vendor 1 Part Number"
	1    5800 1400
	1    0    0    -1  
$EndComp
$Comp
L C_0.1u_0402_10V_10%_JB C27
U 1 1 5761A925
P 6600 5900
F 0 "C27" H 6625 6000 50  0000 L CNN
F 1 "C_0.1u_0402_10V_10%_JB" H 6150 6650 50  0001 L CNN
F 2 "Capacitors_SMD:C_0402" H 6650 6400 50  0001 C CNN
F 3 "" H 6625 6000 50  0000 C CNN
F 4 "0.1uF" H 6725 5800 60  0000 C CNN "Capacitance"
F 5 "Digikey" H 6625 6475 60  0001 C CNN "Vendor 1"
F 6 "445-10894-1-ND" H 6625 6550 60  0001 C CNN "Vendor 1 Part Number"
	1    6600 5900
	1    0    0    -1  
$EndComp
Text GLabel 4750 1850 0    60   Input ~ 0
ADC_SCLK
Wire Wire Line
	4750 1850 4850 1850
$Comp
L GND #PWR17
U 1 1 5761B00E
P 5800 1650
F 0 "#PWR17" H 5800 1400 50  0001 C CNN
F 1 "GND" H 5800 1500 50  0000 C CNN
F 2 "" H 5800 1650 50  0000 C CNN
F 3 "" H 5800 1650 50  0000 C CNN
	1    5800 1650
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR16
U 1 1 5761B042
P 5800 1150
F 0 "#PWR16" H 5800 1000 50  0001 C CNN
F 1 "+3.3V" H 5800 1290 50  0000 C CNN
F 2 "" H 5800 1150 50  0000 C CNN
F 3 "" H 5800 1150 50  0000 C CNN
	1    5800 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 1850 5600 1250
Wire Wire Line
	5600 1250 5800 1250
Wire Wire Line
	5800 1250 5800 1150
Wire Wire Line
	5800 1550 5800 1650
Text GLabel 5700 2000 2    60   Input ~ 0
SD_SCLK
Wire Wire Line
	5600 2000 5700 2000
$Comp
L GND #PWR21
U 1 1 5761C747
P 6600 6100
F 0 "#PWR21" H 6600 5850 50  0001 C CNN
F 1 "GND" H 6600 5950 50  0000 C CNN
F 2 "" H 6600 6100 50  0000 C CNN
F 3 "" H 6600 6100 50  0000 C CNN
	1    6600 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 6050 6600 6100
Wire Wire Line
	6300 6250 6300 5750
Wire Wire Line
	6300 5750 6600 5750
Text GLabel 5400 6250 0    60   Input ~ 0
ADC_SDATA
Wire Wire Line
	5400 6250 5550 6250
Text GLabel 6450 6400 2    60   Input ~ 0
SD_MOSI
Wire Wire Line
	6300 6400 6450 6400
$Comp
L GND #PWR20
U 1 1 5761CAE9
P 6450 6600
F 0 "#PWR20" H 6450 6350 50  0001 C CNN
F 1 "GND" H 6450 6450 50  0000 C CNN
F 2 "" H 6450 6600 50  0000 C CNN
F 3 "" H 6450 6600 50  0000 C CNN
	1    6450 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 6550 6450 6550
Wire Wire Line
	6450 6550 6450 6600
Text GLabel 8000 4800 3    60   Input ~ 0
SD_MOSI_2
Text GLabel 5400 6400 0    60   Input ~ 0
SD_MOSI_2
Wire Wire Line
	5400 6400 5550 6400
Wire Wire Line
	8150 4650 8150 4800
Wire Wire Line
	8000 4650 8000 4800
Text GLabel 5400 6550 0    60   Input ~ 0
SD_MOSI_SEL
Wire Wire Line
	5550 6550 5400 6550
Text GLabel 4750 2150 0    60   Input ~ 0
SD_MOSI_SEL
Wire Wire Line
	4750 2150 4850 2150
Text GLabel 8300 4800 3    60   Input ~ 0
SD_MOSI_SEL
Text GLabel 8450 4800 3    60   Input ~ 0
SD_SCLK_2
Text GLabel 4750 2000 0    60   Input ~ 0
SD_SCLK_2
Wire Wire Line
	4850 2000 4750 2000
Text GLabel 8600 4800 3    60   Input ~ 0
SD_MISO
Wire Wire Line
	8600 4650 8600 4800
$Comp
L microUSB-B_smd U10
U 1 1 57631593
P 1100 5750
F 0 "U10" H 900 6050 60  0000 C CNN
F 1 "microUSB-B_smd" H 1000 5350 60  0000 C CNN
F 2 "lab11-connectors:USB_MICRO_B-HIROSE-ZX62R-B-5P" H 1150 6350 60  0001 C CNN
F 3 "" H 1500 5800 60  0000 C CNN
F 4 "Digikey" H 1050 6450 60  0001 C CNN "Vendor 1"
F 5 "H11574CT-ND" H 1100 6250 60  0001 C CNN "Vendor 1 Part Number"
	1    1100 5750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR15
U 1 1 57631CD2
P 5700 2250
F 0 "#PWR15" H 5700 2000 50  0001 C CNN
F 1 "GND" H 5700 2100 50  0000 C CNN
F 2 "" H 5700 2250 50  0000 C CNN
F 3 "" H 5700 2250 50  0000 C CNN
	1    5700 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 2150 5700 2150
Wire Wire Line
	5700 2150 5700 2250
Wire Wire Line
	8450 4650 8450 4800
Wire Wire Line
	8300 4650 8300 4800
Text GLabel 6350 4200 0    60   Input ~ 0
COMP2_OUT
Wire Wire Line
	6350 4050 6400 4050
Text GLabel 6350 4050 0    60   Input ~ 0
COMP1_OUT
Wire Wire Line
	6350 3900 6400 3900
$Comp
L PROBEPAD_0805 T9
U 1 1 576347C7
P 8450 5300
F 0 "T9" H 8450 5050 60  0000 C CNN
F 1 "PROBEPAD_0805" H 8500 5550 60  0001 C CNN
F 2 "lab11-connectors:PROBEPAD_0805" H 8800 5450 60  0001 C CNN
F 3 "" H 8450 5300 60  0000 C CNN
F 4 "Digikey" H 8450 5250 60  0001 C CNN "Vendor 1"
F 5 "A106144CT-ND" H 8450 5350 60  0001 C CNN "Vendor 1 Part Number"
	1    8450 5300
	1    0    0    -1  
$EndComp
$Comp
L PROBEPAD_0805 T10
U 1 1 57634890
P 8600 5300
F 0 "T10" H 8600 5050 60  0000 C CNN
F 1 "PROBEPAD_0805" H 8650 5550 60  0001 C CNN
F 2 "lab11-connectors:PROBEPAD_0805" H 8950 5450 60  0001 C CNN
F 3 "" H 8600 5300 60  0000 C CNN
F 4 "Digikey" H 8600 5250 60  0001 C CNN "Vendor 1"
F 5 "A106144CT-ND" H 8600 5350 60  0001 C CNN "Vendor 1 Part Number"
	1    8600 5300
	1    0    0    -1  
$EndComp
$Comp
L PROBEPAD_0805 T5
U 1 1 57634909
P 8000 5300
F 0 "T5" H 8000 5050 60  0000 C CNN
F 1 "PROBEPAD_0805" H 8050 5550 60  0001 C CNN
F 2 "lab11-connectors:PROBEPAD_0805" H 8350 5450 60  0001 C CNN
F 3 "" H 8000 5300 60  0000 C CNN
F 4 "Digikey" H 8000 5250 60  0001 C CNN "Vendor 1"
F 5 "A106144CT-ND" H 8000 5350 60  0001 C CNN "Vendor 1 Part Number"
	1    8000 5300
	1    0    0    -1  
$EndComp
$Comp
L PROBEPAD_0805 T7
U 1 1 57634A1C
P 8300 5300
F 0 "T7" H 8300 5050 60  0000 C CNN
F 1 "PROBEPAD_0805" H 8350 5550 60  0001 C CNN
F 2 "lab11-connectors:PROBEPAD_0805" H 8650 5450 60  0001 C CNN
F 3 "" H 8300 5300 60  0000 C CNN
F 4 "Digikey" H 8300 5250 60  0001 C CNN "Vendor 1"
F 5 "A106144CT-ND" H 8300 5350 60  0001 C CNN "Vendor 1 Part Number"
	1    8300 5300
	1    0    0    -1  
$EndComp
$Comp
L PROBEPAD_0805 T11
U 1 1 57634B97
P 10150 4350
F 0 "T11" H 10150 4100 60  0000 C CNN
F 1 "PROBEPAD_0805" H 10200 4600 60  0001 C CNN
F 2 "lab11-connectors:PROBEPAD_0805" H 10500 4500 60  0001 C CNN
F 3 "" H 10150 4350 60  0000 C CNN
F 4 "Digikey" H 10150 4300 60  0001 C CNN "Vendor 1"
F 5 "A106144CT-ND" H 10150 4400 60  0001 C CNN "Vendor 1 Part Number"
	1    10150 4350
	1    0    0    -1  
$EndComp
$Comp
L PROBEPAD_0805 T12
U 1 1 57634BE6
P 10150 4750
F 0 "T12" H 10150 4500 60  0000 C CNN
F 1 "PROBEPAD_0805" H 10200 5000 60  0001 C CNN
F 2 "lab11-connectors:PROBEPAD_0805" H 10500 4900 60  0001 C CNN
F 3 "" H 10150 4750 60  0000 C CNN
F 4 "Digikey" H 10150 4700 60  0001 C CNN "Vendor 1"
F 5 "A106144CT-ND" H 10150 4800 60  0001 C CNN "Vendor 1 Part Number"
	1    10150 4750
	1    0    0    -1  
$EndComp
$Comp
L PROBEPAD_0805 T14
U 1 1 57634C23
P 10150 5550
F 0 "T14" H 10150 5300 60  0000 C CNN
F 1 "PROBEPAD_0805" H 10200 5800 60  0001 C CNN
F 2 "lab11-connectors:PROBEPAD_0805" H 10500 5700 60  0001 C CNN
F 3 "" H 10150 5550 60  0000 C CNN
F 4 "Digikey" H 10150 5500 60  0001 C CNN "Vendor 1"
F 5 "A106144CT-ND" H 10150 5600 60  0001 C CNN "Vendor 1 Part Number"
	1    10150 5550
	1    0    0    -1  
$EndComp
$Comp
L PROBEPAD_0805 T13
U 1 1 57634C84
P 10150 5150
F 0 "T13" H 10150 4900 60  0000 C CNN
F 1 "PROBEPAD_0805" H 10200 5400 60  0001 C CNN
F 2 "lab11-connectors:PROBEPAD_0805" H 10500 5300 60  0001 C CNN
F 3 "" H 10150 5150 60  0000 C CNN
F 4 "Digikey" H 10150 5100 60  0001 C CNN "Vendor 1"
F 5 "A106144CT-ND" H 10150 5200 60  0001 C CNN "Vendor 1 Part Number"
	1    10150 5150
	1    0    0    -1  
$EndComp
Text GLabel 8000 5850 3    60   Input ~ 0
SD_MOSI
Text GLabel 8300 5850 3    60   Input ~ 0
SD_MOSI_SEL
Text GLabel 8450 5850 3    60   Input ~ 0
SD_SCLK
Text GLabel 8600 5850 3    60   Input ~ 0
SD_MISO
Text GLabel 10300 4900 2    60   Input ~ 0
SD_CS
Text GLabel 10300 5300 2    60   Input ~ 0
ADC_CS
Text GLabel 10300 5700 2    60   Input ~ 0
ADC_SDATA
Text GLabel 10300 6100 2    60   Input ~ 0
ADC_SCLK
Wire Wire Line
	10150 6100 10300 6100
Wire Wire Line
	10150 5300 10300 5300
Wire Wire Line
	10150 5700 10300 5700
Wire Wire Line
	10150 4900 10300 4900
$Comp
L PROBEPAD_0805 T3
U 1 1 57638CCD
P 7550 1200
F 0 "T3" H 7550 950 60  0000 C CNN
F 1 "PROBEPAD_0805" H 7600 1450 60  0001 C CNN
F 2 "lab11-connectors:PROBEPAD_0805" H 7900 1350 60  0001 C CNN
F 3 "" H 7550 1200 60  0000 C CNN
F 4 "Digikey" H 7550 1150 60  0001 C CNN "Vendor 1"
F 5 "A106144CT-ND" H 7550 1250 60  0001 C CNN "Vendor 1 Part Number"
	1    7550 1200
	1    0    0    -1  
$EndComp
$Comp
L PROBEPAD_0805 T4
U 1 1 57638DAC
P 7850 1200
F 0 "T4" H 7850 950 60  0000 C CNN
F 1 "PROBEPAD_0805" H 7900 1450 60  0001 C CNN
F 2 "lab11-connectors:PROBEPAD_0805" H 8200 1350 60  0001 C CNN
F 3 "" H 7850 1200 60  0000 C CNN
F 4 "Digikey" H 7850 1150 60  0001 C CNN "Vendor 1"
F 5 "A106144CT-ND" H 7850 1250 60  0001 C CNN "Vendor 1 Part Number"
	1    7850 1200
	1    0    0    -1  
$EndComp
$Comp
L PROBEPAD_0805 T6
U 1 1 57638DEF
P 8150 1200
F 0 "T6" H 8150 950 60  0000 C CNN
F 1 "PROBEPAD_0805" H 8200 1450 60  0001 C CNN
F 2 "lab11-connectors:PROBEPAD_0805" H 8500 1350 60  0001 C CNN
F 3 "" H 8150 1200 60  0000 C CNN
F 4 "Digikey" H 8150 1150 60  0001 C CNN "Vendor 1"
F 5 "A106144CT-ND" H 8150 1250 60  0001 C CNN "Vendor 1 Part Number"
	1    8150 1200
	1    0    0    -1  
$EndComp
$Comp
L PROBEPAD_0805 T8
U 1 1 57638F37
P 8450 1200
F 0 "T8" H 8450 950 60  0000 C CNN
F 1 "PROBEPAD_0805" H 8500 1450 60  0001 C CNN
F 2 "lab11-connectors:PROBEPAD_0805" H 8800 1350 60  0001 C CNN
F 3 "" H 8450 1200 60  0000 C CNN
F 4 "Digikey" H 8450 1150 60  0001 C CNN "Vendor 1"
F 5 "A106144CT-ND" H 8450 1250 60  0001 C CNN "Vendor 1 Part Number"
	1    8450 1200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR22
U 1 1 57639528
P 7550 1750
F 0 "#PWR22" H 7550 1500 50  0001 C CNN
F 1 "GND" H 7550 1600 50  0000 C CNN
F 2 "" H 7550 1750 50  0000 C CNN
F 3 "" H 7550 1750 50  0000 C CNN
	1    7550 1750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR23
U 1 1 576395D2
P 7850 1750
F 0 "#PWR23" H 7850 1500 50  0001 C CNN
F 1 "GND" H 7850 1600 50  0000 C CNN
F 2 "" H 7850 1750 50  0000 C CNN
F 3 "" H 7850 1750 50  0000 C CNN
	1    7850 1750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR24
U 1 1 57639622
P 8150 1750
F 0 "#PWR24" H 8150 1500 50  0001 C CNN
F 1 "GND" H 8150 1600 50  0000 C CNN
F 2 "" H 8150 1750 50  0000 C CNN
F 3 "" H 8150 1750 50  0000 C CNN
	1    8150 1750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR25
U 1 1 576397F8
P 8450 1750
F 0 "#PWR25" H 8450 1500 50  0001 C CNN
F 1 "GND" H 8450 1600 50  0000 C CNN
F 2 "" H 8450 1750 50  0000 C CNN
F 3 "" H 8450 1750 50  0000 C CNN
	1    8450 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 4550 2150 4200
Connection ~ 1650 4550
Text GLabel 3600 4100 2    60   Input ~ 0
SD_DET
$Comp
L +3.3V #PWR10
U 1 1 576474E7
P 3550 3700
F 0 "#PWR10" H 3550 3550 50  0001 C CNN
F 1 "+3.3V" H 3550 3840 50  0000 C CNN
F 2 "" H 3550 3700 50  0000 C CNN
F 3 "" H 3550 3700 50  0000 C CNN
	1    3550 3700
	1    0    0    -1  
$EndComp
$Comp
L GENERIC_R_0402 R26
U 1 1 57647537
P 3550 3900
F 0 "R26" H 3550 3975 50  0000 C CNN
F 1 "GENERIC_R_0402" H 3575 4600 50  0001 C CNN
F 2 "Resistors_SMD:R_0402" H 3550 4450 50  0001 C CNN
F 3 "" H 3650 4525 50  0001 C CNN
F 4 "10k" H 3550 3825 60  0000 C CNN "Resistance"
F 5 "Digikey" H 3550 4350 60  0001 C CNN "Vendor 1"
F 6 "Placeholder" H 3550 4250 60  0001 C CNN "Vendor 1 Part Number"
	1    3550 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	2150 4100 3600 4100
Connection ~ 3550 4100
$Comp
L GND #PWR5
U 1 1 5764826E
P 1900 3050
F 0 "#PWR5" H 1900 2800 50  0001 C CNN
F 1 "GND" H 1900 2900 50  0000 C CNN
F 2 "" H 1900 3050 50  0000 C CNN
F 3 "" H 1900 3050 50  0000 C CNN
	1    1900 3050
	1    0    0    -1  
$EndComp
$Comp
L GENERIC_C_0402 C28
U 1 1 576484B0
P 1700 2900
F 0 "C28" H 1725 3000 50  0000 L CNN
F 1 "GENERIC_C_0402" H 1250 3650 50  0001 L CNN
F 2 "Capacitors_SMD:C_0402" H 1750 3400 50  0001 C CNN
F 3 "" H 1725 3000 50  0000 C CNN
F 4 "0uF" H 1825 2800 60  0000 C CNN "Capacitance"
F 5 "Digikey" H 1725 3475 60  0001 C CNN "Vendor 1"
F 6 "Placeholder" H 1725 3550 60  0001 C CNN "Vendor 1 Part Number"
	1    1700 2900
	1    0    0    -1  
$EndComp
$Comp
L GENERIC_C_0402 C29
U 1 1 57648986
P 2000 2900
F 0 "C29" H 2025 3000 50  0000 L CNN
F 1 "GENERIC_C_0402" H 1550 3650 50  0001 L CNN
F 2 "Capacitors_SMD:C_0402" H 2050 3400 50  0001 C CNN
F 3 "" H 2025 3000 50  0000 C CNN
F 4 "0uF" H 2125 2800 60  0000 C CNN "Capacitance"
F 5 "Digikey" H 2025 3475 60  0001 C CNN "Vendor 1"
F 6 "Placeholder" H 2025 3550 60  0001 C CNN "Vendor 1 Part Number"
	1    2000 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 2750 2000 2750
Connection ~ 1700 2750
Wire Wire Line
	1700 3050 2000 3050
Connection ~ 1900 3050
Wire Wire Line
	6350 4200 6400 4200
Text GLabel 6350 3900 0    60   Input ~ 0
SD_DET
$Comp
L PROBEPAD_0805 T1
U 1 1 576606F2
P 4700 4650
F 0 "T1" H 4700 4400 60  0000 C CNN
F 1 "PROBEPAD_0805" H 4750 4900 60  0001 C CNN
F 2 "lab11-connectors:PROBEPAD_0805" H 5050 4800 60  0001 C CNN
F 3 "" H 4700 4650 60  0000 C CNN
F 4 "Digikey" H 4700 4600 60  0001 C CNN "Vendor 1"
F 5 "A106144CT-ND" H 4700 4700 60  0001 C CNN "Vendor 1 Part Number"
	1    4700 4650
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR14
U 1 1 57660811
P 4950 5200
F 0 "#PWR14" H 4950 5050 50  0001 C CNN
F 1 "+3.3V" H 4950 5340 50  0000 C CNN
F 2 "" H 4950 5200 50  0000 C CNN
F 3 "" H 4950 5200 50  0000 C CNN
	1    4950 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 5200 4950 5200
$Comp
L C_1u_0402_10V_10%_JB C24
U 1 1 577EEE04
P 2100 7050
F 0 "C24" H 2125 7150 50  0000 L CNN
F 1 "C_1u_0402_10V_10%_JB" H 1650 7650 50  0001 L CNN
F 2 "Capacitors_SMD:C_0402" H 2150 7400 50  0001 C CNN
F 3 "" H 2125 7150 50  0000 C CNN
F 4 "1uF" H 2225 6950 60  0000 C CNN "Capacitance"
F 5 "Digikey" H 2125 7475 60  0001 C CNN "Vendor 1"
F 6 "445-10896-1-ND" H 2125 7550 60  0001 C CNN "Vendor 1 Part Number"
	1    2100 7050
	1    0    0    -1  
$EndComp
$Comp
L C_1u_0402_10V_10%_JB C25
U 1 1 577EF3A4
P 3800 6500
F 0 "C25" H 3825 6600 50  0000 L CNN
F 1 "C_1u_0402_10V_10%_JB" H 3350 7100 50  0001 L CNN
F 2 "Capacitors_SMD:C_0402" H 3850 6850 50  0001 C CNN
F 3 "" H 3825 6600 50  0000 C CNN
F 4 "1uF" H 3925 6400 60  0000 C CNN "Capacitance"
F 5 "Digikey" H 3825 6925 60  0001 C CNN "Vendor 1"
F 6 "445-10896-1-ND" H 3825 7000 60  0001 C CNN "Vendor 1 Part Number"
	1    3800 6500
	1    0    0    -1  
$EndComp
$EndSCHEMATC
