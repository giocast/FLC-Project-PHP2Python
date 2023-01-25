<html>
<head>
	<title>A test MF</title>
</head>

<body>

<?php

$i=0;
$j = 2;
	switch($i) {
		case 0:
			echo "i equals 0";
			break;
		case 1:
			echo "i equals 1";
			break;
		case 2:
			echo "i equals 2";
			break;
		default:
			print("VVVVVV");
}


$i = 1;
while ($i <= 10) {
    $i++;  // the printed value would be$i before the increment(post-increment) 
}


function writeMsg($a,$q,$a) {
  echo "Hello world!";
  $s = 3+2;
  $r = "Hello world!";
}

//writeMsg($j,$h);  corretto undefined var
writeMsg($j,$i,0);


$arr = array(1, 2, 3, 4);
foreach ($arr as $value) {
    $value = $value * 2;
}

foreach (array(3,4,32,1,3) as $elem) {
    print($elem);
}

?>

</body>
</html>
