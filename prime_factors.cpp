int sieveArr[10000001];

void initSieve(int N) {
	memset(sieveArr, 0, sizeof(sieveArr));

	for (int i = 4; i <= N; i += 2) sieveArr[i] = 2;
	for (int i = 3; i*i <= N; i += 2) {
		if (sieveArr[i] == 0) {
			for (int j = 2*i; j <= N; j += i) {
				if (!sieveArr[j]) sieveArr[j] = i;
			}
		}
	}
}

vector <int> getFactors(int n) {
	vector <int> ret;
	while (sieveArr[n] != 0) {
		ret.push_back(sieveArr[n]);
		n /= sieveArr[n];
	}
	if (n != 1) {
		ret.push_back(n);
	}
	return ret;
}

