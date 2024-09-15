CXX=g++
BIN_NAME=client-example
OUT_DIR=./build

client-example: setup
	$(CXX) -o $(OUT_DIR)/$(BIN_NAME) -g src/*.cpp

setup:
	if [ ! -d $(OUT_DIR) ]; then mkdir $(OUT_DIR); fi

clean:
	if [ -d $(OUT_DIR) ]; then rm -rf $(OUT_DIR); fi