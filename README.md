# Golden Master Testing for C

I'm developing this toolkit while refactoring one old project I'm working on for fun.
I hope you will find this project useful too.

# Usage

gmt-c is CMake based project, so if you also you CMake,
you can easily connect it to your project:

## CMake

	FIND_PACKAGE(cmake-version4git REQUIRED)

	TARGET_LINK_LIBRARIES(application PRIVATE gmt-c)


## Code

### Session #1:

	gmtBegin()
	gmtInput(a, sizeof(a));
	gmtInput(b, sizeof(b));
	gmtInput(c, sizeof(c));

	asm {
		xor eax, eax
		add eax, a
		add eax, b
		add eax, c
		mov x, eax
	};

	gmtOutput(&x, sizeof(x));
	gmtEnd();

### Session #2 after refactoring

	gmtBegin()
	gmtInput(a, sizeof(a));
	gmtInput(b, sizeof(b));
	gmtInput(c, sizeof(c));
	x = a + b + c;
	gmtOutput(&x, sizeof(x));
	gmtEnd();

## Verification

	compare

# TODO

- Implement **compare** tool.
