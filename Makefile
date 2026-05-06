CXX ?= clang++
CC  ?= clang
AR  ?= ar
CMAKE ?= cmake
GIT ?= git

JOBS ?= 32
MAKEFLAGS += -j$(JOBS)

PROJECT_DIR := $(CURDIR)

BUILD_DIR := build
SRC_DIR := source
CLIENT_DIR := client
INCLUDE_DIR := include

LIBRARIES_DIR := $(PROJECT_DIR)/libraries

BX_SRC          := $(LIBRARIES_DIR)/bx
BIMG_SRC        := $(LIBRARIES_DIR)/bimg
BGFX_SRC        := $(LIBRARIES_DIR)/bgfx
BGFX_CMAKE_SRC  := $(LIBRARIES_DIR)/bgfx.cmake
GLFW_SRC        := $(LIBRARIES_DIR)/glfw

DEPS_BUILD_DIR   := $(LIBRARIES_DIR)/.build
DEPS_INSTALL_DIR := $(LIBRARIES_DIR)/.install

BGFX_BUILD_DIR   := $(DEPS_BUILD_DIR)/bgfx
GLFW_BUILD_DIR   := $(DEPS_BUILD_DIR)/glfw

BGFX_STAMP := $(BGFX_BUILD_DIR)/.built

BGFX_LIB       := $(DEPS_INSTALL_DIR)/lib/libbgfx.a
BIMG_LIB       := $(DEPS_INSTALL_DIR)/lib/libbimg.a
BX_LIB         := $(DEPS_INSTALL_DIR)/lib/libbx.a
GLFW_LIB       := $(DEPS_INSTALL_DIR)/lib/libglfw3.a
SHADERC_BIN    := $(DEPS_INSTALL_DIR)/bin/shaderc

EXTERNAL_LIBS := $(BGFX_LIB) $(BIMG_LIB) $(BX_LIB) $(GLFW_LIB)

CMAKE_BUILD_TYPE ?= Release
ASAN ?= 1

CXXFLAGS ?= -std=c++23 -Wall -Wextra -O2 -DBX_CONFIG_DEBUG=0
CPPFLAGS ?= -I$(INCLUDE_DIR) \
            -I$(DEPS_INSTALL_DIR)/include \
            -I$(BGFX_SRC)/include \
            -I$(BX_SRC)/include \
            -I$(BIMG_SRC)/include \
            -I$(GLFW_SRC)/include \
            -MMD -MP

LDFLAGS += -L$(DEPS_INSTALL_DIR)/lib
LDLIBS  += -lbgfx -lbimg -lbx -lglfw3

ifeq ($(ASAN),1)
SANITIZER_FLAGS := -fsanitize=address -fno-omit-frame-pointer -g
CXXFLAGS += $(SANITIZER_FLAGS)
LDFLAGS  += $(SANITIZER_FLAGS)
endif

MARINER_SOURCES := $(shell find $(SRC_DIR) -type f -name '*.cpp')
CLIENT_SOURCES  := $(shell find $(CLIENT_DIR) -type f -name '*.cpp')

MARINER_OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(MARINER_SOURCES))
CLIENT_OBJS  := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(CLIENT_SOURCES))

LIB    := $(BUILD_DIR)/Mariner.a
CLIENT := $(BUILD_DIR)/.MarinerClient.tmp

# ---- app bundle --------------------------------------------------------

APP_NAME    := MarinerClient
APP_BUNDLE  := $(BUILD_DIR)/$(APP_NAME).app
APP_MACOS   := $(APP_BUNDLE)/Contents/MacOS
APP_RES     := $(APP_BUNDLE)/Contents/Resources

FRAMEWORKS := \
  -framework Cocoa \
  -framework IOKit \
  -framework CoreFoundation \
  -framework CoreGraphics \
  -framework Metal \
  -framework AppKit \
  -framework QuartzCore \
  -framework CoreVideo \
  -framework OpenGL

TOTAL_OBJS  := $(MARINER_OBJS) $(CLIENT_OBJS)
OBJS_COUNT  := $(words $(TOTAL_OBJS))
CURRENT     := 0

# ---- color -------------------------------------------------------------

BLUE  := \033[1;34m
GREEN := \033[1;32m
CYAN  := \033[1;36m
RESET := \033[0m

# -----------------------------------------------------------------------

all: deps $(APP_BUNDLE)

# ---- fetch deps --------------------------------------------------------

$(BX_SRC):
	@printf "$(CYAN)--$(RESET) Cloning bx\n"
	@$(GIT) clone https://github.com/bkaradzic/bx.git $@ --quiet

$(BIMG_SRC):
	@printf "$(CYAN)--$(RESET) Cloning bimg\n"
	@$(GIT) clone https://github.com/bkaradzic/bimg.git $@ --quiet

$(BGFX_SRC):
	@printf "$(CYAN)--$(RESET) Cloning bgfx\n"
	@$(GIT) clone https://github.com/bkaradzic/bgfx.git $@ --quiet

$(BGFX_CMAKE_SRC):
	@printf "$(CYAN)--$(RESET) Cloning bgfx.cmake\n"
	@$(GIT) clone https://github.com/bkaradzic/bgfx.cmake.git $@ --quiet

$(GLFW_SRC):
	@printf "$(CYAN)--$(RESET) Cloning glfw\n"
	@$(GIT) clone https://github.com/glfw/glfw.git $@ --quiet

fetch-deps: $(BX_SRC) $(BIMG_SRC) $(BGFX_SRC) $(BGFX_CMAKE_SRC) $(GLFW_SRC)

# ---- deps --------------------------------------------------------------

deps: fetch-deps $(BGFX_STAMP) $(GLFW_LIB)

# ---- bgfx (single-shot, no races) --------------------------------------

$(BGFX_STAMP): fetch-deps
	@printf "$(BLUE)--$(RESET) Configuring bgfx\n"

	@if [ -f "$(BGFX_BUILD_DIR)/CMakeCache.txt" ]; then \
		if ! grep -q "$(BGFX_CMAKE_SRC)" "$(BGFX_BUILD_DIR)/CMakeCache.txt"; then \
			printf "$(BLUE)--$(RESET) CMake source mismatch. Nuking stale bgfx build dir\n"; \
			rm -rf "$(BGFX_BUILD_DIR)"; \
		fi \
	fi

	@mkdir -p $(BGFX_BUILD_DIR) $(DEPS_INSTALL_DIR)

	@$(CMAKE) -S "$(BGFX_CMAKE_SRC)" -B "$(BGFX_BUILD_DIR)" \
		-DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) \
		-DCMAKE_INSTALL_PREFIX=$(DEPS_INSTALL_DIR) \
		-DBGFX_BUILD_TOOLS=ON \
		-DBGFX_BUILD_EXAMPLES=OFF \
		-DBGFX_BUILD_TESTS=OFF \
		-DBGFX_CUSTOM_TARGETS=OFF \
		-DBGFX_AMALGAMATED=OFF \
		-DBGFX_DIR=$(BGFX_SRC) \
		-DBX_DIR=$(BX_SRC) \
		-DBIMG_DIR=$(BIMG_SRC) \
		> /dev/null 2>&1

	@printf "$(BLUE)--$(RESET) Building bgfx\n"
	@$(CMAKE) --build "$(BGFX_BUILD_DIR)" --target install --parallel $(JOBS) 2>&1 \
		| grep -E "^\[[ 0-9]+%\]" \
		| sed 's/^\(\[[ 0-9]*%\]\)/\x1b[1;32m\1\x1b[0m/'

	@touch $(BGFX_STAMP)

$(BGFX_LIB): $(BGFX_STAMP)
$(BIMG_LIB): $(BGFX_STAMP)
$(BX_LIB):   $(BGFX_STAMP)
$(SHADERC_BIN): $(BGFX_STAMP)

# ---- GLFW --------------------------------------------------------------

$(GLFW_LIB): fetch-deps
	@mkdir -p $(GLFW_BUILD_DIR) $(DEPS_INSTALL_DIR)

	@[ -f "$(GLFW_LIB)" ] && exit 0; \
	printf "$(BLUE)--$(RESET) Configuring GLFW\n"; \
	$(CMAKE) -S "$(GLFW_SRC)" -B "$(GLFW_BUILD_DIR)" \
		-DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) \
		-DCMAKE_INSTALL_PREFIX=$(DEPS_INSTALL_DIR) \
		-DBUILD_SHARED_LIBS=OFF \
		-DGLFW_BUILD_EXAMPLES=OFF \
		-DGLFW_BUILD_TESTS=OFF \
		-DGLFW_BUILD_DOCS=OFF \
		> /dev/null 2>&1; \
	printf "$(BLUE)--$(RESET) Building GLFW\n"; \
	$(CMAKE) --build "$(GLFW_BUILD_DIR)" --target install --parallel $(JOBS) 2>&1 \
		| grep -E "^\[[ 0-9]+%\]" \
		| sed 's/^\(\[[ 0-9]*%\]\)/\x1b[1;32m\1\x1b[0m/'

# ---- project -----------------------------------------------------------

$(MARINER_OBJS) $(CLIENT_OBJS): | $(BGFX_STAMP) $(GLFW_LIB)

$(LIB): $(MARINER_OBJS)
	@mkdir -p $(@D)
	@$(AR) rcs $@ $^

$(CLIENT): $(CLIENT_OBJS) $(LIB) $(EXTERNAL_LIBS)
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) $(CLIENT_OBJS) $(LIB) \
		$(LDFLAGS) \
		$(FRAMEWORKS) \
		$(LDLIBS) \
		-o $@

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@$(eval CURRENT := $(shell echo $$(($(CURRENT)+1))))
	@PERCENT=$$(($(CURRENT)*100/$(OBJS_COUNT))); \
	printf "$(GREEN)[%3d%%]$(RESET) %s\n" $$PERCENT $<; \
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ -MF $(@:.o=.d)

-include $(MARINER_OBJS:.o=.d)
-include $(CLIENT_OBJS:.o=.d)

# ---- app bundle --------------------------------------------------------

$(APP_BUNDLE): $(CLIENT) $(SHADERC_BIN)
	@printf "$(BLUE)--$(RESET) Building app bundle: $(APP_BUNDLE)\n"

	@rm -rf "$(APP_BUNDLE)"
	@mkdir -p "$(APP_MACOS)" "$(APP_RES)"

	@printf '<?xml version="1.0" encoding="UTF-8"?>\n\
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">\n\
<plist version="1.0">\n\
<dict>\n\
	<key>CFBundleExecutable</key>\n\
	<string>$(APP_NAME)</string>\n\
	<key>CFBundleIdentifier</key>\n\
	<string>com.mariner.client</string>\n\
	<key>CFBundleName</key>\n\
	<string>$(APP_NAME)</string>\n\
	<key>CFBundlePackageType</key>\n\
	<string>APPL</string>\n\
	<key>CFBundleShortVersionString</key>\n\
	<string>1.0</string>\n\
	<key>CFBundleVersion</key>\n\
	<string>1</string>\n\
	<key>NSHighResolutionCapable</key>\n\
	<true/>\n\
	<key>NSPrincipalClass</key>\n\
	<string>NSApplication</string>\n\
</dict>\n\
</plist>\n' > "$(APP_BUNDLE)/Contents/Info.plist"

	@cp "$(CLIENT)" "$(APP_MACOS)/$(APP_NAME)"

	@if [ -d "$(PROJECT_DIR)/content" ]; then \
		cp -R "$(PROJECT_DIR)/content" "$(APP_RES)/content"; \
	else \
		printf "$(BLUE)--$(RESET) Warning: $(PROJECT_DIR)/content not found, skipping\n"; \
	fi

	@mkdir -p "$(APP_RES)/content/bin"
	@cp "$(SHADERC_BIN)" "$(APP_RES)/content/bin/shaderc"

	@if [ -d "$(LIBRARIES_DIR)" ]; then \
		cp -R "$(LIBRARIES_DIR)" "$(APP_RES)/libraries"; \
	else \
		printf "$(BLUE)--$(RESET) Warning: $(LIBRARIES_DIR) not found, skipping\n"; \
	fi

	@printf "$(GREEN)--$(RESET) Bundle ready: $(APP_BUNDLE)\n"

# ---- clean -------------------------------------------------------------

clean:
	rm -rf $(BUILD_DIR)

clean-deps:
	rm -rf $(DEPS_BUILD_DIR) $(DEPS_INSTALL_DIR)

.PHONY: all deps clean clean-deps fetch-deps