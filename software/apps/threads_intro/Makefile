CC=gcc
CFLAGS=-Wall -pthread

SRC:=$(wildcard *.c)
TARGETS:= $(SRC:.c=)
#TARGETS=01_sensor_data_aggregation 02_low_latency_actuation 03_audio_processing \
#        04_periodic_logger 05_watchdog_monitor 06_video_frame_processing 07_overloaded_stress_test

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ -lm

clean:
	rm -f $(TARGETS)
