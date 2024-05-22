# Default values for the environment and COM port
ENVIRONMENT ?= menu2Test
UPLOAD_PORT ?= COM5

# PlatformIO command
PLATFORMIO_CMD = C:\Users\Jayden\.platformio\penv\Scripts\platformio.exe

# Run target
.PHONY: run
run:
	"$(PLATFORMIO_CMD)" run --target upload --environment $(ENVIRONMENT) --upload-port $(UPLOAD_PORT)

# Help target to display usage information
.PHONY: help
help:
	@echo "Usage:"
	@echo "  make run [ENVIRONMENT=<environment>] [UPLOAD_PORT=<port>]"
	@echo ""
	@echo "Default values:"
	@echo "  ENVIRONMENT=menu2Test"
	@echo "  UPLOAD_PORT=COM4"

# Default target
.DEFAULT_GOAL := help