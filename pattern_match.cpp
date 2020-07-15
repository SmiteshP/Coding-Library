template <typename T>
void LPS(T& pattern, int size, int* ret) {
	ret[0] = 0;
	int j = 0, i = 1;
	while (i < size) {
		if (pattern[i] == pattern[j])
			ret[i] = ++j, ++i;
		else if (j != 0)
			j = ret[j-1];
		else
			ret[i++] = 0;
	}
}

template <typename T>
std::vector <int> KMP(T& text, T& pattern) {
	int text_size = text.size(), pattern_size = pattern.size();
	int lps[pattern_size];
	LPS <T> (pattern, pattern_size, lps);
	std::vector <int> occurences;
	int i = 0, j = 0;
	while (i < text_size) {
		if (text[i] == pattern[j]) ++i, ++j;
		if (j == pattern_size) occurences.emplace_back(i-j), j = lps[j-1];
		else if (i < text_size && pattern[j] != text[i])
			if (j != 0) j = lps[j - 1];
			else ++i;
	}
	return occurences;
}

template <typename T>
vector <int> naive(T& text, T& pattern) {
	vector <int> ans;
	for (int i = 0; i < text.size(); ++i) {
		if (text[i] == pattern[0]) {
			int j = 0;
			for (j; j < pattern.size() && text[i+j] == pattern[j]; ++j);
			if (j == pattern.size()) {
				ans.emplace_back(i);
			}
		}
	}
	return ans;
}

