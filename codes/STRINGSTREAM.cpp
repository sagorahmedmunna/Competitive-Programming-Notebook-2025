string s;
getline(cin, s);
stringstream custom_in(s);
string word;
int count_word = 0;
while (custom_in >> word) {
	count_word++;
}