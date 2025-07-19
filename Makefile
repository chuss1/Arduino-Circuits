# Default fallback values
DEFAULT_BOARD_FQBN ?= arduino:avr:uno
DEFAULT_PORT ?= /dev/ttyACM0

PROJECT ?=

ifeq ($(PROJECT),)
$(error You must specify a project folder, like 'make PROJECT=blink')
endif

PROJECT_PATH := $(abspath $(PROJECT))
SKETCH_YAML := $(PROJECT_PATH)/sketch.yaml

# Extract values from sketch.yaml if present, else use defaults
BOARD_FQBN := $(shell [ -f $(SKETCH_YAML) ] && grep '^default_fqbn:' $(SKETCH_YAML) | cut -d' ' -f2 || echo $(DEFAULT_BOARD_FQBN))
PORT := $(shell [ -f $(SKETCH_YAML) ] && grep '^default_port:' $(SKETCH_YAML) | cut -d' ' -f2 || echo $(DEFAULT_PORT))

create:
	mkdir -p $(PROJECT)
	echo "default_fqbn: $(DEFAULT_BOARD_FQBN)" > $(PROJECT)/sketch.yaml
	echo "default_port: $(DEFAULT_PORT)" >> $(PROJECT)/sketch.yaml
	touch $(PROJECT)/$(PROJECT).ino
	@echo "Created new Arduino project '$(PROJECT)' with sketch.yaml and empty .ino"

compile:
	arduino-cli compile --fqbn $(BOARD_FQBN) $(PROJECT_PATH)

upload:
	arduino-cli upload -p $(PORT) --fqbn $(BOARD_FQBN) $(PROJECT_PATH)

all: compile upload
