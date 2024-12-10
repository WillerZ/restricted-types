restrict typedef int foo;

foo bar(foo left, foo right);

foo bar(foo left, foo right) {
	return (foo)((int)left + (int)right);
}

int main (int, char*const*) {
	if (5 == (int)bar((foo)2, (foo)3)) {
		return 0;
	}
	return 1;
}
