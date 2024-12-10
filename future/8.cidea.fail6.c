restrict typedef int foo;

foo bar(foo left, foo right);

foo bar(foo left, foo right) {
	return (foo)((int)left + (int)right);
}

int main (int, char*const*) {
	if (5 == (int)bar(2, 3)) { // Fail need explicit int to foo cast for arguments
		return 0;
	}
	return 1;
}
