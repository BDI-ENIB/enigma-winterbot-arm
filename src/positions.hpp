#ifndef POSITIONS_H
#define POSITIONS_H 1

namespace positions {

namespace angle { // servo angles 
	const int HORIZONTAL  = 0;
	const int VERTICAL    = 0;
	const int ANGLED_BACK = 0;
	const int STORAGE     = 0;
}

namespace rotation { // arm rotation
	const int FRONT = 0;
	const int RIGHT = 0;
	const int LEFT  = 0;
	const int STORE_1 = 0;
	const int STORE_2 = 0;
}

namespace height {
	const int BOTTOM = 0;
	const int TOP = 0;

	const int PALET_BACK = 0;
	const int PALET_FRONT = 0;
	const int RAMPE = 0;
	const int BALANCE = 0;
	const int GOLDENIUM = 0;

	const int STORE_0 = 0; // height of store places
	const int STORE_1 = 0;
	const int STORE_2 = 0;
	const int STORE_3 = 0;
}

} // namespace positions

#endif
