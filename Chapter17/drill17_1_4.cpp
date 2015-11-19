void print_array10(ostream& os, int* a){
	const int size = 10;

	for(int i = 0; i < size; ++i)
		os << a[i] << ' ';
	os << endl;
}