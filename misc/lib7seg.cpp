//#include "lib7seg.h"

uint8_t translate(uint8_t value) {
    switch(value) {
		case 1:
			return 0x48;
			break;
		case 2:
			return 0x3d;
			break;
		case 3:
			return 0x6d;
			break;
		case 4:
			return 0x4b;
			break;
		case 5:
			return 0x67;
			break;
		case 6:
			return 0x77;
			break;
		case 7:
			return 0x4c;
			break;
		case 8:
			return 0x7f;
			break;
		case 9:
			return 0x6f;
			break;
		default:
			return 0x7e;
			break;
	}
}
