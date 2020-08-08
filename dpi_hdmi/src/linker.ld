SECTIONS {
	.text.boot 0x80000: { KEEP(*(.text.boot)) }
	.text : { *(.text .text.*) }
	.rodata : { *(.rodata .rodata.*) }
	.data : { *(.data .data.*) }
	. = ALIGN(0x8);
	bss_begin = .;
	.bss : { *(.bss .bss.*) } 
	bss_end = .;
}
