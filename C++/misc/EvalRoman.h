int romanNumber(String roman){
		int valueOfLastChar = 0, valueOfCurrentChar =0;
		int total = 0;
	
		for(int i= roman.length()-1; 0<=i; i--){ 
			switch(roman.charAt(i)){
				case 'I': valueOfCurrentChar = 1; break; 
				case 'V': valueOfCurrentChar = 5; break; 
				case 'X': valueOfCurrentChar = 10; break;
				case 'L': valueOfCurrentChar = 50; break;
				case 'C': valueOfCurrentChar = 100; break;
				case 'D': valueOfCurrentChar = 500; break;
				case 'M': valueOfCurrentChar = 1000; break;
			} 

			total += (valueOfCurrentChar < valueOfLastChar) ? -1*valueOfCurrentChar : valueOfCurrentChar;
			valueOfLastChar = valueOfCurrentChar;
		}

		return total;
}
