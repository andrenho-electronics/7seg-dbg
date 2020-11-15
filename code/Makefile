PROJECT=7digit_dbg
OBJECTS=main.o
AVRDUDE_FLAGS=-p t2313 -C ./avrdude_gpio.conf -c pi_1
FUSES=-U lfuse:w:0x62:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m
MCU=attiny2313
F_CPU=500000UL  # 8 mhz / 8

CC=avr-gcc -Wall -Wextra
CFLAGS=-Os -DF_CPU=${F_CPU} -mmcu=${MCU} -Isrc

${PROJECT}.hex: ${PROJECT}.elf
	avr-objcopy -j .text -j .data -O ihex $< $@

${PROJECT}.elf: ${OBJECTS}
	$(CC) -mmcu=${MCU} -o $@ $^

test-connection:
	sudo avrdude ${AVRDUDE_FLAGS}

clean:
	rm -f *.elf *.o test

upload: ${PROJECT}.hex
	sudo avrdude ${AVRDUDE_FLAGS} -U flash:w:$<:i

fuse:
	sudo avrdude ${AVRDUDE_FLAGS} ${FUSES}

# vim: set ts=8 sts=8 sw=8 noexpandtab:
