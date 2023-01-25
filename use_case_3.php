<?php

/*
Given an array of strings, the system checks if at least one 
element has length greater than 7. If the condition is respected, 
a Boolean variable is set to true. At the end of the for loop, 
if the variable is true the string “There is at least one string 
with length > 7” is printed thought the standard output.

*/

$arr = ["ciro","ciruzzo","pippo","paperino"];
$b = false;
foreach($arr as $el) {
	
	if(strlen($el)>7) {
		$b = true;
	}
}

if($b) {

	echo "There is at least one string with length > 7";
	
}



?>
