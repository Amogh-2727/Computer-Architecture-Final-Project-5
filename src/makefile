  CC = g++

  FLAGS  = -g -Wall

  TARGET = riscv_main
  DEBUG = 0
  R_PC = 0
  R_SP = 65535
  MEM_FILE = def.mem

  all: $(TARGET) exec

  $(TARGET): $(TARGET).cpp
	$(CC) $(FLAGS) -o $(TARGET) $(TARGET).cpp

  clean:
	$(RM) $(TARGET)

  exec:
	./$(TARGET) $(R_PC) $(R_SP) $(MEM_FILE) $(DEBUG)
