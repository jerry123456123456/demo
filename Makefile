CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -lm

.PHONY: all test clean setup

all: calculator

calculator: calculator.c
	$(CC) $(CFLAGS) calculator.c -o calculator

test: calculator.c test_calculator.c
	$(CC) $(CFLAGS) -DUNIT_TEST calculator.c test_calculator.c -o test_calculator
	./test_calculator

# 安装 git hook（新克隆仓库后执行一次）
setup:
	cp .githooks/pre-commit .git/hooks/pre-commit
	chmod +x .git/hooks/pre-commit
	@echo "Git hooks installed."

clean:
	rm -f calculator test_calculator
