restrict typedef int foo;

foo bar(foo left, foo right);

foo bar(foo left, foo right) {
	return (foo)((int)left + (int)right);
}

int main (int, char*const*) {
	if (5 == bar((foo)2, (foo)3)) { // Fail needs cast to compare to int
		return 0;
	}
	return 1;
}
