#include<iostream>
using namespace std;

class String {
public:
	String() { s[0] = '\0'; }
	String(char ss[]) {
		int i = 0;
		while (ss[i] != '\0') {
			s[i] = ss[i];
			i++;
		}
		s[i] = '\0';
	}
	int length() {
		int len = 0;
		int i = 0;
		while (s[i++] != '\0')
			len++;
		return len;
	}
	int find(String goal) {
		int index = -1;
		int len = goal.length();
		for (int i = 0; s[i] != '\0'; i++) {
			int tmp = i;
			bool ok = true;
			for (int j = 0; j < len; j++) {
				if (s[tmp++] != goal.s[j]) {
					ok = false;
					break;
				}
			}
			if (ok) {
				index = i;
				break;
			}
		}
		return index;
	}
	void replace(int index, int len, String seg) {
		String temp = s;
		int i = index, j = 0;
		int segLen = seg.length();
		while (i < index + segLen)
			s[i++] = seg.s[j++];
		j = index + len;
		while(temp.s[j] != '\0')
			s[i++] = temp.s[j++];
		s[i] = '\0';
	}

	char s[100];
};

/*istream &operator>>(istream &cin, String &obj) {
	cin.getline(obj.s, 100);
	return cin;
}

ostream &operator<<(ostream &cout, String &obj) {
	cout << obj.s;
	return cout;
}*/