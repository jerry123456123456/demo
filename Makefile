# ── 编译器和编译参数 ──────────────────────────────────────────────
CC      = gcc               # 使用 GCC 编译器
CFLAGS  = -Wall -Wextra -std=c11 -lm
# -Wall    : 开启所有常见警告（未使用变量、隐式类型转换等）
# -Wextra  : 在 -Wall 基础上再开启额外警告（更严格）
# -std=c11 : 按 C11 标准编译，支持 for 循环内声明变量等现代写法
# -lm      : 链接数学库（math.h 里的 pow/fabs 等需要）

# ── 伪目标声明 ────────────────────────────────────────────────────
# .PHONY 告诉 make：这些目标不是真实文件名，每次都要重新执行
# 否则如果目录里有个叫 "test" 的文件，make test 会认为已经是最新的而跳过
.PHONY: all test clean setup

# ── 默认目标：编译主程序 ──────────────────────────────────────────
# 直接执行 make 时运行的第一个目标
all: calculator

# calculator 依赖 calculator.c，源文件变化时自动重新编译
calculator: calculator.c
	$(CC) $(CFLAGS) calculator.c -o calculator
	# 展开后等价于：
	# gcc -Wall -Wextra -std=c11 -lm calculator.c -o calculator

# ── 测试目标 ─────────────────────────────────────────────────────
# make test：编译测试二进制并立即运行
test: calculator.c test_calculator.c
	$(CC) $(CFLAGS) -DUNIT_TEST calculator.c test_calculator.c -o test_calculator
	# -DUNIT_TEST：定义预处理宏，使 calculator.c 里的 #ifndef UNIT_TEST 跳过 main()
	# 避免 calculator.c 和 test_calculator.c 两个 main() 冲突
	./test_calculator
	# 运行测试；exit code 非 0 时 make 自动报错并停止

# ── 安装 Git Hook ──────────────────────────────────────────────────
# .git/hooks/ 不进版本控制，新克隆仓库后需手动执行一次 make setup
setup:
	cp .githooks/pre-commit .git/hooks/pre-commit
	chmod +x .git/hooks/pre-commit   # 赋予可执行权限，否则 git 不会触发它
	@echo "Git hooks installed."     # @ 前缀：只输出 echo 内容，不打印命令本身

# ── 清理编译产物 ──────────────────────────────────────────────────
clean:
	rm -f calculator test_calculator
	# -f：即使文件不存在也不报错
