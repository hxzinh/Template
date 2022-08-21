#define MAX 1000100
char s[MAX];
int n;

scanf(“%s”, s + 1); // đọc xâu các kí tự được đánh số từ 1
n = strlen(s + 1);

const int BASE = 256;
const int MODULO = 998244353;

int pw[MAX]; // pw[i] = BASE^i
int h[MAX];

// chuẩn bị mảng Hash
pw[0] = 1;
for (int i = 1; i < MAX; i++) pw[i] = 1LL * pw[i - 1] * BASE % MOD;
for (int i = 1; i <= n; i++) h[i] = (h[i - 1] + 1LL * s[i] * pw[i]) % MOD;

// lấy mã hash đoạn [l..r]

int getHash(int l, int r) {
	return 1LL * (h[r] - h[l - 1] + MOD) * pw[MAX - r] % MOD;
}

// trả về true khi và chỉ khi các đoạn con liên tiếp độ dài l xuất phát ở u và v bằng nhau

bool equal(int u, int v, int l) {
	return getHash(u, u + l - 1) == getHash(v, v + l - 1);
}
