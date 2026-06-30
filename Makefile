# ── 编译器和编译参数 ──────────────────────────────────────────────
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -lm

# .PHONY 告诉 make：这些目标不是真实文件名，每次都要重新执行
.PHONY: all test clean setup

all: calculator

calculator: calculator.c
	$(CC) $(CFLAGS) calculator.c -o calculator

# make test：编译测试二进制并立即运行
# -DUNIT_TEST 屏蔽 calculator.c 的 main()，避免和 test_calculator.c 的 main() 冲突
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
