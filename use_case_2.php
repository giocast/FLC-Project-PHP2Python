<?php

/*Ask user to insert a number into the standard input until the number is even 
(while with if equal condition). The user is asked to insert 
EVENNUMBER elements thought the standard input that will be pushed into an array. 
The elements of the array are sorted.
*/


$el = readline("Please insert a even number");

while($el%2!=0) {
	$el = readline("Please insert a even number: \n");
}

$i = 0;

$arr = [];

while($i<$el) {
	$inser = readline("Please insert an element: \n");
	array_push($arr, $inser);
	
	$i++;
}

sort($arr);

?>
