/**************************************************************************
*           MAIN1
*  Pauses for 2 seconds then prints 'Hello World' to the debug stream
*  to display the debug stream:
*      -download the program to the cortex
*      -in the Robot menu select debugger
*      -go back to Robot; then go to the debugger window and select debug stream
*
***************************************************************************/

int hailstone(int n) { // define a function that takes an int (in this case '7')
	if (n % 2 == 0) { // if n is even:
			return (n/2); // return n/2
	}
	else {            // if n is odd:
			return ((3*n) + 1); // return (3*n) + 1
	}
}


task main() // main function
{
	int x=7;  // testing 7
	writeDebugStreamLine("%d", x);  // print initial number (7)
	while(x != 1) { // while n is not equal to 1
		x = hailstone(x); // set x to hailstone of the previous number
		writeDebugStreamLine("%d", x); // print x and loop.
	}
}
