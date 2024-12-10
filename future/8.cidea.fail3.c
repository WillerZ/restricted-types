restrict typedef int foo;

foo bar(foo left, foo right);

foo bar(foo left, foo right) {
	return (int)left + (int)right; // Conversion of result requires an explicit cast
}

int main (int, char*const*) {
	if (5 == (int)bar((foo)2, (foo)3)) {
		return 0;
	}
	return 1;
}
