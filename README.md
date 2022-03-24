# Golden Master Testing for C

I developed this toolkit while refactoring one old project that I've worked on just for fun.

## Session #1:

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

## Session #2 after refactoring

	gmtBegin()
	gmtInput(a, sizeof(a));
	gmtInput(b, sizeof(b));
	gmtInput(c, sizeof(c));
	x = a + b + c;
	gmtOutput(&x, sizeof(x));
	gmtEnd();

## Verification

	compare
