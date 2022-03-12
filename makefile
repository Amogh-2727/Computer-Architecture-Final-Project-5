# the compiler: gcc for C program, define as g++ for C++
  CC = g++

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
  CFLAGS  = -g -Wall

  # the build target executable:
  TARGET = riscv_main
  DEBUG = 0
  R_PC = 0
  R_SP = 65535
  MEM_FILE = prog2.mem

  all: $(TARGET) exec

  $(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

  clean:
	$(RM) $(TARGET)

  exec:
	./$(TARGET) $(R_PC) $(R_SP) $(MEM_FILE) $(DEBUG)

