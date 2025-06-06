BOARD_FQBN ?= arduino:avr:uno
PORT ?= /dev/ttyACM0

PROJECT ?=

ifeq ($(PROJECT),)
$(error You must specify a project folder, like 'make PROJECT=blink')
endif

PROJECT_PATH := $(abspath $(PROJECT))

create:
	mkdir -p $(PROJECT)
	echo "default_fqbn: $(BOARD_FQBN)" > $(PROJECT)/sketch.yaml
	echo "default_port: $(PORT)" >> $(PROJECT)/sketch.yaml
	touch $(PROJECT)/$(PROJECT).ino
	@echo "Created new Arduino project '$(PROJECT)' with sketch.yaml and empty .ino"


compile:
	arduino-cli compile --fqbn $(BOARD_FQBN) $(PROJECT_PATH)

upload:
	arduino-cli upload -p $(PORT) --fqbn $(BOARD_FQBN) $(PROJECT_PATH)

all: compile upload

