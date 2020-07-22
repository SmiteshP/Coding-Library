bool subset_sum_exists(vector <int> v, int sum) {
	bool dp[2][sum+1];
	memset(dp[0], false, (sum+1)*sizeof(bool));
	dp[0][0] = true;
	for (int i = 1; i <= v.size(); ++i) {
		memcpy(dp[i&1], dp[!(i&1)], (min(v[i-1], sum+1))*sizeof(bool));
		for (int j = v[i-1]; j < sum+1; ++j) {
			dp[i&1][j] = dp[!(i&1)][j] || dp[!(i&1)][j-v[i-1]];
		}
	}
	return dp[v.size()&1][sum];
}

