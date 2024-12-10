restrict typedef int foo;

foo bar(foo left, foo right);

foo bar(int left, foo right) { // argument mismatch should fail
	return (foo)((int)left + (int)right);
}

int main (int, char*const*) {
	if (5 == (int)bar((foo)2, (foo)3)) {
		return 0;
	}
	return 1;
}
