#pragma once
#include"stdafx.h"
char dohvatiBrojRegistra(string reg, string ins) {
	if (reg == "r0")
		return 0x00;
	else if (reg == "r1")
		return 0x01;
	else if (reg == "r2")
		return 0x02;
	else if (reg == "r3")
		return 0x03;
	else if (reg == "r4")
		return 0x04;
	else if (reg == "r5")
		return 0x05;
	else if (reg == "r6")
		return 0x06;
	else if (reg == "r7")
		return 0x07;
	else if (reg == "r8")
		return 0x08;
	else if (reg == "r9")
		return 0x09;
	else if (reg == "r10")
		return 0x0a;
	else if (reg == "r11")
		return 0x0b;
	else if (reg == "r12")
		return 0x0c;
	else if (reg == "r13")
		return 0x0d;
	else if (reg == "r14")
		return 0x0e;
	else if (reg == "r15")
		return 0x0f;
	else if (reg == "PC" && (ins == "add" || ins == "sub" || ins == "ldr" || ins == "str" || ins == "call" || ins == "mov" || ins == "shr" || ins == "shl") )
		return 0x10;
	else if (reg == "LR" && (ins == "add" || ins == "sub" || ins == "ldr" || ins == "str" || ins == "call" || ins == "mov" || ins == "shr" || ins == "shl"))
		return 0x11;
	else if (reg == "SP" && (ins == "add" || ins  == "sub" || ins == "ldr" || ins == "str" || ins == "call" || ins == "mov" || ins == "shr" || ins == "shl"))
		return 0x12;
	else if (reg == "PSW" && (ins == "ldr" || ins == "str" || ins == "call" || ins == "mov" || ins == "shr" || ins == "shl"))
		return 0x13;
	else return 'e';
}