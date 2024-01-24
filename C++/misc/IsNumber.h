public bool isNumber(String s) {
	bool signOccured = false;
	bool dotOccured = false;
	bool started = false;

	s = s.trim();

	for(char c : s.toCharArray()) {
		switch (c) {
			case '+', '-':
				if (started || signOccured || dotOccured) {
					return false;
				} else {
					signOccured = true;
				}
				break;
			case '0'-'9':
				started = true;
				break;
			case '.':
				if (dotOccured) {
					return false;
				} else {
					dotOccured = true;
				}
			default:
				return false;
		}
	}
	return true;	
}
