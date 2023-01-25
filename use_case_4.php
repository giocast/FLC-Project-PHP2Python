<?php

/*Given an integer variable, if its value is greater than 4 
and less than 15, a switch condition is applied. 
The possible cases are 5, 6, 7, 8, 9, 10, 11, 12, 
default case (13,14). 
In each case, the system prints into the standard output 
the month related to that number. In the default case 
the system prints the string “Not a month”.*/

$v = 6;

if($v>4 && $v<15) {


	switch($v){
	
		case 5:
			echo "May";
			break;
		case 6:
			echo "June";
			break;
		case 7:
			echo "July";
			break;
		case 8:
			echo "August";
			break;
		case 9:
			echo "September";
			break;
		case 10:
			echo "October";
			break;
		case 11:
			echo "November";
			break;
		case 12:
			echo "December";
			break;
		default:
			echo "Non a month";	
}

}





?>
