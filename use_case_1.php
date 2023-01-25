<?php

/*For each element of an array, check for the condition 'element mult 4 less than
 25'. If the condition is respected, print on the standard output the string 
 'Condition respected for element INDEX'. */
  

$arr = [4,55,12,20];
$cont = 0;

foreach ($arr as $el) {
	
	if($el*4<25) {
		print("Condition respected for element ".$cont);
	}
	
	$cont++;

}


?>
