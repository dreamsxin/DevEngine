#
# makefile
#

# Global settings

export C_COMPILER			  = clang
export C++_COMPILER			  = clang++
export TARGET_ARCHITECTURE	  = x64
export TARGET_CONFIGURATION	  = debug
export TARGET_PLATFORM		  = linux

export MAKE_DIRECTORY := $(CURDIR)/config/make


# Rules

all:
	$(MAKE) -C external/libpng; \
	$(MAKE) -C external/zlib; \
	$(MAKE) -C content; \
	$(MAKE) -C core; \
	$(MAKE) -C graphics; \
	$(MAKE) -C platform; \
	$(MAKE) -C samples/sample \

	# Temporary solution to have assets in correct location
	cp -arv samples/sample/assets/ build/$(TARGET_PLATFORM)/$(TARGET_ARCHITECTURE)/$(TARGET_CONFIGURATION)/

.PHONY: clean
clean:
	$(MAKE) -C external/libpng clean; \
	$(MAKE) -C external/zlib clean; \
	$(MAKE) -C content clean; \
	$(MAKE) -C core clean; \
	$(MAKE) -C graphics clean; \
	$(MAKE) -C platform clean; \
	$(MAKE) -C samples/sample clean \

	# Temporary solution, see above
	rm -fr build/$(TARGET_PLATFORM)/$(TARGET_ARCHITECTURE)/$(TARGET_CONFIGURATION)/assets/
