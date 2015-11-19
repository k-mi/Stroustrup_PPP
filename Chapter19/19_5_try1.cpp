void suspicious(vector<int>& v, int s){
	try{
		int* p = new int[s];
		vector<int> v1;
		// ...	
	}
	catch(bad_alloc){
		throw;
		return;
	}
	catch(...){
		delete[] p;
		throw;
		return;
	}
	
	try{
		int* q = new int[s];	
		vector<double> v2;
		// ...
	}
	catch(bad_alloc){
		throw;
		return;
	}
	catch(...){
		delete[] q;
		throw;
		return;
	}
	
	delete[] p;
	delete[] q;
}