# ── 编译器和编译参数 ──────────────────────────────────────────────
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11
LIBS    = -lm

.PHONY: all test clean setup

all: calculator

calculator: calculator.c
	$(CC) $(CFLAGS) calculator.c -o calculator $(LIBS)

# -lm 放在最后，兼容 Linux ld 链接器（macOS 无所谓，Linux 必须放源文件后）
test: calculator.c test_calculator.c
	$(CC) $(CFLAGS) -DUNIT_TEST calculator.c test_calculator.c -o test_calculator $(LIBS)
	./test_calculator

setup:
	cp .githooks/pre-commit .git/hooks/pre-commit
	chmod +x .git/hooks/pre-commit
	@echo "Git hooks installed."

clean:
	rm -f calculator test_calculator
